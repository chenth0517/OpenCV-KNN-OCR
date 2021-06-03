#ifndef __OPENCV_CORE_TYPES_H__
#define __OPENCV_CORE_TYPES_H__ 

#if !defined _CRT_SECURE_NO_DEPRECATE && defined _MSC_VER
# if _MSC_VER > 1300
#define _CRT_SECURE_NO_DEPRECATE 
# endif
#endif


#ifndef SKIP_INCLUDES

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#if !defined _MSC_VER && !defined __BORLANDC__
# include <stdint.h>
#endif

#if defined __ICL
#define CV_ICC __ICL
#elif defined __ICC
#define CV_ICC __ICC
#elif defined __ECL
#define CV_ICC __ECL
#elif defined __ECC
#define CV_ICC __ECC
#elif defined __INTEL_COMPILER
#define CV_ICC __INTEL_COMPILER
#endif

#if defined CV_ICC && !defined CV_ENABLE_UNROLLED
#define CV_ENABLE_UNROLLED 0
#else
#define CV_ENABLE_UNROLLED 1
#endif

#if (defined _M_X64 && defined _MSC_VER && _MSC_VER >= 1400) || (__GNUC__ >= 4 && defined __x86_64__)
# if defined WIN32
# include <intrin.h>
# endif
# if defined __SSE2__ || !defined __GNUC__
# include <emmintrin.h>
# endif
#endif

#if defined __BORLANDC__
# include <fastmath.h>
#else
# include <math.h>
#endif

#ifdef HAVE_IPL
# ifndef __IPL_H__
# if defined WIN32 || defined _WIN32
# include <ipl.h>
# else
# include <ipl/ipl.h>
# endif
# endif
#elif defined __IPL_H__
#define HAVE_IPL 
#endif

#endif

#if defined WIN32 || defined _WIN32
#define CV_CDECL __cdecl
#define CV_STDCALL __stdcall
#else
#define CV_CDECL 
#define CV_STDCALL 
#endif

#ifndef CV_EXTERN_C
# ifdef __cplusplus
#define CV_EXTERN_C extern "C"
#define CV_DEFAULT(val) = val
# else
#define CV_EXTERN_C 
#define CV_DEFAULT(val) 
# endif
#endif

#ifndef CV_EXTERN_C_FUNCPTR
# ifdef __cplusplus
#define CV_EXTERN_C_FUNCPTR(x) extern "C" { typedef x; }
# else
#define CV_EXTERN_C_FUNCPTR(x) typedef x
# endif
#endif

#ifndef CV_INLINE
# if defined __cplusplus
#define CV_INLINE inline
# elif defined _MSC_VER
#define CV_INLINE __inline
# else
#define CV_INLINE static
# endif
#endif

#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined CVAPI_EXPORTS
#define CV_EXPORTS __declspec(dllexport)
#else
#define CV_EXPORTS 
#endif

#ifndef CVAPI
#define CVAPI(rettype) CV_EXTERN_C CV_EXPORTS rettype CV_CDECL
#endif

#if defined _MSC_VER || defined __BORLANDC__
   typedef __int64 int64;
   typedef unsigned __int64 uint64;
#define CV_BIG_INT(n) n ##I64
#define CV_BIG_UINT(n) n ##UI64
#else
   typedef int64_t int64;
   typedef uint64_t uint64;
#define CV_BIG_INT(n) n ##LL
#define CV_BIG_UINT(n) n ##ULL
#endif

#ifndef HAVE_IPL
   typedef unsigned char uchar;
   typedef unsigned short ushort;
#endif

typedef signed char schar;


#define CV_CARRAY(counter) 
#define CV_CUSTOM_CARRAY(args) 
#define CV_EXPORTS_W CV_EXPORTS
#define CV_EXPORTS_W_SIMPLE CV_EXPORTS
#define CV_EXPORTS_AS(synonym) CV_EXPORTS
#define CV_EXPORTS_W_MAP CV_EXPORTS
#define CV_IN_OUT 
#define CV_OUT 
#define CV_PROP 
#define CV_PROP_RW 
#define CV_WRAP 
#define CV_WRAP_AS(synonym) 
#define CV_WRAP_DEFAULT(value) 






typedef void CvArr;

typedef union Cv32suf
{
    int i;
    unsigned u;
    float f;
}
Cv32suf;

typedef union Cv64suf
{
    int64 i;
    uint64 u;
    double f;
}
Cv64suf;

typedef int CVStatus;

enum {
 CV_StsOk= 0,
 CV_StsBackTrace= -1,
 CV_StsError= -2,
 CV_StsInternal= -3,
 CV_StsNoMem= -4,
 CV_StsBadArg= -5,
 CV_StsBadFunc= -6,
 CV_StsNoConv= -7,
 CV_StsAutoTrace= -8,
 CV_HeaderIsNull= -9,
 CV_BadImageSize= -10,
 CV_BadOffset= -11,
 CV_BadDataPtr= -12,
 CV_BadStep= -13,
 CV_BadModelOrChSeq= -14,
 CV_BadNumChannels= -15,
 CV_BadNumChannel1U= -16,
 CV_BadDepth= -17,
 CV_BadAlphaChannel= -18,
 CV_BadOrder= -19,
 CV_BadOrigin= -20,
 CV_BadAlign= -21,
 CV_BadCallBack= -22,
 CV_BadTileSize= -23,
 CV_BadCOI= -24,
 CV_BadROISize= -25,
 CV_MaskIsTiled= -26,
 CV_StsNullPtr= -27,
 CV_StsVecLengthErr= -28,
 CV_StsFilterStructContentErr= -29,
 CV_StsKernelStructContentErr= -30,
 CV_StsFilterOffsetErr= -31,
 CV_StsBadSize= -201,
 CV_StsDivByZero= -202,
 CV_StsInplaceNotSupported= -203,
 CV_StsObjectNotFound= -204,
 CV_StsUnmatchedFormats= -205,
 CV_StsBadFlag= -206,
 CV_StsBadPoint= -207,
 CV_StsBadMask= -208,
 CV_StsUnmatchedSizes= -209,
 CV_StsUnsupportedFormat= -210,
 CV_StsOutOfRange= -211,
 CV_StsParseError= -212,
 CV_StsNotImplemented= -213,
 CV_StsBadMemBlock= -214,
 CV_StsAssert= -215,
 CV_GpuNotSupported= -216,
 CV_GpuApiCallError= -217,
 CV_OpenGlNotSupported= -218,
 CV_OpenGlApiCallError= -219,
 CV_OpenCLDoubleNotSupported= -220,
 CV_OpenCLInitError= -221,
 CV_OpenCLNoAMDBlasFft= -222
};





#ifdef HAVE_TEGRA_OPTIMIZATION
# include "tegra_round.hpp"
#endif

#define CV_PI 3.1415926535897932384626433832795
#define CV_LOG2 0.69314718055994530941723212145818

#define CV_SWAP(a,b,t) ((t) = (a), (a) = (b), (b) = (t))

