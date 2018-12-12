# -*- coding:utf-8 -*-
'''
剑指offer
时间限制：1秒 空间限制：32768K 热度指数：864915
本题知识点： 查找

题目描述
在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，
判断数组中是否含有该整数。
'''
class Solution:
    # array 二维列表
    #array = [[1,2,3], [4,5,6],[7,8,9]]
    def Find(self, target, array):
        # write code here
        nRet = False
        M = len(array)
        N = len(array[0])
        for i in range(M):
            if(True == self.BiSearch(target, array[i], 0, N-1)):
                nRet = True
                break
        return nRet
    def BiSearch(self, target, array, L, H):
        #terminate
        M = int((L+H)/2)
        if(L > H):
            return False
        if(target == array[M]):
            return True
        elif(target < array[M]):
            return self.BiSearch(target, array, L, M-1) 
        else:
            return self.BiSearch(target, array, M+1, H)
    #如果二维数组按行和列严格递增可以用这个，相当于一维素组查找
    def BiSearchEx(self, target, array, L, H): 
        #terminate
        M = int((L+H)/2)
        N = len(array[0])
        i,j = self.GetIJ(M, N)
        if(L > H):
            return False
        if(target == array[i][j]):
            return True
        elif(target < array[i][j]):
            return self.BiSearch(target, array, L, M-1) 
        else:
            return self.BiSearch(target, array, M+1, H)
    def GetIJ(self, x,N):
        return int(x/N), x%N


if __name__ == "__main__":
    target, array = 5,[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
    obj = Solution()
    nRet = obj.Find(target, array)
    pass
    