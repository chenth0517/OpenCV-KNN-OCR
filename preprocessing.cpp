#include "preprocessing.h"

#include <ctype.h>
#include <math.h>

///大律法求阈值///
int otsu(const IplImage *frame)
{
	///frame灰度级///
	const int GrayScale=256;///灰度级别///
	int width=frame->width;
	int	height=frame->height;
	int pixelCount[GrayScale]={0};
	float pixelPro[GrayScale]={0};
	int i, j, pixelSum = width * height, threshold = 0;
	uchar* data = (uchar*)frame->imageData;
	float w0, w1, u0tmp, u1tmp, u0, u1, deltaTmp, deltaMax = 0;
	///统计每个灰度级中像素的个数///
	for(i = 0; i < height; i++)
	{
		for(j = 0;j < width;j++)
		{
			pixelCount[(int)data[i * width + j]]++;
		}
	}
	///计算每个灰度级的像素数目占整幅图像的比例///
	for(i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / pixelSum;
	}
	///遍历灰度级[0,255],寻找合适的threshold///
	for(i = 0; i < GrayScale; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = deltaTmp = 0;
		for(j = 0; j < GrayScale; j++)
		{
			if(j <= i)   ///背景部分///
			{
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else   ///前景部分///
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
	IplImage* imgTh=cvCreateImage(cvSize(PIC_WIDTH,PIC_HEIGHT),IPL_DEPTH_8U,1);  ///二值图像///

	//cvNamedWindow("1.Original Picture", CV_WINDOW_AUTOSIZE);
	//cvShowImage("1.Original Picture", imgGray);
	//cvWaitKey(5000);
	
	cvNormalize(imgGray, imgTh, 255, 0, CV_MINMAX);

	///显示中处理过程///
	//cvNamedWindow("2.Bin Picture",1); 
	//cvMoveWindow("2.Bin Picture",800,0);
	//cvShowImage("2.Bin Picture",imgTh);

	///阀值化///
	int threshold = otsu(imgTh);///根据大律法确定阈值///
	cvThreshold( imgTh, imgTh, threshold, 255, CV_THRESH_BINARY_INV );

	CvMat data;
	int val=0;///当前图像中白色之和///
	int maxVal = imgTh->height * imgTh->width * 255;///全白图像中白色之和///
	for (int i=0; i< imgTh->width; i++)
	{
		cvGetCol(imgTh, &data, i);
		val += cvSum(&data).val[0];
	}
	if (val>=maxVal/2)///说明当前二值化图像中白色居多，重新二值化///
	{
		cvThreshold( imgTh, imgTh, threshold, 255, CV_THRESH_BINARY_INV );
	}

	///显示处理过程///
	//cvNamedWindow("3.Binary Picture",1); 
	//cvMoveWindow("3.Binary Picture",1200,0);
	//cvShowImage("3.Binary Picture", imgTh);
	//cvWaitKey(500);
	return *imgTh;
}

///将imgSrc图片灰度化，二值化///
IplImage preprocessing_switch(IplImage* imgSrc)
{
	IplImage imgBin = threshold(imgSrc);
	///返回///
	return imgBin;
}