#ifndef MIN
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#endif


#define CV_IMIN(a,b) ((a) ^ (((a)^(b)) & (((a) < (b)) - 1)))

#define CV_IMAX(a,b) ((a) ^ (((a)^(b)) & (((a) > (b)) - 1)))


#ifndef __cplusplus
#define CV_IABS(a) (((a) ^ ((a) < 0 ? -1 : 0)) - ((a) < 0 ? -1 : 0))
#else
#define CV_IABS(a) abs(a)
#endif
#define CV_CMP(a,b) (((a) > (b)) - ((a) < (b)))
#define CV_SIGN(a) CV_CMP((a),0)

CV_INLINE int cvRound( double value )
{
#if (defined _MSC_VER && defined _M_X64) || (defined __GNUC__ && defined __x86_64__ && defined __SSE2__ && !defined __APPLE__)
    __m128d t = _mm_set_sd( value );
    return _mm_cvtsd_si32(t);
#elif defined _MSC_VER && defined _M_IX86
    int t;
    __asm
    {
        fld value;
        fistp t;
    }
    return t;
#elif defined _MSC_VER && defined _M_ARM && defined HAVE_TEGRA_OPTIMIZATION
    TEGRA_ROUND(value);
#elif defined CV_ICC || defined __GNUC__
# ifdef HAVE_TEGRA_OPTIMIZATION
    TEGRA_ROUND(value);
# else
    return (int)lrint(value);
# endif
#else
    double intpart, fractpart;
    fractpart = modf(value, &intpart);
    if ((fabs(fractpart) != 0.5) || ((((int)intpart) % 2) != 0))
        return (int)(value + (value >= 0 ? 0.5 : -0.5));
    else
        return (int)intpart;
#endif
}

#if defined __SSE2__ || (defined _M_IX86_FP && 2 == _M_IX86_FP)
# include "emmintrin.h"
#endif

CV_INLINE int cvFloor( double value )
{
#if defined _MSC_VER && defined _M_X64 || (defined __GNUC__ && defined __SSE2__ && !defined __APPLE__)
    __m128d t = _mm_set_sd( value );
    int i = _mm_cvtsd_si32(t);
    return i - _mm_movemask_pd(_mm_cmplt_sd(t, _mm_cvtsi32_sd(t,i)));
#elif defined __GNUC__
    int i = (int)value;
    return i - (i > value);
#else
    int i = cvRound(value);
    float diff = (float)(value - i);
    return i - (diff < 0);
#endif
}


CV_INLINE int cvCeil( double value )
{
#if defined _MSC_VER && defined _M_X64 || (defined __GNUC__ && defined __SSE2__&& !defined __APPLE__)
    __m128d t = _mm_set_sd( value );
    int i = _mm_cvtsd_si32(t);
    return i + _mm_movemask_pd(_mm_cmplt_sd(_mm_cvtsi32_sd(t,i), t));
#elif defined __GNUC__
    int i = (int)value;
    return i + (i < value);
#else
    int i = cvRound(value);
    float diff = (float)(i - value);
    return i + (diff < 0);
#endif
}

#define cvInvSqrt(value) ((float)(1./sqrt(value)))
#define cvSqrt(value) ((float)sqrt(value))

CV_INLINE int cvIsNaN( double value )
{
    Cv64suf ieee754;
    ieee754.f = value;
    return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) +
           ((unsigned)ieee754.u != 0) > 0x7ff00000;
}


CV_INLINE int cvIsInf( double value )
{
    Cv64suf ieee754;
    ieee754.f = value;
    return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) == 0x7ff00000 &&
           (unsigned)ieee754.u == 0;
}




typedef uint64 CvRNG;

#define CV_RNG_COEFF 4164903690U

CV_INLINE CvRNG cvRNG( int64 seed CV_DEFAULT(-1))
{
    CvRNG rng = seed ? (uint64)seed : (uint64)(int64)-1;
    return rng;
}


CV_INLINE unsigned cvRandInt( CvRNG* rng )
{
    uint64 temp = *rng;
    temp = (uint64)(unsigned)temp*CV_RNG_COEFF + (temp >> 32);
    *rng = temp;
    return (unsigned)temp;
}


CV_INLINE double cvRandReal( CvRNG* rng )
{
    return cvRandInt(rng)*2.3283064365386962890625e-10 ;
}





#ifndef HAVE_IPL






#define IPL_DEPTH_SIGN 0x80000000

#define IPL_DEPTH_1U 1
#define IPL_DEPTH_8U 8
#define IPL_DEPTH_16U 16
#define IPL_DEPTH_32F 32

#define IPL_DEPTH_8S (IPL_DEPTH_SIGN| 8)
#define IPL_DEPTH_16S (IPL_DEPTH_SIGN|16)
#define IPL_DEPTH_32S (IPL_DEPTH_SIGN|32)

#define IPL_DATA_ORDER_PIXEL 0
#define IPL_DATA_ORDER_PLANE 1

#define IPL_ORIGIN_TL 0
#define IPL_ORIGIN_BL 1

#define IPL_ALIGN_4BYTES 4
#define IPL_ALIGN_8BYTES 8
#define IPL_ALIGN_16BYTES 16
#define IPL_ALIGN_32BYTES 32

#define IPL_ALIGN_DWORD IPL_ALIGN_4BYTES
#define IPL_ALIGN_QWORD IPL_ALIGN_8BYTES

#define IPL_BORDER_CONSTANT 0
#define IPL_BORDER_REPLICATE 1
#define IPL_BORDER_REFLECT 2
#define IPL_BORDER_WRAP 3

typedef struct _IplImage
{
    int nSize;
    int ID;
    int nChannels;
    int alphaChannel;
    int depth;

    char colorModel[4];
    char channelSeq[4];
    int dataOrder;

    int origin;

    int align;

    int width;
    int height;
    struct _IplROI *roi;
    struct _IplImage *maskROI;
    void *imageId;
    struct _IplTileInfo *tileInfo;
    int imageSize;


    char *imageData;
    int widthStep;
    int BorderMode[4];
    int BorderConst[4];
    char *imageDataOrigin;


}
IplImage;

typedef struct _IplTileInfo IplTileInfo;

typedef struct _IplROI
{
    int coi;
    int xOffset;
    int yOffset;
    int width;
    int height;
}
IplROI;

typedef struct _IplConvKernel
{
    int nCols;
    int nRows;
    int anchorX;
    int anchorY;
    int *values;
    int nShiftR;
}
IplConvKernel;

typedef struct _IplConvKernelFP
{
    int nCols;
    int nRows;
    int anchorX;
    int anchorY;
    float *values;
}
IplConvKernelFP;

#define IPL_IMAGE_HEADER 1
#define IPL_IMAGE_DATA 2
#define IPL_IMAGE_ROI 4

#endif


#define IPL_BORDER_REFLECT_101 4
#define IPL_BORDER_TRANSPARENT 5

