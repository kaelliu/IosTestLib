//
//  kMainUiLayer.h
//
//  Created by kael on 12/26/12.
//
//

#ifndef __kMainUiLayer__
#define __kMainUiLayer__

#include "kUiLayer.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <list>
USING_NS_CC;
USING_NS_CC_EXT;
class kMainToolBarCell;
enum menuState
{
    kExpand=1,
    kCompact=2
};
class kMainUiLayer:public kUiLayer
{
public:
    // create marco for layerloader
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(kMainUiLayer, create);
//    CREATE_FUNC(kMainUiLayer);
    virtual bool init();
    void preInit();
    virtual ~kMainUiLayer();
    void loaded();
    // for test
//    void menuSwitchCallback(CCObject* pSender);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void menuSwitchCallback(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void onToolBarClicked(int _id);
private:
    menuState _state;
    CCControlButton* pToolbar_switcher;
    std::list<kMainToolBarCell*> horToolButtons;
    std::list<kMainToolBarCell*> verToolButtons;
};

class kMainUiLayerLoader:public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(kMainUiLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(kMainUiLayer);
};

class kMainUiLayerHolder:public CCLayer
{
public:
    CREATE_FUNC(kMainUiLayerHolder);
    virtual bool init();
};
#endif /* defined(__kMainUiLayer__) */
