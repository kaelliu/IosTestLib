//
//  kTestLayer.h
//  demoCode
//
//  Created by kael on 12/27/12.
//
//

#ifndef __demoCode__kTestLayer__
#define __demoCode__kTestLayer__

#include "cocos2d.h"
class kSprite;
class kTestLayer:public cocos2d::CCLayer
{
public:
    CREATE_FUNC(kTestLayer);
    // should have a configure file
    void loadFromConfiguration(const char* name);
    kSprite* role;
    void stopAllAction();
};


#endif /* defined(__demoCode__kTestLayer__) */
