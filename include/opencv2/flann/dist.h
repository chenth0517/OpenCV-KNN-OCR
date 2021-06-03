#ifndef OPENCV_FLANN_DIST_H_
#define OPENCV_FLANN_DIST_H_ 

#include <cmath>
#include <cstdlib>
#include <string.h>
#ifdef _MSC_VER
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include "defines.h"

#if (defined WIN32 || defined _WIN32) && defined(_M_ARM)
# include <Intrin.h>
#endif

#if defined(__ARM_NEON__) || defined(__ARM_NEON)
# include "arm_neon.h"
#endif

namespace cvflann
{

template<typename T>
inline T abs(T x) { return (x<0) ? -x : x; }

template<>
inline int abs<int>(int x) { return ::abs(x); }

template<>
inline float abs<float>(float x) { return fabsf(x); }

template<>
inline double abs<double>(double x) { return fabs(x); }

template<typename T>
struct Accumulator { typedef T Type; };
template<>
struct Accumulator<unsigned char> { typedef float Type; };
template<>
struct Accumulator<unsigned short> { typedef float Type; };
template<>
struct Accumulator<unsigned int> { typedef float Type; };
template<>
struct Accumulator<char> { typedef float Type; };
template<>
struct Accumulator<short> { typedef float Type; };
template<>
struct Accumulator<int> { typedef float Type; };

#undef True
#undef False

class True
{
};

class False
{
};
template<class T>
struct L2_Simple
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;

    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType = -1) const
    {
        ResultType result = ResultType();
        ResultType diff;
        for(size_t i = 0; i < size; ++i ) {
            diff = *a++ - *b++;
            result += diff*diff;
        }
        return result;
    }

    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        return (a-b)*(a-b);
    }
};






template<class T>
struct L2
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;
    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType worst_dist = -1) const
    {
        ResultType result = ResultType();
        ResultType diff0, diff1, diff2, diff3;
        Iterator1 last = a + size;
        Iterator1 lastgroup = last - 3;


        while (a < lastgroup) {
            diff0 = (ResultType)(a[0] - b[0]);
            diff1 = (ResultType)(a[1] - b[1]);
            diff2 = (ResultType)(a[2] - b[2]);
            diff3 = (ResultType)(a[3] - b[3]);
            result += diff0 * diff0 + diff1 * diff1 + diff2 * diff2 + diff3 * diff3;
            a += 4;
            b += 4;

            if ((worst_dist>0)&&(result>worst_dist)) {
                return result;
            }
        }

        while (a < last) {
            diff0 = (ResultType)(*a++ - *b++);
            result += diff0 * diff0;
        }
        return result;
    }







    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        return (a-b)*(a-b);
    }
};





template<class T>
struct L1
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;







    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType worst_dist = -1) const
    {
        ResultType result = ResultType();
        ResultType diff0, diff1, diff2, diff3;
        Iterator1 last = a + size;
        Iterator1 lastgroup = last - 3;


        while (a < lastgroup) {
            diff0 = (ResultType)abs(a[0] - b[0]);
            diff1 = (ResultType)abs(a[1] - b[1]);
            diff2 = (ResultType)abs(a[2] - b[2]);
            diff3 = (ResultType)abs(a[3] - b[3]);
            result += diff0 + diff1 + diff2 + diff3;
            a += 4;
            b += 4;

            if ((worst_dist>0)&&(result>worst_dist)) {
                return result;
            }
        }

        while (a < last) {
            diff0 = (ResultType)abs(*a++ - *b++);
            result += diff0;
        }
        return result;
    }




    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        return abs(a-b);
    }
};



template<class T>
struct MinkowskiDistance
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;

    int order;

    MinkowskiDistance(int order_) : order(order_) {}
    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType worst_dist = -1) const
    {
        ResultType result = ResultType();
        ResultType diff0, diff1, diff2, diff3;
        Iterator1 last = a + size;
        Iterator1 lastgroup = last - 3;


        while (a < lastgroup) {
            diff0 = (ResultType)abs(a[0] - b[0]);
            diff1 = (ResultType)abs(a[1] - b[1]);
            diff2 = (ResultType)abs(a[2] - b[2]);
            diff3 = (ResultType)abs(a[3] - b[3]);
            result += pow(diff0,order) + pow(diff1,order) + pow(diff2,order) + pow(diff3,order);
            a += 4;
            b += 4;

            if ((worst_dist>0)&&(result>worst_dist)) {
                return result;
            }
        }

        while (a < last) {
            diff0 = (ResultType)abs(*a++ - *b++);
            result += pow(diff0,order);
        }
        return result;
    }




    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        return pow(static_cast<ResultType>(abs(a-b)),order);
    }
};



