#ifndef SCROLLVIEWSCENE_H
#define SCROLLVIEWSCENE_H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define ONESCREEN_WIDTH 320
#define ONESCREEN_HEIGHT 48

class ScrollViewScene : public cocos2d::extension::CCScrollView
{
public:
	ScrollViewScene();
	~ScrollViewScene();

	virtual bool init();
	CREATE_FUNC(ScrollViewScene);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};
#endif