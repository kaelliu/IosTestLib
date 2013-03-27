//
//  kUiLayer.h
//
//  Created by kael on 12/21/12.
//
//

#ifndef __kUiLayer__
#define __kUiLayer__
#include "cocos2d.h"
#include "cocos-ext.h"
class kUiLayer:public cocos2d::CCLayer
             , public cocos2d::extension::CCBMemberVariableAssigner
             , public cocos2d::extension::CCBSelectorResolver
{
public:
    virtual ~kUiLayer(){}
    virtual void preInit()=0;
};

#endif /* defined(__kUiLayer__) */
