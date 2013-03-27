//
//  kNpcSpriteContainer.h
//
//  Created by kael on 1/7/13.
//
//

#ifndef __kNpcSpriteContainer__
#define __kNpcSpriteContainer__

#include "kSpriteContainer.h"
#include "kCommonStruct.h"
class kNpcSpriteContainer:public kSpriteContainer
{
public:
    CREATE_FUNC(kNpcSpriteContainer);
    virtual bool init();
    ~kNpcSpriteContainer();
    virtual void loadFromConfiguration(const char* name,void* extraparam=NULL);
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
protected:
    int  npcid;
    bool haveShadow;
};
#endif /* defined(__kNpcSpriteContainer__) */