template<class T>
struct MaxDistance
{
    typedef False is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;






    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType worst_dist = -1) const
    {
        ResultType result = ResultType();
        ResultType diff0, diff1, diff2, diff3;
        Iterator1 last = a + size;
        Iterator1 lastgroup = last - 3;


        while (a < lastgroup) {
            diff0 = abs(a[0] - b[0]);
            diff1 = abs(a[1] - b[1]);
            diff2 = abs(a[2] - b[2]);
            diff3 = abs(a[3] - b[3]);
            if (diff0>result) {result = diff0; }
            if (diff1>result) {result = diff1; }
            if (diff2>result) {result = diff2; }
            if (diff3>result) {result = diff3; }
            a += 4;
            b += 4;

            if ((worst_dist>0)&&(result>worst_dist)) {
                return result;
            }
        }

        while (a < last) {
            diff0 = abs(*a++ - *b++);
            result = (diff0>result) ? diff0 : result;
        }
        return result;
    }




};







struct HammingLUT
{
    typedef False is_kdtree_distance;
    typedef False is_vector_space_distance;

    typedef unsigned char ElementType;
    typedef int ResultType;



    ResultType operator()(const unsigned char* a, const unsigned char* b, int size) const
    {
        static const uchar popCountTable[] =
        {
            0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
        };
        ResultType result = 0;
        for (int i = 0; i < size; i++) {
            result += popCountTable[a[i] ^ b[i]];
        }
        return result;
    }
};





struct HammingLUT2
{
    typedef False is_kdtree_distance;
    typedef False is_vector_space_distance;

    typedef unsigned char ElementType;
    typedef int ResultType;



    ResultType operator()(const unsigned char* a, const unsigned char* b, size_t size) const
    {
        static const uchar popCountTable[] =
        {
            0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
        };
        ResultType result = 0;
        for (size_t i = 0; i < size; i++) {
            result += popCountTable[a[i] ^ b[i]];
        }
        return result;
    }
};





template<class T>
struct Hamming
{
    typedef False is_kdtree_distance;
    typedef False is_vector_space_distance;


    typedef T ElementType;
    typedef int ResultType;

    template<typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType = -1) const
    {
        ResultType result = 0;
#if defined(__ARM_NEON__) || defined(__ARM_NEON)
        {
            uint32x4_t bits = vmovq_n_u32(0);
            for (size_t i = 0; i < size; i += 16) {
                uint8x16_t A_vec = vld1q_u8 (a + i);
                uint8x16_t B_vec = vld1q_u8 (b + i);
                uint8x16_t AxorB = veorq_u8 (A_vec, B_vec);
                uint8x16_t bitsSet = vcntq_u8 (AxorB);
                uint16x8_t bitSet8 = vpaddlq_u8 (bitsSet);
                uint32x4_t bitSet4 = vpaddlq_u16 (bitSet8);
                bits = vaddq_u32(bits, bitSet4);
            }
            uint64x2_t bitSet2 = vpaddlq_u32 (bits);
            result = vgetq_lane_s32 (vreinterpretq_s32_u64(bitSet2),0);
            result += vgetq_lane_s32 (vreinterpretq_s32_u64(bitSet2),2);
        }
#elif __GNUC__
        {

            typedef unsigned long long pop_t;
            const size_t modulo = size % sizeof(pop_t);
            const pop_t* a2 = reinterpret_cast<const pop_t*> (a);
            const pop_t* b2 = reinterpret_cast<const pop_t*> (b);
            const pop_t* a2_end = a2 + (size / sizeof(pop_t));

            for (; a2 != a2_end; ++a2, ++b2) result += __builtin_popcountll((*a2) ^ (*b2));

            if (modulo) {


                pop_t a_final = 0, b_final = 0;
                memcpy(&a_final, a2, modulo);
                memcpy(&b_final, b2, modulo);
                result += __builtin_popcountll(a_final ^ b_final);
            }
        }
#else
        typedef unsigned long long pop_t;
        HammingLUT lut;
        result = lut(reinterpret_cast<const unsigned char*> (a),
                     reinterpret_cast<const unsigned char*> (b), size * sizeof(pop_t));
#endif
        return result;
    }
};

