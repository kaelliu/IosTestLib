//
//  kMainUiLayer.cpp
//  Created by kael on 12/26/12.
//
//

#include "kMainUiLayer.h"
#include "kBaseScene.h"
#include "kUiManager.h"
#include "kTestDemoLayer.h"
#include "kGameView.h"
#include "kNormalMapScene.h"
#include "kSharedData.h"
#include "cocos-ext.h"
#include "kMainToolBarCell.h"
#include "kBaseScene.h"
#include "kSharedData.h"
#include "QiangHLayer.h"
//#include "kFunctions.h"
USING_NS_CC;
USING_NS_CC_EXT;
bool kMainUiLayer::init()
{
    _state = kCompact;
    return true;
}

void kMainUiLayer::loaded()
{
}

void kMainUiLayer::preInit()
{
    // add tool button depends on role's process
   
    // bag,hero,card..
    kMainToolBarCell* cell = new kMainToolBarCell(TOOLBARCELL_HERO);
    cell->setPosition(pToolbar_switcher->getParent()->getPosition());
    this->addChild(cell);
    horToolButtons.push_back(cell);
        
    kMainToolBarCell* cell2 = new kMainToolBarCell(TOOLBARCELL_HERO);
    cell2->setPosition(pToolbar_switcher->getParent()->getPosition());
    this->addChild(cell2);
    horToolButtons.push_back(cell2);
    
    kMainToolBarCell* cell3 = new kMainToolBarCell(TOOLBARCELL_HERO);
    cell3->setPosition(pToolbar_switcher->getParent()->getPosition());
    this->addChild(cell3);
    horToolButtons.push_back(cell3);
    
    kMainToolBarCell* cell4 = new kMainToolBarCell(TOOLBARCELL_HERO);
    cell4->setPosition(pToolbar_switcher->getParent()->getPosition());
    this->addChild(cell4);
    horToolButtons.push_back(cell4);
    
    if(kBaseScene::ksd->rd.lv > 15 && kBaseScene::ksd->rd.lv < 25)
    {
        // blablabla
    }
    
    // testing shadow for text part
    /*
    CCLabelTTF *pLabelTTF = CCLabelTTF::create( "test", "Verdana-BoldItalic", 12 );
    static const ccColor3B ccBlack = {0,0,0};
    pLabelTTF->setPosition(ccp(100,200));
    CCRenderTexture* pstroke = kFunctions::createStroke(pLabelTTF, 1,ccBlack);
    addChild( pstroke,100 );
    addChild( pLabelTTF,100 );
     */
}

kMainUiLayer::~kMainUiLayer()
{
    for(std::list<kMainToolBarCell*>::iterator it = horToolButtons.begin();it!=horToolButtons.end();++it)
    {
        (*it)->release();
    }
    //this->removeAllChildrenWithCleanup(true);
}
// for test

cocos2d::SEL_MenuHandler kMainUiLayer::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuSwitchCallback", kMainUiLayer::menuSwitchCallback);
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler kMainUiLayer::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "menuSwitchCallback", kMainUiLayer::menuSwitchCallback);
    return NULL;
}

bool kMainUiLayer::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "pToolbar_switcher", CCControlButton *, this->pToolbar_switcher);
    return true;
}

void kMainUiLayer::menuSwitchCallback(CCObject* pSender ,cocos2d::extension::CCControlEvent pCCControlEvent)
{
    if(kBaseScene::kuimgr->haveActiveUi)
    {
        kBaseScene::kuimgr->didCloseUi();
    }
    else
    {
        float duration = 0.36f;
        if(_state == kCompact)
        {
            float duration2 = 0.16f * horToolButtons.size();
            pToolbar_switcher->runAction(CCRotateTo::create(duration, 45));
            unsigned char spacebetween=2;
            int totalwidth=0;
            
            for(std::list<kMainToolBarCell*>::iterator it = horToolButtons.begin();
                it!=horToolButtons.end();++it)
            {
                CCPoint pt;
                pt.x = spacebetween+(*it)->getW();
                totalwidth += pt.x;
                pt.x = (*it)->getPositionX() - totalwidth;
                pt.y = pToolbar_switcher->getParent()->getPosition().y;
                (*it)->onExpand(pt, duration2);
            }
            _state = kExpand;
        }
        else if(_state == kExpand)
        {
            CCPoint pt = pToolbar_switcher->getParent()->getPosition();
            pToolbar_switcher->runAction(CCRotateTo::create(duration, 0));
            for(std::list<kMainToolBarCell*>::iterator it = horToolButtons.begin();
                it!=horToolButtons.end();++it)
            {
                
                (*it)->onCompact(pt, duration);
            }
            _state = kCompact;
        }
    }
}

void kMainUiLayer::onToolBarClicked(int _id)
{
    switch (_id) {
        case TOOLBARCELL_HERO:
        {
//            // for demo test,change to other scene
//            if(kBaseScene::ksd->rd.mid == 1)
//                kBaseScene::ksd->rd.mid = 2;
//            else
//            {
//                kBaseScene::ksd->rd.mid = 1;
//            }
//            kBaseScene::ksd->rd.x = 0;
//            kBaseScene::ksd->rd.y = 0;
//            kSceneInterface* normapScene = kNormalMapScene::create();
//            char mapid[16];
//            sprintf(mapid,"map/%d", kBaseScene::ksd->rd.mid);
//            kBaseScene::gameview->changeScene(normapScene,mapid);
             kBaseScene::kuimgr->didSwitchUi( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("uiResource/TestDemos.ccbi"),   "kTestDemoLayer",kTestDemoLayerLoader::loader());
        }
            
            break;
        case TOOLBARCELL_BAG:
            {
                // for demo test,open kTestDemoLayer
                kBaseScene::kuimgr->didSwitchUi( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("uiResource/TestDemos.ccbi"),   "kTestDemoLayer",kTestDemoLayerLoader::loader());
            }
            break;
        default:
            break;
    }
}

bool kMainUiLayerHolder::init()
{
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("kMainUiLayer", kMainUiLayerLoader::loader());
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader* ccbReader =
    new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    CCNode* node = ccbReader->readNodeGraphFromFile(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("uiResource/mainUi.ccbi"));
    kMainUiLayer* m = (kMainUiLayer*)node;
    m->preInit();
    this->addChild(node);
    return true;
}