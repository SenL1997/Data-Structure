#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

int maxSubsequenceSum1(int a[], int size, int &start, int &end);
int maxSubsequenceSum2(int a[], int size,int &start, int &end);
int maxSubsequenceSum3(int a[], int size,int &start, int &end);

int main()
{
    int start,end,i,pNum=0,zNum=0,nNum=0;

    int a[100],b[1000],c[10000];
    for (i=0;i<100;i++)
    {
        a[i]=-rand()%51+25;
        //a[i]=rand()%51;
        //a[i]=-rand()%51;
    }
    for (i=0;i<1000;i++)
    {
        b[i]=-rand()%51+25;
        //b[i]=rand()%51;
        //b[i]=-rand()%51;
    }
    for (i=0;i<10000;i++)
    {
        c[i]=-rand()%51+25;
        //c[i]=rand()%51;
        //c[i]=-rand()%51;
    }
    clock_t begin,finish;
    double totalTime11,totalTime12,totalTime13;
    double totalTime21,totalTime22,totalTime23;
    double totalTime31,totalTime32,totalTime33;

    LARGE_INTEGER m_liPerfFreq = {0};
	//获取每秒多少CPU Performance Tick
	QueryPerformanceFrequency(&m_liPerfFreq);

	LARGE_INTEGER m_liPerfStart11 = {0};
	QueryPerformanceCounter(&m_liPerfStart11);
	maxSubsequenceSum1(a,100,start,end);
	LARGE_INTEGER liPerfNow11 = {0};
	// 计算CPU运行到现在的时间
	QueryPerformanceCounter(&liPerfNow11);
	totalTime11 = (((liPerfNow11.QuadPart - m_liPerfStart11.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
    cout << "Time(maxSubsequenceSum1,100): \t" << totalTime11 <<" microseconds"<<endl;

	LARGE_INTEGER m_liPerfStart12 = {0};
	QueryPerformanceCounter(&m_liPerfStart12);
	maxSubsequenceSum1(b,1000,start,end);
	LARGE_INTEGER liPerfNow12 = {0};
	QueryPerformanceCounter(&liPerfNow12);
	totalTime12 = (((liPerfNow12.QuadPart - m_liPerfStart12.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum1,1000): \t" << totalTime12 <<" microseconds"<<endl;

	LARGE_INTEGER m_liPerfStart13 = {0};
	QueryPerformanceCounter(&m_liPerfStart13);
	maxSubsequenceSum1(c,10000,start,end);
	LARGE_INTEGER liPerfNow13 = {0};
	QueryPerformanceCounter(&liPerfNow13);
	totalTime13 = (((liPerfNow13.QuadPart - m_liPerfStart13.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum1,10000): " << totalTime13 <<" microseconds"<<endl;


	LARGE_INTEGER m_liPerfStart21 = {0};
	QueryPerformanceCounter(&m_liPerfStart21);
	maxSubsequenceSum2(a,100,start,end);
	LARGE_INTEGER liPerfNow21 = {0};
	QueryPerformanceCounter(&liPerfNow21);
	totalTime21 = (((liPerfNow21.QuadPart - m_liPerfStart21.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum2,100): \t" << totalTime21 <<" microseconds"<<endl;

	LARGE_INTEGER m_liPerfStart22 = {0};
	QueryPerformanceCounter(&m_liPerfStart22);
	maxSubsequenceSum2(b,1000,start,end);
	LARGE_INTEGER liPerfNow22 = {0};
	QueryPerformanceCounter(&liPerfNow22);
	totalTime22 = (((liPerfNow22.QuadPart - m_liPerfStart22.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum2,1000): \t" << totalTime22 <<" microseconds"<<endl;

	LARGE_INTEGER m_liPerfStart23 = {0};
	QueryPerformanceCounter(&m_liPerfStart23);
	maxSubsequenceSum2(c,10000,start,end);
	LARGE_INTEGER liPerfNow23 = {0};
	QueryPerformanceCounter(&liPerfNow23);
	totalTime23 = (((liPerfNow23.QuadPart - m_liPerfStart23.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum2,10000): " << totalTime23 <<" microseconds"<<endl;


	LARGE_INTEGER m_liPerfStart31 = {0};
	QueryPerformanceCounter(&m_liPerfStart31);
	maxSubsequenceSum3(a,100,start,end);
	LARGE_INTEGER liPerfNow31 = {0};
	QueryPerformanceCounter(&liPerfNow31);
	totalTime31 = (((liPerfNow31.QuadPart - m_liPerfStart31.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum3,100): \t" << totalTime31 <<" microseconds"<<endl;

	LARGE_INTEGER m_liPerfStart32 = {0};
	QueryPerformanceCounter(&m_liPerfStart32);
	maxSubsequenceSum3(b,1000,start,end);
	LARGE_INTEGER liPerfNow32 = {0};
	QueryPerformanceCounter(&liPerfNow32);
	totalTime32 = (((liPerfNow32.QuadPart - m_liPerfStart32.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum3,1000): \t" << totalTime32 <<" microseconds"<<endl;

	LARGE_INTEGER m_liPerfStart33 = {0};
	QueryPerformanceCounter(&m_liPerfStart33);
	maxSubsequenceSum3(c,10000,start,end);
	LARGE_INTEGER liPerfNow33 = {0};
	QueryPerformanceCounter(&liPerfNow33);
	totalTime33 = (((liPerfNow33.QuadPart - m_liPerfStart33.QuadPart) * 1000000) / m_liPerfFreq.QuadPart);
	cout << "Time(maxSubsequenceSum3,10000): " << totalTime33 <<" microseconds"<<endl;

	for (i=0;i<100;i++)
	{
	    if (a[i]>0) pNum++;
	    else if (a[i]==0) zNum++;
	    else nNum++;
	    //cout << a[i]<<" ";
	}
    cout << "\na[]: " << pNum <<" positive numbers,"<<zNum<<" zeros and "<<nNum<<" negative numbers"<<endl;
    pNum=0;zNum=0;nNum=0;
    for (i=0;i<1000;i++)
	{
	    if (b[i]>0) pNum++;
	    else if (b[i]==0) zNum++;
	    else nNum++;
	    //cout << b[i]<<" ";
	}
    cout << "\nb[]: " << pNum <<" positive numbers,"<<zNum<<" zeros and "<<nNum<<" negative numbers"<<endl;
    pNum=0;zNum=0;nNum=0;
    for (i=0;i<10000;i++)
	{
	    if (c[i]>0) pNum++;
	    else if (c[i]==0) zNum++;
	    else nNum++;
	    //cout << c[i]<<" ";
	}
    cout << "\nc[]: " << pNum <<" positive numbers,"<<zNum<<" zeros and "<<nNum<<" negative numbers"<<endl;

    return 0;
}

int maxSubsequenceSum1(int a[], int size, int &start, int &end)
{
    int maxSum=0;
    for (int i=0;i<size;i++)
        for (int j=i;j<size;j++)
        {
            int thisSum=0;
            for (int k=i;k<=j;k++)
                thisSum+=a[k];
            if(thisSum>maxSum)
            {
                maxSum=thisSum;
                start = i;
                end = j;
            }
        }
    return maxSum;
}

int maxSubsequenceSum2(int a[],int size,int &start, int &end)
{
    int maxSum = 0;
    for (int i=0;i<size;i++)
    {
        int thisSum = 0;
        for (int j=i;j<size;j++)
        {
            thisSum+=a[j];
            if (thisSum > maxSum)
            {
                maxSum=thisSum;
                start = i;
                end = j;
            }
        }
    }
    return maxSum;
}

int maxSubsequenceSum3(int a[],int size,int &start, int &end)
{
    int maxSum=0, thisSum = 0,startTmp = 0;
    start = end = 0;
    for(int j=0;j<size;j++)
    {
        thisSum+=a[j];
        if(thisSum<0)
            thisSum=0;
        else if (thisSum==a[j])
            startTmp=j;
        if (thisSum>maxSum)
        {
            maxSum=thisSum;start=startTmp;end=j;
        }
    }
    return maxSum;
}
