//
//  kTipView.h
//
//  Created by kael on 1/9/13.
//
//

#ifndef __kTipView__
#define __kTipView__

#include "cocos2d.h"
#include "kSingleton.h"
using namespace cocos2d;

class kTipViewBase;
// is also a layer and singleton
class kTipView:public CCLayer,public kSingleton<kTipView>
{
public:
    // add a tip view,use common zoom out,fade in action
    void addTip(CCLayer* curTarget,kTipViewBase* layer,void* extraData);
    void addTipSameType(CCLayer* curTarget,void* extraData);
    // remove all tip view
    void rmTip();
    // cached layer for same tip view reset
    kTipViewBase* curCachedTipLayer;
    CCLayer* _target;
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool init();
protected:
    void repositionTipWidget();
};
#endif /* defined(__kTipView__) */
