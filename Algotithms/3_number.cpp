/*
3�������(number.c/cpp)
������������
Ԫ����ᵽ�ˣ�������Ҫ��֯һ����ᣬ��֪������ n ��ѧ����ÿ��ѧ����
��Ҫһ����һ�޶��ĺ��룬��ʦΪ���չ�ÿ��ѧ����ϲ�ã�������Ҫÿ��ѧ����
��һ���Լ�ϲ���ĺ��������(����������� 1 ��ʼ������С a �ṩ������Ϊ
�� 1 �� x���� 1 �� x ֮�������������ΪС a �ĺ���)�����ڣ�ÿλͬѧ������
������ϲ������������ֵ����ʦ��֪��������������е�ѧ����һ�������ֱ�
�ŵķ�����
������ֿ��ܻ�ܴ���ˣ���ֻ������� mod 1000000007 ���ɡ����
���ǲ����ܵģ������ 0.
�������ʽ��
��һ�� ��һ������ n (1��n��50)
�ڶ��� �� n ����������ʾÿλͬѧ��Ҫ�ĺ�������ֵ�� (1��ֵ��1000)
�������ʽ��
һ��������
���������롿
2
5 8
�����������
35
���������͡���һ��ѧ��ϲ�� 1 �� 5 ���е����֣���������ֿ��ܣ����ڶ���ѧ
��ϲ�� 1 �� 8 ���е����֣���ȥ��һ��ѧ���Ѿ��õ��ģ���ʣ 7 �ֱ�ţ���˹�
5*7=35 �֡�
*/
#include<bits/stdc++.h>
#include<assert.h>
using namespace std;
typedef long long int64;

/*
�������� 
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
		//����
		Qsort(nums, 0, n-1);
		for(int i = 0; i < n; ++i)
		{
			cout << nums[i] << ' ';
		}
		cout << endl;
		//����	
		int64 res = 1;
		for(int i = 0; i < n; ++i)			//(a * b) % p = (a % p * b % p) % p 
		{
			res *= (1000-i);
			res %= MAX;
			cout << res << endl;
		}
	}
	delete[] nums;			//�ͷ��ڴ� 
} 

void Qsort(int64 array[], int left, int right)
{
    assert(array);
    if(left >= right)//��ʾ�Ѿ����һ����
    {
        return;
    }
    int index = partion(array,left,right);//�����λ��
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





