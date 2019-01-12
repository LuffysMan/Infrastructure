#cifar压缩文件提取
import matplotlib.pyplot as plt
import numpy as np
import gzip as gz
import pickle

def unpickle(file):
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

dict = unpickle("E:\\cuiyue\\PyProjects\\test\\data_batch_1")
lstData = []
for k in dict:
    print(k)
    lstData.append(dict.get(k))
# 定义图像数据
#a = np.linspace(0, 1, 9).reshape(3, 3)
imageAll = lstData[2]
image1=imageAll[2]
L = 1024
image1R = image1[0:L].reshape(32,32)
image1G = image1[L:2*L].reshape(32,32)
image1B = image1[2*L:3*L].reshape(32,32)
# 显示图像数据
plt.imshow(image1B, interpolation = 'nearest', cmap = 'bone', origin = 'lower')
# 添加颜色条
plt.colorbar()
# 去掉坐标轴
plt.xticks(())
plt.yticks(())
plt.show()
