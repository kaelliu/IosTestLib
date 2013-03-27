//
//  kBaseScene.cpp
//  demoCode
//
//  Created by kael on 12/21/12.
//
//

#include "kBaseScene.h"
#include "kClientSocket.h"
#include "kUiManager.h"
#include "kTestDemoLayer.h"
#include "kSharedData.h"
#include "kGameView.h"
#include "kNormalMapScene.h"

using namespace std;
using namespace cocos2d;
kClientSocket* kBaseScene::ks = NULL;
kSharedData* kBaseScene::ksd = NULL;
kGameView* kBaseScene::gameview = NULL;
kUiManager* kBaseScene::kuimgr = NULL;
CCScene* kBaseScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    kBaseScene *layer = kBaseScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    //    CCDirector::sharedDirector();
    // return the scene
    return scene;
}

kBaseScene::~kBaseScene()
{
    // use auto release ,just put null here,or may be not need at all
    // if you do not need auto release,every thing from ccobject 's refcount is 1 when it is be created

    // we do ourself here delete it for avoid memory leak
    CC_SAFE_DELETE(ks);
    CC_SAFE_DELETE(ksd);
}

void kBaseScene::onupdate()
{
    if (gameview) {
        gameview->onUpdate();
    }
    if(ks)
    {
        ks->onUpdate();
    }
}

void kBaseScene::registerWithTouchDispatcher()
{
    // true means no bubble up
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority+1,true);
}

// on "init" you need to initialize your instance
bool kBaseScene::init()
{
    // 0.alloc memory for shared data
    ksd = new kSharedData;
    // common use resource load into memory
    CCTexture2D *pTextureShadow = CCTextureCache::sharedTextureCache()->addImage("yy.png");
    CCSpriteFrame* shadowFrame = CCSpriteFrame::createWithTexture(pTextureShadow, CCRectMake(0, 0, pTextureShadow->getPixelsWide(), pTextureShadow->getPixelsHigh()));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(shadowFrame, "yy.png");
    // test fake data
    // you should init the shared data after login scene
    ksd->rd.rid = 1;
    ksd->rd.mid = 1;
    ksd->rd.x = 0;
    ksd->rd.y = 0;
    ksd->rd.lv = 18;
    // test fake data over
    // 1.make the network connection
    int connectresult=0;
    ks = new kClientSocket;
    connectresult = ks->start("127.0.0.1", 8810);
    
    if(connectresult == SOCKET_ERROR)
    {
        // to information and exit
        CCMessageBox("wrong", "Error connect to net,check your configuration plz");
        delete ks;
        ks = NULL;
    }
    else
    {
        
    }
    // 2.run base ui manager
    kuimgr = kUiManager::create();
    kuimgr->setTag(CLOSEABLE_LAYER_Z);
    // frame view add
    this->addChild(kuimgr,CLOSEABLE_LAYER_Z);
    
    // 3.net work msg receive loop
    this->schedule(schedule_selector(kBaseScene::onupdate),0.04);
    
    // 4.create the gameview base layer
    gameview = kGameView::create();
    this->addChild(gameview,GAMELAYER_Z);
    // should start login view here,and from login view call relate initview function to
    // load view
    // here.run base scene from role data for test
    kSceneInterface* normapScene = kNormalMapScene::create();
    char mapid[16];
    sprintf(mapid,"map/%d", ksd->rd.mid);
    gameview->changeScene(normapScene,mapid);
    return true;
}


bool kBaseScene::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    return true;
}

void kBaseScene::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    
}

void kBaseScene::exitGame()
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}