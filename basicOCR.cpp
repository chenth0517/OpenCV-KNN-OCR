/*
 *  basicOCR.c
 *  
 *
 *  Created by damiles on 18/11/08.
 *  Copyright 2008 Damiles. GPL License
 *
 */

#ifndef _EiC
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/ml.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#endif

#include "preprocessing.h"
#include "basicOCR.h"


///将训练内容放在trainData矩阵中，trainData矩阵共500行，每50行为一个组（指向同一个数字），组内每一行为一张图片（size*size）。///
///将人工指定的识别结果放在trainClass矩阵中，共500行，每行为一个数字。///
void basicOCR::getData()
{
	IplImage* src_image;
	IplImage prs_image;
	CvMat row,data;
	char file[255];
	int i,j;
	for(i =0; i<classes_num; i++){
		for( j = 0; j< train_samples; j++){
			
			//Load file
			if(j<10)
				sprintf(file,"%s%s\\00%d.jpg",train_file_path, templateChar[i].c_str(), j);
			else if(j<100)
				sprintf(file,"%s%s\\0%d.jpg",train_file_path, templateChar[i].c_str(), j);
			else
				sprintf(file,"%s%s\\%d.jpg",train_file_path, templateChar[i].c_str(), j);
			src_image = cvLoadImage(file,0);
			if(!src_image){
				printf("Error: Cant load image %s\n", file);
				//exit(-1);
			}
			//process file
			prs_image = preprocessing_switch(src_image);
			//cvNamedWindow(file, CV_WINDOW_AUTOSIZE);
			//cvShowImage(file, &prs_image);
			//cvWaitKey(1000);

			//Set class label
			cvGetRow(trainClasses, &row, i*train_samples + j);
			cvSet(&row, cvRealScalar(i));
			//Set data 
			cvGetRow(trainData, &row, i*train_samples + j);

			IplImage* img = cvCreateImage( cvSize( sizeW, sizeH ), IPL_DEPTH_32F, 1 );///注意此处img的色彩深度为32F，如果是IPL_DEPTH_xxU，则进行下面的操作时会得到全0///
			///将图像色彩深度由preprocessing中定义的8U转换为32F，经显示检测肉眼观察无差别///
			cvConvertScale(&prs_image, img, 0.0039215, 0); // img=prs_image*0.0039215+0   0.0039215=1/255
			///将img中的内容(data)转为行数据(row1)存到trainData中(row)///
			cvGetSubRect(img, &data, cvRect(0,0, sizeW,sizeH));
			CvMat row_header, *row1;
			//convert data matrix sizexsize to vecor
			row1 = cvReshape( &data, &row_header, 0, 1 );
			cvCopy(row1, &row, NULL);
		}
	}
}

void basicOCR::train()
{
	knn=new CvKNearest( trainData, trainClasses, 0, false, K ); ///K表示最大邻居数量（即K方向）///
}

float basicOCR::classify(IplImage* img, int showResult)
{
	IplImage prs_image;
	CvMat data;
	CvMat* nearest=cvCreateMat(1,K,CV_32FC1);
	float result;
	//process file
	prs_image = preprocessing_switch(img);
	
	//Set data 
	IplImage* img32 = cvCreateImage( cvSize( sizeW, sizeH ), IPL_DEPTH_32F, 1 );
	cvConvertScale(&prs_image, img32, 0.0039215, 0);
	cvGetSubRect(img32, &data, cvRect(0,0, sizeW,sizeH));
	CvMat row_header, *row1;
	row1 = cvReshape( &data, &row_header, 0, 1 );

	result=knn->find_nearest(row1,K,0,0,nearest,0);
	
	int accuracy=0;
	for(int i=0;i<K;i++){
		if( nearest->data.fl[i] == result)
                    accuracy++;
	}
	float pre=100*((float)accuracy/(float)K);
	if(showResult==1){
		printf("|\t%s\t| \t%.2f%%  \t| \t%d of %d \t| idx %d \n",templateChar[(int)floor(result+0.5)].c_str(),pre,accuracy,K, (int)floor(result+0.5));
		printf(" ---------------------------------------------------------------\n");
	}
	return result;
}

void basicOCR::test(){
	IplImage* src_image;
	IplImage prs_image;
	CvMat row,data;
	char file[255];
	int i,j;
	int error=0;
	int testCount=0;
	for(i =0; i<classes_num; i++){
		for (j = 0; j< test_samples; j++){
			
			sprintf(file,"%s%d/00%d.jpg",test_file_path, i, j);
			printf("Path: %s\n", file);
			src_image = cvLoadImage(file,0);
			if(!src_image){
				printf("Error: Cant load image %s\n", file);
				//exit(-1);
			}
			
			//process file
			prs_image = preprocessing_switch(src_image);
			//cvNamedWindow(file, CV_WINDOW_AUTOSIZE);
			//cvShowImage(file, &prs_image);
			//cvWaitKey(1000);

			float r = classify(&prs_image, 1);
			if((int)r!=i)
				error++;
			
			testCount++;
		}
	}
	float totalerror=100*(float)error/(float)testCount;
	printf("System Error: %.2f%%\n", totalerror);
	
}

basicOCR::basicOCR()
{

	//initial
	//sprintf(file_path , "OCRlib/");
	sprintf(train_file_path, "./train_pic/");
	sprintf(test_file_path, "./test_pic/");
	train_samples = 10; ///50个用来训练，50个用来测试///
	test_samples = 4;
	//classes_num= 71; ///10个数字，24个字母，37个汉字，所以共分71类///
	classes_num = 2; ///10个数字，24个字母，37个汉字，所以共分71类///
	sizeW = PIC_WIDTH; ///训练样本图片正方形尺寸///
	sizeH = PIC_HEIGHT; ///训练样本图片正方形尺寸///

	trainData = cvCreateMat(train_samples*classes_num, sizeW*sizeH, CV_32FC1);
	trainClasses = cvCreateMat(train_samples*classes_num, 1, CV_32FC1);

	//Get data (get images and process it)
	getData();
	
	//train	
	train();
	
	printf(" ---------------------------------------------------------------\n");
	printf("|\tClass\t|\tPrecision\t|\tAccuracy\t|\n");
	printf(" ---------------------------------------------------------------\n");
	
	//Test	
	test();
	
}


