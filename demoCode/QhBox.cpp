#include "QhBox.h"
#include "QiangHLayer.h"

USING_NS_CC;

QhBox::QhBox()
{

}

QhBox::~QhBox()
{

}

bool QhBox::init()
{
	return true;
}

bool QhBox::containsTouchLocation(CCTouch* touch)
{
	CCRect rect = CCRectMake(0, 0, 38, 38);
	return rect.containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool QhBox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if ( !containsTouchLocation(pTouch) ) return false;
	CCLOG("you touch qhBox id is %d",this->_id);
	QiangHLayer *layer = dynamic_cast<QiangHLayer *> (this->getParent()->getParent()->getParent());

	//layer->flushLeft(this->_id);
	return true;
}

void QhBox::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void QhBox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void QhBox::setItemPic(const char *file)
{
	CCSprite* sha = CCSprite::create(file);
	sha->setAnchorPoint(ccp(0,0));
	this->addChild(sha,0);

	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
}