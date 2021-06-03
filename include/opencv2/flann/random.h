#ifndef OPENCV_FLANN_RANDOM_H
#define OPENCV_FLANN_RANDOM_H 

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "general.h"

namespace cvflann
{





inline void seed_random(unsigned int seed)
{
    srand(seed);
}
inline double rand_double(double high = 1.0, double low = 0)
{
    return low + ((high-low) * (std::rand() / (RAND_MAX + 1.0)));
}







inline int rand_int(int high = RAND_MAX, int low = 0)
{
    return low + (int) ( double(high-low) * (std::rand() / (RAND_MAX + 1.0)));
}





class UniqueRandom
{
    std::vector<int> vals_;
    int size_;
    int counter_;

public:





    UniqueRandom(int n)
    {
        init(n);
    }





    void init(int n)
    {

        vals_.resize(n);
        size_ = n;
        for (int i = 0; i < size_; ++i) vals_[i] = i;


        std::random_shuffle(vals_.begin(), vals_.end());

        counter_ = 0;
    }






    int next()
    {
        if (counter_ == size_) {
            return -1;
        }
        else {
            return vals_[counter_++];
        }
    }
};

}

#endif
