/*
���㲢���10000�����������Ľ׳�
*/
#include<bits/stdc++.h>
#include "conio.h"								//getch()������Ҫ�õ���ͷ�ļ� 
using namespace std;				//ʹ�ñ�׼�����ռ䣬������ʹ��cin��ʱ��Ͳ�����ǰ�����std��std::cin�� 
#define MAXLEN 10000 
//�������� 

void add(int r[],int s[],int z[]);
void mul(int r[],int lr,int s[],int ls,int z[]);
int mtrxLen(int M[]);									//�����鰴λ����nλ 	
void shift(int M[], int n); 							//�����鰴λ����nλ 
void copy(int src[], int dst[]);						//������src����������dst 
void add(int numA[],int numB[],int numR[])				//����ӷ�	
{
	int sum[MAXLEN] = {0}; 
	int lA = mtrxLen(numA);
	int lB = mtrxLen(numB);
	lA = lA>lB?lA:lB;
	int idx=0;
	int m=0, ovfl=0;							//m:��λ���м����� ovfl:��λ 
	while(idx <= lA)							//���ڽ�λ��Ե�ʣ����һ��ѭ����idx==lAʱ���ڽ�λ 
	{
		m = numA[idx] + numB[idx] + ovfl;
		sum[idx] = m%10;
		ovfl = m/10;		
		idx++;
	}	
	copy(sum, numR);			//���������Ŀ������ 
}
void mul(int numA[], int numB[], int numR[])
{
	int sum[MAXLEN]={0};
	int zero[MAXLEN] = {0};			//���ڸ��������� 
	int lA = mtrxLen(numA);
	int lB = mtrxLen(numB);
	int AXB[MAXLEN]={0};			//�˷���ʱ��� 
	int	m=0,ovfl=0;				//m:��������λ��˳˵Ľ��; ovfl:�������ʾ��λ 
	int i=0, j=0;				//i:���numAÿһλ�� j���numB��ÿһλ 
	for(i=0;i<=lA-1;i++)				//numA�Ӹ�λ�����λ������numB�ˣ��ѵõ��Ľ���ۼӣ����õ�������˽�� 
	{
		ovfl = 0;				//��ʱ�������� 
		memset(AXB, 0, MAXLEN*sizeof(int));
		for(j=0;j<=lB;j++)		//���һ��ѭ��ʱj=lB,��ʱnumB[j]Ϊ0��m=ovfl		
		{
			m = numA[i]*numB[j] + ovfl;
			AXB[j] = m%10;
			ovfl = m/10;		
		}
//		tmp[j] = ovfl;			//�����numB���λ�˺��ɽ�λ������ 
		shift(AXB, i);			//�����鰴λ����iλ 
		add(sum, AXB, sum);
	}
	copy(sum, numR);			//���������Ŀ������ 
}
//����������Чλ���� 
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

//�����鰴λ����nλ 
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
void copy(int src[], int dst[])						//������src����������dst 
{
	int nLen = mtrxLen(src);
	for(int i = 0; i < nLen; i++) 
	{
		dst[i] = src[i];
	}
} 
//����10000�����������Ľ׳� 
int main()
{
	int n=0;
	while(1)
	{
		cout << "������һ�����������������-1���˳�����" << endl; 
		cin >> n;						//����10000���ڵ������� ��ʵ�ʲ���ֵ���Ե���400�������̫���� 
		if(-1 == n)						//�������-1���˳����� 
		{
			break;
		}
		int res[MAXLEN]={0};				//result������׳˽�� 
		int one[MAXLEN]={0};
		int tmp[MAXLEN]={0};
		res[0]=1;
		one[0]=1;
		tmp[0]=1;
		int lenRes = 0;
		int lenTmp = 0;
		for(int j=1;j<n;j++)			//n�γ˷� 
		{
			add(tmp,one,tmp);			//������1	
			mul(res, tmp, res);
		}	
		int nSize = mtrxLen(res);		//����������Чλ���� 
		for(int h=nSize-1;h>=0;h--)
		{
		
			printf("%d",res[h]);
		}	
		cout << endl;
	}

	return 0;
}


