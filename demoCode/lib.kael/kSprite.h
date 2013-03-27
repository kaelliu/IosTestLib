//
//  kSprite.h
//
//  Created by kael on 12/4/12.
//
//

#ifndef __kSprite__
#define __kSprite__
#include "cocos2d.h"
struct kAnimationInfo;
// kSprite is a wrapper of cocos2d-x 's sprite and implete the sprite animation
class kSprite
{
public:
    kSprite();
    virtual ~kSprite();
    // init with picture name without postfix
    bool init(const char* name);
    // clean work
    void deinit();
    // change animation
    void setAnimation(const char* name, float animatespeed=0.1f);
    void setAnimationById(int index,float animatespeed=0.1f);
    // get the sprite for rendering
    cocos2d::CCSprite* getSprite()const{return _sprite;}
    unsigned short getFrameW()const{return framew;}
    unsigned short getFrameH()const{return frameh;}
protected:
    // create animation when animation not exist
    cocos2d::CCAction* createAnimation(const char* name,float speed=0.1f);
    cocos2d::CCSprite* _sprite;
    std::map<std::string, kAnimationInfo>  _animationInfos;
    // file name in short,such as p1000001.png for p1000001,8 is enough
    char _identify[8];
    unsigned short framew;
    unsigned short frameh;
};
#endif /* defined(__kSprite__) */
