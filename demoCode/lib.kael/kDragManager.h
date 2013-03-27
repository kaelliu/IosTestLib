//
//  kDragManager.h
//
//  Created by kael on 1/14/13.
//
//

#ifndef __kDragManager__
#define __kDragManager__

#include "cocos2d.h"
#include "kSingleton.h"
//#include <vector>
using namespace cocos2d;
class kDragableObject;
//class kDragSource;
#define NO_DRAG -1
#define IN_DRAG 0
#define MOVE_BUT_NODRAG 1
class kDragManager:public CCLayer,public kSingleton<kDragManager>
{
public:
    //CREATE_FUNC(kDragManager);
    virtual bool init();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void startDrag(kDragableObject* obj);
    void startDrop();
    void startEnter(kDragableObject* obj);
    void startLeave();
    //std::vector<kDragableObject*> dragobjs;
    kDragableObject* curDrag;
    kDragableObject* curTarget;
    long lastMoveTime;
    // true for enable drag state,false for no drag state
    // in drag state can no drag object,to avoid scroll tableview
    char dragState;
};

#endif /* defined(__kDragManager__) */
