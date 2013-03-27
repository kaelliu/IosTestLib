//
//  kFunctions.h
//
//  Created by kael on 1/9/13.
//
//

#ifndef __kFunctions__
#define __kFunctions__
#include "cocos2d.h"
using namespace cocos2d;
class kFunctions
{
public:
    static CCRenderTexture* createStroke(CCLabelTTF* label, float size ,ccColor3B cor);
};
#ifdef __cplusplus
extern "C"
{
#endif
long getNowInMs();
#ifdef __cplusplus
}
#endif
#endif /* defined(__kFunctions__) */
