#include "QiangHLayer.h"
#include "ScrollView.h"


USING_NS_CC;
USING_NS_CC_EXT;

QiangHLayer::QiangHLayer()
: txt_lv(NULL)
, txt_now(NULL)
, txt_update(NULL)
, txt_roleLv(NULL)
, txt_money(NULL)
, btn_qh(NULL)
{
}

QiangHLayer::~QiangHLayer()
{
	CC_SAFE_RELEASE(txt_lv);
	CC_SAFE_RELEASE(txt_now);
	CC_SAFE_RELEASE(txt_update);
	CC_SAFE_RELEASE(txt_roleLv);
	CC_SAFE_RELEASE(txt_money);
	CC_SAFE_RELEASE(btn_qh);
}

void QiangHLayer::preInit()
{
	initExtraUi();
	
}

void QiangHLayer::initExtraUi()
{
	ScrollView *scroll = ScrollView::create();
	if(NULL != scroll)
	{
		scroll->setAnchorPoint(CCPointZero);
		scroll->setPosition(ccp(15,15));
		//scroll->f = &QiangHLayer::flushLeft;
		this->addChild(scroll);
	}

	spt_img = CCSprite::create("c1.png");
	spt_img->setAnchorPoint(CCPointZero);
	spt_img->setPosition(ccp(380,260));
	addChild(spt_img);
}

void QiangHLayer::qhClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	CCLOG("强化");
	CCLOG(this->txt_lv->getString());
	CCMessageBox("强化","提示");
}


SEL_MenuHandler QiangHLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler QiangHLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "qhClicked", QiangHLayer::qhClicked);
	//CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(pTarget);
	//if(pTarget == this && pSelectorName->compare("onBtn_qhClicked") == 0)
	//	return cccontrol_selector(QiangHLayer::onBtn_qhClicked);
	return NULL;
}

void QiangHLayer::flushLeft(int id)
{
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("c%d.png",id)->getCString()); 
	this->spt_img->setTexture(texture);

	this->txt_lv->setString(CCString::createWithFormat("当前等级: %d",id)->getCString());
	this->txt_now->setString(CCString::createWithFormat("当前智防: +%d",id)->getCString());
	this->txt_update->setString(CCString::createWithFormat("升级智防: +%d",id)->getCString());
	this->txt_roleLv->setString(CCString::createWithFormat("升级需要: 主将等级%d级",id)->getCString());
	this->txt_money->setString(CCString::createWithFormat("强化费用: %d铜钱",id)->getCString());
}

bool QiangHLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) 
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_lv", CCLabelTTF *, this->txt_lv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_now", CCLabelTTF *, this->txt_now);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_update", CCLabelTTF *, this->txt_update);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_roleLv", CCLabelTTF *, this->txt_roleLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txt_money", CCLabelTTF *, this->txt_money);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_qh", CCControlButton *, this->btn_qh);
	
	return false;
}