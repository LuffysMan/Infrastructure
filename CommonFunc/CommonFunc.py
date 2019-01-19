'''''''''''''''''''<XXX begin>'''''''''''''''''''''
'''''''''''''''''''<XXX end>'''''''''''''''''''''
'''''''''''''''''''<打印函数 begin>'''''''''''''''''''''
import datetime
def myPrint(content):
	strTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
	print(strTime+"->"+content)
def getTime():
    strTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    return strTime
'''''''''''''''''''<打印函数 end>'''''''''''''''''''''

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

'''''''''''''''''''<读文件begin>'''''''''''''''''''''
import random
import struct
import numpy as np
import pandas as pd

def Get_Data_CLass1():
    f = open('data_class1.txt', 'rb')
    f.seek(0,0)

    res=np.zeros([1024,8])

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

    res=np.zeros([1024,8])

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


'''''''''''''''''''<灰度3D图 begin>'''''''''''''''''''''
# -*- coding: utf-8 -*-
import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter

fig = plt.figure(figsize=(16,12))
ax = fig.gca(projection="3d")

img = cv.imread("E:\\cuiyue\\C_Digital Image Processing\\segment\\D.jpg")     # 修改图片位置
img = cv.cvtColor(img, cv.COLOR_RGB2GRAY)
imgd = np.array(img)      # image类 转 numpy

# 准备数据
sp = img.shape
h = int(sp[0])#height(rows) of image
w = int(sp[1])#width(colums) of image

x = np.arange(0,w,1)
y = np.arange(0,h,1)
x,y = np.meshgrid(x,y)
z = imgd
surf = ax.plot_surface(x, y, z, cmap=cm.coolwarm)
#surf = ax.plot_surface(x, y, z, cmap=cm.coolwarm)  # cmap指color map

# 自定义z轴
ax.set_zlim(-10, 255)
ax.zaxis.set_major_locator(LinearLocator(10))  # z轴网格线的疏密，刻度的疏密，20表示刻度的个数
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))  # 将z的value字符串转为float，保留2位小数

# 设置坐标轴的label和标题
ax.set_xlabel('x', size=15)
ax.set_ylabel('y', size=15)
ax.set_zlabel('z', size=15)
ax.set_title("Surface plot", weight='bold', size=20)

# 添加右侧的色卡条
fig.colorbar(surf, shrink=0.6, aspect=8)  # shrink表示整体收缩比例，aspect仅对bar的宽度有影响，aspect值越大，bar越窄
plt.show()
'''''''''''''''''''<灰度3D图 begin>'''''''''''''''''''''


















