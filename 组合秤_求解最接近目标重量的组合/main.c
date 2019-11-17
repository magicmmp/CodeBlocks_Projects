#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Tag_Array_Length 5000  //��ʱ�����;��ȣ�����gΪ��λ
#define nHoppers         24     //�м�����
#define Find_Result_Num  50     //ȡ���ŵ�ǰ50���ϸ�������


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
    int D_value;//��Ŀ�������Ĳ�ֵ
}Result_Info_Struct;

Result_Info_Struct Result_Info[Find_Result_Num];

//���ݶ�����Ŀ��������������ʼ��һ������ֵ
void init_hopper_weights(int Weights[] ,int nHopper,int target_weight)
{
    int i;
    float D_ratio=(float)0.5;
    //����������ϵĶ����ܶ���������һ
    //�ɴ˵ó�ÿ����Ӧ�ó�ʼ��������
    int  hopper_weight=target_weight*3/nHopper;
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
    for(int i=0;i<=target_weight_max;i++)
        hopper_tag_array[i]=0;
    hopper_tag_array[0]=1;//����Ϊ0��������ϳɵ�

    for(i=0;i<nHoppers;i++)
    {
        for(j=1;j<=target_weight_max;j++)
        {
            if(weights[i]<=j)
            if(hopper_tag_array[j-weights[i])
                hopper_tag_array[j] |=0x1<<i;//��i�Ŷ��ܲ�����ϳ�����j
        }
    }





}







int main()
{

    int i,j;


    target_weight=100;//Ŀ������
    target_weight_min=95;//Ŀ����������
    target_weight_max=105;//Ŀ����������

    init_hopper_weights(weights,nHoppers,target_weight);

    for(i=0;i<nHoppers;i++)
        printf("%d ",weights[i]);
















    return 0;
}
