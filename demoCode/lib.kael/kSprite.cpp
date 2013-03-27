//
//  kSprite.cpp
//  cctest01
//
//  Created by kael on 12/4/12.
//
//
#include "kSprite.h"
#include "kXmlParser.h"
#include "kAnimationInfo.h"
#include<map>
#include<string>
#include "strtk.hpp"
using namespace std;
using namespace cocos2d;
kSprite::kSprite()
{
    _sprite = CCSprite::create();
}

kSprite::~kSprite()
{
    deinit();
}

void kSprite::deinit()
{
    // clear animate frame cache
    
    // remove sprite frames from cache
    // but what if some one else is use this?
    //char plist[16];
    //sprintf(plist, "%s.plist",_identify); 
    //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plist);
    // delete
    CC_SAFE_DELETE(_sprite);
}

bool kSprite::init(const char* name)
{
    std::string fullpath = name;
    strtk::std_string::token_list_type token_list;
    strtk::split("/",fullpath,std::back_inserter(token_list));
    strtk::std_string::token_list_type::reverse_iterator itr = token_list.rbegin();
    // remove path
    strcpy(_identify, itr->first);
    char plist[16];
    char image[16];
    char anim[16];
    sprintf(plist, "%s.plist",name);
    sprintf(image, "%s.png",name);// png here
    sprintf(anim, "%s.anim",name);
    // file mode as rgba4444 or rgba8888 is depend on you
    // 1.init as sprite frame cache
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, image);
    // 2.find the animation info
    kXmlParser kxp ;
    kxp.initHXmlParse(anim);
    CCDictElement* element = NULL;
    CCDictionary * dict = kxp.mDic;
    CCDICT_FOREACH(dict, element)
    {
        if (element == NULL) {
            continue;
        }
        kAnimationInfo ka;
        strcpy(ka.name,element->getStrKey());
        const CCString* content = (CCString*)element->getObject();
        std::string substring = content->m_sString;
        // parse thing to struct 's data
        strtk::parse(substring, ",", ka.from, ka.to, ka.anchor_x, ka.anchor_y);
        /*
        short pos = 0;
        std::vector<std::string > m_VecTag;
        for(; (pos = substring.find(',')) != std::string::npos; )
        {
            int start = 0;
            std::string label = substring.substr(start, pos);
            m_VecTag.push_back(substring.substr(0));
            std::string tmp = substring.substr(pos+1);
            substring = tmp;
        }
        m_VecTag.push_back(substring.substr(0));
        if(m_VecTag.size()==4)
        {
            ka.from = atoi(m_VecTag[0].c_str());
            ka.to = atoi(m_VecTag[1].c_str());
            ka.anchor_x = atoi(m_VecTag[2].c_str());
            ka.anchor_y = atoi(m_VecTag[3].c_str());
        }
        */
        _animationInfos[ka.name] = ka;
    }
    
    // gather meta message
    char names[32];
    sprintf(names, "%s_01.png",_identify);
    // get frame from cache,we make frames at init
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(names);
    framew = frame->getOriginalSize().width;
    frameh = frame->getOriginalSize().height;
    return true;
}

void kSprite::setAnimationById(int index,float animatespeed)
{
    if(index >=0 && index < _animationInfos.size())
    {
        if(_sprite)
        {
            //_sprite->runAction(createAnimation(<#const char *name#>))
        }
    }
}

void kSprite::setAnimation(const char* name, float animatespeed)
{
    if(_sprite)
    {
        _sprite->runAction(createAnimation(name,animatespeed));
    }
}

CCAction* kSprite::createAnimation(const char *name, float animatespeed)
{ 
    if(_animationInfos.find(name) == _animationInfos.end())
        return NULL;
    kAnimationInfo ka = _animationInfos[name];
    // 0.set the anchor point
    _sprite->setAnchorPoint(ccp(float(ka.anchor_x)/100.0, float(ka.anchor_y)/100.0));
    // 1.get the animation cache
    CCAnimationCache* animationCache = CCAnimationCache::sharedAnimationCache();
    // 2.make the animation frame array as sprite frame
    CCArray* array = CCArray::createWithCapacity(ka.to - ka.from);
    char names[32];
    for(unsigned short i = ka.from;i <= ka.to;++i)
    {
        if(i<10)
            sprintf(names, "%s_0%d.png",_identify,i);
        else
            sprintf(names, "%s_%d.png",_identify,i);
        //        cout<<names<<endl;
        // get frame from cache,we make frames at init
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(names);
        array->addObject(frame);
    }
    // 3.create an animation and add to cache
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(array,animatespeed);
    animationCache->addAnimation(animation,name);
    // 4.clear array 's memory
    array->removeAllObjects();
    // 5.reset animation
    // p.s. different between CCAnimation and CCAnimate:
    // CCAnimation is a wrapper of frame container,it contains info which animate can use
    // CCAnimate is a subclass of CCAction,like move to action ,can take effect on sprite
    animation->setRestoreOriginalFrame(true);
    // 6.create animate and make the action interval
    CCAnimate* ani = CCAnimate::create(animation);
    CCActionInterval* interval = (CCActionInterval*)(CCSequence::create(ani,ani->copy()->autorelease(),NULL));
    // 7.return action for animation
    return CCRepeatForever::create(interval);
}