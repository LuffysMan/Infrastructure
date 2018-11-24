#include "pch.h"
#include "CommonFunc.h"

void listFiles(char * dir, vector<char*>& vecSzFilename)
{
	char szDir[_MAX_PATH] = { 0 };
	sprintf_s(szDir, _MAX_PATH, "%s%s", dir, "*.*");			//±éÀúÇ°¼ÓÉÏÍ¨Åä·û
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(szDir, &findData);    // ²éÕÒÄ¿Â¼ÖÐµÄµÚÒ»¸öÎÄ¼þ
	if (handle == -1)
	{
		cout << "Failed to find first file!\n";
		return;
	}

	do
	{
		if (findData.attrib & _A_SUBDIR
			|| strcmp(findData.name, ".") == 0
			|| strcmp(findData.name, "..") == 0
			)    // ÊÇ·ñÊÇ×ÓÄ¿Â¼²¢ÇÒ²»Îª"."»ò".."
		{
			//cout << findData.name << "\t<dir>\n";
		}
		else
		{
			//cout << findData.name << "\t" << findData.size << endl;
			char* pBuffer = new char[_MAX_PATH]();
			sprintf_s(pBuffer, _MAX_PATH, "%s%s", dir, findData.name);
			vecSzFilename.push_back(pBuffer);
		}
	} while (_findnext(handle, &findData) == 0);    // ²éÕÒÄ¿Â¼ÖÐµÄÏÂÒ»¸öÎÄ¼þ

	//cout << "Done!\n";
	_findclose(handle);    // ¹Ø±ÕËÑË÷¾ä±ú
}
//Ã¶¾ÙÖ¸¶¨Â·¾¶ÏÂÎÄ¼þ¼Ð
void listDir(char * dir, vector<char*>& vecSzDir)
{
	char szDir[_MAX_PATH] = { 0 };
	sprintf_s(szDir, _MAX_PATH, "%s%s", dir, "*.*");			//±éÀúÇ°¼ÓÉÏÍ¨Åä·û
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(szDir, &findData);    // ²éÕÒÄ¿Â¼ÖÐµÄµÚÒ»¸öÎÄ¼þ
	if (handle == -1)
	{
		cout << "Failed to find first file!\n";
		return;
	}
	do
	{
		if (findData.attrib & _A_SUBDIR && 
			strcmp(findData.name, ".") != 0 &&
			strcmp(findData.name, "..") != 0)// Ö»¹Ø×¢×ÓÄ¿Â¼
		{
			cout << findData.name << "\t<dir>\n";
			char* pBuffer = new char[_MAX_PATH]();
			sprintf_s(pBuffer, _MAX_PATH, "%s%s%s", dir, findData.name, "\\");
			vecSzDir.push_back(pBuffer);
		}
		else
		{
			////cout << findData.name << "\t" << findData.size << endl;
			//char* pBuffer = new char[_MAX_PATH]();
			//sprintf_s(pBuffer, _MAX_PATH, "%s%s", dir, findData.name);
			//vecSzFilename.push_back(pBuffer);
		}
	} while (_findnext(handle, &findData) == 0);    // ²éÕÒÄ¿Â¼ÖÐµÄÏÂÒ»¸öÎÄ¼þ
	_findclose(handle);    // ¹Ø±ÕËÑË÷¾ä±ú
}

int getWorkDir(char* szProgramPath)
{
	char szPath[_MAX_PATH] = { 0 };
	char szDrive[_MAX_DRIVE] = { 0 };
	char szDir[_MAX_DIR] = { 0 };
	char szFname[_MAX_FNAME] = { 0 };
	char szExt[_MAX_EXT] = { 0 };

	GetModuleFileNameA(NULL, szPath, sizeof(szPath));
	//ZeroMemory(szProgramPath, strlen(szProgramPath));
	_splitpath_s(szPath, szDrive, szDir, szFname, szExt);
	sprintf_s(szProgramPath, _MAX_PATH, "%s%s", szDrive, szDir);

	return 0;
}

double getSpecificTime()
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	double time;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);
	Sleep(1000);
	QueryPerformanceCounter(&nEndTime);
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
	return time;
}

