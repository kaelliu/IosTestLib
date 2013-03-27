//
//  kAction.h
//
//  Created by kael on 12/27/12.
//
//

#ifndef __kAction__
#define __kAction__
#include<list>
#include"cocos2d.h"
#define SPEED_PER_PIXEL 128
#define AUTOMATIC_ACTION_MOVE_TO   1
#define AUTOMATIC_ACTION_OPEN_UI   2
#define AUTOMATIC_ACTION_CLOSE_UI  3
//enum kAutoMationAction
//{
//    kAutoMaticActionMoveTo=1,
//    kAutoMaticActionOpenUi=2,
//    kAutoMaticActionCloseUi=3,
//    kAutoMaticActionCount,
//};
struct kAction
{
    unsigned short _type;
    bool working;// is working?
};

struct kAMoveTo:public kAction
{
    short x;
    short y;
    kAMoveTo(){_type = AUTOMATIC_ACTION_MOVE_TO;}
};

struct kAOpenUi:public kAction
{
    char uiPath[32];
    kAOpenUi(){_type = AUTOMATIC_ACTION_OPEN_UI;}
};

// close ui is close current ui,no data ,use kAction

// common function for map scene,fb scene,activity scene's role move control
class kMapStruct;
class kAstarAlgorithm;
class kPathFindBehaviour
{
public:
    // to generate path fingding action list
    static kAction* onTouchEnd(kAstarAlgorithm* algo,const cocos2d::CCPoint& start,
                               const cocos2d::CCPoint& target,cocos2d::CCLayer* parentLayer);
    // begin to go,change the direction ,and make the move to action
    // target sprite/from/to point/ goto action finished callback function
    static void onBeginToGo(cocos2d::CCLayer* target,
                            const cocos2d::CCPoint& end,cocos2d::CCLayer* parentLayer,cocos2d::CCCallFunc* overCallback,int layerscrollwidth,int layerscrollheight);
    static int towards;
};
#endif /* defined(__kAction__) */
