#ifndef QHBOX_H
#define QHBOX_H

#include "cocos2d.h"
using namespace cocos2d;

class QiangHLayer;
class QhBox : public cocos2d::CCLayer
{
public:
	QhBox();
	~QhBox();

	CREATE_FUNC(QhBox);
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
public:
	int _id;
	void setItemPic(const char *file);
private:
	bool containsTouchLocation(CCTouch* touch);
};

#endif