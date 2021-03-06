/*
 *  preprocessing.h
 *  
 *
 *  Created by damiles on 18/11/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>
#include <stdio.h>
#include <ctype.h>
#endif
const std::string templateChar[CLASS_NUM] = { "а", "в", "е", "и", "к", "л", "м", "н", "о", "п", "р", "т", "ф" };

class basicOCR{
	public:
		float classify(IplImage* img,int showResult);
		basicOCR ();
		void test();	
	private:
		char train_file_path[255];
		char test_file_path[255];
		int train_samples;
		int test_samples;
		int classes_num;
		CvMat* trainData;
		CvMat* trainClasses;
		int sizeW, sizeH;
		static const int K = TRAIN_NUM;
		CvKNearest *knn;
		void getData();
		void train();
};
