#include "opencv2/core/core.hpp"
#import "opencv2/highgui/cap_ios.h"

UIImage* MatToUIImage(const cv::Mat& image);
void UIImageToMat(const UIImage* image,
                         cv::Mat& m, bool alphaExist = false);
