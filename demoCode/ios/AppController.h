//
//  demoCodeAppController.h
//  demoCode
//
//  Created by kael on 12/21/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    // add by kael
    UIImageView *splashView;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;
-(void) startupAnimationDone:(NSString*)animationID finished:(NSNumber*)finished context:(void*)context;
@end

