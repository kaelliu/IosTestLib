//
//  demoCodeAppDelegate.h
//  demoCode
//
//  Created by kael on 12/21/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "cocos2d.h"
// for screen fit
typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;
static Resource iphone3gs = {cocos2d::CCSize(480,320),"ip3gs"};
static Resource iphone4 = {cocos2d::CCSize(960,640),"ip4"};
static Resource ipad3 = {cocos2d::CCSize(2048,1536),"pad3"};
static Resource ipadmini = {cocos2d::CCSize(1024,768),"mini"};
static Resource iphone5 = {cocos2d::CCSize(1136,640),"ip5"};
static cocos2d::CCSize designResolutionSize = cocos2d::CCSize(480,320);
/**
@brief    The cocos2d Application.

The reason to implement with private inheritance is to hide some interface details of CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function is called when the application enters the background
    @param  the pointer of the application instance
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function is called when the application enters the foreground
    @param  the pointer of the application instance
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

