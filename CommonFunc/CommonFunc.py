'''''''''''''''''''<写文件begin>'''''''''''''''''''''
#encoding=utf-8
import csv
import codecs
import xlwt
#将数组保存为Txt
def text_save(filename, data):#filename为写入CSV文件的路径，data为要写入数据列表.
    file = open(filename,'a')
    for i in range(len(data)):
        s = str(data[i]).replace('[','').replace(']','')#去除[],这两行按数据不同，可以选择
        s = s.replace("'",'').replace(',','') +'\n'   #去除单引号，逗号，每行末尾追加换行符
        file.write(s)
    file.close()
    print("保存文件成功") 

#将数据保存为csv
def data_write_csv(file_name, datas):#file_name为写入CSV文件的路径，datas为要写入数据列表
    file_csv = codecs.open(file_name,'w+','utf-8')#追加
    writer = csv.writer(file_csv, delimiter=' ', quotechar=' ', quoting=csv.QUOTE_MINIMAL)
    for data in datas:
        writer.writerow(data)
    print("保存文件成功，处理结束")

#将数据保存为excel
#  将数据写入新文件
def data_write(file_path, datas):
    f = xlwt.Workbook()
    sheet1 = f.add_sheet(u'sheet1',cell_overwrite_ok=True) #创建sheet
    
    #将数据写入第 i 行，第 j 列
    i = 0
    for data in datas:
        for j in range(len(data)):
            sheet1.write(i,j,data[j])
        i = i + 1
        
    f.save(file_path) #保存文件
'''''''''''''''''''<写文件end>'''''''''''''''''''''


''''''''''''''''''''''''<读文件begin>''''''''''''''''''''
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
'''''''''''''''''''''<读文件begin>'''''''''''''''''''''''''



















