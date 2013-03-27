//
//  kSceneInterface.h
//
//  Created by kael on 12/21/12.
//
//

#ifndef _kSceneInterface_h
#define _kSceneInterface_h
#include"cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include<vector>
#include<map>
using namespace cocos2d;
class kSceneDelegate
{
public:
    virtual ~kSceneInterface()=0;
    virtual onLoadScene()=0;
    virtual onUnLoadScene()=0;
    virtual onTouchesEvent() = 0;
    //virtual onGesture()=0;
    
};

class kSharedRoleData
{
public:
    // role struct
    // hero list struct
    // bag dara struct...
};

// appdelegate->did load first scene,kBaseScene
class kClientSocket;// socket operation
class kGameObject;
class kGameObjectDelegate;
class kPlayerSpriteDelegate;
class kPlayerSprite;
class kNpcSprite;
class kMonsterSprite;
class kTrassionSprite;
// game scene:normal map,fb map,manzu map,implete scene delegate
class kGameScene:public cocos2d::CCLayer
{
public:
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    // socket event dispatched by kClientSocket
    //virtual void onSocketData(void* data)=0;
    void init();
    std::map<int,std::map<int,kGameObject>>& getMapObjects(){return mapObjects;}
protected:
    // type:map(id:gameObject)
    std::map<int,std::map<int,kGameObject>> mapObjects;
    // touch,common event
    kSceneDelegate* sceneLogic;
//    kGameObjectDelegate* sceneObjectLogic;
};

class kNormapSceneDelegate:public kSceneDelegate
{
public:
    kGameScene* view;
};

class kFbmapSceneDelegate:public kSceneDelegate
{};
class kManZuSceneDelegate:public kSceneDelegate
{};

class kSceneLoader
{};

class kSceneModelDelegate
{
public:
    virtual ~kSceneModelDelegate()=0;
};

class kUiLayerDelegate
{
public:
    virtual ~kUiLayerDelegate()=0;
    // loading bar show
    virtual void onPreload();
    // load and register events
    void load(const char* filename);
    void didunload();
    // touch events
    // ...
};
//
//class kUiLayer:public cocos2d::CCLayer
//{
//public:
//    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
//    void loadUi(const char* filename){kUiLayerDelegate->load(filename);}
//protected:
//    
//    kUiLayerDelegate* uilogic;
//};
//
//class kTestDemoUiLayerDelegate::public kUiLayerDelegate
//{
//    
//}

class kUiLayer:public cocos2d::CCLayer
             , public cocos2d::extension::CCBMemberVariableAssigner
             , public cocos2d::extension::CCBSelectorResolver
{
public:
    //virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual ~kUiLayer()=0;
};

class kTestDemoUiLayer:public kUiLayer
{
public:
    ~kTestDemoUiLayer();
    // touch event
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    //
    void arrangeUi();
};

class kUiManager:public CCLayer   // did load/unload ui
{
public:
    virtual bool init();
    CREATE_FUNC(kUiManager);
    static void didSwitchUi(const char* uiconfig);
protected:
    kUiLayer* curLayer;
};
//...
cocos2d::CCNotificationCenter;

// black scene with infite size
class kBaseScene
{
public:
    static kSharedRoleData* globalData;
protected:
    kClientSocket* ks;
    kGameScene* scene;
    kUiManager* uimgr;
};
#endif
