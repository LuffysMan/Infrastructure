#coding=utf-8
import random
import struct
import numpy as np
import pandas as pd

def Get_Data_CLass1():
    f = open('data_class1.txt', 'rb')
    f.seek(0,0)

    res=numpy.zeros([1024,8])

    for i in range(0,1024):
        for j in range (0,8):
            bytes=f.read(4)
            fvalue,=struct.unpack("f",bytes)
            res[i][j]=fvalue
    print(res.shape)
    return res
def Get_Data_CLass2():
    f = open('data_class2.txt', 'rb')
    f.seek(0,0)

    res=numpy.zeros([1024,8])

    for i in range(0,1024):
        for j in range (0,8):
            bytes=f.read(4)
            fvalue,=struct.unpack("f",bytes)
            res[i][j]=fvalue
    print(res.shape)
    return res
#读csv文件
def getTrainSet_csv(filepath):
    dataSet = pd.read_csv(filepath)
    dataSetNP = np.array(dataSet)  #将数据由dataframe类型转换为数组类型
    trainData = dataSetNP[:,0:dataSetNP.shape[1]-1]   #训练数据x1,x2,x3
    labels = dataSetNP[:,dataSetNP.shape[1]-1]        #训练数据所对应的所属类型Y
    return trainData, labels
