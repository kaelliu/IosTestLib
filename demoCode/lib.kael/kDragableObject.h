//
//  kDragableObject.h
//
//  Created by kael on 1/14/13.
//
//

#ifndef __kDragableObject__
#define __kDragableObject__

#include "cocos2d.h"
using namespace cocos2d;
class kDragableObject:public CCLayer
{
public:
    virtual ~kDragableObject(){}
    virtual void onDragEnter()=0;
    virtual void onDragLeave()=0;
    virtual void onDragDrop(kDragableObject* target)=0;
    
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual CCRect rect()=0;
    bool keepMoveRespone;
};
#endif /* defined(__kDragableObject__) */
