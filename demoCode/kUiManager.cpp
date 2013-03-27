//
//  kUiManager.cpp
//
//  Created by kael on 12/21/12.
//
//

#include "kUiManager.h"
#include "kUiLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

kUiManager::~kUiManager()
{
}

bool kUiManager::init()
{
    // init as blank layer
    haveActiveUi = false;
    return true;
}

// open a new view
void kUiManager::didSwitchUi(const char* uifilename,const char* nodename,CCNodeLoader* nodeloader)
{
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    if(nodename != NULL && nodeloader!=NULL)
    {
        ccNodeLoaderLibrary->registerCCNodeLoader(nodename, nodeloader);
    }
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader* ccbReader =
    new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    CCNode* node = ccbReader->readNodeGraphFromFile(uifilename, this);
    // do ui view pre work here
    kUiLayer* todostaff = reinterpret_cast<kUiLayer*>(node);
    todostaff->preInit();
    // create as a scene
//    CCScene * scene = CCScene::create();
//    if(node != NULL) {
//        scene->addChild(node);
//    }         
//    /* Push the new scene with a fancy transition. */
//    ccColor3B transitionColor;
//    transitionColor.r = 0;
//    transitionColor.g = 0;
//    transitionColor.b = 0;
//    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene, transitionColor));
    haveActiveUi = true;
    this->addChild(node);
}

// close a view
void kUiManager::didCloseUi()
{
    haveActiveUi = false;
    this->removeAllChildrenWithCleanup(true);
}
