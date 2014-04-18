/*
 *  CMMotionManagerSim.h
 *
 *  Created by Lloyd Hughes on 10/04/2013
 *
 *  Based off of the original work by
 *  Created by Otto Chrons on 9/26/08.
 *  Copyright 2008 Seastringo Oy. All rights reserved.
 *
 */
#import <TargetConditionals.h>
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

// when compiling to ARM (iPhone device), hide everything and use system defaults
// if you wish to use simulation mode even on the device, remove the #if/#endif
#if !TARGET_CPU_ARM

@interface CMAccelerationSimulation: CMAccelerometerData
{
    NSTimeInterval timestamp;
	CMAcceleration acceleration;
}
@property(readwrite, nonatomic) CMAcceleration acceleration;
@property (readwrite, nonatomic) NSTimeInterval timestamp;

@end

@interface CMMagneticSimulation: CMMagnetometerData
{
    NSTimeInterval timestamp;
	CMMagneticField magneticField;
}
@property(readwrite, nonatomic) CMMagneticField magneticField;
@property (readwrite, nonatomic) NSTimeInterval timestamp;

@end

@interface CMRotationSimulation: CMGyroData
{
    NSTimeInterval timestamp;
	CMRotationRate rotationRate;
}

@property(readwrite, nonatomic) CMRotationRate rotationRate;
@property (readwrite, nonatomic) NSTimeInterval timestamp;

@end

struct SAttitude {
    double roll;
    double pitch;
    double yaw;
};

typedef struct SAttitude SAttitude;
@interface CMAttitudeSimulation: CMAttitude
{
    NSTimeInterval timestamp;
    double roll;
    double pitch;
    double yaw;
}

@property(readwrite, nonatomic) double roll;
@property(readwrite, nonatomic) double pitch;
@property(readwrite, nonatomic) double yaw;
@property (readwrite, nonatomic) NSTimeInterval timestamp;

@end


@interface CMDeviceMotionSimulation: CMDeviceMotion
{
    NSTimeInterval timestamp;
    CMAttitude *attitude;
    CMAcceleration gravity;
	CMCalibratedMagneticField magneticField;
    CMRotationRate rotationRate;
    CMAcceleration userAcceleration;
   
}
@property (readwrite, nonatomic) NSTimeInterval timestamp;
@property(readonly, nonatomic) CMAttitude *attitude;
@property(readonly, nonatomic) CMAcceleration gravity;
@property(readwrite, nonatomic) CMCalibratedMagneticField magneticField;
@property(readonly, nonatomic) CMRotationRate rotationRate;
@property(readonly, nonatomic) CMAcceleration userAcceleration;
@end


@interface CMMotionManager (Simulation)
@property(readonly, nonatomic, getter=isAccelerometerAvailable) BOOL accelerometerAvailable;
@property(readonly, nonatomic, getter=isGyroAvailable) BOOL gyroAvailable;
@property(readonly, nonatomic, getter=isMagnetometerAvailable) BOOL magnetometerAvailable;

- (BOOL) isAccelerometerAvailable;
- (BOOL) isGyroAvailable;
- (BOOL) isMagnetometerAvailable;
- (BOOL) isDeviceMotionAvailable;
@end

@interface CMMotionManagerSim : CMMotionManager <NSMachPortDelegate>
{

	//CFSocketRef udpSocket;
	int udpSocket;
    
    BOOL gyroOn, accelOn, magOn, deviceOn;
    
	NSThread *thread;
	BOOL isExiting;
	CMAccelerationSimulation *accelerometerData;
    CMRotationSimulation *gyroData;
    CMMagneticSimulation *magnetometerData;
    CMAttitudeSimulation *attData;
    CMDeviceMotionSimulation *deviceData;
    
    // Threaded notification support 
    NSMutableArray *notifications;
    NSThread *notificationThread;
    NSLock *notificationLock;
    NSMachPort *notificationPort;
    __block CMAccelerometerHandler accelHandler;
    __block CMGyroHandler gyroHandler;
    __block CMMagnetometerHandler magHandler;
    __block CMDeviceMotionHandler deviceHandler;
}

@property(readwrite, assign) CMAccelerationSimulation *accelerometerData;
@property(readwrite, assign) CMRotationSimulation *gyroData;
@property(readwrite, assign) CMMagneticSimulation *magnetometerData;
@property(readwrite, assign) CMAttitudeSimulation *attData;
@property(readwrite, assign) CMDeviceMotionSimulation *deviceData;


- (void)startAccelerometerUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMAccelerometerHandler)handler;
- (void)startGyroUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMGyroHandler)handler;
- (void)startMagnetometerUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMMagnetometerHandler)handler;
- (void)startDeviceMotionUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMDeviceMotionHandler)handler;

- (void) setUpThreadingSupport;
- (void) handleMachMessage:(void *) msg;
- (void) processNotification:(NSNotification *) notification;
- (CMMotionManagerSim *)init;

- (BOOL) isMagnetometerActive;
- (BOOL) isAccelerometerActive;
- (BOOL) isGyroActive;

@end

#endif
