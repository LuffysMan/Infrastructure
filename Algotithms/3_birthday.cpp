/*
04:������ͬ 2.0
�鿴
�ύ
ͳ��
����
��ʱ������:?1000ms?�ڴ�����:?65536kB������һ����180�˵Ĵ�༶�У�����������������ͬ�ĸ��ʷǳ����ָ���ÿ��ѧ�������֣��������ա����ҳ�����������ͬ��ѧ����

�����һ��Ϊ����n����ʾ��n��ѧ����n �� 180���˺�ÿ�а���һ���ַ����������������ֱ��ʾѧ�������֣����ֵ�һ����ĸ��д������Сд��
�����ո��ҳ���С��20���ͳ�����(1 �� m �� 12)��(1 �� d �� 31)�����֡��¡���֮����һ���ո�ָ����ÿ��������ͬ��ѧ�������һ�У�
����ǰ�������ֱ�ʾ�º��գ�������������ڵ��������ѧ�������֣����֡�����֮�䶼��һ���ո�ָ��������е������Ҫ�����ڴ�ǰ��
���˳������� ��������ͬ�����֣������ִӶ̵������������������ͬ�İ��ֵ����������û��������ͬ��ѧ���������None��
��������6
Avril 3 2
Candy 4 5
Tim 3 2
Sufia 4 5
Lagrange 4 5
Bill 3 2
�������
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
		r[i].judge = r[i].month + (r[i].day) / 100.0;			//100.0��Ȼ3/100���Ϊ0
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
				printf("%2.d %2.d ", r[j].month, r[j].day);						//ֱ�������/��

				sort(r + transition - index + 1, r + transition + 1, wqy);	//������������Ϊr + transition + 1, Ӧ����sort�������ص�
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

