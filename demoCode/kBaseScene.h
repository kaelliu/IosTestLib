//
//  kBaseScene.h
//  demoCode
//
//  Created by kael on 12/21/12.
//
//

#ifndef __demoCode__kBaseScene__
#define __demoCode__kBaseScene__

#include "cocos2d.h"
//class CCSprite;
#define GAMELAYER_Z 1
#define COMMON_UI_LAYER_Z 2
#define CLOSEABLE_LAYER_Z 3
class kClientSocket;
class kUiManager;
class kGameView;
struct kSharedData;
class kBaseScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(kBaseScene);
    ~kBaseScene();
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void onupdate();
    //virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);
    //virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
   
    static kClientSocket* ks;
    static kSharedData* ksd;
    static kGameView* gameview;
    static kUiManager* kuimgr;
private:
    void exitGame();
};

#endif /* defined(__demoCode__kBaseScene__) */
