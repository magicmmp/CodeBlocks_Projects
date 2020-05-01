#include <stdio.h>
#include <stdlib.h>
#include<math.h>


float integral(float(*p)(float), float a, float b, int n)
{
	int i;
	float x, h, s;
	h = (b - a) / n;//牛顿莱布尼茨公式运用
	x = a;
	s = 0;
	for (i = 0; i < n; i++)
	{
		x = x + h;
		s = s + (*p)(x)*h;
	}
	return (s);
}
float fsin(float x)
{
	return sin(x);
}
float fcos(float x)
{
	return cos(x);
}
float fexp(float x)
{
	return exp(x);
}

int main()
{


    printf("sin(pi)=%5.2f\n",integral(fsin,(0.7-0.2)*3.14,3.14,100));


    return 0;
}