#define IPL_IMAGE_MAGIC_VAL ((int)sizeof(IplImage))
#define CV_TYPE_NAME_IMAGE "opencv-image"

#define CV_IS_IMAGE_HDR(img) \
    ((img) != NULL && ((const IplImage*)(img))->nSize == sizeof(IplImage))

#define CV_IS_IMAGE(img) \
    (CV_IS_IMAGE_HDR(img) && ((IplImage*)img)->imageData != NULL)



#define IPL_DEPTH_64F 64



#define CV_IMAGE_ELEM(image,elemtype,row,col) \
    (((elemtype*)((image)->imageData + (image)->widthStep*(row)))[(col)])





#define CV_CN_MAX 512
#define CV_CN_SHIFT 3
#define CV_DEPTH_MAX (1 << CV_CN_SHIFT)

#define CV_8U 0
#define CV_8S 1
#define CV_16U 2
#define CV_16S 3
#define CV_32S 4
#define CV_32F 5
#define CV_64F 6
#define CV_USRTYPE1 7

#define CV_MAT_DEPTH_MASK (CV_DEPTH_MAX - 1)
#define CV_MAT_DEPTH(flags) ((flags) & CV_MAT_DEPTH_MASK)

#define CV_MAKETYPE(depth,cn) (CV_MAT_DEPTH(depth) + (((cn)-1) << CV_CN_SHIFT))
#define CV_MAKE_TYPE CV_MAKETYPE

#define CV_8UC1 CV_MAKETYPE(CV_8U,1)
#define CV_8UC2 CV_MAKETYPE(CV_8U,2)
#define CV_8UC3 CV_MAKETYPE(CV_8U,3)
#define CV_8UC4 CV_MAKETYPE(CV_8U,4)
#define CV_8UC(n) CV_MAKETYPE(CV_8U,(n))

#define CV_8SC1 CV_MAKETYPE(CV_8S,1)
#define CV_8SC2 CV_MAKETYPE(CV_8S,2)
#define CV_8SC3 CV_MAKETYPE(CV_8S,3)
#define CV_8SC4 CV_MAKETYPE(CV_8S,4)
#define CV_8SC(n) CV_MAKETYPE(CV_8S,(n))

#define CV_16UC1 CV_MAKETYPE(CV_16U,1)
#define CV_16UC2 CV_MAKETYPE(CV_16U,2)
#define CV_16UC3 CV_MAKETYPE(CV_16U,3)
#define CV_16UC4 CV_MAKETYPE(CV_16U,4)
#define CV_16UC(n) CV_MAKETYPE(CV_16U,(n))

#define CV_16SC1 CV_MAKETYPE(CV_16S,1)
#define CV_16SC2 CV_MAKETYPE(CV_16S,2)
#define CV_16SC3 CV_MAKETYPE(CV_16S,3)
#define CV_16SC4 CV_MAKETYPE(CV_16S,4)
#define CV_16SC(n) CV_MAKETYPE(CV_16S,(n))

#define CV_32SC1 CV_MAKETYPE(CV_32S,1)
#define CV_32SC2 CV_MAKETYPE(CV_32S,2)
#define CV_32SC3 CV_MAKETYPE(CV_32S,3)
#define CV_32SC4 CV_MAKETYPE(CV_32S,4)
#define CV_32SC(n) CV_MAKETYPE(CV_32S,(n))

#define CV_32FC1 CV_MAKETYPE(CV_32F,1)
#define CV_32FC2 CV_MAKETYPE(CV_32F,2)
#define CV_32FC3 CV_MAKETYPE(CV_32F,3)
#define CV_32FC4 CV_MAKETYPE(CV_32F,4)
#define CV_32FC(n) CV_MAKETYPE(CV_32F,(n))

#define CV_64FC1 CV_MAKETYPE(CV_64F,1)
#define CV_64FC2 CV_MAKETYPE(CV_64F,2)
#define CV_64FC3 CV_MAKETYPE(CV_64F,3)
#define CV_64FC4 CV_MAKETYPE(CV_64F,4)
#define CV_64FC(n) CV_MAKETYPE(CV_64F,(n))

#define CV_AUTO_STEP 0x7fffffff
#define CV_WHOLE_ARR cvSlice( 0, 0x3fffffff )

#define CV_MAT_CN_MASK ((CV_CN_MAX - 1) << CV_CN_SHIFT)
#define CV_MAT_CN(flags) ((((flags) & CV_MAT_CN_MASK) >> CV_CN_SHIFT) + 1)
#define CV_MAT_TYPE_MASK (CV_DEPTH_MAX*CV_CN_MAX - 1)
#define CV_MAT_TYPE(flags) ((flags) & CV_MAT_TYPE_MASK)
#define CV_MAT_CONT_FLAG_SHIFT 14
#define CV_MAT_CONT_FLAG (1 << CV_MAT_CONT_FLAG_SHIFT)
#define CV_IS_MAT_CONT(flags) ((flags) & CV_MAT_CONT_FLAG)
#define CV_IS_CONT_MAT CV_IS_MAT_CONT
#define CV_SUBMAT_FLAG_SHIFT 15
#define CV_SUBMAT_FLAG (1 << CV_SUBMAT_FLAG_SHIFT)
#define CV_IS_SUBMAT(flags) ((flags) & CV_MAT_SUBMAT_FLAG)

#define CV_MAGIC_MASK 0xFFFF0000
#define CV_MAT_MAGIC_VAL 0x42420000
#define CV_TYPE_NAME_MAT "opencv-matrix"

typedef struct CvMat
{
    int type;
    int step;


    int* refcount;
    int hdr_refcount;

    union
    {
        uchar* ptr;
        short* s;
        int* i;
        float* fl;
        double* db;
    } data;

#ifdef __cplusplus
    union
    {
        int rows;
        int height;
    };

    union
    {
        int cols;
        int width;
    };
#else
    int rows;
    int cols;
#endif

}
CvMat;


#define CV_IS_MAT_HDR(mat) \
    ((mat) != NULL && \
    (((const CvMat*)(mat))->type & CV_MAGIC_MASK) == CV_MAT_MAGIC_VAL && \
    ((const CvMat*)(mat))->cols > 0 && ((const CvMat*)(mat))->rows > 0)

#define CV_IS_MAT_HDR_Z(mat) \
    ((mat) != NULL && \
    (((const CvMat*)(mat))->type & CV_MAGIC_MASK) == CV_MAT_MAGIC_VAL && \
    ((const CvMat*)(mat))->cols >= 0 && ((const CvMat*)(mat))->rows >= 0)

#define CV_IS_MAT(mat) \
    (CV_IS_MAT_HDR(mat) && ((const CvMat*)(mat))->data.ptr != NULL)

#define CV_IS_MASK_ARR(mat) \
    (((mat)->type & (CV_MAT_TYPE_MASK & ~CV_8SC1)) == 0)

#define CV_ARE_TYPES_EQ(mat1,mat2) \
    ((((mat1)->type ^ (mat2)->type) & CV_MAT_TYPE_MASK) == 0)

