#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<iostream>
#include <sys/time.h>
#include"cpuinfo.h"
#include <netinet/tcp.h>
#include<pthread.h>
#include <errno.h>

#define SERVER_SEND 1
#define CLIENT_SEND 2
#define DELAY_SERVER_FIRST 3
#define DELAY_CLIENT_FIRST 4


#define N_BUFS 10

struct _CONFIG {
	int port ;
	std::string ip ;
	long int startPackageSize ;
	long int endPackageSize ;
	long int stepPackageSize ;
	long int curPackageSize ;
	int timeSpan ;
	int mode ;
	int travelTimes ;
	bool isServer ;
	bool tcp ;
	bool udpsend ;
} config ;

bool g_ctrlSend ;

inline uint64_t currentTime()
{
	struct timeval t ;
	gettimeofday(&t, NULL);
	return (uint64_t)t.tv_usec + (uint64_t)t.tv_sec*1000000ULL;
}


int SetSocketOptions(int fd)
{
  int sockopt = 0;
  int SOCKET_ERROR = -1;
  static const int c_so_rcvbuf = 256 * 1024; // limit set by Linux!
  static const int c_so_sndbuf = 256 * 1024; // limit set by Linux!


  // setsockopt SO_REUSEADDR - enable/disable local address reuse
  sockopt = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&sockopt, sizeof(sockopt)) == SOCKET_ERROR)
  {
    perror("SetSocketOptions  error from setsockopt1");
    return -1;
  }

  // setsockopt SO_SNDBUF - set buffer size for output
  sockopt = c_so_sndbuf;
  if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char*)&sockopt, sizeof(sockopt)) == SOCKET_ERROR)
  {
    perror("SetSocketOptions  error from setsockopt2");
    return -1;
  }
 
  // setsockopt SO_RCVBUF - set buffer size for input
  sockopt = c_so_rcvbuf;
  if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (char*)&sockopt, sizeof(sockopt)) == SOCKET_ERROR)
  {
    perror("SetSocketOptions  error from setsockopt3");
    return -1;
  }

  // setsockopt TCP_NODELAY - to defeat the packetization algorithm
  sockopt = 0; // 0 to enable Nagle algorithm
  if (setsockopt(fd, getprotobyname("tcp")->p_proto, TCP_NODELAY, (char *)&sockopt, sizeof(sockopt)) == SOCKET_ERROR)
  {
    perror("SetSocketOptions  error from setsockopt4");
    return -1;
  }
  return 0;
}




typedef void *(*THREAD_FUN)(void *) ;
pthread_t createThread (THREAD_FUN fun, void *arg) 
{
	pthread_t tid;

	/*  pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	 */
	if(pthread_create(&tid,NULL,fun,arg))
	{
		return 0;
	}
	return tid ;
}

void *threadReceive (void *arg) 
{
	//char buf[1024*1024] = {0};
	//char *buf = new char[1024*1024*1024];
	char *buf[N_BUFS]; //= new char[1024*1024*1024];
	int curr = 0;
	for(int i=0; i<N_BUFS; i++) {
		buf[i] = new char[1024*1024*1024];
	}

	char counter = 0 ;
	int skt = *((int *)arg) ;
	unsigned long sizeRecv =0, sizeLeft = 0;
	int ret ;
	
	timeval t1, t2 ;
	CpuInfo cif ;

    recv (skt, (void *)buf, 1, 0) ;
	//read (skt, (void *)buf[curr], 1) ;
	gettimeofday(&t1,NULL) ;
	cif.Start () ;
	while(1)
	{
		sizeLeft=config.curPackageSize;
		while (sizeLeft > 0)
		{
	//		ret = recv (skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			
			ret = read (skt, (void*)(buf[curr]+config.curPackageSize-sizeLeft), sizeLeft) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: recv data error. " << std::endl ;
				exit (1) ;
			}
			sizeRecv += ret ;
			sizeLeft -= ret ;
		}
		if (buf[curr][0] == 'e')
		{
			break ;
		}
		/*for (int i=2; i<config.curPackageSize; i++) {
			if (buf[i] != (char)i) {
				//std::cout << "ERROR: package check error!" << std::endl ;
				//return NULL ;
			}
		}*/
		/*if (buf[1] != counter && counter%100==0) {
			//std::cout << "ERROR: package lost!" << std::endl ;
			//return NULL ;
		}*/
		counter ++ ;
	}
	cif.End () ;
	gettimeofday(&t2, NULL) ;

	double timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
	float cpu = 0 ;
	for (int i=0; i<cif.GetN(); i++)
	{
		cpu += cif.GetUsed (i) ;
	}
	cpu /= cif.GetN () ;
	printf ("Recv --> Package:%d CPU:%f Time:%f Bytes:%ld Speed:%.2fMB/s\n", config.curPackageSize, cpu, timeSpan, sizeRecv, (sizeRecv/timeSpan)/(1024*1024)) ;
	return NULL ;
}

