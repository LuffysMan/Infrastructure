/*
5、 汉诺塔问题的移动次数(answer.cpp)
【问题描述】我们知道，一个盘子的汉诺塔问题的移动次数是 1 次，两个盘子的
汉诺塔问题的移动次数是 3 次， 3 个盘子的汉诺塔问题的移动次数是 7 次??如
果我们用 f(n)来表示 n 个盘子的汉诺塔问题的移动次数，那么，f(n)=2f(n-1)+1。(实际就是2^n - 1)
现在给出任意一个 n，输出 f(n)。
【输入数据】 (answer.in)
一个整数 n
【输出数据】 (answer.out)
对应的移动次数
【样例输入】
60
【样例输出】
1152921504606846975
【数据范围】
50≤N≤200
*/
#include<bits/stdc++.h>
using namespace std;				
#define MAX 1000000000 
#define LEN 10
//鍑芥暟澹版槑 
typedef unsigned long long uint64;
void mul(uint64 A[], int B);
void add(uint64 A[], int B);
int main()
{
	while(1)
	{
		uint64 res[LEN] = {0};				//存储乘法结果
		res[0] = 1;
		int n = 0;
		cin >> n;					//输入次幂
		//n次乘法 
		for(int i = 0; i < n; ++i)
		{
			mul(res, 2);
		}
		//减去1 
		add(res, -1); 

		//输出乘法结果
		for(int k = LEN -1; k >= 0; --k)
		{
			if(1)
			{
				printf("%09d ", res[k]);	
			}
		} 	
	}

	return 0;
}
void mul(uint64 A[], int B)
{	
	uint64 tmp = 0;				//用于暂存乘法结果 
	uint64 jw = 0;				//用于表示进位 
	for(int j = 0; j < LEN; ++j)
	{
		tmp = A[j] * B;
		A[j] = tmp%MAX + jw;	
		jw = tmp / MAX;
	}	
}

void add(uint64 A[], int B)
{	
	uint64 tmp = 0;				//用于暂存加法结果 
	uint64 jw = 0;				//用于表示进位 
	for(int j = 0; j < LEN; ++j)
	{
		if(0 != j)
		{
			tmp = A[j] + jw;
		}
		else
		{
			tmp = A[j] + B + jw;	
		} 
		A[j] = tmp%MAX;	
		jw = tmp / MAX;
	}	
}









