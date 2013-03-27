//
//  kDragManager.cpp
//
//  Created by kael on 1/14/13.
//
//

#include "kDragManager.h"
#include "kDragableObject.h"

template<> kDragManager* kSingleton<kDragManager>::_singleton = NULL;
long getNowInMs()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

bool kDragManager::init()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, -2, false);
    curDrag = NULL;
    curTarget = NULL;
    lastMoveTime = -1;
    dragState = NO_DRAG;
    return true;
}

bool kDragManager::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(lastMoveTime == -1)
    {
        long nowMoveTime = getNowInMs();
        lastMoveTime = nowMoveTime;
    }

    return true;
}

void kDragManager::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    startDrop();
    dragState = NO_DRAG;
    lastMoveTime = -1;
    curDrag = NULL;
}

void kDragManager::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (dragState == NO_DRAG) {
        long nowMoveTime = getNowInMs();
        if(lastMoveTime == -1)
        {
            lastMoveTime = nowMoveTime;
            return;
        }
        long diffTime = nowMoveTime - lastMoveTime;
        lastMoveTime = nowMoveTime;
        // decide the behaviour by hold time
        if(diffTime > 350)
        {
            // long time move,pan
            dragState = IN_DRAG;
        }
        else
        {
            // quick move ,swipe
            dragState = MOVE_BUT_NODRAG;
        }
    }
    else if(dragState == IN_DRAG)
    {
        // do move staff
        if(curDrag == NULL)
        {
            // no drag target
        
        }
        else
        {
            
        }
    }
}

void kDragManager::startDrag(kDragableObject* obj)
{
    if(curDrag == NULL)
    {
        curDrag = obj;
        dragState = IN_DRAG;
    }
}

void kDragManager::startEnter(kDragableObject* obj)
{
    obj->onDragEnter();
    curTarget = obj;
}

void kDragManager::startLeave()
{
    if(curTarget)
    {
        curTarget->onDragLeave();
        curTarget = NULL;
    }
}

void kDragManager::startDrop()
{
    // find target object
    // do drop staff,may custom by yourself
    // if target is null ,need a set back action
    if(curDrag)
        curDrag->onDragDrop(curTarget);
}