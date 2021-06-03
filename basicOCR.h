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
const std::string templateChar[71] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","J","K","L","M","N","P","Q","R","S","T","U","V","W","X","Y","Z","°Ä","²Ø","´¨","¶õ","¸Ê","¸Ó","¸Û","¹ó","¹ð","ºÚ","»¦","¼ª","¼½","½ò","½ú","¾©","¾¯","ÁÉ","Áì","Â³","ÃÉ","Ãö","Äþ","Çà","Çí","ÉÂ","Ê¹","ËÕ","Íî","Ïæ","ÐÂ","Ñ§","Óå","Ô¥","ÔÁ","ÔÆ","Õã"};

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
		static const int K=10;
		CvKNearest *knn;
		void getData();
		void train();
};