#define CV_ARE_CNS_EQ(mat1,mat2) \
    ((((mat1)->type ^ (mat2)->type) & CV_MAT_CN_MASK) == 0)

#define CV_ARE_DEPTHS_EQ(mat1,mat2) \
    ((((mat1)->type ^ (mat2)->type) & CV_MAT_DEPTH_MASK) == 0)

#define CV_ARE_SIZES_EQ(mat1,mat2) \
    ((mat1)->rows == (mat2)->rows && (mat1)->cols == (mat2)->cols)

#define CV_IS_MAT_CONST(mat) \
    (((mat)->rows|(mat)->cols) == 1)



#define CV_ELEM_SIZE1(type) \
    ((((sizeof(size_t)<<28)|0x8442211) >> CV_MAT_DEPTH(type)*4) & 15)


#define CV_ELEM_SIZE(type) \
    (CV_MAT_CN(type) << ((((sizeof(size_t)/4+1)*16384|0x3a50) >> CV_MAT_DEPTH(type)*2) & 3))

#define IPL2CV_DEPTH(depth) \
    ((((CV_8U)+(CV_16U<<4)+(CV_32F<<8)+(CV_64F<<16)+(CV_8S<<20)+ \
    (CV_16S<<24)+(CV_32S<<28)) >> ((((depth) & 0xF0) >> 2) + \
    (((depth) & IPL_DEPTH_SIGN) ? 20 : 0))) & 15)





CV_INLINE CvMat cvMat( int rows, int cols, int type, void* data CV_DEFAULT(NULL))
{
    CvMat m;

    assert( (unsigned)CV_MAT_DEPTH(type) <= CV_64F );
    type = CV_MAT_TYPE(type);
    m.type = CV_MAT_MAGIC_VAL | CV_MAT_CONT_FLAG | type;
    m.cols = cols;
    m.rows = rows;
    m.step = m.cols*CV_ELEM_SIZE(type);
    m.data.ptr = (uchar*)data;
    m.refcount = NULL;
    m.hdr_refcount = 0;

    return m;
}


#define CV_MAT_ELEM_PTR_FAST(mat,row,col,pix_size) \
    (assert( (unsigned)(row) < (unsigned)(mat).rows && \
             (unsigned)(col) < (unsigned)(mat).cols ), \
     (mat).data.ptr + (size_t)(mat).step*(row) + (pix_size)*(col))

#define CV_MAT_ELEM_PTR(mat,row,col) \
    CV_MAT_ELEM_PTR_FAST( mat, row, col, CV_ELEM_SIZE((mat).type) )

#define CV_MAT_ELEM(mat,elemtype,row,col) \
    (*(elemtype*)CV_MAT_ELEM_PTR_FAST( mat, row, col, sizeof(elemtype)))


CV_INLINE double cvmGet( const CvMat* mat, int row, int col )
{
    int type;

    type = CV_MAT_TYPE(mat->type);
    assert( (unsigned)row < (unsigned)mat->rows &&
            (unsigned)col < (unsigned)mat->cols );

    if( type == CV_32FC1 )
        return ((float*)(void*)(mat->data.ptr + (size_t)mat->step*row))[col];
    else
    {
        assert( type == CV_64FC1 );
        return ((double*)(void*)(mat->data.ptr + (size_t)mat->step*row))[col];
    }
}


CV_INLINE void cvmSet( CvMat* mat, int row, int col, double value )
{
    int type;
    type = CV_MAT_TYPE(mat->type);
    assert( (unsigned)row < (unsigned)mat->rows &&
            (unsigned)col < (unsigned)mat->cols );

    if( type == CV_32FC1 )
        ((float*)(void*)(mat->data.ptr + (size_t)mat->step*row))[col] = (float)value;
    else
    {
        assert( type == CV_64FC1 );
        ((double*)(void*)(mat->data.ptr + (size_t)mat->step*row))[col] = value;
    }
}


CV_INLINE int cvIplDepth( int type )
{
    int depth = CV_MAT_DEPTH(type);
    return CV_ELEM_SIZE1(depth)*8 | (depth == CV_8S || depth == CV_16S ||
           depth == CV_32S ? IPL_DEPTH_SIGN : 0);
}






#define CV_MATND_MAGIC_VAL 0x42430000
#define CV_TYPE_NAME_MATND "opencv-nd-matrix"

#define CV_MAX_DIM 32
#define CV_MAX_DIM_HEAP 1024

typedef struct CvMatND
{
    int type;
    int dims;

    int* refcount;
    int hdr_refcount;

    union
    {
        uchar* ptr;
        float* fl;
        double* db;
        int* i;
        short* s;
    } data;

    struct
    {
        int size;
        int step;
    }
    dim[CV_MAX_DIM];
}
CvMatND;

#define CV_IS_MATND_HDR(mat) \
    ((mat) != NULL && (((const CvMatND*)(mat))->type & CV_MAGIC_MASK) == CV_MATND_MAGIC_VAL)

#define CV_IS_MATND(mat) \
    (CV_IS_MATND_HDR(mat) && ((const CvMatND*)(mat))->data.ptr != NULL)






#define CV_SPARSE_MAT_MAGIC_VAL 0x42440000
#define CV_TYPE_NAME_SPARSE_MAT "opencv-sparse-matrix"

struct CvSet;

typedef struct CvSparseMat
{
    int type;
    int dims;
    int* refcount;
    int hdr_refcount;

    struct CvSet* heap;
    void** hashtable;
    int hashsize;
    int valoffset;
    int idxoffset;
    int size[CV_MAX_DIM];
}
CvSparseMat;

#define CV_IS_SPARSE_MAT_HDR(mat) \
    ((mat) != NULL && \
    (((const CvSparseMat*)(mat))->type & CV_MAGIC_MASK) == CV_SPARSE_MAT_MAGIC_VAL)

#define CV_IS_SPARSE_MAT(mat) \
    CV_IS_SPARSE_MAT_HDR(mat)



typedef struct CvSparseNode
{
    unsigned hashval;
    struct CvSparseNode* next;
}
CvSparseNode;

typedef struct CvSparseMatIterator
{
    CvSparseMat* mat;
    CvSparseNode* node;
    int curidx;
}
CvSparseMatIterator;

#define CV_NODE_VAL(mat,node) ((void*)((uchar*)(node) + (mat)->valoffset))
#define CV_NODE_IDX(mat,node) ((int*)((uchar*)(node) + (mat)->idxoffset))





typedef int CvHistType;

#define CV_HIST_MAGIC_VAL 0x42450000
#define CV_HIST_UNIFORM_FLAG (1 << 10)


#define CV_HIST_RANGES_FLAG (1 << 11)

#define CV_HIST_ARRAY 0
#define CV_HIST_SPARSE 1
#define CV_HIST_TREE CV_HIST_SPARSE



#define CV_HIST_UNIFORM 1

