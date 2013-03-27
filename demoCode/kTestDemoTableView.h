//
//  kTestDemoTableView.h
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#ifndef __demoCode__kTestDemoTableView__
#define __demoCode__kTestDemoTableView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "kStructDemoModule.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class kTestDemoTableView: public cocos2d::CCLayer,public cocos2d::extension::CCTableViewDelegate
    ,public cocos2d::extension::CCTableViewDataSource
{
public:
    kTestDemoTableView(void);
    ~kTestDemoTableView(void);
public:
    virtual bool init();
    
    CREATE_FUNC(kTestDemoTableView);
    // over ride
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table,cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table,unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView* table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    void onPageDataBack(std::vector<UserInfo>& us);
    void visit();
protected:
    std::vector<UserInfo> datasource;
    CCTableView* tableView;
    bool m_bFresh;
public:
    UserInfo* getDataAtSelect(){
        if(curSelect_inx<0)
            return NULL;
        else
            return &(datasource[curSelect_inx]);
    }
    int curSelect_inx;
    void onDelCell(int idx);
    void onAddCell(UserInfo& ui);
    void onReloaded(){tableView->reloadData();}
};


#endif /* defined(__demoCode__kTestDemoTableView__) */
