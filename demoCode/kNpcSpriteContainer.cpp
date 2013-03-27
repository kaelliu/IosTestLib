//
//  kNpcSpriteContainer.cpp
//
//  Created by kael on 1/7/13.
//
//

#include "kNpcSpriteContainer.h"
#include "cocos2d.h"
#include "kSprite.h"
using namespace cocos2d;
bool kNpcSpriteContainer::init()
{
    npcid = 0;
    _type = SPRITE_CONTAINER_TYPE_NPC;
    haveShadow = true;
    return true;
}

kNpcSpriteContainer::~kNpcSpriteContainer()
{
    this->removeAllChildrenWithCleanup(true);
//    for(std::map<std::string, kSprite*>::iterator it = parts.begin();it != parts.end();
//        ++it)
//    {
//        CC_SAFE_DELETE(it->second);
//    }
//    this->removeFromParentAndCleanup(true);
}

void kNpcSpriteContainer::loadFromConfiguration(const char* name,void* extraparam)
{
    kSprite* role = new kSprite();
    role->init(name);
    role->setAnimation("idle");
    
    this->addChild(role->getSprite(),1);
    parts[name] = role;
    if(haveShadow)
    {
        CCSprite* shadow = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yy.png"));
        this->addChild(shadow,0);
        float px = 0.07 * role->getFrameW();
        float py = (-role->getFrameH()) * 0.23;
        shadow->setPosition(ccp(px,py));
    }
    // name
    if(extraparam != NULL)
    {
        kNpcStruct* data = (kNpcStruct*)extraparam;
        npcid = data->id;
        this->setPosition(data->x, data->y);
        // use icon for instead
        CCLabelTTF* npcname = CCLabelTTF::create(data->icon.c_str(), "arial", 13);
//        CCLabelTTF* npcname = CCLabelTTF::create(data->name.c_str(), "arial", 13);
        npcname->setPositionY( -role->getFrameH() / 2 + npcname->getContentSize().height);
        this->addChild(npcname,2);
    }
}

bool kNpcSpriteContainer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void kNpcSpriteContainer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}