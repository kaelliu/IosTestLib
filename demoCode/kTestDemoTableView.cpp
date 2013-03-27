//
//  kTestDemoTableView.cpp
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#include "kTestDemoTableView.h"
#include "kTestDemoTableViewCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

kTestDemoTableView::kTestDemoTableView(void)
{
    curSelect_inx = -1;
}

kTestDemoTableView::~kTestDemoTableView(void)
{
    datasource.clear();
}

// on "init" you need to initialize your instance
bool kTestDemoTableView::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    // Add the BG
    //    CCSprite* tableViewBG = CCSprite::create("right.png");
    //    tableViewBG->setPosition(ccp(winSize.width-45, winSize.height/2));
    //    this->addChild(tableViewBG);
    //    CCSprite* upBG = CCSprite::create("up.png");
    //    upBG->setPosition(ccp(winSize.width-45, winSize.height-30));
    //    this->addChild(upBG);
    //    CCSprite* downBG = CCSprite::create("down.png");
    //    downBG->setPosition(ccp(winSize.width-45, 10));
    //    this->addChild(downBG);
    
    // Add the CCTableView
    
    
    tableView = CCTableView::create(this, CCSizeMake(60,120));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(0,0));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView);
    tableView->reloadData();
    return true;
}

void kTestDemoTableView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    //打印相应cell的Idx
    CCLOG("cell touched at index: %i", cell->getIdx());
    curSelect_inx = cell->getIdx();
}

CCSize kTestDemoTableView::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(60, 20);
}

CCTableViewCell* kTestDemoTableView::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string;
    CCLOG("is:%d,%s",idx,datasource[idx].name);
    string = CCString::createWithFormat("%s", datasource[idx].name);
//    string = CCString::createWithFormat("%s", "kkkk");
    CCTableViewCell* cell = table->dequeueCell();
    // do your cell staff here
    if (!cell) {
        // the sprite
        cell = new kTestDemoTableViewCell();
        cell->autorelease();

        CCLabelTTF* label = CCLabelTTF::create(string->getCString(),"Thonburi", 16);
        label->setPosition(ccp(0,0));
        label->setTag(123);
        label->setAnchorPoint(ccp(0,0));
        cell->addChild(label);
        cell->setAnchorPoint(ccp(0,0));
    }
    else{
        // the sprite       
        // the label
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    return cell;
}

void kTestDemoTableView::onPageDataBack(std::vector<UserInfo>& us)
{
    bool first_added = (datasource.size() == 0);
    for (int i=0;i<us.size(); ++i) {
        datasource.push_back(us[i]);
    }
//    m_bFresh = true;
    tableView->reloadData(first_added);
}

void kTestDemoTableView::visit()
{
    CCLayer::visit();
//    if (m_bFresh) {
//        tableView->reloadData();
//        m_bFresh = false;
//    }
}

void kTestDemoTableView::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
    int curPage = datasource.size() / 10;// 10 per page
    // go query page data
}

unsigned int kTestDemoTableView::numberOfCellsInTableView(CCTableView *table)
{
    return datasource.size();
//    return 16;
}

void kTestDemoTableView::onDelCell(int idx)
{
    if(idx< 0 || idx>=datasource.size())return;
    else
    {
        std::vector<UserInfo>::iterator pos = datasource.begin() + idx;
        datasource.erase(pos);
        tableView->reloadData();
    }
}

void kTestDemoTableView::onAddCell(UserInfo& ui)
{
    datasource.push_back(ui);
    tableView->reloadData();
}