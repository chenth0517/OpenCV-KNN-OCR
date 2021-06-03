#include "preprocessing.h"

#include <ctype.h>
#include <math.h>

///���ɷ�����ֵ///
int otsu(const IplImage *frame)
{
	///frame�Ҷȼ�///
	const int GrayScale=256;///�Ҷȼ���///
	int width=frame->width;
	int	height=frame->height;
	int pixelCount[GrayScale]={0};
	float pixelPro[GrayScale]={0};
	int i, j, pixelSum = width * height, threshold = 0;
	uchar* data = (uchar*)frame->imageData;
	float w0, w1, u0tmp, u1tmp, u0, u1, deltaTmp, deltaMax = 0;
	///ͳ��ÿ���Ҷȼ������صĸ���///
	for(i = 0; i < height; i++)
	{
		for(j = 0;j < width;j++)
		{
			pixelCount[(int)data[i * width + j]]++;
		}
	}
	///����ÿ���Ҷȼ���������Ŀռ����ͼ��ı���///
	for(i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / pixelSum;
	}
	///�����Ҷȼ�[0,255],Ѱ�Һ��ʵ�threshold///
	for(i = 0; i < GrayScale; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = deltaTmp = 0;
		for(j = 0; j < GrayScale; j++)
		{
			if(j <= i)   ///��������///
			{
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else   ///ǰ������///
			{
				w1 += pixelPro[j];
				u1tmp += j * pixelPro[j];
			}
		}
		u0 = u0tmp / w0;
		u1 = u1tmp / w1;
		deltaTmp = (float)(w0 *w1* pow((u0 - u1), 2)) ;
		if(deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	return threshold;
}

IplImage threshold(IplImage* imgGray)
{
	IplImage* imgTh=cvCreateImage(cvSize(PIC_WIDTH,PIC_HEIGHT),IPL_DEPTH_8U,1);  ///��ֵͼ��///

	//cvNamedWindow("1.Original Picture", CV_WINDOW_AUTOSIZE);
	//cvShowImage("1.Original Picture", imgGray);
	//cvWaitKey(5000);
	
	cvNormalize(imgGray, imgTh, 255, 0, CV_MINMAX);

	///��ʾ�д������///
	//cvNamedWindow("2.Bin Picture",1); 
	//cvMoveWindow("2.Bin Picture",800,0);
	//cvShowImage("2.Bin Picture",imgTh);

	///��ֵ��///
	int threshold = otsu(imgTh);///���ݴ��ɷ�ȷ����ֵ///
	cvThreshold( imgTh, imgTh, threshold, 255, CV_THRESH_BINARY_INV );

	CvMat data;
	int val=0;///��ǰͼ���а�ɫ֮��///
	int maxVal = imgTh->height * imgTh->width * 255;///ȫ��ͼ���а�ɫ֮��///
	for (int i=0; i< imgTh->width; i++)
	{
		cvGetCol(imgTh, &data, i);
		val += cvSum(&data).val[0];
	}
	if (val>=maxVal/2)///˵����ǰ��ֵ��ͼ���а�ɫ�Ӷ࣬���¶�ֵ��///
	{
		cvThreshold( imgTh, imgTh, threshold, 255, CV_THRESH_BINARY_INV );
	}

	///��ʾ�������///
	//cvNamedWindow("3.Binary Picture",1); 
	//cvMoveWindow("3.Binary Picture",1200,0);
	//cvShowImage("3.Binary Picture", imgTh);
	//cvWaitKey(500);
	return *imgTh;
}

///��imgSrcͼƬ�ҶȻ�����ֵ��///
IplImage preprocessing_switch(IplImage* imgSrc)
{
	IplImage imgBin = threshold(imgSrc);
	///����///
	return imgBin;
}
