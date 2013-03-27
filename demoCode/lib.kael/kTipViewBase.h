//
//  kTipViewBase.h
//
//  Created by kael on 1/15/13.
//
//

#ifndef __kTipViewBase__
#define __kTipViewBase__
#include "cocos2d.h"
using namespace cocos2d;

#define TIPVIEW_BAGITEM 1
#define TIPVIEW_BAGCARD 2

class kTipViewBase:public CCLayer
{
public:
    // tipview type
    short _type;
    virtual void initWithData(void* data,int len=0)=0;
    virtual ~kTipViewBase(){}
};
#endif /* defined(__kTipViewBase__) */
