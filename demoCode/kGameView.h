//
//  kGameView.h
//  demoCode
//
//  Created by kael on 12/24/12.
//
//

#ifndef __kGameView__
#define __kGameView__

#include "cocos2d.h"
#include "kSingleton.h"
class kSceneInterface;
class kGameView:public cocos2d::CCLayer
{
public:
//    kGameView();
    CREATE_FUNC(kGameView);
    virtual bool init();
    ~kGameView();
    void onUpdate();
    kSceneInterface* getCurScene(){return curScene;}
    void changeScene(kSceneInterface* newScene,void* param=NULL);
protected:
    // scene holder,implete each scene's delegate,show function,data model
    kSceneInterface* curScene;// game scene,fb scene,activty scene
    // should can mdify z order when scene changed,this ui layer will always be holded
    cocos2d::CCLayer* mainui; //  the game main ui
};

#endif /* defined(__kGameView__) */
