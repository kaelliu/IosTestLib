#ifndef QIANGHLAYER_H
#define QIANGHLAYER_H

#include "kUiLayer.h"

class QiangHLayer : public kUiLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(QiangHLayer, create);

	QiangHLayer();
	virtual ~QiangHLayer();
 	virtual void preInit();

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);

	void qhClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

	void flushLeft(int id);
private:
	cocos2d::CCLabelTTF *txt_lv;
	cocos2d::CCLabelTTF *txt_now;
	cocos2d::CCLabelTTF *txt_update;
	cocos2d::CCLabelTTF *txt_roleLv;
	cocos2d::CCLabelTTF *txt_money;
	cocos2d::extension::CCControlButton *btn_qh;
	cocos2d::CCSprite *spt_img;

	 void initExtraUi();

};

class QiangHLayerLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(QiangHLayerLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(QiangHLayer);
};

#endif