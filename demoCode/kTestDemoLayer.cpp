//
//  kTestDemoLayer.cpp
//  demoCode
//
//  Created by kael on 12/21/12.
//
//

#include "kTestDemoLayer.h"
#include "kConstDefine.h"
#include "kTestDemoTableView.h"
#include "kCommonEditbox.h"
//#include "kCommonEditBoxEx.h"
#include "kBaseScene.h"
#include "kClientSocket.h"
#include "lib.kael/kJsonProtocolBase.h"
USING_NS_CC;
USING_NS_CC_EXT;

kTestDemoLayer::kTestDemoLayer()
{
    // layer start step 1
    btnAdd = NULL;
    btnDel= NULL;
    btnQuery= NULL;
    btnModify= NULL;
    
    mEditLayer= NULL;
    mListLayer= NULL;
    // also remove your listener here
}

void kTestDemoLayer::preInit()
{
    // layer start step 2,after cclayer's init
    // init your own ui here
    initExtraUi();
    // init your listener here
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(kTestDemoLayer::onPageDataBack), STRING_FY(TEST_CMD_QUERY), NULL);
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(kTestDemoLayer::onOperateResult), STRING_FY(TEST_CMD_OP_SUCCESS), NULL);
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(kTestDemoLayer::onOperateResult), STRING_FY(TEST_CMD_OP_FAILED), NULL);
    kJsonProtocolBase jpb;
    // query list
    jpb.addValue("cmd",Json::Value(Json::Int(TEST_CMD_QUERY)));
    jpb.addValue("p",Json::Value(Json::Int(1)));// query for page 1
    jpb.sendToJavaServer(kBaseScene::ks->getSock());
}

void kTestDemoLayer::onOperateResult(cocos2d::CCObject* pdata)
{
    kJsonProtocolBase jpb = *((kJsonProtocolBase*)pdata);
    const Json::Value Obj = jpb.getValue("res_code");
    int code = Obj.asInt();
    if(code == 2802)
    {
        CCMessageBox("delete ok", "haha");
        tableview->onDelCell(tableview->curSelect_inx);
    }
    else if(code/1000 == 2801)
    {
        CCMessageBox("add ok", "haha");
        int id = code % 1000;
        UserInfo ui;
        ui._id = id;
        strcpy(ui.name,kebox->getContents());
        std::vector<UserInfo> a;
        a.push_back(ui);
        tableview->onPageDataBack(a);
        kebox->clearContent();
    }
    else if(code == 2803)
    {
        CCMessageBox("modify ok", "haha");
    }
}

void kTestDemoLayer::initExtraUi()
{
    // list view
    tableview = kTestDemoTableView::create();
//    kTestDemoTableView::instance=tableview;

    mListLayer->addChild(tableview);
    mListLayer->setPositionY(mListLayer->getPositionY()-130);
    // edit box for input
    kebox = kCommonEditbox::textFieldWithWidthAndHeight(100, 30);
//    kCursorTextField* kebox = kCursorTextField::textFieldWithPlaceHolder("kael", "Thonburi", 15);
    kebox->setPosition(ccp(0,0));
    kebox->setAnchorPoint(ccp(0,0));
    mEditLayer->addChild(kebox);
    
    // NO WORK HERE!!! EDITBOX WILL MAKE TEXT AREA TO LEFT CONNER,IF NEED EDITBOX,PUT THEM IN SCENE
//    kCommonEditBoxEx* kebox = kCommonEditBoxEx::textFieldWithWidthAndHeight(100, 30, CCScale9Sprite::create("green_edit.png"));
//    kebox->setPosition(ccp(0,0));
//    kebox->setAnchorPoint(ccp(0,0));
//    mEditLayer->addChild(kebox);
//    kebox->attachWithIME();
    
    // SUCKER IDEA
//    CCEditBox* editbox = cocos2d::extension::CCEditBox::create(CCSizeMake(100, 30), CCScale9Sprite::create("green_edit.png"));
//    editbox->setPosition(ccp(mEditLayer->getPositionY(),mEditLayer->getPositionY()));
//    //editbox->setAnchorPoint(ccp(0,0));
//    editbox->setFontColor(ccWHITE);
//    editbox->setPlaceHolder("User:");
//    editbox->setMaxLength(8);
//    editbox->setReturnType(cocos2d::extension::kKeyboardReturnTypeDone);
//    editbox->setDelegate(this);
//    this->addChild(editbox);
    
    // test code
//    UserInfo ui;
//    std::vector<UserInfo> ss;
//    ss.push_back(ui);
//    tableview->onPageDataBack(ss);
}