template<typename T>
struct Hamming2
{
    typedef False is_kdtree_distance;
    typedef False is_vector_space_distance;

    typedef T ElementType;
    typedef int ResultType;



    unsigned int popcnt32(uint32_t n) const
    {
        n -= ((n >> 1) & 0x55555555);
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
        return (((n + (n >> 4))& 0xF0F0F0F)* 0x1010101) >> 24;
    }

#ifdef FLANN_PLATFORM_64_BIT
    unsigned int popcnt64(uint64_t n) const
    {
        n -= ((n >> 1) & 0x5555555555555555);
        n = (n & 0x3333333333333333) + ((n >> 2) & 0x3333333333333333);
        return (((n + (n >> 4))& 0x0f0f0f0f0f0f0f0f)* 0x0101010101010101) >> 56;
    }
#endif

    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType = -1) const
    {
#ifdef FLANN_PLATFORM_64_BIT
        const uint64_t* pa = reinterpret_cast<const uint64_t*>(a);
        const uint64_t* pb = reinterpret_cast<const uint64_t*>(b);
        ResultType result = 0;
        size /= (sizeof(uint64_t)/sizeof(unsigned char));
        for(size_t i = 0; i < size; ++i ) {
            result += popcnt64(*pa ^ *pb);
            ++pa;
            ++pb;
        }
#else
        const uint32_t* pa = reinterpret_cast<const uint32_t*>(a);
        const uint32_t* pb = reinterpret_cast<const uint32_t*>(b);
        ResultType result = 0;
        size /= (sizeof(uint32_t)/sizeof(unsigned char));
        for(size_t i = 0; i < size; ++i ) {
            result += popcnt32(*pa ^ *pb);
            ++pa;
            ++pb;
        }
#endif
        return result;
    }
};





template<class T>
struct HistIntersectionDistance
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;




    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType worst_dist = -1) const
    {
        ResultType result = ResultType();
        ResultType min0, min1, min2, min3;
        Iterator1 last = a + size;
        Iterator1 lastgroup = last - 3;


        while (a < lastgroup) {
            min0 = (ResultType)(a[0] < b[0] ? a[0] : b[0]);
            min1 = (ResultType)(a[1] < b[1] ? a[1] : b[1]);
            min2 = (ResultType)(a[2] < b[2] ? a[2] : b[2]);
            min3 = (ResultType)(a[3] < b[3] ? a[3] : b[3]);
            result += min0 + min1 + min2 + min3;
            a += 4;
            b += 4;
            if ((worst_dist>0)&&(result>worst_dist)) {
                return result;
            }
        }

        while (a < last) {
            min0 = (ResultType)(*a < *b ? *a : *b);
            result += min0;
            ++a;
            ++b;
        }
        return result;
    }




    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        return a<b ? a : b;
    }
};



template<class T>
struct HellingerDistance
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;




    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType = -1) const
    {
        ResultType result = ResultType();
        ResultType diff0, diff1, diff2, diff3;
        Iterator1 last = a + size;
        Iterator1 lastgroup = last - 3;


        while (a < lastgroup) {
            diff0 = sqrt(static_cast<ResultType>(a[0])) - sqrt(static_cast<ResultType>(b[0]));
            diff1 = sqrt(static_cast<ResultType>(a[1])) - sqrt(static_cast<ResultType>(b[1]));
            diff2 = sqrt(static_cast<ResultType>(a[2])) - sqrt(static_cast<ResultType>(b[2]));
            diff3 = sqrt(static_cast<ResultType>(a[3])) - sqrt(static_cast<ResultType>(b[3]));
            result += diff0 * diff0 + diff1 * diff1 + diff2 * diff2 + diff3 * diff3;
            a += 4;
            b += 4;
        }
        while (a < last) {
            diff0 = sqrt(static_cast<ResultType>(*a++)) - sqrt(static_cast<ResultType>(*b++));
            result += diff0 * diff0;
        }
        return result;
    }




    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        return sqrt(static_cast<ResultType>(a)) - sqrt(static_cast<ResultType>(b));
    }
};


