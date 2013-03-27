//
//  kGameView.cpp
//  demoCode
//
//  Created by kael on 12/24/12.
//
//

#include "kGameView.h"
#include "kSceneInterface.h"
#include "kMainUiLayer.h"
bool kGameView::init()
{
    curScene = NULL;
    // main ui view will always keep there,so it is init here
    mainui = kMainUiLayerHolder::create();
    this->addChild(mainui,1);// this layer is upper than map view
    return true;
}

kGameView::~kGameView()
{
    CC_SAFE_RELEASE(mainui);
    CC_SAFE_DELETE(curScene);
}

void kGameView::onUpdate()
{
    if (curScene) {
        curScene->onUpdate();
    }
}

void kGameView::changeScene(kSceneInterface* newScene,void* param)
{
    if (NULL != curScene) {
        curScene->onUnloadScene();
        curScene->removeFromParentAndCleanup(true);
    }
    newScene->onLoadScene((char*)param);
    this->addChild(newScene,0);// game map,player is downest layer
    curScene = newScene;
}