void *threadSend (void *arg)
{
	g_ctrlSend = true ;
	//char buf[1024*1024] = {0};
	char *buf = new char[1024*1024*1024];
	int skt = *((int *)arg) ;
	unsigned long sizeSent =0, sizeLeft = 0;
	int ret ;

	timeval t1, t2 ;
	CpuInfo cif ;

	// start 
	buf[0] = 's' ;
	send (skt, (void*)buf, 1, 0) ;
	// write (skt, buf, 1) ;
	for (int i=2; i<1024*1024; i++) {
		buf[i] = i ;
	}

	gettimeofday(&t1,NULL) ;
	cif.Start () ;
	while (1)
	{
		// send one package 
		sizeLeft=config.curPackageSize;
		while (sizeLeft > 0)
		{
//			ret = send(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
		ret = write(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: send data error. " << std::endl ;
				exit (1) ;
			}
			sizeSent += ret ;
			sizeLeft -= ret ;
		}
		buf[1] ++ ;
		//////
		if (buf[0] == 'e')
		{
			break ;
		}
		if (g_ctrlSend == false)
		{
			buf[0] = 'e' ;
		}
	}
	cif.End () ;
	gettimeofday(&t2, NULL) ;

        double timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
	float cpu = 0 ;
	for (int i=0; i<cif.GetN(); i++)
	{
		cpu += cif.GetUsed (i) ;
	}
	cpu /= cif.GetN () ;
	printf ("Send --> Package:%d CPU:%f Time:%f Bytes:%ld Speed:%.2fMB/s\n", config.curPackageSize, cpu, timeSpan, sizeSent, (sizeSent/timeSpan)/(1024*1024)) ;
	return NULL ;
}

ssize_t sendData(int skt, char *data, int len)
{
	sleep(1) ;
	uint64_t t1 = currentTime();
	struct iovec vec[1];
	vec[0].iov_base = (void *)data;
	vec[0].iov_len  = len;

	struct msghdr hdr = { 0, 0, vec, 1, 0, 0, 0 };
	ssize_t ret = sendmsg(skt, &hdr, MSG_NOSIGNAL);
	uint64_t t2 = currentTime();
	/*for(int i=0; i<len; i++) {
		data[i] = i ;
	}*/

	std::cout << "DT send: " << t2-t1 << std::endl ;

	return ret;
}

ssize_t recvData(int skt, char *data, int len)
{
	uint64_t t1 = currentTime();
	struct iovec vec[1];
	struct msghdr hdr = { 0, 0, vec, 1, 0, 0, 0 };
	vec[0].iov_base = data;
	vec[0].iov_len  = len;

	int res = ::recvmsg(skt, &hdr, 0);
	uint64_t t2 = currentTime();
	std::cout << "DT recv: " << t2-t1 << std::endl ;
	return (ssize_t )res;
}


