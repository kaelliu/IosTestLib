//
//  kDragableObject.cpp
//
//  Created by kael on 1/14/13.
//
//

#include "kDragableObject.h"
#include "kDragManager.h"

bool kDragableObject::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    // always return true here;
    return true;
}

void kDragableObject::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if(kDragManager::getInstance().dragState == IN_DRAG)
    {
        if ( !containsTouchLocation(pTouch) )
        {
            // is it the last target object?
            if(this == kDragManager::getInstance().curTarget)
            {
                // curtarget is not me this time
                kDragManager::getInstance().startLeave();
            }
            keepMoveRespone = false;
        }
        else
        {
            // not drag target yet,set it
            if(kDragManager::getInstance().curDrag == NULL)
            {
                kDragManager::getInstance().startDrag(this);
            }
            else
            {
                // no target yet
                if(kDragManager::getInstance().curTarget == NULL)
                {
                    // drag source not set to target,if drop target is null
                    // consider drop is invaild
                    if (this != kDragManager::getInstance().curDrag) {
                        kDragManager::getInstance().startEnter(this);
                    }
                }
            }
            keepMoveRespone = true;
        }
    }
    else
    {
        // do nothing
        keepMoveRespone = false;
    }
}

bool kDragableObject::containsTouchLocation(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}