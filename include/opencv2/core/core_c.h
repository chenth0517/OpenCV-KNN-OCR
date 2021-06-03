#ifndef __OPENCV_CORE_C_H__
#define __OPENCV_CORE_C_H__ 

#include "opencv2/core/types_c.h"

#ifdef __cplusplus
extern "C" {
#endif
CVAPI(void*) cvAlloc( size_t size );







CVAPI(void) cvFree_( void* ptr );
#define cvFree(ptr) (cvFree_(*(ptr)), *(ptr)=0)


CVAPI(IplImage*) cvCreateImageHeader( CvSize size, int depth, int channels );


CVAPI(IplImage*) cvInitImageHeader( IplImage* image, CvSize size, int depth,
                                   int channels, int origin CV_DEFAULT(0),
                                   int align CV_DEFAULT(4));


CVAPI(IplImage*) cvCreateImage( CvSize size, int depth, int channels );


CVAPI(void) cvReleaseImageHeader( IplImage** image );


CVAPI(void) cvReleaseImage( IplImage** image );


CVAPI(IplImage*) cvCloneImage( const IplImage* image );



CVAPI(void) cvSetImageCOI( IplImage* image, int coi );


CVAPI(int) cvGetImageCOI( const IplImage* image );


CVAPI(void) cvSetImageROI( IplImage* image, CvRect rect );


CVAPI(void) cvResetImageROI( IplImage* image );


CVAPI(CvRect) cvGetImageROI( const IplImage* image );


CVAPI(CvMat*) cvCreateMatHeader( int rows, int cols, int type );

#define CV_AUTOSTEP 0x7fffffff


CVAPI(CvMat*) cvInitMatHeader( CvMat* mat, int rows, int cols,
                              int type, void* data CV_DEFAULT(NULL),
                              int step CV_DEFAULT(CV_AUTOSTEP) );


CVAPI(CvMat*) cvCreateMat( int rows, int cols, int type );



CVAPI(void) cvReleaseMat( CvMat** mat );



CV_INLINE void cvDecRefData( CvArr* arr )
{
    if( CV_IS_MAT( arr ))
    {
        CvMat* mat = (CvMat*)arr;
        mat->data.ptr = NULL;
        if( mat->refcount != NULL && --*mat->refcount == 0 )
            cvFree( &mat->refcount );
        mat->refcount = NULL;
    }
    else if( CV_IS_MATND( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;
        mat->data.ptr = NULL;
        if( mat->refcount != NULL && --*mat->refcount == 0 )
            cvFree( &mat->refcount );
        mat->refcount = NULL;
    }
}


CV_INLINE int cvIncRefData( CvArr* arr )
{
    int refcount = 0;
    if( CV_IS_MAT( arr ))
    {
        CvMat* mat = (CvMat*)arr;
        if( mat->refcount != NULL )
            refcount = ++*mat->refcount;
    }
    else if( CV_IS_MATND( arr ))
    {
        CvMatND* mat = (CvMatND*)arr;
        if( mat->refcount != NULL )
            refcount = ++*mat->refcount;
    }
    return refcount;
}



CVAPI(CvMat*) cvCloneMat( const CvMat* mat );




CVAPI(CvMat*) cvGetSubRect( const CvArr* arr, CvMat* submat, CvRect rect );
#define cvGetSubArr cvGetSubRect



CVAPI(CvMat*) cvGetRows( const CvArr* arr, CvMat* submat,
                        int start_row, int end_row,
                        int delta_row CV_DEFAULT(1));

CV_INLINE CvMat* cvGetRow( const CvArr* arr, CvMat* submat, int row )
{
    return cvGetRows( arr, submat, row, row + 1, 1 );
}




CVAPI(CvMat*) cvGetCols( const CvArr* arr, CvMat* submat,
                        int start_col, int end_col );

CV_INLINE CvMat* cvGetCol( const CvArr* arr, CvMat* submat, int col )
{
    return cvGetCols( arr, submat, col, col + 1 );
}





CVAPI(CvMat*) cvGetDiag( const CvArr* arr, CvMat* submat,
                            int diag CV_DEFAULT(0));


CVAPI(void) cvScalarToRawData( const CvScalar* scalar, void* data, int type,
                              int extend_to_12 CV_DEFAULT(0) );

CVAPI(void) cvRawDataToScalar( const void* data, int type, CvScalar* scalar );


CVAPI(CvMatND*) cvCreateMatNDHeader( int dims, const int* sizes, int type );


CVAPI(CvMatND*) cvCreateMatND( int dims, const int* sizes, int type );


CVAPI(CvMatND*) cvInitMatNDHeader( CvMatND* mat, int dims, const int* sizes,
                                    int type, void* data CV_DEFAULT(NULL) );


CV_INLINE void cvReleaseMatND( CvMatND** mat )
{
    cvReleaseMat( (CvMat**)mat );
}


CVAPI(CvMatND*) cvCloneMatND( const CvMatND* mat );


CVAPI(CvSparseMat*) cvCreateSparseMat( int dims, const int* sizes, int type );


CVAPI(void) cvReleaseSparseMat( CvSparseMat** mat );


CVAPI(CvSparseMat*) cvCloneSparseMat( const CvSparseMat* mat );



CVAPI(CvSparseNode*) cvInitSparseMatIterator( const CvSparseMat* mat,
                                              CvSparseMatIterator* mat_iterator );


CV_INLINE CvSparseNode* cvGetNextSparseNode( CvSparseMatIterator* mat_iterator )
{
    if( mat_iterator->node->next )
        return mat_iterator->node = mat_iterator->node->next;
    else
    {
        int idx;
        for( idx = ++mat_iterator->curidx; idx < mat_iterator->mat->hashsize; idx++ )
        {
            CvSparseNode* node = (CvSparseNode*)mat_iterator->mat->hashtable[idx];
            if( node )
            {
                mat_iterator->curidx = idx;
                return mat_iterator->node = node;
            }
        }
        return NULL;
    }
}



#define CV_MAX_ARR 10

typedef struct CvNArrayIterator
{
    int count;
    int dims;
    CvSize size;
    uchar* ptr[CV_MAX_ARR];
    int stack[CV_MAX_DIM];
    CvMatND* hdr[CV_MAX_ARR];

}
CvNArrayIterator;

#define CV_NO_DEPTH_CHECK 1
#define CV_NO_CN_CHECK 2
#define CV_NO_SIZE_CHECK 4




CVAPI(int) cvInitNArrayIterator( int count, CvArr** arrs,
                                 const CvArr* mask, CvMatND* stubs,
                                 CvNArrayIterator* array_iterator,
                                 int flags CV_DEFAULT(0) );


CVAPI(int) cvNextNArraySlice( CvNArrayIterator* array_iterator );




CVAPI(int) cvGetElemType( const CvArr* arr );



CVAPI(int) cvGetDims( const CvArr* arr, int* sizes CV_DEFAULT(NULL) );





CVAPI(int) cvGetDimSize( const CvArr* arr, int index );




CVAPI(uchar*) cvPtr1D( const CvArr* arr, int idx0, int* type CV_DEFAULT(NULL));
CVAPI(uchar*) cvPtr2D( const CvArr* arr, int idx0, int idx1, int* type CV_DEFAULT(NULL) );
CVAPI(uchar*) cvPtr3D( const CvArr* arr, int idx0, int idx1, int idx2,
                      int* type CV_DEFAULT(NULL));





CVAPI(uchar*) cvPtrND( const CvArr* arr, const int* idx, int* type CV_DEFAULT(NULL),
                      int create_node CV_DEFAULT(1),
                      unsigned* precalc_hashval CV_DEFAULT(NULL));


CVAPI(CvScalar) cvGet1D( const CvArr* arr, int idx0 );
CVAPI(CvScalar) cvGet2D( const CvArr* arr, int idx0, int idx1 );
CVAPI(CvScalar) cvGet3D( const CvArr* arr, int idx0, int idx1, int idx2 );
CVAPI(CvScalar) cvGetND( const CvArr* arr, const int* idx );


CVAPI(double) cvGetReal1D( const CvArr* arr, int idx0 );
CVAPI(double) cvGetReal2D( const CvArr* arr, int idx0, int idx1 );
CVAPI(double) cvGetReal3D( const CvArr* arr, int idx0, int idx1, int idx2 );
CVAPI(double) cvGetRealND( const CvArr* arr, const int* idx );


CVAPI(void) cvSet1D( CvArr* arr, int idx0, CvScalar value );
CVAPI(void) cvSet2D( CvArr* arr, int idx0, int idx1, CvScalar value );
CVAPI(void) cvSet3D( CvArr* arr, int idx0, int idx1, int idx2, CvScalar value );
CVAPI(void) cvSetND( CvArr* arr, const int* idx, CvScalar value );


CVAPI(void) cvSetReal1D( CvArr* arr, int idx0, double value );
CVAPI(void) cvSetReal2D( CvArr* arr, int idx0, int idx1, double value );
CVAPI(void) cvSetReal3D( CvArr* arr, int idx0,
                        int idx1, int idx2, double value );
CVAPI(void) cvSetRealND( CvArr* arr, const int* idx, double value );



CVAPI(void) cvClearND( CvArr* arr, const int* idx );






CVAPI(CvMat*) cvGetMat( const CvArr* arr, CvMat* header,
                       int* coi CV_DEFAULT(NULL),
                       int allowND CV_DEFAULT(0));


CVAPI(IplImage*) cvGetImage( const CvArr* arr, IplImage* image_header );
CVAPI(CvArr*) cvReshapeMatND( const CvArr* arr,
                             int sizeof_header, CvArr* header,
                             int new_cn, int new_dims, int* new_sizes );

#define cvReshapeND(arr,header,new_cn,new_dims,new_sizes) \
      cvReshapeMatND( (arr), sizeof(*(header)), (header), \
                      (new_cn), (new_dims), (new_sizes))

CVAPI(CvMat*) cvReshape( const CvArr* arr, CvMat* header,
                        int new_cn, int new_rows CV_DEFAULT(0) );



CVAPI(void) cvRepeat( const CvArr* src, CvArr* dst );


CVAPI(void) cvCreateData( CvArr* arr );


CVAPI(void) cvReleaseData( CvArr* arr );




CVAPI(void) cvSetData( CvArr* arr, void* data, int step );




CVAPI(void) cvGetRawData( const CvArr* arr, uchar** data,
                         int* step CV_DEFAULT(NULL),
                         CvSize* roi_size CV_DEFAULT(NULL));


CVAPI(CvSize) cvGetSize( const CvArr* arr );


CVAPI(void) cvCopy( const CvArr* src, CvArr* dst,
                     const CvArr* mask CV_DEFAULT(NULL) );



CVAPI(void) cvSet( CvArr* arr, CvScalar value,
                    const CvArr* mask CV_DEFAULT(NULL) );


CVAPI(void) cvSetZero( CvArr* arr );
#define cvZero cvSetZero




CVAPI(void) cvSplit( const CvArr* src, CvArr* dst0, CvArr* dst1,
                      CvArr* dst2, CvArr* dst3 );



CVAPI(void) cvMerge( const CvArr* src0, const CvArr* src1,
                      const CvArr* src2, const CvArr* src3,
                      CvArr* dst );



CVAPI(void) cvMixChannels( const CvArr** src, int src_count,
                            CvArr** dst, int dst_count,
                            const int* from_to, int pair_count );






CVAPI(void) cvConvertScale( const CvArr* src, CvArr* dst,
                             double scale CV_DEFAULT(1),
                             double shift CV_DEFAULT(0) );
#define cvCvtScale cvConvertScale
#define cvScale cvConvertScale
#define cvConvert(src,dst) cvConvertScale( (src), (dst), 1, 0 )







CVAPI(void) cvConvertScaleAbs( const CvArr* src, CvArr* dst,
                                double scale CV_DEFAULT(1),
                                double shift CV_DEFAULT(0) );
#define cvCvtScaleAbs cvConvertScaleAbs






CVAPI(CvTermCriteria) cvCheckTermCriteria( CvTermCriteria criteria,
                                           double default_eps,
                                           int default_max_iters );






CVAPI(void) cvAdd( const CvArr* src1, const CvArr* src2, CvArr* dst,
                    const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvAddS( const CvArr* src, CvScalar value, CvArr* dst,
                     const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvSub( const CvArr* src1, const CvArr* src2, CvArr* dst,
                    const CvArr* mask CV_DEFAULT(NULL));


CV_INLINE void cvSubS( const CvArr* src, CvScalar value, CvArr* dst,
                         const CvArr* mask CV_DEFAULT(NULL))
{
    cvAddS( src, cvScalar( -value.val[0], -value.val[1], -value.val[2], -value.val[3]),
            dst, mask );
}


CVAPI(void) cvSubRS( const CvArr* src, CvScalar value, CvArr* dst,
                      const CvArr* mask CV_DEFAULT(NULL));



CVAPI(void) cvMul( const CvArr* src1, const CvArr* src2,
                    CvArr* dst, double scale CV_DEFAULT(1) );




CVAPI(void) cvDiv( const CvArr* src1, const CvArr* src2,
                    CvArr* dst, double scale CV_DEFAULT(1));


CVAPI(void) cvScaleAdd( const CvArr* src1, CvScalar scale,
                         const CvArr* src2, CvArr* dst );
#define cvAXPY(A,real_scalar,B,C) cvScaleAdd(A, cvRealScalar(real_scalar), B, C)


CVAPI(void) cvAddWeighted( const CvArr* src1, double alpha,
                            const CvArr* src2, double beta,
                            double gamma, CvArr* dst );


CVAPI(double) cvDotProduct( const CvArr* src1, const CvArr* src2 );


CVAPI(void) cvAnd( const CvArr* src1, const CvArr* src2,
                  CvArr* dst, const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvAndS( const CvArr* src, CvScalar value,
                   CvArr* dst, const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvOr( const CvArr* src1, const CvArr* src2,
                 CvArr* dst, const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvOrS( const CvArr* src, CvScalar value,
                  CvArr* dst, const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvXor( const CvArr* src1, const CvArr* src2,
                  CvArr* dst, const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvXorS( const CvArr* src, CvScalar value,
                   CvArr* dst, const CvArr* mask CV_DEFAULT(NULL));


CVAPI(void) cvNot( const CvArr* src, CvArr* dst );


CVAPI(void) cvInRange( const CvArr* src, const CvArr* lower,
                      const CvArr* upper, CvArr* dst );


CVAPI(void) cvInRangeS( const CvArr* src, CvScalar lower,
                       CvScalar upper, CvArr* dst );

#define CV_CMP_EQ 0
#define CV_CMP_GT 1
#define CV_CMP_GE 2
#define CV_CMP_LT 3
#define CV_CMP_LE 4
#define CV_CMP_NE 5





CVAPI(void) cvCmp( const CvArr* src1, const CvArr* src2, CvArr* dst, int cmp_op );


CVAPI(void) cvCmpS( const CvArr* src, double value, CvArr* dst, int cmp_op );


CVAPI(void) cvMin( const CvArr* src1, const CvArr* src2, CvArr* dst );


CVAPI(void) cvMax( const CvArr* src1, const CvArr* src2, CvArr* dst );


CVAPI(void) cvMinS( const CvArr* src, double value, CvArr* dst );


CVAPI(void) cvMaxS( const CvArr* src, double value, CvArr* dst );


CVAPI(void) cvAbsDiff( const CvArr* src1, const CvArr* src2, CvArr* dst );


CVAPI(void) cvAbsDiffS( const CvArr* src, CvArr* dst, CvScalar value );
#define cvAbs(src,dst) cvAbsDiffS( (src), (dst), cvScalarAll(0))







CVAPI(void) cvCartToPolar( const CvArr* x, const CvArr* y,
                            CvArr* magnitude, CvArr* angle CV_DEFAULT(NULL),
                            int angle_in_degrees CV_DEFAULT(0));




CVAPI(void) cvPolarToCart( const CvArr* magnitude, const CvArr* angle,
                            CvArr* x, CvArr* y,
                            int angle_in_degrees CV_DEFAULT(0));


CVAPI(void) cvPow( const CvArr* src, CvArr* dst, double power );




CVAPI(void) cvExp( const CvArr* src, CvArr* dst );





CVAPI(void) cvLog( const CvArr* src, CvArr* dst );


CVAPI(float) cvFastArctan( float y, float x );


CVAPI(float) cvCbrt( float value );





#define CV_CHECK_RANGE 1
#define CV_CHECK_QUIET 2
CVAPI(int) cvCheckArr( const CvArr* arr, int flags CV_DEFAULT(0),
                        double min_val CV_DEFAULT(0), double max_val CV_DEFAULT(0));
#define cvCheckArray cvCheckArr

#define CV_RAND_UNI 0
#define CV_RAND_NORMAL 1
CVAPI(void) cvRandArr( CvRNG* rng, CvArr* arr, int dist_type,
                      CvScalar param1, CvScalar param2 );

CVAPI(void) cvRandShuffle( CvArr* mat, CvRNG* rng,
                           double iter_factor CV_DEFAULT(1.));

#define CV_SORT_EVERY_ROW 0
#define CV_SORT_EVERY_COLUMN 1
#define CV_SORT_ASCENDING 0
#define CV_SORT_DESCENDING 16

CVAPI(void) cvSort( const CvArr* src, CvArr* dst CV_DEFAULT(NULL),
                    CvArr* idxmat CV_DEFAULT(NULL),
                    int flags CV_DEFAULT(0));


CVAPI(int) cvSolveCubic( const CvMat* coeffs, CvMat* roots );


CVAPI(void) cvSolvePoly(const CvMat* coeffs, CvMat *roots2,
      int maxiter CV_DEFAULT(20), int fig CV_DEFAULT(100));






CVAPI(void) cvCrossProduct( const CvArr* src1, const CvArr* src2, CvArr* dst );


#define cvMatMulAdd(src1,src2,src3,dst) cvGEMM( (src1), (src2), 1., (src3), 1., (dst), 0 )
#define cvMatMul(src1,src2,dst) cvMatMulAdd( (src1), (src2), NULL, (dst))

#define CV_GEMM_A_T 1
#define CV_GEMM_B_T 2
#define CV_GEMM_C_T 4


CVAPI(void) cvGEMM( const CvArr* src1, const CvArr* src2, double alpha,
                     const CvArr* src3, double beta, CvArr* dst,
                     int tABC CV_DEFAULT(0));
#define cvMatMulAddEx cvGEMM



CVAPI(void) cvTransform( const CvArr* src, CvArr* dst,
                          const CvMat* transmat,
                          const CvMat* shiftvec CV_DEFAULT(NULL));
#define cvMatMulAddS cvTransform


CVAPI(void) cvPerspectiveTransform( const CvArr* src, CvArr* dst,
                                     const CvMat* mat );


CVAPI(void) cvMulTransposed( const CvArr* src, CvArr* dst, int order,
                             const CvArr* delta CV_DEFAULT(NULL),
                             double scale CV_DEFAULT(1.) );


CVAPI(void) cvTranspose( const CvArr* src, CvArr* dst );
#define cvT cvTranspose


CVAPI(void) cvCompleteSymm( CvMat* matrix, int LtoR CV_DEFAULT(0) );




CVAPI(void) cvFlip( const CvArr* src, CvArr* dst CV_DEFAULT(NULL),
                     int flip_mode CV_DEFAULT(0));
#define cvMirror cvFlip


#define CV_SVD_MODIFY_A 1
#define CV_SVD_U_T 2
#define CV_SVD_V_T 4


CVAPI(void) cvSVD( CvArr* A, CvArr* W, CvArr* U CV_DEFAULT(NULL),
                     CvArr* V CV_DEFAULT(NULL), int flags CV_DEFAULT(0));



CVAPI(void) cvSVBkSb( const CvArr* W, const CvArr* U,
                        const CvArr* V, const CvArr* B,
                        CvArr* X, int flags );

#define CV_LU 0
#define CV_SVD 1
#define CV_SVD_SYM 2
#define CV_CHOLESKY 3
#define CV_QR 4
#define CV_NORMAL 16


CVAPI(double) cvInvert( const CvArr* src, CvArr* dst,
                         int method CV_DEFAULT(CV_LU));
#define cvInv cvInvert



CVAPI(int) cvSolve( const CvArr* src1, const CvArr* src2, CvArr* dst,
                     int method CV_DEFAULT(CV_LU));


CVAPI(double) cvDet( const CvArr* mat );


CVAPI(CvScalar) cvTrace( const CvArr* mat );


CVAPI(void) cvEigenVV( CvArr* mat, CvArr* evects, CvArr* evals,
                        double eps CV_DEFAULT(0),
                        int lowindex CV_DEFAULT(-1),
                        int highindex CV_DEFAULT(-1));






CVAPI(void) cvSetIdentity( CvArr* mat, CvScalar value CV_DEFAULT(cvRealScalar(1)) );


CVAPI(CvArr*) cvRange( CvArr* mat, double start, double end );



#define CV_COVAR_SCRAMBLED 0


#define CV_COVAR_NORMAL 1



#define CV_COVAR_USE_AVG 2


#define CV_COVAR_SCALE 4


#define CV_COVAR_ROWS 8


#define CV_COVAR_COLS 16

CVAPI(void) cvCalcCovarMatrix( const CvArr** vects, int count,
                                CvArr* cov_mat, CvArr* avg, int flags );

#define CV_PCA_DATA_AS_ROW 0
#define CV_PCA_DATA_AS_COL 1
#define CV_PCA_USE_AVG 2
CVAPI(void) cvCalcPCA( const CvArr* data, CvArr* mean,
                        CvArr* eigenvals, CvArr* eigenvects, int flags );

CVAPI(void) cvProjectPCA( const CvArr* data, const CvArr* mean,
                           const CvArr* eigenvects, CvArr* result );

CVAPI(void) cvBackProjectPCA( const CvArr* proj, const CvArr* mean,
                               const CvArr* eigenvects, CvArr* result );


CVAPI(double) cvMahalanobis( const CvArr* vec1, const CvArr* vec2, const CvArr* mat );
#define cvMahalonobis cvMahalanobis






CVAPI(CvScalar) cvSum( const CvArr* arr );


CVAPI(int) cvCountNonZero( const CvArr* arr );


CVAPI(CvScalar) cvAvg( const CvArr* arr, const CvArr* mask CV_DEFAULT(NULL) );


CVAPI(void) cvAvgSdv( const CvArr* arr, CvScalar* mean, CvScalar* std_dev,
                       const CvArr* mask CV_DEFAULT(NULL) );


CVAPI(void) cvMinMaxLoc( const CvArr* arr, double* min_val, double* max_val,
                          CvPoint* min_loc CV_DEFAULT(NULL),
                          CvPoint* max_loc CV_DEFAULT(NULL),
                          const CvArr* mask CV_DEFAULT(NULL) );


#define CV_C 1
#define CV_L1 2
#define CV_L2 4
#define CV_NORM_MASK 7
#define CV_RELATIVE 8
#define CV_DIFF 16
#define CV_MINMAX 32

#define CV_DIFF_C (CV_DIFF | CV_C)
#define CV_DIFF_L1 (CV_DIFF | CV_L1)
#define CV_DIFF_L2 (CV_DIFF | CV_L2)
#define CV_RELATIVE_C (CV_RELATIVE | CV_C)
#define CV_RELATIVE_L1 (CV_RELATIVE | CV_L1)
#define CV_RELATIVE_L2 (CV_RELATIVE | CV_L2)


CVAPI(double) cvNorm( const CvArr* arr1, const CvArr* arr2 CV_DEFAULT(NULL),
                       int norm_type CV_DEFAULT(CV_L2),
                       const CvArr* mask CV_DEFAULT(NULL) );

CVAPI(void) cvNormalize( const CvArr* src, CvArr* dst,
                          double a CV_DEFAULT(1.), double b CV_DEFAULT(0.),
                          int norm_type CV_DEFAULT(CV_L2),
                          const CvArr* mask CV_DEFAULT(NULL) );


#define CV_REDUCE_SUM 0
#define CV_REDUCE_AVG 1
#define CV_REDUCE_MAX 2
#define CV_REDUCE_MIN 3

CVAPI(void) cvReduce( const CvArr* src, CvArr* dst, int dim CV_DEFAULT(-1),
                       int op CV_DEFAULT(CV_REDUCE_SUM) );





#define CV_DXT_FORWARD 0
#define CV_DXT_INVERSE 1
#define CV_DXT_SCALE 2
#define CV_DXT_INV_SCALE (CV_DXT_INVERSE + CV_DXT_SCALE)
#define CV_DXT_INVERSE_SCALE CV_DXT_INV_SCALE
#define CV_DXT_ROWS 4
#define CV_DXT_MUL_CONJ 8





CVAPI(void) cvDFT( const CvArr* src, CvArr* dst, int flags,
                    int nonzero_rows CV_DEFAULT(0) );
#define cvFFT cvDFT


CVAPI(void) cvMulSpectrums( const CvArr* src1, const CvArr* src2,
                             CvArr* dst, int flags );


CVAPI(int) cvGetOptimalDFTSize( int size0 );


CVAPI(void) cvDCT( const CvArr* src, CvArr* dst, int flags );






CVAPI(int) cvSliceLength( CvSlice slice, const CvSeq* seq );





CVAPI(CvMemStorage*) cvCreateMemStorage( int block_size CV_DEFAULT(0));



CVAPI(CvMemStorage*) cvCreateChildMemStorage( CvMemStorage* parent );




CVAPI(void) cvReleaseMemStorage( CvMemStorage** storage );






CVAPI(void) cvClearMemStorage( CvMemStorage* storage );


CVAPI(void) cvSaveMemStoragePos( const CvMemStorage* storage, CvMemStoragePos* pos );


CVAPI(void) cvRestoreMemStoragePos( CvMemStorage* storage, CvMemStoragePos* pos );


CVAPI(void*) cvMemStorageAlloc( CvMemStorage* storage, size_t size );


CVAPI(CvString) cvMemStorageAllocString( CvMemStorage* storage, const char* ptr,
                                         int len CV_DEFAULT(-1) );


CVAPI(CvSeq*) cvCreateSeq( int seq_flags, size_t header_size,
                            size_t elem_size, CvMemStorage* storage );



CVAPI(void) cvSetSeqBlockSize( CvSeq* seq, int delta_elems );



CVAPI(schar*) cvSeqPush( CvSeq* seq, const void* element CV_DEFAULT(NULL));



CVAPI(schar*) cvSeqPushFront( CvSeq* seq, const void* element CV_DEFAULT(NULL));



CVAPI(void) cvSeqPop( CvSeq* seq, void* element CV_DEFAULT(NULL));



CVAPI(void) cvSeqPopFront( CvSeq* seq, void* element CV_DEFAULT(NULL));


#define CV_FRONT 1
#define CV_BACK 0

CVAPI(void) cvSeqPushMulti( CvSeq* seq, const void* elements,
                             int count, int in_front CV_DEFAULT(0) );


CVAPI(void) cvSeqPopMulti( CvSeq* seq, void* elements,
                            int count, int in_front CV_DEFAULT(0) );



CVAPI(schar*) cvSeqInsert( CvSeq* seq, int before_index,
                            const void* element CV_DEFAULT(NULL));


CVAPI(void) cvSeqRemove( CvSeq* seq, int index );





CVAPI(void) cvClearSeq( CvSeq* seq );





CVAPI(schar*) cvGetSeqElem( const CvSeq* seq, int index );



CVAPI(int) cvSeqElemIdx( const CvSeq* seq, const void* element,
                         CvSeqBlock** block CV_DEFAULT(NULL) );


CVAPI(void) cvStartAppendToSeq( CvSeq* seq, CvSeqWriter* writer );



CVAPI(void) cvStartWriteSeq( int seq_flags, int header_size,
                              int elem_size, CvMemStorage* storage,
                              CvSeqWriter* writer );





CVAPI(CvSeq*) cvEndWriteSeq( CvSeqWriter* writer );




CVAPI(void) cvFlushSeqWriter( CvSeqWriter* writer );




CVAPI(void) cvStartReadSeq( const CvSeq* seq, CvSeqReader* reader,
                           int reverse CV_DEFAULT(0) );



CVAPI(int) cvGetSeqReaderPos( CvSeqReader* reader );




CVAPI(void) cvSetSeqReaderPos( CvSeqReader* reader, int index,
                                 int is_relative CV_DEFAULT(0));


CVAPI(void*) cvCvtSeqToArray( const CvSeq* seq, void* elements,
                               CvSlice slice CV_DEFAULT(CV_WHOLE_SEQ) );




CVAPI(CvSeq*) cvMakeSeqHeaderForArray( int seq_type, int header_size,
                                       int elem_size, void* elements, int total,
                                       CvSeq* seq, CvSeqBlock* block );


CVAPI(CvSeq*) cvSeqSlice( const CvSeq* seq, CvSlice slice,
                         CvMemStorage* storage CV_DEFAULT(NULL),
                         int copy_data CV_DEFAULT(0));

CV_INLINE CvSeq* cvCloneSeq( const CvSeq* seq, CvMemStorage* storage CV_DEFAULT(NULL))
{
    return cvSeqSlice( seq, CV_WHOLE_SEQ, storage, 1 );
}


CVAPI(void) cvSeqRemoveSlice( CvSeq* seq, CvSlice slice );


CVAPI(void) cvSeqInsertSlice( CvSeq* seq, int before_index, const CvArr* from_arr );


typedef int (CV_CDECL* CvCmpFunc)(const void* a, const void* b, void* userdata );


CVAPI(void) cvSeqSort( CvSeq* seq, CvCmpFunc func, void* userdata CV_DEFAULT(NULL) );


CVAPI(schar*) cvSeqSearch( CvSeq* seq, const void* elem, CvCmpFunc func,
                           int is_sorted, int* elem_idx,
                           void* userdata CV_DEFAULT(NULL) );


CVAPI(void) cvSeqInvert( CvSeq* seq );


CVAPI(int) cvSeqPartition( const CvSeq* seq, CvMemStorage* storage,
                            CvSeq** labels, CvCmpFunc is_equal, void* userdata );


CVAPI(void) cvChangeSeqBlock( void* reader, int direction );
CVAPI(void) cvCreateSeqBlock( CvSeqWriter* writer );



CVAPI(CvSet*) cvCreateSet( int set_flags, int header_size,
                            int elem_size, CvMemStorage* storage );


CVAPI(int) cvSetAdd( CvSet* set_header, CvSetElem* elem CV_DEFAULT(NULL),
                      CvSetElem** inserted_elem CV_DEFAULT(NULL) );


CV_INLINE CvSetElem* cvSetNew( CvSet* set_header )
{
    CvSetElem* elem = set_header->free_elems;
    if( elem )
    {
        set_header->free_elems = elem->next_free;
        elem->flags = elem->flags & CV_SET_ELEM_IDX_MASK;
        set_header->active_count++;
    }
    else
        cvSetAdd( set_header, NULL, &elem );
    return elem;
}


CV_INLINE void cvSetRemoveByPtr( CvSet* set_header, void* elem )
{
    CvSetElem* _elem = (CvSetElem*)elem;
    assert( _elem->flags >= 0 );
    _elem->next_free = set_header->free_elems;
    _elem->flags = (_elem->flags & CV_SET_ELEM_IDX_MASK) | CV_SET_ELEM_FREE_FLAG;
    set_header->free_elems = _elem;
    set_header->active_count--;
}


CVAPI(void) cvSetRemove( CvSet* set_header, int index );



CV_INLINE CvSetElem* cvGetSetElem( const CvSet* set_header, int idx )
{
    CvSetElem* elem = (CvSetElem*)(void *)cvGetSeqElem( (CvSeq*)set_header, idx );
    return elem && CV_IS_SET_ELEM( elem ) ? elem : 0;
}


CVAPI(void) cvClearSet( CvSet* set_header );


CVAPI(CvGraph*) cvCreateGraph( int graph_flags, int header_size,
                                int vtx_size, int edge_size,
                                CvMemStorage* storage );


CVAPI(int) cvGraphAddVtx( CvGraph* graph, const CvGraphVtx* vtx CV_DEFAULT(NULL),
                           CvGraphVtx** inserted_vtx CV_DEFAULT(NULL) );



CVAPI(int) cvGraphRemoveVtx( CvGraph* graph, int index );
CVAPI(int) cvGraphRemoveVtxByPtr( CvGraph* graph, CvGraphVtx* vtx );






CVAPI(int) cvGraphAddEdge( CvGraph* graph,
                            int start_idx, int end_idx,
                            const CvGraphEdge* edge CV_DEFAULT(NULL),
                            CvGraphEdge** inserted_edge CV_DEFAULT(NULL) );

CVAPI(int) cvGraphAddEdgeByPtr( CvGraph* graph,
                               CvGraphVtx* start_vtx, CvGraphVtx* end_vtx,
                               const CvGraphEdge* edge CV_DEFAULT(NULL),
                               CvGraphEdge** inserted_edge CV_DEFAULT(NULL) );


CVAPI(void) cvGraphRemoveEdge( CvGraph* graph, int start_idx, int end_idx );
CVAPI(void) cvGraphRemoveEdgeByPtr( CvGraph* graph, CvGraphVtx* start_vtx,
                                     CvGraphVtx* end_vtx );


CVAPI(CvGraphEdge*) cvFindGraphEdge( const CvGraph* graph, int start_idx, int end_idx );
CVAPI(CvGraphEdge*) cvFindGraphEdgeByPtr( const CvGraph* graph,
                                           const CvGraphVtx* start_vtx,
                                           const CvGraphVtx* end_vtx );
#define cvGraphFindEdge cvFindGraphEdge
#define cvGraphFindEdgeByPtr cvFindGraphEdgeByPtr


CVAPI(void) cvClearGraph( CvGraph* graph );



CVAPI(int) cvGraphVtxDegree( const CvGraph* graph, int vtx_idx );
CVAPI(int) cvGraphVtxDegreeByPtr( const CvGraph* graph, const CvGraphVtx* vtx );



#define cvGetGraphVtx(graph,idx) (CvGraphVtx*)cvGetSetElem((CvSet*)(graph), (idx))


#define cvGraphVtxIdx(graph,vtx) ((vtx)->flags & CV_SET_ELEM_IDX_MASK)


#define cvGraphEdgeIdx(graph,edge) ((edge)->flags & CV_SET_ELEM_IDX_MASK)

#define cvGraphGetVtxCount(graph) ((graph)->active_count)
#define cvGraphGetEdgeCount(graph) ((graph)->edges->active_count)

#define CV_GRAPH_VERTEX 1
#define CV_GRAPH_TREE_EDGE 2
#define CV_GRAPH_BACK_EDGE 4
#define CV_GRAPH_FORWARD_EDGE 8
#define CV_GRAPH_CROSS_EDGE 16
#define CV_GRAPH_ANY_EDGE 30
#define CV_GRAPH_NEW_TREE 32
#define CV_GRAPH_BACKTRACKING 64
#define CV_GRAPH_OVER -1

#define CV_GRAPH_ALL_ITEMS -1


#define CV_GRAPH_ITEM_VISITED_FLAG (1 << 30)
#define CV_IS_GRAPH_VERTEX_VISITED(vtx) \
    (((CvGraphVtx*)(vtx))->flags & CV_GRAPH_ITEM_VISITED_FLAG)
#define CV_IS_GRAPH_EDGE_VISITED(edge) \
    (((CvGraphEdge*)(edge))->flags & CV_GRAPH_ITEM_VISITED_FLAG)
#define CV_GRAPH_SEARCH_TREE_NODE_FLAG (1 << 29)
#define CV_GRAPH_FORWARD_EDGE_FLAG (1 << 28)

typedef struct CvGraphScanner
{
    CvGraphVtx* vtx;
    CvGraphVtx* dst;
    CvGraphEdge* edge;

    CvGraph* graph;
    CvSeq* stack;
    int index;
    int mask;
}
CvGraphScanner;


CVAPI(CvGraphScanner*) cvCreateGraphScanner( CvGraph* graph,
                                             CvGraphVtx* vtx CV_DEFAULT(NULL),
                                             int mask CV_DEFAULT(CV_GRAPH_ALL_ITEMS));


CVAPI(void) cvReleaseGraphScanner( CvGraphScanner** scanner );


CVAPI(int) cvNextGraphItem( CvGraphScanner* scanner );


CVAPI(CvGraph*) cvCloneGraph( const CvGraph* graph, CvMemStorage* storage );
#define CV_RGB(r,g,b) cvScalar( (b), (g), (r), 0 )
#define CV_FILLED -1

#define CV_AA 16


CVAPI(void) cvLine( CvArr* img, CvPoint pt1, CvPoint pt2,
                     CvScalar color, int thickness CV_DEFAULT(1),
                     int line_type CV_DEFAULT(8), int shift CV_DEFAULT(0) );



CVAPI(void) cvRectangle( CvArr* img, CvPoint pt1, CvPoint pt2,
                          CvScalar color, int thickness CV_DEFAULT(1),
                          int line_type CV_DEFAULT(8),
                          int shift CV_DEFAULT(0));


CVAPI(void) cvRectangleR( CvArr* img, CvRect r,
                           CvScalar color, int thickness CV_DEFAULT(1),
                           int line_type CV_DEFAULT(8),
                           int shift CV_DEFAULT(0));




CVAPI(void) cvCircle( CvArr* img, CvPoint center, int radius,
                       CvScalar color, int thickness CV_DEFAULT(1),
                       int line_type CV_DEFAULT(8), int shift CV_DEFAULT(0));




CVAPI(void) cvEllipse( CvArr* img, CvPoint center, CvSize axes,
                        double angle, double start_angle, double end_angle,
                        CvScalar color, int thickness CV_DEFAULT(1),
                        int line_type CV_DEFAULT(8), int shift CV_DEFAULT(0));

CV_INLINE void cvEllipseBox( CvArr* img, CvBox2D box, CvScalar color,
                               int thickness CV_DEFAULT(1),
                               int line_type CV_DEFAULT(8), int shift CV_DEFAULT(0) )
{
    CvSize axes;
    axes.width = cvRound(box.size.width*0.5);
    axes.height = cvRound(box.size.height*0.5);

    cvEllipse( img, cvPointFrom32f( box.center ), axes, box.angle,
               0, 360, color, thickness, line_type, shift );
}


CVAPI(void) cvFillConvexPoly( CvArr* img, const CvPoint* pts, int npts, CvScalar color,
                               int line_type CV_DEFAULT(8), int shift CV_DEFAULT(0));


CVAPI(void) cvFillPoly( CvArr* img, CvPoint** pts, const int* npts,
                         int contours, CvScalar color,
                         int line_type CV_DEFAULT(8), int shift CV_DEFAULT(0) );


CVAPI(void) cvPolyLine( CvArr* img, CvPoint** pts, const int* npts, int contours,
                         int is_closed, CvScalar color, int thickness CV_DEFAULT(1),
                         int line_type CV_DEFAULT(8), int shift CV_DEFAULT(0) );

#define cvDrawRect cvRectangle
#define cvDrawLine cvLine
#define cvDrawCircle cvCircle
#define cvDrawEllipse cvEllipse
#define cvDrawPolyLine cvPolyLine




CVAPI(int) cvClipLine( CvSize img_size, CvPoint* pt1, CvPoint* pt2 );




CVAPI(int) cvInitLineIterator( const CvArr* image, CvPoint pt1, CvPoint pt2,
                                CvLineIterator* line_iterator,
                                int connectivity CV_DEFAULT(8),
                                int left_to_right CV_DEFAULT(0));


#define CV_NEXT_LINE_POINT(line_iterator) \
{ \
    int _line_iterator_mask = (line_iterator).err < 0 ? -1 : 0; \
    (line_iterator).err += (line_iterator).minus_delta + \
        ((line_iterator).plus_delta & _line_iterator_mask); \
    (line_iterator).ptr += (line_iterator).minus_step + \
        ((line_iterator).plus_step & _line_iterator_mask); \
}



#define CV_FONT_HERSHEY_SIMPLEX 0
#define CV_FONT_HERSHEY_PLAIN 1
#define CV_FONT_HERSHEY_DUPLEX 2
#define CV_FONT_HERSHEY_COMPLEX 3
#define CV_FONT_HERSHEY_TRIPLEX 4
#define CV_FONT_HERSHEY_COMPLEX_SMALL 5
#define CV_FONT_HERSHEY_SCRIPT_SIMPLEX 6
#define CV_FONT_HERSHEY_SCRIPT_COMPLEX 7


#define CV_FONT_ITALIC 16

#define CV_FONT_VECTOR0 CV_FONT_HERSHEY_SIMPLEX



typedef struct CvFont
{
  const char* nameFont;
  CvScalar color;
    int font_face;
    const int* ascii;
    const int* greek;
    const int* cyrillic;
    float hscale, vscale;
    float shear;
    int thickness;
    float dx;
    int line_type;
}
CvFont;


CVAPI(void) cvInitFont( CvFont* font, int font_face,
                         double hscale, double vscale,
                         double shear CV_DEFAULT(0),
                         int thickness CV_DEFAULT(1),
                         int line_type CV_DEFAULT(8));

CV_INLINE CvFont cvFont( double scale, int thickness CV_DEFAULT(1) )
{
    CvFont font;
    cvInitFont( &font, CV_FONT_HERSHEY_PLAIN, scale, scale, 0, thickness, CV_AA );
    return font;
}



CVAPI(void) cvPutText( CvArr* img, const char* text, CvPoint org,
                        const CvFont* font, CvScalar color );


CVAPI(void) cvGetTextSize( const char* text_string, const CvFont* font,
                            CvSize* text_size, int* baseline );






CVAPI(CvScalar) cvColorToScalar( double packed_color, int arrtype );







CVAPI(int) cvEllipse2Poly( CvPoint center, CvSize axes,
                 int angle, int arc_start, int arc_end, CvPoint * pts, int delta );


CVAPI(void) cvDrawContours( CvArr *img, CvSeq* contour,
                             CvScalar external_color, CvScalar hole_color,
                             int max_level, int thickness CV_DEFAULT(1),
                             int line_type CV_DEFAULT(8),
                             CvPoint offset CV_DEFAULT(cvPoint(0,0)));



CVAPI(void) cvLUT( const CvArr* src, CvArr* dst, const CvArr* lut );



typedef struct CvTreeNodeIterator
{
    const void* node;
    int level;
    int max_level;
}
CvTreeNodeIterator;

CVAPI(void) cvInitTreeNodeIterator( CvTreeNodeIterator* tree_iterator,
                                   const void* first, int max_level );
CVAPI(void*) cvNextTreeNode( CvTreeNodeIterator* tree_iterator );
CVAPI(void*) cvPrevTreeNode( CvTreeNodeIterator* tree_iterator );




CVAPI(void) cvInsertNodeIntoTree( void* node, void* parent, void* frame );


CVAPI(void) cvRemoveNodeFromTree( void* node, void* frame );



CVAPI(CvSeq*) cvTreeToNodeSeq( const void* first, int header_size,
                              CvMemStorage* storage );



#define CV_KMEANS_USE_INITIAL_LABELS 1
CVAPI(int) cvKMeans2( const CvArr* samples, int cluster_count, CvArr* labels,
                      CvTermCriteria termcrit, int attempts CV_DEFAULT(1),
                      CvRNG* rng CV_DEFAULT(0), int flags CV_DEFAULT(0),
                      CvArr* _centers CV_DEFAULT(0), double* compactness CV_DEFAULT(0) );






CVAPI(int) cvRegisterModule( const CvModuleInfo* module_info );


CVAPI(int) cvUseOptimized( int on_off );


CVAPI(void) cvGetModuleInfo( const char* module_name,
                              const char** version,
                              const char** loaded_addon_plugins );

typedef void* (CV_CDECL *CvAllocFunc)(size_t size, void* userdata);
typedef int (CV_CDECL *CvFreeFunc)(void* pptr, void* userdata);



CVAPI(void) cvSetMemoryManager( CvAllocFunc alloc_func CV_DEFAULT(NULL),
                               CvFreeFunc free_func CV_DEFAULT(NULL),
                               void* userdata CV_DEFAULT(NULL));


typedef IplImage* (CV_STDCALL* Cv_iplCreateImageHeader)
                            (int,int,int,char*,char*,int,int,int,int,int,
                            IplROI*,IplImage*,void*,IplTileInfo*);
typedef void (CV_STDCALL* Cv_iplAllocateImageData)(IplImage*,int,int);
typedef void (CV_STDCALL* Cv_iplDeallocate)(IplImage*,int);
typedef IplROI* (CV_STDCALL* Cv_iplCreateROI)(int,int,int,int,int);
typedef IplImage* (CV_STDCALL* Cv_iplCloneImage)(const IplImage*);


CVAPI(void) cvSetIPLAllocators( Cv_iplCreateImageHeader create_header,
                               Cv_iplAllocateImageData allocate_data,
                               Cv_iplDeallocate deallocate,
                               Cv_iplCreateROI create_roi,
                               Cv_iplCloneImage clone_image );

#define CV_TURN_ON_IPL_COMPATIBILITY() \
    cvSetIPLAllocators( iplCreateImageHeader, iplAllocateImage, \
                        iplDeallocate, iplCreateROI, iplCloneImage )
CVAPI(CvFileStorage*) cvOpenFileStorage( const char* filename, CvMemStorage* memstorage,
                                          int flags, const char* encoding CV_DEFAULT(NULL) );


CVAPI(void) cvReleaseFileStorage( CvFileStorage** fs );


CVAPI(const char*) cvAttrValue( const CvAttrList* attr, const char* attr_name );


CVAPI(void) cvStartWriteStruct( CvFileStorage* fs, const char* name,
                                int struct_flags, const char* type_name CV_DEFAULT(NULL),
                                CvAttrList attributes CV_DEFAULT(cvAttrList()));


CVAPI(void) cvEndWriteStruct( CvFileStorage* fs );


CVAPI(void) cvWriteInt( CvFileStorage* fs, const char* name, int value );


CVAPI(void) cvWriteReal( CvFileStorage* fs, const char* name, double value );


CVAPI(void) cvWriteString( CvFileStorage* fs, const char* name,
                           const char* str, int quote CV_DEFAULT(0) );


CVAPI(void) cvWriteComment( CvFileStorage* fs, const char* comment,
                            int eol_comment );



CVAPI(void) cvWrite( CvFileStorage* fs, const char* name, const void* ptr,
                         CvAttrList attributes CV_DEFAULT(cvAttrList()));


CVAPI(void) cvStartNextStream( CvFileStorage* fs );


CVAPI(void) cvWriteRawData( CvFileStorage* fs, const void* src,
                                int len, const char* dt );



CVAPI(CvStringHashNode*) cvGetHashedKey( CvFileStorage* fs, const char* name,
                                        int len CV_DEFAULT(-1),
                                        int create_missing CV_DEFAULT(0));



CVAPI(CvFileNode*) cvGetRootFileNode( const CvFileStorage* fs,
                                     int stream_index CV_DEFAULT(0) );



CVAPI(CvFileNode*) cvGetFileNode( CvFileStorage* fs, CvFileNode* map,
                                 const CvStringHashNode* key,
                                 int create_missing CV_DEFAULT(0) );


CVAPI(CvFileNode*) cvGetFileNodeByName( const CvFileStorage* fs,
                                       const CvFileNode* map,
                                       const char* name );

CV_INLINE int cvReadInt( const CvFileNode* node, int default_value CV_DEFAULT(0) )
{
    return !node ? default_value :
        CV_NODE_IS_INT(node->tag) ? node->data.i :
        CV_NODE_IS_REAL(node->tag) ? cvRound(node->data.f) : 0x7fffffff;
}


CV_INLINE int cvReadIntByName( const CvFileStorage* fs, const CvFileNode* map,
                         const char* name, int default_value CV_DEFAULT(0) )
{
    return cvReadInt( cvGetFileNodeByName( fs, map, name ), default_value );
}


CV_INLINE double cvReadReal( const CvFileNode* node, double default_value CV_DEFAULT(0.) )
{
    return !node ? default_value :
        CV_NODE_IS_INT(node->tag) ? (double)node->data.i :
        CV_NODE_IS_REAL(node->tag) ? node->data.f : 1e300;
}


CV_INLINE double cvReadRealByName( const CvFileStorage* fs, const CvFileNode* map,
                        const char* name, double default_value CV_DEFAULT(0.) )
{
    return cvReadReal( cvGetFileNodeByName( fs, map, name ), default_value );
}


CV_INLINE const char* cvReadString( const CvFileNode* node,
                        const char* default_value CV_DEFAULT(NULL) )
{
    return !node ? default_value : CV_NODE_IS_STRING(node->tag) ? node->data.str.ptr : 0;
}


CV_INLINE const char* cvReadStringByName( const CvFileStorage* fs, const CvFileNode* map,
                        const char* name, const char* default_value CV_DEFAULT(NULL) )
{
    return cvReadString( cvGetFileNodeByName( fs, map, name ), default_value );
}



CVAPI(void*) cvRead( CvFileStorage* fs, CvFileNode* node,
                        CvAttrList* attributes CV_DEFAULT(NULL));


CV_INLINE void* cvReadByName( CvFileStorage* fs, const CvFileNode* map,
                              const char* name, CvAttrList* attributes CV_DEFAULT(NULL) )
{
    return cvRead( fs, cvGetFileNodeByName( fs, map, name ), attributes );
}



CVAPI(void) cvStartReadRawData( const CvFileStorage* fs, const CvFileNode* src,
                               CvSeqReader* reader );


CVAPI(void) cvReadRawDataSlice( const CvFileStorage* fs, CvSeqReader* reader,
                               int count, void* dst, const char* dt );


CVAPI(void) cvReadRawData( const CvFileStorage* fs, const CvFileNode* src,
                          void* dst, const char* dt );


CVAPI(void) cvWriteFileNode( CvFileStorage* fs, const char* new_node_name,
                            const CvFileNode* node, int embed );


CVAPI(const char*) cvGetFileNodeName( const CvFileNode* node );



CVAPI(void) cvRegisterType( const CvTypeInfo* info );
CVAPI(void) cvUnregisterType( const char* type_name );
CVAPI(CvTypeInfo*) cvFirstType(void);
CVAPI(CvTypeInfo*) cvFindType( const char* type_name );
CVAPI(CvTypeInfo*) cvTypeOf( const void* struct_ptr );


CVAPI(void) cvRelease( void** struct_ptr );
CVAPI(void*) cvClone( const void* struct_ptr );


CVAPI(void) cvSave( const char* filename, const void* struct_ptr,
                    const char* name CV_DEFAULT(NULL),
                    const char* comment CV_DEFAULT(NULL),
                    CvAttrList attributes CV_DEFAULT(cvAttrList()));
CVAPI(void*) cvLoad( const char* filename,
                     CvMemStorage* memstorage CV_DEFAULT(NULL),
                     const char* name CV_DEFAULT(NULL),
                     const char** real_name CV_DEFAULT(NULL) );





CVAPI(int64) cvGetTickCount( void );
CVAPI(double) cvGetTickFrequency( void );



#define CV_CPU_NONE 0
#define CV_CPU_MMX 1
#define CV_CPU_SSE 2
#define CV_CPU_SSE2 3
#define CV_CPU_SSE3 4
#define CV_CPU_SSSE3 5
#define CV_CPU_SSE4_1 6
#define CV_CPU_SSE4_2 7
#define CV_CPU_POPCNT 8
#define CV_CPU_AVX 10
#define CV_CPU_AVX2 11
#define CV_HARDWARE_MAX_FEATURE 255

CVAPI(int) cvCheckHardwareSupport(int feature);




CVAPI(int) cvGetNumThreads( void );
CVAPI(void) cvSetNumThreads( int threads CV_DEFAULT(0) );

CVAPI(int) cvGetThreadNum( void );





CVAPI(int) cvGetErrStatus( void );


CVAPI(void) cvSetErrStatus( int status );

#define CV_ErrModeLeaf 0
#define CV_ErrModeParent 1
#define CV_ErrModeSilent 2


CVAPI(int) cvGetErrMode( void );


CVAPI(int) cvSetErrMode( int mode );




CVAPI(void) cvError( int status, const char* func_name,
                    const char* err_msg, const char* file_name, int line );


CVAPI(const char*) cvErrorStr( int status );


CVAPI(int) cvGetErrInfo( const char** errcode_desc, const char** description,
                        const char** filename, int* line );


CVAPI(int) cvErrorFromIppStatus( int ipp_status );

typedef int (CV_CDECL *CvErrorCallback)( int status, const char* func_name,
                                        const char* err_msg, const char* file_name, int line, void* userdata );


CVAPI(CvErrorCallback) cvRedirectError( CvErrorCallback error_handler,
                                       void* userdata CV_DEFAULT(NULL),
                                       void** prev_userdata CV_DEFAULT(NULL) );







CVAPI(int) cvNulDevReport( int status, const char* func_name, const char* err_msg,
                          const char* file_name, int line, void* userdata );

CVAPI(int) cvStdErrReport( int status, const char* func_name, const char* err_msg,
                          const char* file_name, int line, void* userdata );

CVAPI(int) cvGuiBoxReport( int status, const char* func_name, const char* err_msg,
                          const char* file_name, int line, void* userdata );

#define OPENCV_ERROR(status,func,context) \
cvError((status),(func),(context),__FILE__,__LINE__)

#define OPENCV_ERRCHK(func,context) \
{if (cvGetErrStatus() >= 0) \
{OPENCV_ERROR(CV_StsBackTrace,(func),(context));}}

#define OPENCV_ASSERT(expr,func,context) \
{if (! (expr)) \
{OPENCV_ERROR(CV_StsInternal,(func),(context));}}

#define OPENCV_RSTERR() (cvSetErrStatus(CV_StsOk))

#define OPENCV_CALL(Func) \
{ \
Func; \
}



#ifdef CV_NO_FUNC_NAMES
#define CV_FUNCNAME(Name) 
#define cvFuncName ""
#else
#define CV_FUNCNAME(Name) \
static char cvFuncName[] = Name
#endif






#define CV_ERROR(Code,Msg) \
{ \
    cvError( (Code), cvFuncName, Msg, __FILE__, __LINE__ ); \
    __CV_EXIT__; \
}


#define CV_ERROR_FROM_CODE(code) \
    CV_ERROR( code, "" )






#define CV_CHECK() \
{ \
    if( cvGetErrStatus() < 0 ) \
        CV_ERROR( CV_StsBackTrace, "Inner function failed." ); \
}







#define CV_CALL(Func) \
{ \
    Func; \
    CV_CHECK(); \
}



#define CV_ASSERT(Condition) \
{ \
    if( !(Condition) ) \
        CV_ERROR( CV_StsInternal, "Assertion: " #Condition " failed" ); \
}

#define __CV_BEGIN__ {
#define __CV_END__ goto exit; exit: ; }
#define __CV_EXIT__ goto exit

#ifdef __cplusplus
}


struct CV_EXPORTS CvModule
{
    CvModule( CvModuleInfo* _info );
    ~CvModule();
    CvModuleInfo* info;

    static CvModuleInfo* first;
    static CvModuleInfo* last;
};

struct CV_EXPORTS CvType
{
    CvType( const char* type_name,
            CvIsInstanceFunc is_instance, CvReleaseFunc release=0,
            CvReadFunc read=0, CvWriteFunc write=0, CvCloneFunc clone=0 );
    ~CvType();
    CvTypeInfo* info;

    static CvTypeInfo* first;
    static CvTypeInfo* last;
};

#endif

#endif
