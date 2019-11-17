#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Tag_Array_Length 5000  //暂时不降低精度，就以g为单位
#define nHoppers         24     //有几个斗
#define Find_Result_Num  50     //取最优的前50个合格结果看看


//hopper_number_tag[k]&0x1<<(hopper_num) 非零说明第hopper_num号斗能参与组成重量k.
//要确保数组元素至少是32位，一位代表一个斗
unsigned int hopper_tag_array[Tag_Array_Length];

int weights[nHoppers];//每个斗的重量
int target_weight;//目标重量，g为单位
int target_weight_min;//目标重量下限
int target_weight_max;//目标重量上限

typedef struct
{
    unsigned int hopper_number_tag;//位i是否是1表示斗i是否在这个组合中
    int combination_weight;//这个组合的重量
    int D_value;//与目标重量的差值
}Result_Info_Struct;

Result_Info_Struct Result_Info[Find_Result_Num];

//根据斗数和目标重量，给斗初始化一个重量值
void init_hopper_weights(int Weights[] ,int nHopper,int target_weight)
{
    int i;
    float D_ratio=(float)0.5;
    //期望参与组合的斗是总斗数的三分一
    //由此得出每个斗应该初始化的重量
    int  hopper_weight=target_weight*3/nHopper;
    int  D_value=hopper_weight*D_ratio;//斗初始化重量的上限偏差
    int flag=1;
    for(i=0;i<nHopper;i++)
    {
        if(flag==1)
            flag=-1;
        else
            flag=1;
        srand((unsigned int)(time(NULL)+i*127*flag));
        float f=rand()%100;
        f=f/100;//产生0到1之间均匀分布的小数
        Weights[i]=hopper_weight-D_value+D_value*2*f;
    }
}

void find_possible_combinations()
{
    int i,j;
    //初始化标记数组
    for(int i=0;i<=target_weight_max;i++)
        hopper_tag_array[i]=0;
    hopper_tag_array[0]=1;//重量为0总是能组合成的

    for(i=0;i<nHoppers;i++)
    {
        for(j=1;j<=target_weight_max;j++)
        {
            if(weights[i]<=j)
            if(hopper_tag_array[j-weights[i])
                hopper_tag_array[j] |=0x1<<i;//第i号斗能参与组合成重量j
        }
    }





}







int main()
{

    int i,j;


    target_weight=100;//目标重量
    target_weight_min=95;//目标重量下限
    target_weight_max=105;//目标重量上限

    init_hopper_weights(weights,nHoppers,target_weight);

    for(i=0;i<nHoppers;i++)
        printf("%d ",weights[i]);
















    return 0;
}
