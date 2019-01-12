/*
04:生日相同 2.0
查看
提交
统计
提问
总时间限制:?1000ms?内存限制:?65536kB描述在一个有180人的大班级中，存在两个人生日相同的概率非常大，现给出每个学生的名字，出生月日。试找出所有生日相同的学生。

输入第一行为整数n，表示有n个学生，n ≤ 180。此后每行包含一个字符串和两个整数，分别表示学生的名字（名字第一个字母大写，其余小写，
不含空格，且长度小于20）和出生月(1 ≤ m ≤ 12)日(1 ≤ d ≤ 31)。名字、月、日之间用一个空格分隔输出每组生日相同的学生，输出一行，
其中前两个数字表示月和日，后面跟着所有在当天出生的学生的名字，数字、名字之间都用一个空格分隔。对所有的输出，要求按日期从前到
后的顺序输出。 对生日相同的名字，按名字从短到长按序输出，长度相同的按字典序输出。如没有生日相同的学生，输出”None”
样例输入6
Avril 3 2
Candy 4 5
Tim 3 2
Sufia 4 5
Lagrange 4 5
Bill 3 2
样例输出
3 2 Tim Bill Avril
4 5 Candy Sufia Lagrange
*/
#include<bits/stdc++.h>
using namespace std;
const int nsize = 5;
struct birthday
{
	char name[20];
	int month;
	int day;
	float judge;
};
bool wqy(birthday e, birthday z)
{
	if (strlen(e.name) != strlen(z.name))
		return strlen(e.name) < strlen(z.name);
	else
		return strcmp(e.name, z.name) < 0;
}
bool wyq(birthday x, birthday y)
{
	return x.judge < y.judge;
}

int main()
{
	birthday r[180] = { 0 };
	int n = 0, index = 1, transition = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> r[i].name >> r[i].month >> r[i].day;
		r[i].judge = r[i].month + (r[i].day) / 100.0;			//100.0不然3/100结果为0
	}
	sort(r, r + n, wyq);
	for (int j = 0; j < n; j++)						
	{
		if (r[j].judge == r[j - 1].judge)
		{
			transition = j;
			index++;
			if (r[j].judge != r[j + 1].judge)
			{
				//printf("%2.f ", r[j].judge);
				//while (r[j].judge > 0)
				//{
				//	r[j].judge -= 1;
				//}
				//printf("%f ", r[j].judge * 100);
				printf("%2.d %2.d ", r[j].month, r[j].day);						//直接输出月/日

				sort(r + transition - index + 1, r + transition + 1, wqy);	//数组排序上限为r + transition + 1, 应该是sort函数的特点
				for (int l = transition - index + 1; l <= transition; l++)
				{
					cout << r[l].name << " ";
					if (l == transition)
						cout << endl;
				}
				index = 1;
			}
		}
	}
	return 0;
}