template<class T>
struct ChiSquareDistance
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;




    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType worst_dist = -1) const
    {
        ResultType result = ResultType();
        ResultType sum, diff;
        Iterator1 last = a + size;

        while (a < last) {
            sum = (ResultType)(*a + *b);
            if (sum>0) {
                diff = (ResultType)(*a - *b);
                result += diff*diff/sum;
            }
            ++a;
            ++b;

            if ((worst_dist>0)&&(result>worst_dist)) {
                return result;
            }
        }
        return result;
    }




    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        ResultType result = ResultType();
        ResultType sum, diff;

        sum = (ResultType)(a+b);
        if (sum>0) {
            diff = (ResultType)(a-b);
            result = diff*diff/sum;
        }
        return result;
    }
};


template<class T>
struct KL_Divergence
{
    typedef True is_kdtree_distance;
    typedef True is_vector_space_distance;

    typedef T ElementType;
    typedef typename Accumulator<T>::Type ResultType;




    template <typename Iterator1, typename Iterator2>
    ResultType operator()(Iterator1 a, Iterator2 b, size_t size, ResultType worst_dist = -1) const
    {
        ResultType result = ResultType();
        Iterator1 last = a + size;

        while (a < last) {
            if (* a != 0) {
                ResultType ratio = (ResultType)(*a / *b);
                if (ratio>0) {
                    result += *a * log(ratio);
                }
            }
            ++a;
            ++b;

            if ((worst_dist>0)&&(result>worst_dist)) {
                return result;
            }
        }
        return result;
    }




    template <typename U, typename V>
    inline ResultType accum_dist(const U& a, const V& b, int) const
    {
        ResultType result = ResultType();
        ResultType ratio = (ResultType)(a / b);
        if (ratio>0) {
            result = a * log(ratio);
        }
        return result;
    }
};
template <typename T>
struct ZeroIterator
{

    T operator*()
    {
        return 0;
    }

    T operator[](int)
    {
        return 0;
    }

    const ZeroIterator<T>& operator ++()
    {
        return *this;
    }

    ZeroIterator<T> operator ++(int)
    {
        return *this;
    }

    ZeroIterator<T>& operator+=(int)
    {
        return *this;
    }

};







template <typename Distance, typename ElementType>
struct squareDistance
{
    typedef typename Distance::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return dist*dist; }
};


template <typename ElementType>
struct squareDistance<L2_Simple<ElementType>, ElementType>
{
    typedef typename L2_Simple<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return dist; }
};

template <typename ElementType>
struct squareDistance<L2<ElementType>, ElementType>
{
    typedef typename L2<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return dist; }
};


template <typename ElementType>
struct squareDistance<MinkowskiDistance<ElementType>, ElementType>
{
    typedef typename MinkowskiDistance<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return dist; }
};

template <typename ElementType>
struct squareDistance<HellingerDistance<ElementType>, ElementType>
{
    typedef typename HellingerDistance<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return dist; }
};

template <typename ElementType>
struct squareDistance<ChiSquareDistance<ElementType>, ElementType>
{
    typedef typename ChiSquareDistance<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return dist; }
};


template <typename Distance>
typename Distance::ResultType ensureSquareDistance( typename Distance::ResultType dist )
{
    typedef typename Distance::ElementType ElementType;

    squareDistance<Distance, ElementType> dummy;
    return dummy( dist );
}







template <typename Distance, typename ElementType>
struct simpleDistance
{
    typedef typename Distance::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return dist; }
};


template <typename ElementType>
struct simpleDistance<L2_Simple<ElementType>, ElementType>
{
    typedef typename L2_Simple<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return sqrt(dist); }
};

template <typename ElementType>
struct simpleDistance<L2<ElementType>, ElementType>
{
    typedef typename L2<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return sqrt(dist); }
};


template <typename ElementType>
struct simpleDistance<MinkowskiDistance<ElementType>, ElementType>
{
    typedef typename MinkowskiDistance<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return sqrt(dist); }
};

template <typename ElementType>
struct simpleDistance<HellingerDistance<ElementType>, ElementType>
{
    typedef typename HellingerDistance<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return sqrt(dist); }
};

template <typename ElementType>
struct simpleDistance<ChiSquareDistance<ElementType>, ElementType>
{
    typedef typename ChiSquareDistance<ElementType>::ResultType ResultType;
    ResultType operator()( ResultType dist ) { return sqrt(dist); }
};


template <typename Distance>
typename Distance::ResultType ensureSimpleDistance( typename Distance::ResultType dist )
{
    typedef typename Distance::ElementType ElementType;

    simpleDistance<Distance, ElementType> dummy;
    return dummy( dist );
}

}

#endif
