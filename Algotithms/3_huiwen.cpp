/*
4、第 N 个回文数(huiwen.cpp)
【问题描述】回文数，就是你从左读到右，和从右读到左，是一样的。例如
121,1221 都是回文数。现在请输出第 N 个回文数.
【输入数据】 (huiwen.in)
输入有多组数据，每行一个数。整个测试以数字 0 表示结束
【输出数据】 (huiwen.out)
每行一个数，表示第 N 个回文数
【样例输入】
1
12
24
0
【样例输出】
1
33
151
【数据范围】
1≤N≤2000000000
*/

#include<bits/stdc++.h>
typedef	unsigned long long uint64;
using namespace std;
uint64 find(int index) {
        uint64 count = 0;            
        uint64 number = 9;                        //记录数位上的回文数，如个位回文数为9
        uint64 w = 0;                            //记录数位       
        uint64 half;                            //保存回文数的左半边的结果
        uint64 h = 1;                            //回文数的左半边的起始基数
        uint64 res;                            //结果
        
        while(true) {
            if(w > 0 && w%2 == 0) {            //每进两个数位，回文数乘以10
                number *= 10;
            }
            w++;                            //数位加一
            if(count + number > index)        //回文数大于查找的回数,跳出
                break;
                
            count += number;                //回文数加上当前数位上的回文数
        }
        
        index -= count;                        //在当前数位上的位置。如w=5,index=50,则万位上的第50个回文数是我们所求
        
        for(int i = 0; i < (w-1) / 2; i++) {    //求回文数的左半边的基数，如回文数在万位上，则为100
            h *= 10;
        }
        
        half = h + index - 1;                        //回文数的左半边，如100 + 50 = 150
        
        res = half;
        
        if(w%2 != 0)                            //如果为奇数，则中间那个数不必算入右半边了！
            half /=10;

        while(half != 0) {                        //拼接回文数
            res = res *10 + half % 10;
            half /= 10;
        }

        return res;
    }
    
    
int main()
{
	while(1)
	{
		long index;
		cin >> index;
		uint64 num = find(index);
		cout << num <<endl;
	}
	return 0;
 } 