typedef struct CvHistogram
{
    int type;
    CvArr* bins;
    float thresh[CV_MAX_DIM][2];
    float** thresh2;
    CvMatND mat;
}
CvHistogram;

#define CV_IS_HIST(hist) \
    ((hist) != NULL && \
     (((CvHistogram*)(hist))->type & CV_MAGIC_MASK) == CV_HIST_MAGIC_VAL && \
     (hist)->bins != NULL)

#define CV_IS_UNIFORM_HIST(hist) \
    (((hist)->type & CV_HIST_UNIFORM_FLAG) != 0)

#define CV_IS_SPARSE_HIST(hist) \
    CV_IS_SPARSE_MAT((hist)->bins)

#define CV_HIST_HAS_RANGES(hist) \
    (((hist)->type & CV_HIST_RANGES_FLAG) != 0)







typedef struct CvRect
{
    int x;
    int y;
    int width;
    int height;
}
CvRect;

CV_INLINE CvRect cvRect( int x, int y, int width, int height )
{
    CvRect r;

    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;

    return r;
}


CV_INLINE IplROI cvRectToROI( CvRect rect, int coi )
{
    IplROI roi;
    roi.xOffset = rect.x;
    roi.yOffset = rect.y;
    roi.width = rect.width;
    roi.height = rect.height;
    roi.coi = coi;

    return roi;
}


CV_INLINE CvRect cvROIToRect( IplROI roi )
{
    return cvRect( roi.xOffset, roi.yOffset, roi.width, roi.height );
}



#define CV_TERMCRIT_ITER 1
#define CV_TERMCRIT_NUMBER CV_TERMCRIT_ITER
#define CV_TERMCRIT_EPS 2

typedef struct CvTermCriteria
{
    int type;


    int max_iter;
    double epsilon;
}
CvTermCriteria;

CV_INLINE CvTermCriteria cvTermCriteria( int type, int max_iter, double epsilon )
{
    CvTermCriteria t;

    t.type = type;
    t.max_iter = max_iter;
    t.epsilon = (float)epsilon;

    return t;
}




typedef struct CvPoint
{
    int x;
    int y;
}
CvPoint;


CV_INLINE CvPoint cvPoint( int x, int y )
{
    CvPoint p;

    p.x = x;
    p.y = y;

    return p;
}


typedef struct CvPoint2D32f
{
    float x;
    float y;
}
CvPoint2D32f;


CV_INLINE CvPoint2D32f cvPoint2D32f( double x, double y )
{
    CvPoint2D32f p;

    p.x = (float)x;
    p.y = (float)y;

    return p;
}


CV_INLINE CvPoint2D32f cvPointTo32f( CvPoint point )
{
    return cvPoint2D32f( (float)point.x, (float)point.y );
}


CV_INLINE CvPoint cvPointFrom32f( CvPoint2D32f point )
{
    CvPoint ipt;
    ipt.x = cvRound(point.x);
    ipt.y = cvRound(point.y);

    return ipt;
}


typedef struct CvPoint3D32f
{
    float x;
    float y;
    float z;
}
CvPoint3D32f;


CV_INLINE CvPoint3D32f cvPoint3D32f( double x, double y, double z )
{
    CvPoint3D32f p;

    p.x = (float)x;
    p.y = (float)y;
    p.z = (float)z;

    return p;
}


typedef struct CvPoint2D64f
{
    double x;
    double y;
}
CvPoint2D64f;


CV_INLINE CvPoint2D64f cvPoint2D64f( double x, double y )
{
    CvPoint2D64f p;

    p.x = x;
    p.y = y;

    return p;
}


typedef struct CvPoint3D64f
{
    double x;
    double y;
    double z;
}
CvPoint3D64f;


CV_INLINE CvPoint3D64f cvPoint3D64f( double x, double y, double z )
{
    CvPoint3D64f p;

    p.x = x;
    p.y = y;
    p.z = z;

    return p;
}




typedef struct CvSize
{
    int width;
    int height;
}
CvSize;

CV_INLINE CvSize cvSize( int width, int height )
{
    CvSize s;

    s.width = width;
    s.height = height;

    return s;
}

typedef struct CvSize2D32f
{
    float width;
    float height;
}
CvSize2D32f;


CV_INLINE CvSize2D32f cvSize2D32f( double width, double height )
{
    CvSize2D32f s;

    s.width = (float)width;
    s.height = (float)height;

    return s;
}

typedef struct CvBox2D
{
    CvPoint2D32f center;
    CvSize2D32f size;
    float angle;

}
CvBox2D;



typedef struct CvLineIterator
{

    uchar* ptr;


    int err;
    int plus_delta;
    int minus_delta;
    int plus_step;
    int minus_step;
}
CvLineIterator;





typedef struct CvSlice
{
    int start_index, end_index;
}
CvSlice;

CV_INLINE CvSlice cvSlice( int start, int end )
{
    CvSlice slice;
    slice.start_index = start;
    slice.end_index = end;

    return slice;
}

#define CV_WHOLE_SEQ_END_INDEX 0x3fffffff
#define CV_WHOLE_SEQ cvSlice(0, CV_WHOLE_SEQ_END_INDEX)




typedef struct CvScalar
{
    double val[4];
}
CvScalar;

CV_INLINE CvScalar cvScalar( double val0, double val1 CV_DEFAULT(0),
                               double val2 CV_DEFAULT(0), double val3 CV_DEFAULT(0))
{
    CvScalar scalar;
    scalar.val[0] = val0; scalar.val[1] = val1;
    scalar.val[2] = val2; scalar.val[3] = val3;
    return scalar;
}


CV_INLINE CvScalar cvRealScalar( double val0 )
{
    CvScalar scalar;
    scalar.val[0] = val0;
    scalar.val[1] = scalar.val[2] = scalar.val[3] = 0;
    return scalar;
}

CV_INLINE CvScalar cvScalarAll( double val0123 )
{
    CvScalar scalar;
    scalar.val[0] = val0123;
    scalar.val[1] = val0123;
    scalar.val[2] = val0123;
    scalar.val[3] = val0123;
    return scalar;
}







typedef struct CvMemBlock
{
    struct CvMemBlock* prev;
    struct CvMemBlock* next;
}
CvMemBlock;

#define CV_STORAGE_MAGIC_VAL 0x42890000

typedef struct CvMemStorage
{
    int signature;
    CvMemBlock* bottom;
    CvMemBlock* top;
    struct CvMemStorage* parent;
    int block_size;
    int free_space;
}
CvMemStorage;

#define CV_IS_STORAGE(storage) \
    ((storage) != NULL && \
    (((CvMemStorage*)(storage))->signature & CV_MAGIC_MASK) == CV_STORAGE_MAGIC_VAL)


typedef struct CvMemStoragePos
{
    CvMemBlock* top;
    int free_space;
}
CvMemStoragePos;




typedef struct CvSeqBlock
{
    struct CvSeqBlock* prev;
    struct CvSeqBlock* next;
  int start_index;

    int count;
    schar* data;
}
CvSeqBlock;


