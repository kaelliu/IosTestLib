//
//  demoCodeAppDelegate.cpp
//  demoCode
//
//  Created by kael on 12/21/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "kBaseScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // set auto fit screen
    // set the resolution pixel per screen width and height
    // for example,screen is 480*320 pixel in logic,if you set 80,320 for it,u will see the picture
    // in screen 's width will be expand,80 pixel will show in 480 pixel,equal scale as 6times
    // to adjust screen size for android/ipad for setting this
    // you can scale the scene by this
    // if you have an asset suit as size of 480*320,screen is 960*640,should set to resource size
    // if your asset suit is smaller than screen's frame size,make this function to resize the
    // resolution size
    // if your asset suit is larger then screen,you should zoom in screen for fit,use this as scale
    // small
    // like 2X scale here
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    //CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height,kResolutionNoBorder);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height,kResolutionExactFit);

    
    // create a scene. it's an autorelease object
    CCScene *pScene = kBaseScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
