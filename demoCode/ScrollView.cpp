#include "ScrollView.h"
#include "QhBox.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool ScrollView::init()
{
	//init scroll_view content

	CCLayer *layer = CCLayer::create();
	
	int pages = 9;

	for(int i = 0;i<pages;++i)
	{
		CCSprite *backgroundSprite = CCSprite::create(i%2 ? "bg1.png" : "bg2.png");

		for (int j = 0; j<5; ++j)
		{
			QhBox *spt_img = QhBox::create();
			//spt_img->f = f;
			spt_img->_id = j;
			spt_img->setItemPic(CCString::createWithFormat("c%d.png",j+1)->getCString());
			//CCSprite *spt_img = CCSprite::create("c1.png");
			//spt_img->setAnchorPoint(CCPointZero);
			spt_img->setPosition(ccp(50*j + 70,5));
			backgroundSprite->addChild(spt_img);
		}	


		backgroundSprite->setAnchorPoint(CCPointZero);
		backgroundSprite->setPositionY(ONESCREEN_HEIGHT*i);
		layer->addChild(backgroundSprite);
	}

	scrollView = ScrollViewScene::create();
	scrollView->setViewSize(CCSizeMake(ONESCREEN_WIDTH, ONESCREEN_HEIGHT*6));
	scrollView->setContainer(layer);
	scrollView->setContentSize(CCSizeMake(ONESCREEN_WIDTH, ONESCREEN_HEIGHT*pages));
	scrollView->setPosition(CCPointZero);
	scrollView->setDirection(kCCScrollViewDirectionVertical);
	scrollView->setDelegate(this);
	this->addChild(scrollView);

	return true;
}

void ScrollView::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
}

void ScrollView::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void ScrollView::scrollViewDidScroll(CCScrollView* view)
{

}

void ScrollView::scrollViewDidZoom(CCScrollView* view)
{

}

bool ScrollView::containsTouchLocation(CCTouch* touch)
{
	CCSize s = getContentSize();
	CCRect rect = CCRectMake(0, 0, s.width, s.height);
	return rect.containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool ScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if ( !containsTouchLocation(pTouch) ) return false;
	CCLog("scrollView TouchBegan");
	return true;
}

void ScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void ScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