cv::Mat TransBufferToMat(unsigned char* pBuffer, int nWidth, int nHeight, int nBandNum, int nBPB)
{
	cv::Mat mDst;
	if (nBandNum == 4)
	{
		if (nBPB == 1)
		{
			mDst = cv::Mat::zeros(cv::Size(nWidth, nHeight), CV_8UC4);
		}
		else if (nBPB == 2)
		{
			mDst = cv::Mat::zeros(cv::Size(nWidth, nHeight), CV_16UC4);
		}
	}
	else if (nBandNum == 3)
	{
		if (nBPB == 1)
		{
			mDst = cv::Mat::zeros(cv::Size(nWidth, nHeight), CV_8UC3);
		}
		else if (nBPB == 2)
		{
			mDst = cv::Mat::zeros(cv::Size(nWidth, nHeight), CV_16UC3);
		}
	}
	else if (nBandNum == 1)
	{
		if (nBPB == 1)
		{
			mDst = cv::Mat::zeros(cv::Size(nWidth, nHeight), CV_8UC1);
		}
		else if (nBPB == 2)
		{
			mDst = cv::Mat::zeros(cv::Size(nWidth, nHeight), CV_16UC1);
		}
	}

	for (int j = 0; j < nHeight; ++j)
	{
		unsigned char* data = mDst.ptr<unsigned char>(j);
		//unsigned char* pSubBuffer = pBuffer + (nHeight - 1 - j) * nWidth * nBandNum * nBPB;		//{modified by yuecui 2018/11/21
		unsigned char* pSubBuffer = pBuffer + j * nWidth * nBandNum * nBPB;			//}end modify yuecui 2018/11/21
		memcpy(data, pSubBuffer, nWidth * nBandNum * nBPB);
	}
	if (nBandNum == 1)
	{
		cv::cvtColor(mDst, mDst, CV_GRAY2BGR);
	}
	else if (nBandNum == 3)
	{
		cv::cvtColor(mDst, mDst, CV_RGB2BGR);
	}
	else if (nBandNum == 4)
	{
		cv::cvtColor(mDst, mDst, CV_RGBA2BGR);
	}

	return mDst;
}

int TransMatToBuffer(cv::Mat mSrc, unsigned char*& ppBuffer, int& nWidth, int& nHeight, int& nBandNum, int& nBPB, size_t& nMemSize)
{
	if (ppBuffer)
	{
		delete[] ppBuffer;
		ppBuffer = nullptr;
	}

	nWidth = mSrc.cols;
	//nWidth = ((nWidth + 3) / 4) * 4;
	nHeight = mSrc.rows;
	nBandNum = mSrc.channels();
	nBPB = (mSrc.depth() >> 1) + 1;

	//size_t nMemSize = nWidth * nHeight * nBandNum * nBPB;				// {modified by yue.cui 2018/11/21
	nMemSize = nWidth * nHeight * nBandNum * nBPB;						// }end modify 2018/11/21
	//ÕâÑù¿ÉÒÔ¸Ä±äÍâ²¿*pBufferµÄÖµ
	ppBuffer = new uchar[nMemSize];
	memset(ppBuffer, 0, nMemSize);
	uchar* pT = ppBuffer;
	for (int j = 0; j < nHeight; ++j)
	{
		unsigned char* data = mSrc.ptr<unsigned char>(j);
		unsigned char* pSubBuffer = ppBuffer + (j)* nWidth * nBandNum * nBPB;
		memcpy(pSubBuffer, data, nWidth * nBandNum * nBPB);
	}

	return 0;
}

//用windowsAPI获取程序所在路径
int GetWorkDirWinAPI()
{
    //用于存储当前路径
    CHAR szCurrentDirectory[MAX_PATH];
    //用于存储模块路径
    CHAR szMoudlePath[MAX_PATH];
    //Kernel32文件名与句柄
    LPSTR szKernel32="kernel32.dll";
    HMODULE hKernel32;
    //当前路径长度，也用于判断是否获取成功
    DWORD dwCurDirPathLen;
    //获取进程当前目录
    dwCurDirPathLen=
        GetCurrentDirectoryA(MAX_PATH,szCurrentDirectory);
    if(dwCurDirPathLen==0)
    {
        printf("获取当前目录错误。\n");
        return 0;
    }
    printf("进程当前目录为 %s \n",szCurrentDirectory);

    //将进程当前目录设为"D:\"
    lstrcpyA(szCurrentDirectory,"D:\\");
    if(!SetCurrentDirectoryA(szCurrentDirectory))
    {
        printf("获取当前目录错误。\n");
        return 0;
    }
    printf("已设置当前目录为 %s \n",szCurrentDirectory);

    //在当前目录下创建子目录"current_dir"
    //运行完后D:盘下将出现"current_dir"文件夹
    CreateDirectoryA("current_dir",NULL);

    //再次获取系统当前目录
    dwCurDirPathLen=
        GetCurrentDirectoryA(MAX_PATH,szCurrentDirectory);
    if(dwCurDirPathLen==0)
    {
        printf("获取当前目录错误。\n");
        return 0;
    }
    printf("GetCurrentDirectoryA获取当前目录为 %s \n",szCurrentDirectory);

    //使用NULL参数，获取本模块路径
    if(!GetModuleFileNameA(NULL,szMoudlePath,MAX_PATH))
    {
        printf("获取模块路径错误。\n");
        return 0;
    }
    printf("本模块路径 %s \n",szMoudlePath);

    //获取Kernel32.dll的模块句柄
    hKernel32=LoadLibraryA(szKernel32);

    //使用Kernel32.dll的句柄模块，获取其路径
    if(!GetModuleFileNameA(hKernel32,szMoudlePath,MAX_PATH))
    {
        printf("获取模块路径错误。\n");
        return 0;
    }
    printf("kernel32模块路径 %s \n",szMoudlePath);

    return 0;
}