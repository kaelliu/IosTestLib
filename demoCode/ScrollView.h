#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ScrollViewScene.h"

USING_NS_CC;
USING_NS_CC_EXT;


class QiangHLayer;
class ScrollView 
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCScrollViewDelegate
{
public:
	CREATE_FUNC(ScrollView);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//void (QiangHLayer::*f)(int );
	QiangHLayer *layer;
private:
	cocos2d::CCLabelTTF *pLabel;
	ScrollViewScene *scrollView;
	bool containsTouchLocation(CCTouch* touch);
};

#endif