#define CV_TREE_NODE_FIELDS(node_type) \
    int flags; \
    int header_size; \
    struct node_type* h_prev; \
    struct node_type* h_next; \
    struct node_type* v_prev; \
    struct node_type* v_next





#define CV_SEQUENCE_FIELDS() \
    CV_TREE_NODE_FIELDS(CvSeq); \
    int total; \
    int elem_size; \
    schar* block_max; \
    schar* ptr; \
    int delta_elems; \
    CvMemStorage* storage; \
    CvSeqBlock* free_blocks; \
    CvSeqBlock* first;

typedef struct CvSeq
{
    CV_SEQUENCE_FIELDS()
}
CvSeq;

#define CV_TYPE_NAME_SEQ "opencv-sequence"
#define CV_TYPE_NAME_SEQ_TREE "opencv-sequence-tree"
#define CV_SET_ELEM_FIELDS(elem_type) \
    int flags; \
    struct elem_type* next_free;

typedef struct CvSetElem
{
    CV_SET_ELEM_FIELDS(CvSetElem)
}
CvSetElem;

#define CV_SET_FIELDS() \
    CV_SEQUENCE_FIELDS() \
    CvSetElem* free_elems; \
    int active_count;

typedef struct CvSet
{
    CV_SET_FIELDS()
}
CvSet;


#define CV_SET_ELEM_IDX_MASK ((1 << 26) - 1)
#define CV_SET_ELEM_FREE_FLAG (1 << (sizeof(int)*8-1))


#define CV_IS_SET_ELEM(ptr) (((CvSetElem*)(ptr))->flags >= 0)
#define CV_GRAPH_EDGE_FIELDS() \
    int flags; \
    float weight; \
    struct CvGraphEdge* next[2]; \
    struct CvGraphVtx* vtx[2];


#define CV_GRAPH_VERTEX_FIELDS() \
    int flags; \
    struct CvGraphEdge* first;


typedef struct CvGraphEdge
{
    CV_GRAPH_EDGE_FIELDS()
}
CvGraphEdge;

typedef struct CvGraphVtx
{
    CV_GRAPH_VERTEX_FIELDS()
}
CvGraphVtx;

typedef struct CvGraphVtx2D
{
    CV_GRAPH_VERTEX_FIELDS()
    CvPoint2D32f* ptr;
}
CvGraphVtx2D;





#define CV_GRAPH_FIELDS() \
    CV_SET_FIELDS() \
    CvSet* edges;

typedef struct CvGraph
{
    CV_GRAPH_FIELDS()
}
CvGraph;

#define CV_TYPE_NAME_GRAPH "opencv-graph"



typedef struct CvChain
{
    CV_SEQUENCE_FIELDS()
    CvPoint origin;
}
CvChain;

#define CV_CONTOUR_FIELDS() \
    CV_SEQUENCE_FIELDS() \
    CvRect rect; \
    int color; \
    int reserved[3];

typedef struct CvContour
{
    CV_CONTOUR_FIELDS()
}
CvContour;

typedef CvContour CvPoint2DSeq;





#define CV_SEQ_MAGIC_VAL 0x42990000

#define CV_IS_SEQ(seq) \
    ((seq) != NULL && (((CvSeq*)(seq))->flags & CV_MAGIC_MASK) == CV_SEQ_MAGIC_VAL)

#define CV_SET_MAGIC_VAL 0x42980000
#define CV_IS_SET(set) \
    ((set) != NULL && (((CvSeq*)(set))->flags & CV_MAGIC_MASK) == CV_SET_MAGIC_VAL)

#define CV_SEQ_ELTYPE_BITS 12
#define CV_SEQ_ELTYPE_MASK ((1 << CV_SEQ_ELTYPE_BITS) - 1)

#define CV_SEQ_ELTYPE_POINT CV_32SC2
#define CV_SEQ_ELTYPE_CODE CV_8UC1
#define CV_SEQ_ELTYPE_GENERIC 0
#define CV_SEQ_ELTYPE_PTR CV_USRTYPE1
#define CV_SEQ_ELTYPE_PPOINT CV_SEQ_ELTYPE_PTR
#define CV_SEQ_ELTYPE_INDEX CV_32SC1
#define CV_SEQ_ELTYPE_GRAPH_EDGE 0
#define CV_SEQ_ELTYPE_GRAPH_VERTEX 0
#define CV_SEQ_ELTYPE_TRIAN_ATR 0
#define CV_SEQ_ELTYPE_CONNECTED_COMP 0
#define CV_SEQ_ELTYPE_POINT3D CV_32FC3

#define CV_SEQ_KIND_BITS 2
#define CV_SEQ_KIND_MASK (((1 << CV_SEQ_KIND_BITS) - 1)<<CV_SEQ_ELTYPE_BITS)


#define CV_SEQ_KIND_GENERIC (0 << CV_SEQ_ELTYPE_BITS)
#define CV_SEQ_KIND_CURVE (1 << CV_SEQ_ELTYPE_BITS)
#define CV_SEQ_KIND_BIN_TREE (2 << CV_SEQ_ELTYPE_BITS)


#define CV_SEQ_KIND_GRAPH (1 << CV_SEQ_ELTYPE_BITS)
#define CV_SEQ_KIND_SUBDIV2D (2 << CV_SEQ_ELTYPE_BITS)

#define CV_SEQ_FLAG_SHIFT (CV_SEQ_KIND_BITS + CV_SEQ_ELTYPE_BITS)


#define CV_SEQ_FLAG_CLOSED (1 << CV_SEQ_FLAG_SHIFT)
#define CV_SEQ_FLAG_SIMPLE (0 << CV_SEQ_FLAG_SHIFT)
#define CV_SEQ_FLAG_CONVEX (0 << CV_SEQ_FLAG_SHIFT)
#define CV_SEQ_FLAG_HOLE (2 << CV_SEQ_FLAG_SHIFT)


#define CV_GRAPH_FLAG_ORIENTED (1 << CV_SEQ_FLAG_SHIFT)

#define CV_GRAPH CV_SEQ_KIND_GRAPH
#define CV_ORIENTED_GRAPH (CV_SEQ_KIND_GRAPH|CV_GRAPH_FLAG_ORIENTED)


#define CV_SEQ_POINT_SET (CV_SEQ_KIND_GENERIC| CV_SEQ_ELTYPE_POINT)
#define CV_SEQ_POINT3D_SET (CV_SEQ_KIND_GENERIC| CV_SEQ_ELTYPE_POINT3D)
#define CV_SEQ_POLYLINE (CV_SEQ_KIND_CURVE | CV_SEQ_ELTYPE_POINT)
#define CV_SEQ_POLYGON (CV_SEQ_FLAG_CLOSED | CV_SEQ_POLYLINE )
#define CV_SEQ_CONTOUR CV_SEQ_POLYGON
#define CV_SEQ_SIMPLE_POLYGON (CV_SEQ_FLAG_SIMPLE | CV_SEQ_POLYGON )


