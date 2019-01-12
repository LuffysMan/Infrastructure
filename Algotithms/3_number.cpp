/*
3、编号码(number.c/cpp)
【问题描述】
元旦晚会到了，竞赛班要组织一场晚会，已知班里有 n 个学生，每个学生都
需要一个独一无二的号码，老师为了照顾每个学生的喜好，现在需要每个学生提
供一个自己喜欢的号码的区间(这个区间必须从 1 开始，比如小 a 提供的区间为
从 1 到 x，即 1 到 x 之间的数都可以作为小 a 的号码)。现在，每位同学都给出
了他们喜欢的区间的最大值，老师想知道，如果满足所有的学生，一共多少种编
号的方法。
这个数字可能会很大，因此，你只用输出答案 mod 1000000007 即可。如果
这是不可能的，就输出 0.
【输入格式】
第一行 是一个整数 n (1≤n≤50)
第二行 是 n 个整数，表示每位同学想要的号码的最大值。 (1≤值≤1000)
【输出格式】
一个整数。
【样例输入】
2
5 8
【样例输出】
35
【样例解释】第一个学生喜欢 1 到 5 所有的数字，因此有五种可能，而第二个学
生喜欢 1 到 8 所有的数字，除去第一个学生已经用到的，还剩 7 种编号，因此共
5*7=35 种。
*/
#include<bits/stdc++.h>
#include<assert.h>
using namespace std;
typedef long long int64;

/*
快速排序 
*/
void Qsort(int64 arr[], int L, int H);
int partion(int64 arr[], int L, int H);

int main()
{
	int MAX = 1000000007;
	int64 n;
	int64* nums = new int64[n];
//	while(true)
	{
		cin >> n;

		for(int i = 0; i<n; i++){
			cin >> nums[i];
			cout << nums[i] << ' ';
		}
		cout << endl;
		//排序
		Qsort(nums, 0, n-1);
		for(int i = 0; i < n; ++i)
		{
			cout << nums[i] << ' ';
		}
		cout << endl;
		//连乘	
		int64 res = 1;
		for(int i = 0; i < n; ++i)			//(a * b) % p = (a % p * b % p) % p 
		{
			res *= (1000-i);
			res %= MAX;
			cout << res << endl;
		}
	}
	delete[] nums;			//释放内存 
} 

void Qsort(int64 array[], int left, int right)
{
    assert(array);
    if(left >= right)//表示已经完成一个组
    {
        return;
    }
    int index = partion(array,left,right);//枢轴的位置
    Qsort(array,left,index - 1);
    Qsort(array,index + 1,right);
}

int partion(int64* array,int left,int right)
{
    int64& key = array[right];
    while(left < right)
    {
        while(left < right && array[left] <= key)
        {
            ++left;
        }
        while(left < right && array[right] >= key)
        {
            --right;
        }
        swap(array[left],array[right]);
    }
    swap(array[left],key);
    return left;
}





