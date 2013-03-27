//
//  kTestLayer.cpp
//  demoCode
//
//  Created by kael on 12/27/12.
//
//

#include "kTestLayer.h"
#include "kSprite.h"
using namespace cocos2d;
void kTestLayer::loadFromConfiguration(const char *name)
{
    CCSprite* shadow = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yy.png"));
    this->addChild(shadow);
    role = new kSprite();
    role->init(name);
    role->setAnimation("idle");
    
    this->addChild(role->getSprite());
    float px = 0.07 * 73;
    float py = (-68) * 0.23;
    shadow->setPosition(ccp(px,py));
}
void kTestLayer::stopAllAction()
{
    role->getSprite()->stopAllActions();
    this->stopAllActions();
}