// network message callback
void kTestDemoLayer::onPageDataBack(CCObject* pdata)
{
    kJsonProtocolBase jpb = *((kJsonProtocolBase*)pdata);
    const Json::Value arrayObj = jpb.getValue("p");
    std::vector<UserInfo> datas;
    for (unsigned int i = 0; i < arrayObj.size(); i++)
    {
        Json::Value jv = arrayObj[i];//["time"].asInt();
        std::string name = jv["name"].asString();
        UserInfo ui;
        ui._id = jv["id"].asInt();
        strcpy(ui.name, name.c_str());
        datas.push_back(ui);
    }
    for (unsigned int i = 0; i < 50; i++)
    {
        UserInfo ui;
        ui._id = 123+i;
        strcpy(ui.name, "hhhha");
        datas.push_back(ui);
    }
    
    CCLog("suck %d",tableview);
    tableview->onPageDataBack(datas);
}

kTestDemoLayer::~kTestDemoLayer()
{
    CC_SAFE_RELEASE(btnAdd);
    CC_SAFE_RELEASE(btnDel);
    CC_SAFE_RELEASE(btnQuery);
    CC_SAFE_RELEASE(btnModify);
    CC_SAFE_RELEASE(mEditLayer);
    CC_SAFE_RELEASE(mListLayer);
    kebox = NULL;
    // upload your listener here
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, STRING_FY(TEST_CMD_QUERY));
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, STRING_FY(TEST_CMD_OP_SUCCESS));
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, STRING_FY(TEST_CMD_OP_FAILED));
}

SEL_MenuHandler kTestDemoLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    return NULL;
}

SEL_CCControlHandler kTestDemoLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAddClicked", kTestDemoLayer::onAddClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onDelClicked", kTestDemoLayer::onDelClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onModifyClicked", kTestDemoLayer::onModifyClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onQueryClicked", kTestDemoLayer::onQueryClicked);
    return NULL;
}

bool kTestDemoLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnAdd", CCControlButton *, this->btnAdd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnDel", CCControlButton *, this->btnDel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnQuery", CCControlButton *, this->btnQuery);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnModify", CCControlButton *, this->btnModify);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEditLayer", CCLayerGradient *, this->mEditLayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mListLayer", CCLayer *, this->mListLayer);
    return false;
}

void kTestDemoLayer::onAddClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    // TOUCH detail if you needed
    switch(pCCControlEvent) {
        case CCControlEventTouchDown:
            CCLOG("Touch Down.");
            break;
        case CCControlEventTouchDragInside:
            CCLOG("Touch Drag Inside.");
            break;
        case CCControlEventTouchDragOutside:
            CCLOG("Touch Drag Outside.");
            break;
        case CCControlEventTouchDragEnter:
            CCLOG("Touch Drag Enter.");
            break;
        case CCControlEventTouchDragExit:
            CCLOG("Touch Drag Exit.");
            break;
        case CCControlEventTouchUpInside:
            CCLOG("Touch Up Inside.");
            break;
        case CCControlEventTouchUpOutside:
            CCLOG("Touch Up Outside.");
            break;
        case CCControlEventTouchCancel:
            CCLOG("Touch Cancel.");
            break;
        case CCControlEventValueChanged:
            CCLOG("Value Changed.");
            break;
        default:
            assert(false); // OH SHIT!
    }
    kJsonProtocolBase jpb;
    // query list
    jpb.addValue("cmd",Json::Value(Json::Int(TEST_CMD_REGISTER)));
    jpb.addValue("un",Json::Value(kebox->getContents()));// query for page 1
    jpb.addValue("sex", Json::Value(Json::Int(1)));
    jpb.sendToJavaServer(kBaseScene::ks->getSock());
}

void kTestDemoLayer::onDelClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    UserInfo* UI = tableview->getDataAtSelect();
    if(UI!=NULL)
    {
        kJsonProtocolBase jpb;
        // query list
        jpb.addValue("cmd",Json::Value(Json::Int(TEST_CMD_DELETE)));
        jpb.addValue("uid",Json::Value(Json::Int(UI->_id)));// query for page 1
        jpb.sendToJavaServer(kBaseScene::ks->getSock());
    }
}

void kTestDemoLayer::onModifyClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    UserInfo* UI = tableview->getDataAtSelect();
    if(UI!=NULL)
    {
        strcpy(UI->name,kebox->getContents());
        tableview->onReloaded();
        kJsonProtocolBase jpb;
        // query list
        jpb.addValue("cmd",Json::Value(Json::Int(TEST_CMD_MODIFY)));
        jpb.addValue("uid",Json::Value(Json::Int(UI->_id)));// query for page 1
        jpb.addValue("nun", Json::Value(kebox->getContents()));
        jpb.sendToJavaServer(kBaseScene::ks->getSock());
    }
}

void kTestDemoLayer::onQueryClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{}

void kTestDemoLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox){}
void kTestDemoLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox){}
void kTestDemoLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text){}
void kTestDemoLayer::editBoxReturn(cocos2d::extension::CCEditBox* editBox){}

