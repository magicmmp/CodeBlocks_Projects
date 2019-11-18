#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Tag_Array_Length 5000  //暂时不降低精度，就以g为单位
#define nHoppers         15     //有几个斗
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
    int n_hoppers;
    int D_value;//与目标重量的差值
}Result_Info_Struct;

Result_Info_Struct Result_Info[Find_Result_Num];
int result_count=0;//找到了几个结果

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
    for(i=0;i<=target_weight_max;i++)
        hopper_tag_array[i]=0;
    hopper_tag_array[0]=1;//重量为0总是能组合成的

    for(i=0;i<nHoppers;i++)
    {
        for(j=1;j<=target_weight_max;j++)
        {
            if(weights[i]<=j)
            if(hopper_tag_array[j-weights[i]])
                hopper_tag_array[j] |=0x1<<i;//第i号斗能参与组合成重量j
        }
    }
}


const unsigned int bit_flag[32]=
{
0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080,
0x00000100,0x00000200,0x00000400,0x00000800,0x00001000,0x00002000,0x00004000,0x00008000,
0x00010000,0x00020000,0x00040000,0x00080000,0x00100000,0x00200000,0x00400000,0x00800000,
0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,
};
unsigned int hopper_number_tag_tmp=0;//位i是否是1表示斗i是否在这个组合中
int combination_weight_tmp=0;//这个组合的重量

void dfs(int next_weight)//查看哪些斗参与组合成这个重量
{
    int hopper_index=0;
    while(result_count<Find_Result_Num&&hopper_index<nHoppers)
    {
        if(hopper_tag_array[next_weight]&bit_flag[hopper_index])//如果斗hopper_index参与了组合
        {
            hopper_number_tag_tmp|=bit_flag[hopper_index];
            combination_weight_tmp+=weights[hopper_index];
            if(next_weight==weights[hopper_index])//找到一个组合
            {
                Result_Info[result_count].combination_weight=combination_weight_tmp;
                Result_Info[result_count].hopper_number_tag=hopper_number_tag_tmp;
                result_count++;
            }
            else
                dfs(next_weight-weights[hopper_index]);//如果该组合还有其他斗
            hopper_number_tag_tmp&=~bit_flag[hopper_index];
            combination_weight_tmp-=weights[hopper_index];
        }
        hopper_index++;
    }
}





int main()
{

    int i,j;


    target_weight=100;//目标重量
    target_weight_min=98;//目标重量下限
    target_weight_max=101;//目标重量上限

    init_hopper_weights(weights,nHoppers,target_weight);
    find_possible_combinations();
    dfs(target_weight);
   // dfs(target_weight-1);
   // dfs(target_weight+1);
    //dfs(target_weight-2);
    //dfs(target_weight+2);


    for(i=0;i<nHoppers;i++)
    {
        if(i%4==0)
            printf("\n\n");
        printf("斗%2d重量 %4d 克,  ",i,weights[i]);
    }


        printf("\n\n");

    for(i=0;i<5;i++)
    {
         Result_Info[i].n_hoppers=0;
        for(j=0;j<nHoppers;j++)
        {
            if(Result_Info[i].hopper_number_tag&bit_flag[j])
                Result_Info[i].n_hoppers++;
        }
         printf("\n\n");
        printf("第%3d个组合  ,总重量= %4d克，参与组合斗数= %2d\n",
               i,Result_Info[i].combination_weight,Result_Info[i].n_hoppers);
        int num=0;

        for(j=0;j<nHoppers;j++)
        {
            if(Result_Info[i].hopper_number_tag&bit_flag[j])
            {
                printf("斗%3d(%4d 克),  ",j,weights[j]);
                num++;
                if(num%4==0)
                    printf("\n");
            }
        }


    }



    return 0;
}
