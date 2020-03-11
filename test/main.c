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
	printf("目标重量=%d 克, 快=%d, 中=%d, 慢=%d\n",target_wt/10,weight_coarse_1s/10,weight_medium_1s/10,weight_fine_1s/10);

    int w_fine,w_medium,w_coarse;
    w_fine=target_wt-weight_fine_1s;
    w_medium=target_wt-weight_medium_1s*1.6;
    w_coarse=target_wt-weight_coarse_1s*3;
    printf("已有重量小于 %d 克,处于快加阶段\n",w_coarse/10);
    printf("已有重量在   %d 克和 %d 克之间,处于中加阶段\n",w_coarse/10,w_medium/10);
    printf("已有重量在   %d 克和 %d 克之间,处于慢加阶段\n",w_medium/10,w_fine/10);
    printf("已有重量大于 %d 克,处于补料阶段\n",w_fine/10);
    printf("\n\n");

}

int main()
{
    int i=5000;
    int target_wt=5600;
    int weight[10]={20,50,100,200,250,300,350,500,1000,2000};
    float f=(1-(target_wt-2500.0)/500*0.1);

    printf("浮点数=%f\n",f);

    for(i=0;i<10;i++)
        VB_Control_Init_when_PwrON(weight[i]*10);




    return 0;
}
