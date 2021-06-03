#ifndef __PREPROCESSING_H__
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <ctype.h>

const int PIC_WIDTH = 200;
const int PIC_HEIGHT = 200;

IplImage preprocessing_switch(IplImage* imgSrc);

IplImage threshold(IplImage* imgGray);

#endif
