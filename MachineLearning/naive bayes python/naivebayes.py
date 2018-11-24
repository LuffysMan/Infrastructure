#coding:utf-8
# 极大似然估计  朴素贝叶斯算法
import pandas as pd
import numpy as np

class NaiveBayes(object):
    def getTrainSet(self):
        dataSet = pd.read_csv('.//career_data_quantitive.csv')
        dataSetNP = np.array(dataSet)  #将数据由dataframe类型转换为数组类型
        trainData = dataSetNP[:,0:dataSetNP.shape[1]-1]   #训练数据x1,x2,x3
        labels = dataSetNP[:,dataSetNP.shape[1]-1]        #训练数据所对应的所属类型Y
        return trainData, labels
    
    def crossDevide(self, arrTrainDataOri, arrLabelsOri, index):
        lstTrainData = arrTrainDataOri.tolist()
        lstLabels = arrLabelsOri.tolist()
        retFeatures = arrTrainDataOri[index]
        del lstTrainData[index]
        del lstLabels[index]
        retTrainData = np.array(lstTrainData)
        retLabels = np.array(lstLabels)
        return retTrainData, retLabels, retFeatures

    def classify(self, trainData, labels, features):
        #求labels中每个label的先验概率
        labels = list(labels)    #转换为list类型
        P_y = {}       #存入label的概率
        for label in labels:
            P_y[label] = labels.count(label)/float(len(labels))   # p = count(y) / count(Y)

        #求label与feature同时发生的概率
        P_xy = {}
        for y in P_y.keys():
            y_index = [i for i, label in enumerate(labels) if label == y]  # labels中出现y值的所有数值的下标索引
            for j in range(len(features)):      # features[0] 在trainData[:,0]中出现的值的所有下标索引
                x_index = [i for i, feature in enumerate(trainData[:,j]) if feature == features[j]]
                xy_count = len(set(x_index) & set(y_index))   # set(x_index)&set(y_index)列出两个表相同的元素
                pkey = str(features[j]) + '*' + str(y)
                P_xy[pkey] = xy_count / float(len(labels))

        #求条件概率
        P = {}
        for y in P_y.keys():
            for x in features:
                pkey = str(x) + '|' + str(y)
                P[pkey] = P_xy[str(x)+'*'+str(y)] / float(P_y[y])    #P[X1/Y] = P[X1Y]/P[Y]

        #求[2,'S']所属类别
        F = {}   #[2,'S']属于各个类别的概率
        for y in P_y:
            F[y] = P_y[y]
            for x in features:
                F[y] = F[y]*P[str(x)+'|'+str(y)]     #P[y/X] = P[X/y]*P[y]/P[X]，分母相等，比较分子即可，所以有F=P[X/y]*P[y]=P[x1/Y]*P[x2/Y]*P[y]

        features_label = max(F, key=F.get)  #概率最大值对应的类别
        return features_label
    
    def getRightCount(self, arrLabelsOri, arrLabelsOutput):
        retRightCount = 0
        for i in range(len(arrLabelsOri)):
            if arrLabelsOri[i] == arrLabelsOutput[i]:
                retRightCount = retRightCount + 1 
        return retRightCount
    
    def getAccuracy(self, arrLabelsOri, arrLabelsOutput):
        nRightCount = self.getRightCount(arrLabelsOri, arrLabelsOutput)
        nLen = len(arrLabelsOutput)
        retAccuracy = float(nRightCount)/nLen
        return retAccuracy

if __name__ == '__main__':
    nb = NaiveBayes()
    lstLabelsClsfd = []
    # 训练数据
    arrTrainDataOri, arrLabelsOri = nb.getTrainSet()
    #print arrTrainDataOri,'\n',arrLabelsOri
    for i in range(len(arrTrainDataOri)): 
        #划分训练集合测试集
        arrTrainData, arrLabels, arrFeatures = nb.crossDevide(arrTrainDataOri, arrLabelsOri, i)
        #测试
        result = nb.classify(arrTrainData, arrLabels, arrFeatures) # 该特征应属于哪一类
        print arrFeatures,' belongs to ', result,'\n'
        lstLabelsClsfd.append(result)
    #输出错误数量和模型准确度
    arrLabelsClsfd = np.array(lstLabelsClsfd)
    nWrong = len(arrLabelsOri) - nb.getRightCount(arrLabelsOri, arrLabelsClsfd)
    fAccuracy = nb.getAccuracy(arrLabelsOri, arrLabelsClsfd)
    arrWrongAndAccuracy = [[-1 for i in range(2)] for i in range(10)]
    arrWrongAndAccuracy[0][0] = nWrong
    arrWrongAndAccuracy[0][1] = fAccuracy
    print 'wrong count:', nWrong,'\n', 'accuracy:', fAccuracy, '\n'
    print 'the result has been saved in "result.csv"\n'
    #将结果输出到csv
    arrOutputCsv = np.hstack((arrTrainDataOri, arrLabelsOri.reshape(-1,1),arrLabelsClsfd.reshape(-1,1), arrWrongAndAccuracy))
    df = pd.DataFrame(arrOutputCsv, columns=['985', 'degree', 'skill', 'enroll', 'enroll_predict', 'wrongCount', 'accuracy'])
    df.to_csv('.//result.csv', index = False, sep = ',')
	
	
	
	
	
	
	
	
	
	
	
	