void travelDelaySend (int skt) 
{
	//char buf[1024*1024] = {0} ;
	char *buf[N_BUFS]; //= new char[1024*1024*1024];
	int curr = 0;
	for(int i=0; i<N_BUFS; i++) {
		buf[i] = new char[1024*1024*1024];
	}

	int sizeLeft ;
	int ret ;
	timeval t1, t2 ;

	gettimeofday(&t1,NULL) ;
	for (int i=0; i<config.travelTimes; i++)
	{
		if (i == config.travelTimes - 1)
			buf[curr][0] = 'e' ;
		// send a package 
		sizeLeft=config.curPackageSize;
		while (sizeLeft > 0)
		{
			//ret = send(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			ret = sendData(skt, (char*)(buf[curr]+config.curPackageSize-sizeLeft), sizeLeft);
			if (ret == -1)
			{
				std::cerr << "ERROR: send data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}
		
		// receive client reply
		sizeLeft=config.curPackageSize;
		while (sizeLeft > 0)
		{
			//ret = recv (skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			ret = recvData(skt, (char*)(buf[curr]+config.curPackageSize-sizeLeft), sizeLeft) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: recv data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}

		curr = (curr+1) % N_BUFS ;
	}
	gettimeofday(&t2,NULL) ;
	
	double timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
	printf ("travel --> Package:%d TimeSpan:%f Tims:%d SingleTravelTime:%f\n", config.curPackageSize, timeSpan, config.travelTimes, timeSpan/config.travelTimes*1000) ;
}

void travelDelayReceive (int skt) 
{
	//char buf[1024*1024] = {0} ;
	//char *buf = new char[1024*1024*1024];
	char *buf[N_BUFS]; //= new char[1024*1024*1024];
	int curr = 0;
	for(int i=0; i<N_BUFS; i++) {
		buf[i] = new char[1024*1024*1024];
	}

	int sizeLeft ;
	int ret ;

	while (1) 
	{
		// receive a package
		sizeLeft=config.curPackageSize;
		while (sizeLeft > 0)
		{
			ret = recvData(skt, (char*)(buf[curr]+config.curPackageSize-sizeLeft), sizeLeft) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: recv data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}

		// send a reply
		sizeLeft=config.curPackageSize;
		while (sizeLeft > 0)
		{
			//ret = send(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			ret = sendData(skt, (char*)(buf[curr]+config.curPackageSize-sizeLeft), sizeLeft) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: send data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}

		if (buf[curr][0] == 'e') 
			break ;

		curr = (curr+1)%N_BUFS;
	}
}

void server ()
{
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	int sock_descriptor;
	int temp_sock_descriptor;
	//struct cfg a;
	struct protoent *proto;
	if(!(proto = getprotobyname("tcp"))){
		printf("unknown protocol!\n");
		exit (1) ;
	}

	sock_descriptor=socket(AF_INET,SOCK_STREAM,0);
	int opt = 1 ;
	int val ;
	unsigned int sz = sizeof(int) ;
//	setsockopt(sock_descriptor, proto->p_proto, TCP_NODELAY, &opt, sizeof(int));
	getsockopt(sock_descriptor, IPPROTO_TCP, TCP_NODELAY, &val, &sz);
	//printf ("val=%d", val) ;
	if(sock_descriptor==-1)
	{ 
		perror("socket!\n");
		exit(1);
	}
	bzero(&sin,sizeof(sin));
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_port=htons(config.port);
	if(bind(sock_descriptor,(struct sockaddr *)&sin,sizeof (sin))==-1)
	{
		perror("bind!\n");
		exit(1);
	}
	if(listen (sock_descriptor,20)==-1)
	{
		perror("listen!\n");
		exit(1);
	}
	printf("Waiting for accepting connection from client!\n");
	socklen_t length = sizeof(struct sockaddr *) ;
	temp_sock_descriptor=accept(sock_descriptor, (struct sockaddr *)&pin,&length);
	//setsockopt(temp_sock_descriptor, proto->p_proto, TCP_NODELAY, &opt, sizeof(int));
	getsockopt(sock_descriptor, IPPROTO_TCP, TCP_NODELAY, &val, &sz);
	//printf ("val=%d", val) ;
	if(temp_sock_descriptor==-1)
	{
		perror("call to accept!\n");
		exit (1);
	}

	if (config.mode == DELAY_SERVER_FIRST )
	{
		travelDelaySend (temp_sock_descriptor) ;
	}
	else if (config.mode == DELAY_CLIENT_FIRST )
	{
		travelDelayReceive (temp_sock_descriptor) ;
	}
	else
	{
		for (config.curPackageSize = config.startPackageSize; config.curPackageSize <= config.endPackageSize; config.curPackageSize*=config.stepPackageSize)
		{
			pthread_t tid ;
			if (config.mode == SERVER_SEND)
			{
				if (!(tid=createThread (threadSend, (void *)&temp_sock_descriptor)))
				{
					std::cerr << "can't create thread " << std::endl ;
					exit (1) ;
				}
				sleep (config.timeSpan) ;
				g_ctrlSend = false ;
				std::cerr << "waiting send thread ... " << std::endl ;
				pthread_join (tid, NULL) ;
				sleep (1) ;
			}
			else if ( config.mode == CLIENT_SEND)
			{
				if (!(tid=createThread (threadReceive, (void *)&temp_sock_descriptor)))
				{
					std::cerr << "can't create thread " << std::endl ;
					exit (1) ;
				}
				pthread_join (tid, NULL) ;
			}
		}
	}

	close (temp_sock_descriptor);
}

void client () 
{
	int socket_descriptor;
	struct sockaddr_in pin;
	struct protoent *proto;
	if(!(proto = getprotobyname("tcp"))){
		printf("unknown protocol!\n");
		exit (1) ;
	}

	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	inet_pton(AF_INET,config.ip.c_str(),&pin.sin_addr);
	pin.sin_port=htons(config.port);
	if((socket_descriptor=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Error openung socket!\n");
		exit(1);
	}
	printf("before connect !\n") ;
	if(connect(socket_descriptor,(sockaddr*)&pin,sizeof (pin))==-1)
	{
		perror("can not connecting to server!\n");
		exit (1);
	}
	printf("connected !\n") ;
//	int opt = 1 ;
	//setsockopt(socket_descriptor, proto->p_proto, TCP_NODELAY, &opt, sizeof(int));

//	if (SetSocketOptions(socket_descriptor))
//	{
//		perror("error: ");
//		exit(1);
  //   }


	if (config.mode == DELAY_SERVER_FIRST )
	{
		travelDelayReceive (socket_descriptor) ;
	}
	else if (config.mode == DELAY_CLIENT_FIRST )
	{
		travelDelaySend (socket_descriptor) ;
	}
	else
	{
		for (config.curPackageSize = config.startPackageSize; config.curPackageSize <= config.endPackageSize; config.curPackageSize*=config.stepPackageSize)
		{
			pthread_t tid ;
		
                        
 
                   	if (config.mode == CLIENT_SEND)
			{
				if (!(tid=createThread (threadSend, (void *)&socket_descriptor)))
				{
					std::cerr << "can't create thread " << std::endl ;
					exit (1) ;
				}
				sleep (config.timeSpan) ;
				g_ctrlSend = false ;
				std::cerr << "waiting send thread ... " << std::endl ;
				pthread_join (tid, NULL) ;
				sleep (1) ;
			}
			else if( config.mode == SERVER_SEND)
			{
				if (!(tid=createThread (threadReceive, (void *)&socket_descriptor)))
				{
					std::cerr << "can't create thread " << std::endl ;
					exit (1) ;
				}
				pthread_join (tid, NULL) ;
			}
		}
	}

	close (socket_descriptor);
}

void udpClient () 
{
	int socket_descriptor;
	struct sockaddr_in pin;

	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	inet_pton(AF_INET,config.ip.c_str(),&pin.sin_addr);
	pin.sin_port=htons(config.port);
	if((socket_descriptor=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("Error openung socket!\n");
		exit(1);
	}
	/*if(bind(socket_descriptor, (struct sockaddr *)&pin, sizeof(pin)) == -1)
	{
		perror("bind error");
		exit(1);
	}*/

/*	if(connect(socket_descriptor,(sockaddr*)&pin,sizeof (pin))==-1)
	{
		perror("can not connecting to server!\n");
		exit (1);
	}*/

	if (config.mode == DELAY_SERVER_FIRST || config.mode == DELAY_CLIENT_FIRST) {
		travelDelaySend (socket_descriptor) ;
	}
	else {
		pthread_t tid ;
		for (config.curPackageSize = config.startPackageSize; config.curPackageSize <= config.endPackageSize; config.curPackageSize*=config.stepPackageSize) {
			if (!(tid=createThread (threadSend, (void *)&socket_descriptor)))
			{
				std::cerr << "can't create thread " << std::endl ;
				exit (1) ;
			}
			sleep (config.timeSpan) ;
			g_ctrlSend = false ;
			std::cerr << "waiting send thread ... " << std::endl ;
			pthread_join (tid, NULL) ;
			sleep (1) ;
		}
	}
}

void udpServer ()
{
	int sockfd;
	struct sockaddr_in servaddr ;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */

	/* init servaddr */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(config.port);

	/* bind address and port to socket */
	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind error");
		exit(1);
	}

	if (config.mode == DELAY_SERVER_FIRST || config.mode == DELAY_CLIENT_FIRST)
	{
		travelDelayReceive (sockfd) ;
	}
	else {
		pthread_t tid ;
		for (config.curPackageSize = config.startPackageSize; config.curPackageSize <= config.endPackageSize; config.curPackageSize*=config.stepPackageSize) {
			if (!(tid=createThread (threadReceive, (void *)&sockfd)))
			{
				std::cerr << "can't create thread " << std::endl ;
				exit (1) ;
			}
			pthread_join (tid, NULL) ;
		}
	}
}

void printHelp () 
{
	std::cout << "Useage: " << std::endl ;
	std::cout << "  nettest [-c|-s] [-m 1|2|3|4] [-a IP] [-p port] " << std::endl ;
	std::cout << "          [--start startPackageSize]" << std::endl ;
	std::cout << "          [--end startPackageSize]" << std::endl ;
	std::cout << "          [--step stepPackageSize]" << std::endl ;
	std::cout << "          [--time timePerPoint]" << std::endl ;
	std::cout << "          [--traveltimes travelTimes]" << std::endl ;
	std::cout << "          [--pkgsize packageSize]" << std::endl ;
	std::cout << "          [--udp 0|1]" << std::endl ;

	std::cout << std::endl ;
	std::cout << " -m: TCP: 1, server send first; 2, client send first; 3, delay server send first ..." << std::endl ;
	std::cout << "     UDP: 0|1, baund width; 3|4, traffic delay "<< std::endl ;
	std::cout << " --udp: 0, for server; 1 for client" << std::endl ;
}

int main (int argc, char *argv[])
{
	config.port = 5678 ;
	config.ip = "192.168.168.10" ;
	config.mode = SERVER_SEND ;
	config.isServer = false ;
	config.startPackageSize = 1*1024 ;
	config.endPackageSize = 16*1024*1024 ;
	config.stepPackageSize = 2 ;
	config.timeSpan = 10 ;
	config.travelTimes = 10000 ;
	config.curPackageSize = 1*1024 ;
	config.tcp = true ;
	for (int i=1; i<argc; i++)
	{
		if(strcmp(argv[i], "-m")==0)
		{
			i ++ ;
			config.mode = atoi(argv[i]) ;
		}
		else if(strcmp(argv[i], "-a")==0)
		{
			i ++ ; 
			config.ip = argv[i] ;
		}
		else if(strcmp(argv[i], "-port")==0)
		{
			i ++ ; 
			config.port = atoi(argv[i]) ;
		}
		else if(strcmp(argv[i], "-s")==0)
		{
			config.isServer = true ;
		}
		else if(strcmp(argv[i], "-c")==0)
		{
			config.isServer = false ;
		}
		else if(strcmp(argv[i], "--start")==0)
		{
			i ++ ;
			config.startPackageSize = atol(argv[i]) ;
		}
		else if(strcmp(argv[i], "--end")==0)
		{
			i ++ ;
			config.endPackageSize = atol(argv[i]) ;
		}
		else if(strcmp(argv[i], "--step")==0)
		{
			i ++ ;
			config.stepPackageSize = atol(argv[i]) ;
		}
		else if(strcmp(argv[i], "--time")==0)
		{
			i ++ ;
			config.timeSpan = atol(argv[i]) ;
		}
		else if(strcmp(argv[i], "--pkgsize")==0)
		{
			i ++ ;
			config.curPackageSize = atol(argv[i]) ;
		}
		else if(strcmp(argv[i], "--traveltimes")==0)
		{
			i ++ ;
			config.travelTimes = atol(argv[i]) ;
		}
		else if(strcmp(argv[i], "--udp")==0)
		{
			i++ ;
			config.tcp = false ;
			config.udpsend = atol(argv[i]) ;
	
		}
		else if(strcmp(argv[i], "--help")==0)
		{
			printHelp () ;
			return 0 ;
		}
	}
	if (config.tcp && config.isServer)
	{
		server () ;
	}
	else if (config.tcp)
	{
		client () ;
	}
	else if (config.udpsend) {
		udpClient () ;
	}
	else {
		udpServer () ;
	}
	return 0 ;
}
