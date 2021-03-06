#ifndef __PREPROCESSING_H__
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <ctype.h>

const int PIC_WIDTH = 18;
const int PIC_HEIGHT = 28;
const int CLASS_NUM = 13;
const int TRAIN_NUM = 10;
const int TEST_NUM = 1;

IplImage preprocessing_switch(IplImage* imgSrc);

IplImage threshold(IplImage* imgGray);

#endif
