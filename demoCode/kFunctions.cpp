//
//  kFunctions.cpp
//
//  Created by kael on 1/9/13.
//
//

#include "kFunctions.h"
#include"cocos2d.h"
using namespace cocos2d;

CCRenderTexture* kFunctions::createStroke(CCLabelTTF* label, float size ,ccColor3B cor)
{
    float RealSize = size;
    CCRenderTexture* rt = CCRenderTexture::create(label->getTexture()->getContentSize().width + RealSize*2, label->getTexture()->getContentSize().height + RealSize*2);
    CCPoint originalPos = label->getPosition();
    ccColor3B originalColor = label->getColor();
    bool originalVisibility = label->isVisible();
    label->setColor(cor);
    label->setVisible(true);
    ccBlendFunc originalBlend = label->getBlendFunc();
    ccBlendFunc tBlendFunc = {GL_SRC_ALPHA, GL_ONE };
    label->setBlendFunc(tBlendFunc);
    CCPoint bottomLeft = ccp(label->getTexture()->getContentSize().width * label->getAnchorPoint().x + RealSize, label->getTexture()->getContentSize().height * label->getAnchorPoint().y + RealSize);
    CCPoint positionOffset = ccp(label->getTexture()->getContentSize().width * label->getAnchorPoint().x - label->getTexture()->getContentSize().width/2, label->getTexture()->getContentSize().height * label->getAnchorPoint().y - label->getTexture()->getContentSize().height/2);
    CCPoint position = ccpSub(originalPos, positionOffset);
    
    rt->begin();
    for (int i=0; i<360; i+=30)
    {
        label->setPosition(ccp(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*RealSize, bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*RealSize));
        label->visit();
    }
    rt->end();
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    label->setVisible(originalVisibility);
    rt->setPosition(position);
    return rt;
}

long getNowInMs()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}