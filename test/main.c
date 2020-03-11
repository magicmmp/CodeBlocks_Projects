#include <stdio.h>
#include <stdlib.h>

void VB_Control_Init_when_PwrON(int target_wt)
{
	int weight_coarse_1s,weight_medium_1s,weight_fine_1s;
	weight_coarse_1s=target_wt*0.2;
	if(weight_coarse_1s>1500)
		weight_coarse_1s=1500;

	if(target_wt>5000)//500  50
	{
		weight_medium_1s=weight_coarse_1s*0.5;
		weight_fine_1s=150;
	}
	else if(target_wt>2500)//250 50
	{
		weight_medium_1s=weight_coarse_1s*(1-(target_wt-2500.0)/500*0.1);
		weight_fine_1s=100;
	}
	else//
	{
		weight_medium_1s=weight_coarse_1s;
		if(weight_medium_1s>100)
			weight_fine_1s=100;
		else
		  weight_fine_1s=weight_medium_1s;
	}
	printf("Ŀ������=%d ��, ��=%d, ��=%d, ��=%d\n",target_wt/10,weight_coarse_1s/10,weight_medium_1s/10,weight_fine_1s/10);

    int w_fine,w_medium,w_coarse;
    w_fine=target_wt-weight_fine_1s;
    w_medium=target_wt-weight_medium_1s*1.6;
    w_coarse=target_wt-weight_coarse_1s*3;
    printf("��������С�� %d ��,���ڿ�ӽ׶�\n",w_coarse/10);
    printf("����������   %d �˺� %d ��֮��,�����мӽ׶�\n",w_coarse/10,w_medium/10);
    printf("����������   %d �˺� %d ��֮��,�������ӽ׶�\n",w_medium/10,w_fine/10);
    printf("������������ %d ��,���ڲ��Ͻ׶�\n",w_fine/10);
    printf("\n\n");

}

int main()
{
    int i=5000;
    int target_wt=5600;
    int weight[10]={20,50,100,200,250,300,350,500,1000,2000};
    float f=(1-(target_wt-2500.0)/500*0.1);

    printf("������=%f\n",f);

    for(i=0;i<10;i++)
        VB_Control_Init_when_PwrON(weight[i]*10);




    return 0;
}
