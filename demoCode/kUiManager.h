//
//  kUiManager.h
//
//  Created by kael on 12/21/12.
//
//

#ifndef __kUiManager__
#define __kUiManager__

#include "cocos2d.h"
#include "cocos-ext.h"
class kUiLayer;
class kUiManager:public cocos2d::CCLayer
{
public:
    ~kUiManager();
    virtual bool init();
    CREATE_FUNC(kUiManager);
    /*static*/ void didSwitchUi(const char* uifilename,const char* nodename,cocos2d::extension::CCNodeLoader* nodeloader);
    void didCloseUi();
    bool haveActiveUi;
protected:
//    cocos2d::CCNode* mainUiLayer;
};

#endif /* defined(__kUiManager__) */
