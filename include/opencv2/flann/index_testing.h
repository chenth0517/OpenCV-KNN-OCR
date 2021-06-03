#ifndef OPENCV_FLANN_INDEX_TESTING_H_
#define OPENCV_FLANN_INDEX_TESTING_H_ 

#include <cstring>
#include <cassert>
#include <cmath>

#include "matrix.h"
#include "nn_index.h"
#include "result_set.h"
#include "logger.h"
#include "timer.h"


namespace cvflann
{

inline int countCorrectMatches(int* neighbors, int* groundTruth, int n)
{
    int count = 0;
    for (int i=0; i<n; ++i) {
        for (int k=0; k<n; ++k) {
            if (neighbors[i]==groundTruth[k]) {
                count++;
                break;
            }
        }
    }
    return count;
}


template <typename Distance>
typename Distance::ResultType computeDistanceRaport(const Matrix<typename Distance::ElementType>& inputData, typename Distance::ElementType* target,
                                                    int* neighbors, int* groundTruth, int veclen, int n, const Distance& distance)
{
    typedef typename Distance::ResultType DistanceType;

    DistanceType ret = 0;
    for (int i=0; i<n; ++i) {
        DistanceType den = distance(inputData[groundTruth[i]], target, veclen);
        DistanceType num = distance(inputData[neighbors[i]], target, veclen);

        if ((den==0)&&(num==0)) {
            ret += 1;
        }
        else {
            ret += num/den;
        }
    }

    return ret;
}

template <typename Distance>
float search_with_ground_truth(NNIndex<Distance>& index, const Matrix<typename Distance::ElementType>& inputData,
                               const Matrix<typename Distance::ElementType>& testData, const Matrix<int>& matches, int nn, int checks,
                               float& time, typename Distance::ResultType& dist, const Distance& distance, int skipMatches)
{
    typedef typename Distance::ResultType DistanceType;

    if (matches.cols<size_t(nn)) {
        Logger::info("matches.cols=%d, nn=%d\n",matches.cols,nn);

        throw FLANNException("Ground truth is not computed for as many neighbors as requested");
    }

    KNNResultSet<DistanceType> resultSet(nn+skipMatches);
    SearchParams searchParams(checks);

    std::vector<int> indices(nn+skipMatches);
    std::vector<DistanceType> dists(nn+skipMatches);
    int* neighbors = &indices[skipMatches];

    int correct = 0;
    DistanceType distR = 0;
    StartStopTimer t;
    int repeats = 0;
    while (t.value<0.2) {
        repeats++;
        t.start();
        correct = 0;
        distR = 0;
        for (size_t i = 0; i < testData.rows; i++) {
            resultSet.init(&indices[0], &dists[0]);
            index.findNeighbors(resultSet, testData[i], searchParams);

            correct += countCorrectMatches(neighbors,matches[i], nn);
            distR += computeDistanceRaport<Distance>(inputData, testData[i], neighbors, matches[i], (int)testData.cols, nn, distance);
        }
        t.stop();
    }
    time = float(t.value/repeats);

    float precicion = (float)correct/(nn*testData.rows);

    dist = distR/(testData.rows*nn);

    Logger::info("%8d %10.4g %10.5g %10.5g %10.5g\n",
                 checks, precicion, time, 1000.0 * time / testData.rows, dist);

    return precicion;
}


template <typename Distance>
float test_index_checks(NNIndex<Distance>& index, const Matrix<typename Distance::ElementType>& inputData,
                        const Matrix<typename Distance::ElementType>& testData, const Matrix<int>& matches,
                        int checks, float& precision, const Distance& distance, int nn = 1, int skipMatches = 0)
{
    typedef typename Distance::ResultType DistanceType;

    Logger::info("  Nodes  Precision(%)   Time(s)   Time/vec(ms)  Mean dist\n");
    Logger::info("---------------------------------------------------------\n");

    float time = 0;
    DistanceType dist = 0;
    precision = search_with_ground_truth(index, inputData, testData, matches, nn, checks, time, dist, distance, skipMatches);

    return time;
}

template <typename Distance>
float test_index_precision(NNIndex<Distance>& index, const Matrix<typename Distance::ElementType>& inputData,
                           const Matrix<typename Distance::ElementType>& testData, const Matrix<int>& matches,
                           float precision, int& checks, const Distance& distance, int nn = 1, int skipMatches = 0)
{
    typedef typename Distance::ResultType DistanceType;
    const float SEARCH_EPS = 0.001f;

    Logger::info("  Nodes  Precision(%)   Time(s)   Time/vec(ms)  Mean dist\n");
    Logger::info("---------------------------------------------------------\n");

    int c2 = 1;
    float p2;
    int c1 = 1;

    float time;
    DistanceType dist;

    p2 = search_with_ground_truth(index, inputData, testData, matches, nn, c2, time, dist, distance, skipMatches);

    if (p2>precision) {
        Logger::info("Got as close as I can\n");
        checks = c2;
        return time;
    }

    while (p2<precision) {
        c1 = c2;

        c2 *=2;
        p2 = search_with_ground_truth(index, inputData, testData, matches, nn, c2, time, dist, distance, skipMatches);
    }

    int cx;
    float realPrecision;
    if (fabs(p2-precision)>SEARCH_EPS) {
        Logger::info("Start linear estimation\n");



        cx = (c1+c2)/2;
        realPrecision = search_with_ground_truth(index, inputData, testData, matches, nn, cx, time, dist, distance, skipMatches);
        while (fabs(realPrecision-precision)>SEARCH_EPS) {

            if (realPrecision<precision) {
                c1 = cx;
            }
            else {
                c2 = cx;
            }
            cx = (c1+c2)/2;
            if (cx==c1) {
                Logger::info("Got as close as I can\n");
                break;
            }
            realPrecision = search_with_ground_truth(index, inputData, testData, matches, nn, cx, time, dist, distance, skipMatches);
        }

        c2 = cx;
        p2 = realPrecision;

    }
    else {
        Logger::info("No need for linear estimation\n");
        cx = c2;
        realPrecision = p2;
    }

    checks = cx;
    return time;
}


template <typename Distance>
void test_index_precisions(NNIndex<Distance>& index, const Matrix<typename Distance::ElementType>& inputData,
                           const Matrix<typename Distance::ElementType>& testData, const Matrix<int>& matches,
                           float* precisions, int precisions_length, const Distance& distance, int nn = 1, int skipMatches = 0, float maxTime = 0)
{
    typedef typename Distance::ResultType DistanceType;

    const float SEARCH_EPS = 0.001;


    std::sort(precisions, precisions+precisions_length);

    int pindex = 0;
    float precision = precisions[pindex];

    Logger::info("  Nodes  Precision(%)   Time(s)   Time/vec(ms)  Mean dist\n");
    Logger::info("---------------------------------------------------------\n");

    int c2 = 1;
    float p2;

    int c1 = 1;
    float p1;

    float time;
    DistanceType dist;

    p2 = search_with_ground_truth(index, inputData, testData, matches, nn, c2, time, dist, distance, skipMatches);




    while (precisions[pindex]<p2 && pindex<precisions_length) {
        pindex++;
    }

    if (pindex==precisions_length) {
        Logger::info("Got as close as I can\n");
        return;
    }

    for (int i=pindex; i<precisions_length; ++i) {

        precision = precisions[i];
        while (p2<precision) {
            c1 = c2;
            p1 = p2;
            c2 *=2;
            p2 = search_with_ground_truth(index, inputData, testData, matches, nn, c2, time, dist, distance, skipMatches);
            if ((maxTime> 0)&&(time > maxTime)&&(p2<precision)) return;
        }

        int cx;
        float realPrecision;
        if (fabs(p2-precision)>SEARCH_EPS) {
            Logger::info("Start linear estimation\n");



            cx = (c1+c2)/2;
            realPrecision = search_with_ground_truth(index, inputData, testData, matches, nn, cx, time, dist, distance, skipMatches);
            while (fabs(realPrecision-precision)>SEARCH_EPS) {

                if (realPrecision<precision) {
                    c1 = cx;
                }
                else {
                    c2 = cx;
                }
                cx = (c1+c2)/2;
                if (cx==c1) {
                    Logger::info("Got as close as I can\n");
                    break;
                }
                realPrecision = search_with_ground_truth(index, inputData, testData, matches, nn, cx, time, dist, distance, skipMatches);
            }

            c2 = cx;
            p2 = realPrecision;

        }
        else {
            Logger::info("No need for linear estimation\n");
            cx = c2;
            realPrecision = p2;
        }

    }
}

}

#endif
