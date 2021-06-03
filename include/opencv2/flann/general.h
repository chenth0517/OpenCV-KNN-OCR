#ifndef OPENCV_FLANN_GENERAL_H_
#define OPENCV_FLANN_GENERAL_H_ 

#include "defines.h"
#include <stdexcept>
#include <cassert>

namespace cvflann
{

class FLANNException : public std::runtime_error
{
public:
    FLANNException(const char* message) : std::runtime_error(message) { }

    FLANNException(const std::string& message) : std::runtime_error(message) { }
};

}


#endif
