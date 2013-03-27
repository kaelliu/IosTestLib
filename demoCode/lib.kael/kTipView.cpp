//
//  kTipView.cpp
//
//  Created by kael on 1/9/13.
//
//

#include "kTipView.h"
#include "kTipViewBase.h"
template<> kTipView* kSingleton<kTipView>::_singleton = NULL;

bool kTipView::init()
{
    curCachedTipLayer = NULL;
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, -3, false);
    return true;
}

bool kTipView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    // always return true here
    return true;
}

void kTipView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    // first respone,to take off tipview
    rmTip();
}

// add tip view use new layer 
void kTipView::addTip(CCLayer* curTarget,kTipViewBase* layer,void* extraData)
{
    if(this->getChildrenCount() > 0)
        this->removeAllChildrenWithCleanup(true);
    this->addChild((CCLayer*)layer);
    curCachedTipLayer = layer;
    curCachedTipLayer->initWithData(extraData);
    _target = curTarget;
    repositionTipWidget();
}

// add tip view use exist view
void kTipView::addTipSameType(CCLayer* curTarget,void* extraData)
{
    if (curCachedTipLayer!=NULL) {
        curCachedTipLayer->initWithData(extraData);
        _target = curTarget;
        repositionTipWidget();
    }
}

void kTipView::rmTip()
{
    this->removeAllChildrenWithCleanup(true);
    curCachedTipLayer = NULL;
}

void kTipView::repositionTipWidget()
{
    CCNode* parentnode = _target->getParent();
    CCNode* childnode = _target;
    CCPoint pt = childnode->getPosition();
    while (parentnode) {
        pt.x+=parentnode->getPositionX();
        pt.y+=parentnode->getPositionY();
        childnode = parentnode;
        parentnode = parentnode->getParent();
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if(pt.x + curCachedTipLayer->getContentSize().width > size.width)
        pt.x = size.width - curCachedTipLayer->getContentSize().width;
    if(pt.y + curCachedTipLayer->getContentSize().height > size.height)
        pt.y = size.height - curCachedTipLayer->getContentSize().height;
    curCachedTipLayer->setAnchorPoint(ccp(0,0));
    curCachedTipLayer->setPosition(pt);
}