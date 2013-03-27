//
//  kSpriteContainer.h
//  Created by kael on 12/6/12.
//
//

#ifndef __kSpriteContainer__
#define __kSpriteContainer__

#include "cocos2d.h"
#include <string>
#include <map>

#define SPRITE_CONTAINER_TYPE_PLAYER  1
#define SPRITE_CONTAINER_TYPE_NPC     2
#define SPRITE_CONTAINER_TYPE_MONSTER 3
#define SPRITE_CONTAINER_TYPE_TRANS   4

class kSprite;
class kSpriteContainer:public cocos2d::CCLayer
{
public:
//    CREATE_FUNC(kSpriteContainer);
    virtual ~kSpriteContainer(){}
    // should have a configure file
    // shadow is common use,should init at start
    virtual void loadFromConfiguration(const char* name,void* extraparam=NULL)=0;
protected:
    // should have a map of sprite name and relative sprite
    std::map<std::string,kSprite*> parts;
    unsigned short _type;
};

#endif /* defined(__kSpriteContainer__) */
