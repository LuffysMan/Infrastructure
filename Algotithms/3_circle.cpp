/*转圈游戏
【问题描述】 n 个小伙伴(编号从 0 到 n-1)围坐一圈玩游戏。按照顺时针方向
给 n 个位置编号，从 0 到 n-1。最初，第 0 号小伙伴在第 0 号位置，第 1 号
小伙伴在第 1 号位置， ??，依此类推。
游戏规则如下：每一轮第 0 号位置上的小伙伴顺时针走到第 m 号位置，第 1 号
位置小伙伴走到第 m+1 号位置， ??，依此类推，第 n - m 号位置上的小伙伴
走到第 0 号位置，第 n-m+1 号位置上的小伙伴走到第 1 号位置， ??，第 n-1
号位置上的小伙伴顺时针走到第 m-1 号位置。
现在，一共进行了 10k 轮，请问 x 号小伙伴最后走到了第几号位置。

【输入数据】 (circle.in)
输入共 1 行，包含 4 个整数 n、 m、 k、 x，每两个整数之间用一个空格隔开。
【输出数据】 (circle.out)
输出共 1 行，包含 1 个整数，表示 10^k 轮后 x 号小伙伴所在的位置编号。
【样例输入】
10 3 4 5
【样例输出】
5
【数据说明】
对于30%的数据， 0<?<7；
对于80%的数据， 0<?<107；
对于 100%的数据， 1<?<1,000,000， 0<?<?， 1≤x≤n， 0<?<109。
*/ 
#include <iostream>
#include <cmath>
using namespace std;
#define MAXLEN 100 
typedef unsigned long long uint64;

uint64 dcf(int WS, uint64 LS);
void rightshifit(uint64& res, int& WS, uint64 LS);
uint64 calLS(uint64 m, uint64 n);
int func();

int main()
{
	while (1)
	{
		func();
	}
	return 0;
}

int func()
{
	uint64 n = 0, m = 0, k = 0, x = 0;			 
	int WS = 0;						//用到了负值,不用无符号 
	uint64 res = 0;
	uint64 LS = 0;
	int pos = 0;
	cin >> n >> m >> k >> x;
	WS = k + 1; 					//WS表示轮数的位数, 比如当k=10^7时, 轮数为10...0(1后面有10^7个0, 算上前面的1共有10^7 + 1 位) 
	LS = calLS(m, n);				//计算回到原位置的最小轮数 
	cout << "最小轮数" << LS << endl; 
	res = dcf(WS, LS); 				//计算余数(表示有效的轮数) 
	pos = (x + res * m) % n;		//x号小伙伴的最终位置
	cout << pos << endl;
	return 0;
}

//计算最小公倍数, 即转圈回到原位的最小轮数 
uint64 calLS(uint64 m, uint64 n) {
	int p = 1;
	while (p * m % n != 0) {
		p++;
	}
	return p;
}


//短除法 
uint64 dcf(int WS, uint64 LS)
{
	uint64 res = 1;
	int j = 0;
	//剩余的位数 
	while (1)
	{
		rightshifit(res, WS, LS);				//剩余需要处理的位数 
		if (WS <= 0)
		{
			res /= pow(10, 1 - WS);	//1-WS,表示多补了几个0
			break;					//不够除了, 导致res后面补零已经超了 
		}
		res %= LS;
		if (0 == res)	break;					//整除,直接退出循环 

	}
	return res;				//返回余数, 如果为0则表示整除 
}
//短除法中间步骤的余数继续除 
void rightshifit(uint64& res, int& WS, uint64 LS)			//&表示引用, 变量值可以在函数内改变, 调用结束后变量值是改变后的值 
{
	int j = 0;
	while (true)
	{
		if (res < LS)		//余数不够除, 则继续补零 
		{
			res *= 10;
			++j;
		}
		else
		{
			break;
		}
	}
	WS -= j;					//短除法商的位置,如果为0表示已经到个位了,不能 
}
