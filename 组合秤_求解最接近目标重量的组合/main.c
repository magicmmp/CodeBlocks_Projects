#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Tag_Array_Length 5000  //暂时不降低精度，就以g为单位
 //有几个斗,运算时斗号从0开始，范围0到nHoppers-1.显示给人看则是从1开始。
#define nHoppers         15
#define Find_Result_Num  50     //取最优的前50个合格结果看看

const unsigned int bit_flag[32]=
{
0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080,
0x00000100,0x00000200,0x00000400,0x00000800,0x00001000,0x00002000,0x00004000,0x00008000,
0x00010000,0x00020000,0x00040000,0x00080000,0x00100000,0x00200000,0x00400000,0x00800000,
0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,
};

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
    int  hopper_weight=target_weight*2/nHopper;//总是期望一半的斗参与组合，能得到最多的有效组合数?
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
    hopper_tag_array[0]=1;//重量为0总是能组合成的
    for(i=1;i<=target_weight_max;i++)
        hopper_tag_array[i]=0;


    for(i=0;i<nHoppers;i++)
    {
        for(j=weights[i];j<=target_weight_max;j++)
        {
            if(hopper_tag_array[j-weights[i]])
                hopper_tag_array[j] |=bit_flag[i];//第i号斗能参与组合成重量j
        }
    }
}


unsigned int hopper_number_tag_tmp;//位i是否是1表示斗i是否在这个组合中
int combination_weight_tmp;//这个组合的重量

void dfs(int next_weight)//查看哪些斗参与组合成这个重量
{
    int hopper_index=0;
    while(result_count<Find_Result_Num&&hopper_index<nHoppers)
    {
        if((hopper_number_tag_tmp&bit_flag[hopper_index])==0)//防止一次组合中同一个斗被重复计算
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


//1、特别注意：一次组合中，同一个斗不要被重复计算

//2、此算法暂时没发现问题，有空与暴力算法结果一一比较，才能确认是完全正确的。
//     比较方法：此方法只需运行一次即可获得所有结果，当验证到 某个重量都有什么组合时，
//               暴力算法都要重新枚举一次，以搜集等于该重量的所有组合。
//               然后检查： 能组成该重量的组合总数和每个组合有哪些斗。看得出的结果是否一样。
//     一开始可以用5~10个斗来验证，以简化验证过程，节约时间。

//居然打印出重复的结果？2019-12-26
/**
Yes ,第 31个组合  ,总重量= 1000克，参与组合斗数= 8
斗 4( 121克),  斗 5( 117克),  斗 6( 159克),  斗 7(  77克),
斗 8(  67克),  斗 9( 171克),  斗10( 105克),  斗14( 183克),

Yes ,第 32个组合  ,总重量= 1000克，参与组合斗数= 8
斗 4( 121克),  斗 5( 117克),  斗 6( 159克),  斗 7(  77克),
斗 8(  67克),  斗 9( 171克),  斗10( 105克),  斗14( 183克),
*/
//此问题的原因应该是：a+b=10，a和b有几种不同的取值一样，2+8可以，8+2也可以，
//这样就产生了很多重复的结果,应该搜索到目标值的1/2(包括1/2目标重量的临界值)即可。
//超过1/2的不理会。

int main()
{

    int i,j;


    target_weight=1000;//目标重量
    target_weight_min=995;//目标重量下限
    target_weight_max=1001;//目标重量上限

    result_count=0;
    hopper_number_tag_tmp=0;//位i是否是1表示斗i是否在这个组合中
    combination_weight_tmp=0;//这个组合的重量


    init_hopper_weights(weights,nHoppers,target_weight);
    find_possible_combinations();

    dfs(target_weight);
    hopper_number_tag_tmp=0;//位i是否是1表示斗i是否在这个组合中
    combination_weight_tmp=0;//这个组合的重量
   // dfs(target_weight-1);
   // dfs(target_weight+1);
    //dfs(target_weight-2);
    //dfs(target_weight+2);


    for(i=0;i<nHoppers;i++)
    {
        if(i%4==0)
            printf("\n\n");
        printf("斗%2d重量=%4d克,  ",i+1,weights[i]);
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

         //检验实际被选中的斗总重量和递归计算的总重量是否相等
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

        printf("%s ,第%3d个组合  ,总重量= %4d克，参与组合斗数=%2d\n",CheckBuffer[buffer_Index],
                  i+1,Result_Info[i].combination_weight,Result_Info[i].n_hoppers);
        int num=0;

        for(j=0;j<nHoppers;j++)
        {
            if(Result_Info[i].hopper_number_tag&bit_flag[j])
            {
                printf("斗%2d(%4d克),  ",j+1,weights[j]);
                num++;
                if(num%4==0)
                    printf("\n");
            }
        }


    }



    return 0;
}
