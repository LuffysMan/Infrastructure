/*
����: һ���ַ���, ������10������
���: �����ĵ���
*/
#include<stdio.h>
#include<string.h>
#include "conio.h"								//getch()������Ҫ�õ���ͷ�ļ� 

int maxlength1()
{
	//��һ�� �����ַ���
	char str[10][10] = {0};						//���������ַ��������10�����ʣ�ÿ�������10���ַ� 
	char cIn = 0;
	int i = 0;
	int j = 0;
	int index = 0;								//���ڼ�¼������±� 
	int max = 0;								//��¼���ʳ��� 
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			cIn = getch();						//getch()������һ���ַ�����������أ���getchar()��scanf()����Ҫ�ȴ��س���
			printf("%c", cIn);					//getch()�����������ַ���ʱ����ʾ��������Ҫprintf()����ʾ 
			if(cIn == 0x0d || cIn == ' ') 		//��������ո������ڲ�ѭ��������������һ������ 
			{
				break;
			}
			else
			{
				str[i][j] = cIn;
			} 
		}
		if(cIn == 0x0d)							//�����س�ֱ�ӽ�������Ϊ�����Ѿ�������� 
		{
			break;
		}	
	} 
	
	//�ڶ��� ����ÿ�����ʳ��ȣ���¼���±�
	for(i = 0; i < 10; i++)
	{
		if(strlen(str[i]) > max)
		{
			max = strlen(str[i]);
			index = i;
		}
	} 
	
	//������ �������
	printf("the word with max length is:%s", str[index]); 
	
} 

void maxlength2()
{
	//��һ�� �����ַ���
	char str[100] = {0};						//���������ַ��������100���ַ� 
	gets(str);									//�Ӽ��̽����ַ��� 
	int i = 0 ;
	int j = -1;									//������ʱ��¼�ո��ַ����±� 
	int len = 0;								//������ʱ��¼���ʳ��� 
	int index = 0;								//��¼����ʵ���ʼλ��	
	int max = 0;								//��¼����ʳ���					 
	//�ڶ��� ���ַ������տո��ַ����зָ�����ά����
	for(i = 0; i < 100; i++)
	{
		if(str[i] == ' ')					//�����˿ո� ,���в�������¼���ʳ��ȵ�max,��¼��ǰ�ո�λ�õ�j�������´μ��㵥�ʳ��� 
		{
			len = i - j - 1;				//���㵥�ʳ���
			if(len > max)
			{
				max = len;					//��¼���ʳ��ȵ�max
				j = i;						//��¼��ǰ�ո�λ�õ�j
				index = j + 1;				//��¼���ʵ���ʼλ�� 
			} 
		}
		if(str[i] == '\0')					// �ַ�������������ѭ�� 
		{
			break;							
		}
	}
	//������ ��������
	printf("the word with max length is :");
	for(int k = 0; k < max; k++)
	{
		printf("%c", str[index]);	
	} 
}