#define CV_SEQ_CHAIN (CV_SEQ_KIND_CURVE | CV_SEQ_ELTYPE_CODE)
#define CV_SEQ_CHAIN_CONTOUR (CV_SEQ_FLAG_CLOSED | CV_SEQ_CHAIN)


#define CV_SEQ_POLYGON_TREE (CV_SEQ_KIND_BIN_TREE | CV_SEQ_ELTYPE_TRIAN_ATR)


#define CV_SEQ_CONNECTED_COMP (CV_SEQ_KIND_GENERIC | CV_SEQ_ELTYPE_CONNECTED_COMP)


#define CV_SEQ_INDEX (CV_SEQ_KIND_GENERIC | CV_SEQ_ELTYPE_INDEX)

#define CV_SEQ_ELTYPE(seq) ((seq)->flags & CV_SEQ_ELTYPE_MASK)
#define CV_SEQ_KIND(seq) ((seq)->flags & CV_SEQ_KIND_MASK )


#define CV_IS_SEQ_INDEX(seq) ((CV_SEQ_ELTYPE(seq) == CV_SEQ_ELTYPE_INDEX) && \
                                     (CV_SEQ_KIND(seq) == CV_SEQ_KIND_GENERIC))

#define CV_IS_SEQ_CURVE(seq) (CV_SEQ_KIND(seq) == CV_SEQ_KIND_CURVE)
#define CV_IS_SEQ_CLOSED(seq) (((seq)->flags & CV_SEQ_FLAG_CLOSED) != 0)
#define CV_IS_SEQ_CONVEX(seq) 0
#define CV_IS_SEQ_HOLE(seq) (((seq)->flags & CV_SEQ_FLAG_HOLE) != 0)
#define CV_IS_SEQ_SIMPLE(seq) 1


#define CV_IS_SEQ_POINT_SET(seq) \
    ((CV_SEQ_ELTYPE(seq) == CV_32SC2 || CV_SEQ_ELTYPE(seq) == CV_32FC2))

#define CV_IS_SEQ_POINT_SUBSET(seq) \
    (CV_IS_SEQ_INDEX( seq ) || CV_SEQ_ELTYPE(seq) == CV_SEQ_ELTYPE_PPOINT)

#define CV_IS_SEQ_POLYLINE(seq) \
    (CV_SEQ_KIND(seq) == CV_SEQ_KIND_CURVE && CV_IS_SEQ_POINT_SET(seq))

#define CV_IS_SEQ_POLYGON(seq) \
    (CV_IS_SEQ_POLYLINE(seq) && CV_IS_SEQ_CLOSED(seq))

#define CV_IS_SEQ_CHAIN(seq) \
    (CV_SEQ_KIND(seq) == CV_SEQ_KIND_CURVE && (seq)->elem_size == 1)

#define CV_IS_SEQ_CONTOUR(seq) \
    (CV_IS_SEQ_CLOSED(seq) && (CV_IS_SEQ_POLYLINE(seq) || CV_IS_SEQ_CHAIN(seq)))

#define CV_IS_SEQ_CHAIN_CONTOUR(seq) \
    (CV_IS_SEQ_CHAIN( seq ) && CV_IS_SEQ_CLOSED( seq ))

#define CV_IS_SEQ_POLYGON_TREE(seq) \
    (CV_SEQ_ELTYPE (seq) == CV_SEQ_ELTYPE_TRIAN_ATR && \
    CV_SEQ_KIND( seq ) == CV_SEQ_KIND_BIN_TREE )

#define CV_IS_GRAPH(seq) \
    (CV_IS_SET(seq) && CV_SEQ_KIND((CvSet*)(seq)) == CV_SEQ_KIND_GRAPH)

#define CV_IS_GRAPH_ORIENTED(seq) \
    (((seq)->flags & CV_GRAPH_FLAG_ORIENTED) != 0)

#define CV_IS_SUBDIV2D(seq) \
    (CV_IS_SET(seq) && CV_SEQ_KIND((CvSet*)(seq)) == CV_SEQ_KIND_SUBDIV2D)





#define CV_SEQ_WRITER_FIELDS() \
    int header_size; \
    CvSeq* seq; \
    CvSeqBlock* block; \
    schar* ptr; \
    schar* block_min; \
    schar* block_max;

typedef struct CvSeqWriter
{
    CV_SEQ_WRITER_FIELDS()
}
CvSeqWriter;


#define CV_SEQ_READER_FIELDS() \
    int header_size; \
    CvSeq* seq; \
    CvSeqBlock* block; \
    schar* ptr; \
    schar* block_min; \
    schar* block_max; \
    int delta_index; \
    schar* prev_elem;


typedef struct CvSeqReader
{
    CV_SEQ_READER_FIELDS()
}
CvSeqReader;





#define CV_SEQ_ELEM(seq,elem_type,index) \
                                                                 \
( assert(sizeof((seq)->first[0]) == sizeof(CvSeqBlock) && \
    (seq)->elem_size == sizeof(elem_type)), \
    (elem_type*)((seq)->first && (unsigned)index < \
    (unsigned)((seq)->first->count) ? \
    (seq)->first->data + (index) * sizeof(elem_type) : \
    cvGetSeqElem( (CvSeq*)(seq), (index) )))
#define CV_GET_SEQ_ELEM(elem_type,seq,index) CV_SEQ_ELEM( (seq), elem_type, (index) )


#define CV_WRITE_SEQ_ELEM_VAR(elem_ptr,writer) \
{ \
    if( (writer).ptr >= (writer).block_max ) \
    { \
        cvCreateSeqBlock( &writer); \
    } \
    memcpy((writer).ptr, elem_ptr, (writer).seq->elem_size);\
    (writer).ptr += (writer).seq->elem_size; \
}

#define CV_WRITE_SEQ_ELEM(elem,writer) \
{ \
    assert( (writer).seq->elem_size == sizeof(elem)); \
    if( (writer).ptr >= (writer).block_max ) \
    { \
        cvCreateSeqBlock( &writer); \
    } \
    assert( (writer).ptr <= (writer).block_max - sizeof(elem));\
    memcpy((writer).ptr, &(elem), sizeof(elem)); \
    (writer).ptr += sizeof(elem); \
}



#define CV_NEXT_SEQ_ELEM(elem_size,reader) \
{ \
    if( ((reader).ptr += (elem_size)) >= (reader).block_max ) \
    { \
        cvChangeSeqBlock( &(reader), 1 ); \
    } \
}



#define CV_PREV_SEQ_ELEM(elem_size,reader) \
{ \
    if( ((reader).ptr -= (elem_size)) < (reader).block_min ) \
    { \
        cvChangeSeqBlock( &(reader), -1 ); \
    } \
}


#define CV_READ_SEQ_ELEM(elem,reader) \
{ \
    assert( (reader).seq->elem_size == sizeof(elem)); \
    memcpy( &(elem), (reader).ptr, sizeof((elem))); \
    CV_NEXT_SEQ_ELEM( sizeof(elem), reader ) \
}


