/*
4���� N ��������(huiwen.cpp)
���������������������������������ң��ʹ��Ҷ�������һ���ġ�����
121,1221 ���ǻ������������������ N ��������.
���������ݡ� (huiwen.in)
�����ж������ݣ�ÿ��һ�������������������� 0 ��ʾ����
��������ݡ� (huiwen.out)
ÿ��һ��������ʾ�� N ��������
���������롿
1
12
24
0
�����������
1
33
151
�����ݷ�Χ��
1��N��2000000000
*/

#include<bits/stdc++.h>
typedef	unsigned long long uint64;
using namespace std;
uint64 find(int index) {
        uint64 count = 0;            
        uint64 number = 9;                        //��¼��λ�ϵĻ����������λ������Ϊ9
        uint64 w = 0;                            //��¼��λ       
        uint64 half;                            //��������������ߵĽ��
        uint64 h = 1;                            //�����������ߵ���ʼ����
        uint64 res;                            //���
        
        while(true) {
            if(w > 0 && w%2 == 0) {            //ÿ��������λ������������10
                number *= 10;
            }
            w++;                            //��λ��һ
            if(count + number > index)        //���������ڲ��ҵĻ���,����
                break;
                
            count += number;                //���������ϵ�ǰ��λ�ϵĻ�����
        }
        
        index -= count;                        //�ڵ�ǰ��λ�ϵ�λ�á���w=5,index=50,����λ�ϵĵ�50������������������
        
        for(int i = 0; i < (w-1) / 2; i++) {    //������������ߵĻ����������������λ�ϣ���Ϊ100
            h *= 10;
        }
        
        half = h + index - 1;                        //�����������ߣ���100 + 50 = 150
        
        res = half;
        
        if(w%2 != 0)                            //���Ϊ���������м��Ǹ������������Ұ���ˣ�
            half /=10;

        while(half != 0) {                        //ƴ�ӻ�����
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
