#import <UIKit/UIKit.h>
#import <Accelerate/Accelerate.h>
#import <AVFoundation/AVFoundation.h>
#import <ImageIO/ImageIO.h>
#include "opencv2/core/core.hpp"



@class CvAbstractCamera;

@interface CvAbstractCamera : NSObject
{
    AVCaptureSession* captureSession;
    AVCaptureConnection* videoCaptureConnection;
    AVCaptureVideoPreviewLayer *captureVideoPreviewLayer;

    UIDeviceOrientation currentDeviceOrientation;

    BOOL cameraAvailable;
    BOOL captureSessionLoaded;
    BOOL running;
    BOOL useAVCaptureVideoPreviewLayer;

    AVCaptureDevicePosition defaultAVCaptureDevicePosition;
    AVCaptureVideoOrientation defaultAVCaptureVideoOrientation;
    NSString *const defaultAVCaptureSessionPreset;

    int defaultFPS;

    UIView* parentView;

    int imageWidth;
    int imageHeight;
}

@property (nonatomic, retain) AVCaptureSession* captureSession;
@property (nonatomic, retain) AVCaptureConnection* videoCaptureConnection;

@property (nonatomic, readonly) BOOL running;
@property (nonatomic, readonly) BOOL captureSessionLoaded;

@property (nonatomic, assign) int defaultFPS;
@property (nonatomic, assign) AVCaptureDevicePosition defaultAVCaptureDevicePosition;
@property (nonatomic, assign) AVCaptureVideoOrientation defaultAVCaptureVideoOrientation;
@property (nonatomic, assign) BOOL useAVCaptureVideoPreviewLayer;
@property (nonatomic, strong) NSString *const defaultAVCaptureSessionPreset;

@property (nonatomic, assign) int imageWidth;
@property (nonatomic, assign) int imageHeight;

@property (nonatomic, retain) UIView* parentView;

- (void)start;
- (void)stop;
- (void)switchCameras;

- (id)initWithParentView:(UIView*)parent;

- (void)createCaptureOutput;
- (void)createVideoPreviewLayer;
- (void)updateOrientation;

- (void)lockFocus;
- (void)unlockFocus;
- (void)lockExposure;
- (void)unlockExposure;
- (void)lockBalance;
- (void)unlockBalance;

@end



@class CvVideoCamera;

@protocol CvVideoCameraDelegate <NSObject>

#ifdef __cplusplus

- (void)processImage:(cv::Mat&)image;
#endif

@end

@interface CvVideoCamera : CvAbstractCamera<AVCaptureVideoDataOutputSampleBufferDelegate>
{
    AVCaptureVideoDataOutput *videoDataOutput;

    dispatch_queue_t videoDataOutputQueue;
    CALayer *customPreviewLayer;

    BOOL grayscaleMode;

    BOOL recordVideo;
    BOOL rotateVideo;
    AVAssetWriterInput* recordAssetWriterInput;
    AVAssetWriterInputPixelBufferAdaptor* recordPixelBufferAdaptor;
    AVAssetWriter* recordAssetWriter;

    CMTime lastSampleTime;

}

@property (nonatomic, assign) id<CvVideoCameraDelegate> delegate;
@property (nonatomic, assign) BOOL grayscaleMode;

@property (nonatomic, assign) BOOL recordVideo;
@property (nonatomic, assign) BOOL rotateVideo;
@property (nonatomic, retain) AVAssetWriterInput* recordAssetWriterInput;
@property (nonatomic, retain) AVAssetWriterInputPixelBufferAdaptor* recordPixelBufferAdaptor;
@property (nonatomic, retain) AVAssetWriter* recordAssetWriter;

- (void)adjustLayoutToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;
- (void)layoutPreviewLayer;
- (void)saveVideo;
- (NSURL *)videoFileURL;


@end



@class CvPhotoCamera;

@protocol CvPhotoCameraDelegate <NSObject>

- (void)photoCamera:(CvPhotoCamera*)photoCamera capturedImage:(UIImage *)image;
- (void)photoCameraCancel:(CvPhotoCamera*)photoCamera;

@end

@interface CvPhotoCamera : CvAbstractCamera
{
    AVCaptureStillImageOutput *stillImageOutput;
}

@property (nonatomic, assign) id<CvPhotoCameraDelegate> delegate;

- (void)takePicture;

@end