#define CV_REV_READ_SEQ_ELEM(elem,reader) \
{ \
    assert( (reader).seq->elem_size == sizeof(elem)); \
    memcpy(&(elem), (reader).ptr, sizeof((elem))); \
    CV_PREV_SEQ_ELEM( sizeof(elem), reader ) \
}


#define CV_READ_CHAIN_POINT(_pt,reader) \
{ \
    (_pt) = (reader).pt; \
    if( (reader).ptr ) \
    { \
        CV_READ_SEQ_ELEM( (reader).code, (reader)); \
        assert( ((reader).code & ~7) == 0 ); \
        (reader).pt.x += (reader).deltas[(int)(reader).code][0]; \
        (reader).pt.y += (reader).deltas[(int)(reader).code][1]; \
    } \
}

#define CV_CURRENT_POINT(reader) (*((CvPoint*)((reader).ptr)))
#define CV_PREV_POINT(reader) (*((CvPoint*)((reader).prev_elem)))

#define CV_READ_EDGE(pt1,pt2,reader) \
{ \
    assert( sizeof(pt1) == sizeof(CvPoint) && \
            sizeof(pt2) == sizeof(CvPoint) && \
            reader.seq->elem_size == sizeof(CvPoint)); \
    (pt1) = CV_PREV_POINT( reader ); \
    (pt2) = CV_CURRENT_POINT( reader ); \
    (reader).prev_elem = (reader).ptr; \
    CV_NEXT_SEQ_ELEM( sizeof(CvPoint), (reader)); \
}




#define CV_NEXT_GRAPH_EDGE(edge,vertex) \
     (assert((edge)->vtx[0] == (vertex) || (edge)->vtx[1] == (vertex)), \
      (edge)->next[(edge)->vtx[1] == (vertex)])
typedef struct CvFileStorage CvFileStorage;


#define CV_STORAGE_READ 0
#define CV_STORAGE_WRITE 1
#define CV_STORAGE_WRITE_TEXT CV_STORAGE_WRITE
#define CV_STORAGE_WRITE_BINARY CV_STORAGE_WRITE
#define CV_STORAGE_APPEND 2
#define CV_STORAGE_MEMORY 4
#define CV_STORAGE_FORMAT_MASK (7<<3)
#define CV_STORAGE_FORMAT_AUTO 0
#define CV_STORAGE_FORMAT_XML 8
#define CV_STORAGE_FORMAT_YAML 16


typedef struct CvAttrList
{
    const char** attr;
    struct CvAttrList* next;
}
CvAttrList;

CV_INLINE CvAttrList cvAttrList( const char** attr CV_DEFAULT(NULL),
                                 CvAttrList* next CV_DEFAULT(NULL) )
{
    CvAttrList l;
    l.attr = attr;
    l.next = next;

    return l;
}

struct CvTypeInfo;

#define CV_NODE_NONE 0
#define CV_NODE_INT 1
#define CV_NODE_INTEGER CV_NODE_INT
#define CV_NODE_REAL 2
#define CV_NODE_FLOAT CV_NODE_REAL
#define CV_NODE_STR 3
#define CV_NODE_STRING CV_NODE_STR
#define CV_NODE_REF 4
#define CV_NODE_SEQ 5
#define CV_NODE_MAP 6
#define CV_NODE_TYPE_MASK 7

#define CV_NODE_TYPE(flags) ((flags) & CV_NODE_TYPE_MASK)


#define CV_NODE_FLOW 8
#define CV_NODE_USER 16
#define CV_NODE_EMPTY 32
#define CV_NODE_NAMED 64

#define CV_NODE_IS_INT(flags) (CV_NODE_TYPE(flags) == CV_NODE_INT)
#define CV_NODE_IS_REAL(flags) (CV_NODE_TYPE(flags) == CV_NODE_REAL)
#define CV_NODE_IS_STRING(flags) (CV_NODE_TYPE(flags) == CV_NODE_STRING)
#define CV_NODE_IS_SEQ(flags) (CV_NODE_TYPE(flags) == CV_NODE_SEQ)
#define CV_NODE_IS_MAP(flags) (CV_NODE_TYPE(flags) == CV_NODE_MAP)
#define CV_NODE_IS_COLLECTION(flags) (CV_NODE_TYPE(flags) >= CV_NODE_SEQ)
#define CV_NODE_IS_FLOW(flags) (((flags) & CV_NODE_FLOW) != 0)
#define CV_NODE_IS_EMPTY(flags) (((flags) & CV_NODE_EMPTY) != 0)
#define CV_NODE_IS_USER(flags) (((flags) & CV_NODE_USER) != 0)
#define CV_NODE_HAS_NAME(flags) (((flags) & CV_NODE_NAMED) != 0)

#define CV_NODE_SEQ_SIMPLE 256
#define CV_NODE_SEQ_IS_SIMPLE(seq) (((seq)->flags & CV_NODE_SEQ_SIMPLE) != 0)

typedef struct CvString
{
    int len;
    char* ptr;
}
CvString;



typedef struct CvStringHashNode
{
    unsigned hashval;
    CvString str;
    struct CvStringHashNode* next;
}
CvStringHashNode;

typedef struct CvGenericHash CvFileNodeHash;


typedef struct CvFileNode
{
    int tag;
    struct CvTypeInfo* info;

    union
    {
        double f;
        int i;
        CvString str;
        CvSeq* seq;
        CvFileNodeHash* map;
    } data;
}
CvFileNode;

#ifdef __cplusplus
extern "C" {
#endif
typedef int (CV_CDECL *CvIsInstanceFunc)( const void* struct_ptr );
typedef void (CV_CDECL *CvReleaseFunc)( void** struct_dblptr );
typedef void* (CV_CDECL *CvReadFunc)( CvFileStorage* storage, CvFileNode* node );
typedef void (CV_CDECL *CvWriteFunc)( CvFileStorage* storage, const char* name,
                                      const void* struct_ptr, CvAttrList attributes );
typedef void* (CV_CDECL *CvCloneFunc)( const void* struct_ptr );
#ifdef __cplusplus
}
#endif

typedef struct CvTypeInfo
{
    int flags;
    int header_size;
    struct CvTypeInfo* prev;
    struct CvTypeInfo* next;
    const char* type_name;
    CvIsInstanceFunc is_instance;
    CvReleaseFunc release;
    CvReadFunc read;
    CvWriteFunc write;
    CvCloneFunc clone;
}
CvTypeInfo;




typedef struct CvPluginFuncInfo
{
    void** func_addr;
    void* default_func_addr;
    const char* func_names;
    int search_modules;
    int loaded_from;
}
CvPluginFuncInfo;

typedef struct CvModuleInfo
{
    struct CvModuleInfo* next;
    const char* name;
    const char* version;
    CvPluginFuncInfo* func_tab;
}
CvModuleInfo;

#endif
