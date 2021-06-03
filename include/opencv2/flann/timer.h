#ifndef OPENCV_FLANN_TIMER_H
#define OPENCV_FLANN_TIMER_H 

#include <time.h>


namespace cvflann
{






class StartStopTimer
{
    clock_t startTime;

public:



    double value;





    StartStopTimer()
    {
        reset();
    }




    void start()
    {
        startTime = clock();
    }




    void stop()
    {
        clock_t stopTime = clock();
        value += ( (double)stopTime - startTime) / CLOCKS_PER_SEC;
    }




    void reset()
    {
        value = 0;
    }

};

}

#endif
