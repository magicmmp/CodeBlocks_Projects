#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Tag_Array_Length 5000  //��ʱ�����;��ȣ�����gΪ��λ
 //�м�����,����ʱ���Ŵ�0��ʼ����Χ0��nHoppers-1.��ʾ���˿����Ǵ�1��ʼ��
#define nHoppers         15
#define Find_Result_Num  50     //ȡ���ŵ�ǰ50���ϸ�������

const unsigned int bit_flag[32]=
{
0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080,
0x00000100,0x00000200,0x00000400,0x00000800,0x00001000,0x00002000,0x00004000,0x00008000,
0x00010000,0x00020000,0x00040000,0x00080000,0x00100000,0x00200000,0x00400000,0x00800000,
0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,
};

//hopper_number_tag[k]&0x1<<(hopper_num) ����˵����hopper_num�Ŷ��ܲ����������k.
//Ҫȷ������Ԫ��������32λ��һλ����һ����
unsigned int hopper_tag_array[Tag_Array_Length];

int weights[nHoppers];//ÿ����������
int target_weight;//Ŀ��������gΪ��λ
int target_weight_min;//Ŀ����������
int target_weight_max;//Ŀ����������

typedef struct
{
    unsigned int hopper_number_tag;//λi�Ƿ���1��ʾ��i�Ƿ�����������
    int combination_weight;//�����ϵ�����
    int n_hoppers;
    int D_value;//��Ŀ�������Ĳ�ֵ
}Result_Info_Struct;

Result_Info_Struct Result_Info[Find_Result_Num];
int result_count=0;//�ҵ��˼������

//���ݶ�����Ŀ��������������ʼ��һ������ֵ
void init_hopper_weights(int Weights[] ,int nHopper,int target_weight)
{
    int i;
    float D_ratio=(float)0.5;
    //����������ϵĶ����ܶ���������һ
    //�ɴ˵ó�ÿ����Ӧ�ó�ʼ��������
    int  hopper_weight=target_weight*2/nHopper;//��������һ��Ķ�������ϣ��ܵõ�������Ч�����?
    int  D_value=hopper_weight*D_ratio;//����ʼ������������ƫ��
    int flag=1;
    for(i=0;i<nHopper;i++)
    {
        if(flag==1)
            flag=-1;
        else
            flag=1;
        srand((unsigned int)(time(NULL)+i*127*flag));
        float f=rand()%100;
        f=f/100;//����0��1֮����ȷֲ���С��
        Weights[i]=hopper_weight-D_value+D_value*2*f;
    }
}

void find_possible_combinations()
{
    int i,j;
    //��ʼ���������
    hopper_tag_array[0]=1;//����Ϊ0��������ϳɵ�
    for(i=1;i<=target_weight_max;i++)
        hopper_tag_array[i]=0;


    for(i=0;i<nHoppers;i++)
    {
        for(j=weights[i];j<=target_weight_max;j++)
        {
            if(hopper_tag_array[j-weights[i]])
                hopper_tag_array[j] |=bit_flag[i];//��i�Ŷ��ܲ�����ϳ�����j
        }
    }
}


unsigned int hopper_number_tag_tmp;//λi�Ƿ���1��ʾ��i�Ƿ�����������
int combination_weight_tmp;//�����ϵ�����

void dfs(int next_weight)//�鿴��Щ��������ϳ��������
{
    int hopper_index=0;
    while(result_count<Find_Result_Num&&hopper_index<nHoppers)
    {
        if((hopper_number_tag_tmp&bit_flag[hopper_index])==0)//��ֹһ�������ͬһ�������ظ�����
        if(hopper_tag_array[next_weight]&bit_flag[hopper_index])//�����hopper_index���������
        {
            hopper_number_tag_tmp|=bit_flag[hopper_index];
            combination_weight_tmp+=weights[hopper_index];
            if(next_weight==weights[hopper_index])//�ҵ�һ�����
            {
                Result_Info[result_count].combination_weight=combination_weight_tmp;
                Result_Info[result_count].hopper_number_tag=hopper_number_tag_tmp;
                result_count++;
            }
            else
                dfs(next_weight-weights[hopper_index]);//�������ϻ���������
            hopper_number_tag_tmp&=~bit_flag[hopper_index];
            combination_weight_tmp-=weights[hopper_index];
        }
        hopper_index++;
    }
}


