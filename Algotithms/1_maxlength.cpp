/*
输入: 一个字符串, 不超过10个单词
输出: 输出最长的单词
*/
#include<stdio.h>
#include<string.h>
#include "conio.h"								//getch()函数需要用到此头文件 

int maxlength1()
{
	//第一步 输入字符串
	char str[10][10] = {0};						//接收输入字符串，最多10个单词，每个单词最长10个字符 
	char cIn = 0;
	int i = 0;
	int j = 0;
	int index = 0;								//用于记录最长单词下标 
	int max = 0;								//记录单词长度 
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			cIn = getch();						//getch()在敲如一个字符后就立即返回，而getchar()和scanf()都需要等待回车键
			printf("%c", cIn);					//getch()函数再输入字符的时候不显示，所以需要printf()来显示 
			if(cIn == 0x0d || cIn == ' ') 		//如果遇到空格跳出内层循环，继续接收下一个单词 
			{
				break;
			}
			else
			{
				str[i][j] = cIn;
			} 
		}
		if(cIn == 0x0d)							//遇到回车直接结束，认为句子已经输入完成 
		{
			break;
		}	
	} 
	
	//第二步 计算每个单词长度，记录其下标
	for(i = 0; i < 10; i++)
	{
		if(strlen(str[i]) > max)
		{
			max = strlen(str[i]);
			index = i;
		}
	} 
	
	//第三步 输出单词
	printf("the word with max length is:%s", str[index]); 
	
} 

void maxlength2()
{
	//第一步 输入字符串
	char str[100] = {0};						//接收输入字符串，最多100个字符 
	gets(str);									//从键盘结束字符串 
	int i = 0 ;
	int j = -1;									//用于临时记录空格字符的下标 
	int len = 0;								//用于临时记录单词长度 
	int index = 0;								//记录最长单词的起始位置	
	int max = 0;								//记录最长单词长度					 
	//第二步 将字符串按照空格字符进行分割并存入二维数组
	for(i = 0; i < 100; i++)
	{
		if(str[i] == ' ')					//碰到了空格 ,进行操作：记录单词长度到max,记录当前空格位置到j，用于下次计算单词长度 
		{
			len = i - j - 1;				//计算单词长度
			if(len > max)
			{
				max = len;					//记录单词长度到max
				j = i;						//记录当前空格位置到j
				index = j + 1;				//记录单词的起始位置 
			} 
		}
		if(str[i] == '\0')					// 字符串结束，跳出循环 
		{
			break;							
		}
	}
	//第三步 输出最长单词
	printf("the word with max length is :");
	for(int k = 0; k < max; k++)
	{
		printf("%c", str[index]);	
	} 
}
