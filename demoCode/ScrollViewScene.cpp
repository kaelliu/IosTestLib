#include "ScrollViewScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

ScrollViewScene::ScrollViewScene()
{

}

ScrollViewScene::~ScrollViewScene()
{
	
}

bool ScrollViewScene::init()
{
	return CCScrollView::init();
}

bool ScrollViewScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

	CCScrollView::ccTouchBegan(pTouch, pEvent);
	return true;
}

void ScrollViewScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCScrollView::ccTouchMoved(pTouch, pEvent);
}

void ScrollViewScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCScrollView::ccTouchEnded(pTouch, pEvent);
}