//1���ر�ע�⣺һ������У�ͬһ������Ҫ���ظ�����

//2�����㷨��ʱû�������⣬�п��뱩���㷨���һһ�Ƚϣ�����ȷ������ȫ��ȷ�ġ�
//     �ȽϷ������˷���ֻ������һ�μ��ɻ�����н��������֤�� ĳ����������ʲô���ʱ��
//               �����㷨��Ҫ����ö��һ�Σ����Ѽ����ڸ�������������ϡ�
//               Ȼ���飺 ����ɸ����������������ÿ���������Щ�������ó��Ľ���Ƿ�һ����
//     һ��ʼ������5~10��������֤���Լ���֤���̣���Լʱ�䡣

//��Ȼ��ӡ���ظ��Ľ����2019-12-26
/**
Yes ,�� 31�����  ,������= 1000�ˣ�������϶���= 8
�� 4( 121��),  �� 5( 117��),  �� 6( 159��),  �� 7(  77��),
�� 8(  67��),  �� 9( 171��),  ��10( 105��),  ��14( 183��),

Yes ,�� 32�����  ,������= 1000�ˣ�������϶���= 8
�� 4( 121��),  �� 5( 117��),  �� 6( 159��),  �� 7(  77��),
�� 8(  67��),  �� 9( 171��),  ��10( 105��),  ��14( 183��),
*/
//�������ԭ��Ӧ���ǣ�a+b=10��a��b�м��ֲ�ͬ��ȡֵһ����2+8���ԣ�8+2Ҳ���ԣ�
//�����Ͳ����˺ܶ��ظ��Ľ��,Ӧ��������Ŀ��ֵ��1/2(����1/2Ŀ���������ٽ�ֵ)���ɡ�
//����1/2�Ĳ���ᡣ

int main()
{

    int i,j;


    target_weight=1000;//Ŀ������
    target_weight_min=995;//Ŀ����������
    target_weight_max=1001;//Ŀ����������

    result_count=0;
    hopper_number_tag_tmp=0;//λi�Ƿ���1��ʾ��i�Ƿ�����������
    combination_weight_tmp=0;//�����ϵ�����


    init_hopper_weights(weights,nHoppers,target_weight);
    find_possible_combinations();

    dfs(target_weight);
    hopper_number_tag_tmp=0;//λi�Ƿ���1��ʾ��i�Ƿ�����������
    combination_weight_tmp=0;//�����ϵ�����
   // dfs(target_weight-1);
   // dfs(target_weight+1);
    //dfs(target_weight-2);
    //dfs(target_weight+2);


    for(i=0;i<nHoppers;i++)
    {
        if(i%4==0)
            printf("\n\n");
        printf("��%2d����=%4d��,  ",i+1,weights[i]);
    }


        printf("\n\n");

    for(i=0;i<Find_Result_Num;i++)
    {
         Result_Info[i].n_hoppers=0;
        for(j=0;j<nHoppers;j++)
        {
            if(Result_Info[i].hopper_number_tag&bit_flag[j])
                Result_Info[i].n_hoppers++;
        }
         printf("\n\n");

         //����ʵ�ʱ�ѡ�еĶ��������͵ݹ������������Ƿ����
        char CheckBuffer[2][4]={"Yes"," No"};
        int buffer_Index;
        int actual_weight_tmp=0;
        for(j=0;j<nHoppers;j++)
        {
            if(Result_Info[i].hopper_number_tag&bit_flag[j])
                actual_weight_tmp+=weights[j];
        }
        if(actual_weight_tmp==Result_Info[i].combination_weight)
            buffer_Index=0;
        else
            buffer_Index=1;

        printf("%s ,��%3d�����  ,������= %4d�ˣ�������϶���=%2d\n",CheckBuffer[buffer_Index],
                  i+1,Result_Info[i].combination_weight,Result_Info[i].n_hoppers);
        int num=0;

        for(j=0;j<nHoppers;j++)
        {
            if(Result_Info[i].hopper_number_tag&bit_flag[j])
            {
                printf("��%2d(%4d��),  ",j+1,weights[j]);
                num++;
                if(num%4==0)
                    printf("\n");
            }
        }


    }



    return 0;
}
