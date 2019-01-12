/*
5�� ��ŵ��������ƶ�����(answer.cpp)
����������������֪����һ�����ӵĺ�ŵ��������ƶ������� 1 �Σ��������ӵ�
��ŵ��������ƶ������� 3 �Σ� 3 �����ӵĺ�ŵ��������ƶ������� 7 ��??��
�������� f(n)����ʾ n �����ӵĺ�ŵ��������ƶ���������ô��f(n)=2f(n-1)+1��(ʵ�ʾ���2^n - 1)
���ڸ�������һ�� n����� f(n)��
���������ݡ� (answer.in)
һ������ n
��������ݡ� (answer.out)
��Ӧ���ƶ�����
���������롿
60
�����������
1152921504606846975
�����ݷ�Χ��
50��N��200
*/
#include<bits/stdc++.h>
using namespace std;				
#define MAX 1000000000 
#define LEN 10
//函数声明 
typedef unsigned long long uint64;
void mul(uint64 A[], int B);
void add(uint64 A[], int B);
int main()
{
	while(1)
	{
		uint64 res[LEN] = {0};				//�洢�˷����
		res[0] = 1;
		int n = 0;
		cin >> n;					//�������
		//n�γ˷� 
		for(int i = 0; i < n; ++i)
		{
			mul(res, 2);
		}
		//��ȥ1 
		add(res, -1); 

		//����˷����
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
	uint64 tmp = 0;				//�����ݴ�˷���� 
	uint64 jw = 0;				//���ڱ�ʾ��λ 
	for(int j = 0; j < LEN; ++j)
	{
		tmp = A[j] * B;
		A[j] = tmp%MAX + jw;	
		jw = tmp / MAX;
	}	
}

void add(uint64 A[], int B)
{	
	uint64 tmp = 0;				//�����ݴ�ӷ���� 
	uint64 jw = 0;				//���ڱ�ʾ��λ 
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









