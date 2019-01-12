/*
计算并输出10000以内正整数的阶乘
*/
#include<bits/stdc++.h>
#include "conio.h"								//getch()函数需要用到此头文件 
using namespace std;				//使用标准命名空间，这样在使用cin的时候就不用在前面加上std（std::cin） 
#define MAXLEN 10000 
//函数声明 

void add(int r[],int s[],int z[]);
void mul(int r[],int lr,int s[],int ls,int z[]);
int mtrxLen(int M[]);									//将数组按位右移n位 	
void shift(int M[], int n); 							//将数组按位右移n位 
void copy(int src[], int dst[]);						//将数组src拷贝给数组dst 
void add(int numA[],int numB[],int numR[])				//数组加法	
{
	int sum[MAXLEN] = {0}; 
	int lA = mtrxLen(numA);
	int lB = mtrxLen(numB);
	lA = lA>lB?lA:lB;
	int idx=0;
	int m=0, ovfl=0;							//m:按位加中间结果； ovfl:进位 
	while(idx <= lA)							//由于进位的缘故，最后一次循环当idx==lA时用于进位 
	{
		m = numA[idx] + numB[idx] + ovfl;
		sum[idx] = m%10;
		ovfl = m/10;		
		idx++;
	}	
	copy(sum, numR);			//拷贝结果到目标数组 
}
void mul(int numA[], int numB[], int numR[])
{
	int sum[MAXLEN]={0};
	int zero[MAXLEN] = {0};			//用于给数组清零 
	int lA = mtrxLen(numA);
	int lB = mtrxLen(numB);
	int AXB[MAXLEN]={0};			//乘法临时结果 
	int	m=0,ovfl=0;				//m:两个数两位相乘乘的结果; ovfl:溢出，表示进位 
	int i=0, j=0;				//i:标记numA每一位； j标记numB的每一位 
	for(i=0;i<=lA-1;i++)				//numA从各位到最高位依次与numB乘，把得到的结果累加，最后得到两数相乘结果 
	{
		ovfl = 0;				//临时变量清零 
		memset(AXB, 0, MAXLEN*sizeof(int));
		for(j=0;j<=lB;j++)		//最后一次循环时j=lB,此时numB[j]为0，m=ovfl		
		{
			m = numA[i]*numB[j] + ovfl;
			AXB[j] = m%10;
			ovfl = m/10;		
		}
//		tmp[j] = ovfl;			//如果与numB最高位乘后由进位，保存 
		shift(AXB, i);			//将数组按位右移i位 
		add(sum, AXB, sum);
	}
	copy(sum, numR);			//拷贝结果到目标数组 
}
//计算数组有效位长度 
int mtrxLen(int M[])
{
	int i = 0;
	for(i = MAXLEN-1; i >= 0; --i)
	{
		if(0 != M[i])
		{
			break;
		}
	}
	return i+1;	  
}

//将数组按位右移n位 
void shift(int M[], int n) 
{
	if(0 != n)
	{
		for(int idx = MAXLEN-1; (idx-n) >= 0; idx--)
		{
			M[idx]=M[idx - n];					
			M[idx - n] = 0;
		}	
	} 
}
void copy(int src[], int dst[])						//将数组src拷贝给数组dst 
{
	int nLen = mtrxLen(src);
	for(int i = 0; i < nLen; i++) 
	{
		dst[i] = src[i];
	}
} 
//计算10000以内正整数的阶乘 
int main()
{
	int n=0;
	while(1)
	{
		cout << "请输入一个正整数，如果输入-1则退出程序" << endl; 
		cin >> n;						//输入10000以内的正整数 ，实际测试值测试到了400，后面的太慢了 
		if(-1 == n)						//如果输入-1则退出程序 
		{
			break;
		}
		int res[MAXLEN]={0};				//result，保存阶乘结果 
		int one[MAXLEN]={0};
		int tmp[MAXLEN]={0};
		res[0]=1;
		one[0]=1;
		tmp[0]=1;
		int lenRes = 0;
		int lenTmp = 0;
		for(int j=1;j<n;j++)			//n次乘法 
		{
			add(tmp,one,tmp);			//乘数加1	
			mul(res, tmp, res);
		}	
		int nSize = mtrxLen(res);		//计算数组有效位长度 
		for(int h=nSize-1;h>=0;h--)
		{
		
			printf("%d",res[h]);
		}	
		cout << endl;
	}

	return 0;
}


