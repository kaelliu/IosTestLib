//
//  kTestDemoLayer.h
//  demoCode
//
//  Created by kael on 12/21/12.
//
//

#ifndef __demoCode__kTestDemoLayer__
#define __demoCode__kTestDemoLayer__

#include "kUiLayer.h"
class kTestDemoTableView;
class kCommonEditbox;
class kTestDemoLayer:public kUiLayer,cocos2d::extension::CCEditBoxDelegate
{
public:
    // create marco for layerloader
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(kTestDemoLayer, create);
    kTestDemoLayer();
    // virtual function to implete here
    virtual void preInit();
    virtual ~kTestDemoLayer();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    // your control function here
    void onAddClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onDelClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onModifyClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onQueryClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    // editbox
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    void onPageDataBack(cocos2d::CCObject* pdata);
    void onOperateResult(cocos2d::CCObject* pdata);
private:
    // your relate member varible here
    cocos2d::extension::CCControlButton* btnAdd;
    cocos2d::extension::CCControlButton* btnDel;
    cocos2d::extension::CCControlButton* btnQuery;
    cocos2d::extension::CCControlButton* btnModify;
    
    cocos2d::CCLayerGradient* mEditLayer;
    cocos2d::CCLayer* mListLayer;
    kCommonEditbox* kebox;
    kTestDemoTableView* tableview;
    void initExtraUi();
};

class kTestDemoLayerLoader:public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(kTestDemoLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(kTestDemoLayer);
};

#endif /* defined(__demoCode__kTestDemoLayer__) */
