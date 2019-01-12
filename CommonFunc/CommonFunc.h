#pragma once
#include "pch.h"
#include <direct.h>

using namespace cv;
using namespace std;
//枚举指定路径下文件，c++方法
void listFiles(char* dir, vector<char*>& vecSzFilename);
//枚举指定路径下文件夹，c++方法
void listDir(char* dir, vector<char*>& vecSzDir);
//获取程序所在文件夹，c++方法
int getWorkDir(char* szProgramPath);
//用windowsAPI获取程序所在路径
int GetWorkDirWinAPI()
//获取精确时间（微秒级），可用于测试性能
double getSpecificTime();

//opencv Mat和普通uchar数组互转
cv::Mat TransBufferToMat(unsigned char* pBuffer, int nWidth, int nHeight, int nBandNum, int nBPB = 1);
int TransMatToBuffer(cv::Mat mSrc, unsigned char*& ppBuffer, int& nWidth, int& nHeight, int& nBandNum, int& nBPB, size_t& nMemSize);

//序列化一幅图像到dat文件
//#include<fstream>
int serialize(Mat src, char* filename);
int deserialize(Mat& dst, char* filename);












