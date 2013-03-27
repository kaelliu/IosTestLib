//
//  kNormalMapScene.h
//
//  Created by kael on 12/26/12.
//
//

#ifndef __kNormalMapScene__
#define __kNormalMapScene__
#include "kSceneInterface.h"
#include <map>
#include <string>
class kSprite;
// for temp
struct kPlayerModel
{
    int      rid;
    kSprite* sp;
    cocos2d::CCLayer* name;
    cocos2d::CCLayer* shadow;
    
};
class kAction;
class kTestLayer;
class kSpriteContainer;
struct kMapStruct;
class kMapXmlParserDelegate;
class kNormalMapScene:public kSceneInterface
{
public:
    CREATE_FUNC(kNormalMapScene);
    virtual bool init();
    ~kNormalMapScene();
    void onLoadScene(const char* filename=NULL);
    void onUnloadScene();
    void onBroadcast(void* data);
    void onUpdate();
    // CCLayer Touch
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void onRunOver();
    virtual void initAstarAlgorithm();
protected:
    void onRunOneStepAutomatic();
    void onRunAllOver();
    // data placeholder
    // sprite for view show
    std::map<int,kSpriteContainer*>      other_players;
    std::map<int,kSpriteContainer*>      npcs;
    std::map<int,kSpriteContainer*>      trans;
    kTestLayer*                          player;
    cocos2d::CCSprite*                   mapbg;
    // common datastruct for map use
    kMapStruct*                          map_datastruct;
    kMapXmlParserDelegate*               map_parser;
    void onRegisterListeners();
    void onUnRegisterListeners();
    kAction* curAutomaticAction;
};

#endif /* defined(__kNormalMapScene__) */
