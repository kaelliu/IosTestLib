//
//  kEllipseLayer.h
//
//  Created by kael on 12/5/12.
//
//

#ifndef __kEllipseLayer__
#define __kEllipseLayer__
#include "cocos2d.h"

class kEllipseLayer:public cocos2d::CCLayer
{
public:
    kEllipseLayer();
    virtual void draw();
    CREATE_FUNC(kEllipseLayer);
    virtual bool init();
};

#endif 
