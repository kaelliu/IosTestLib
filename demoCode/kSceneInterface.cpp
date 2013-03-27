#include "kSceneInterface.h"
USING_NS_CC;
cocos2d::CCPoint kSceneInterface::centerView(const cocos2d::CCPoint& rolePostion,
                                             cocos2d::CCLayer* targetLayer)
{
    CCSize s = cocos2d::CCDirector::sharedDirector()->getWinSize();
    int w = targetLayer->getContentSize().width;//()->getPixelsWide();
    int h = targetLayer->getContentSize().height;//getTexture()->getPixelsHigh();
    CCPoint centerView = ccp(s.width/2,s.height/2);
    
    CCPoint targetPoint = ccpSub(centerView,rolePostion);
    if(targetPoint.x + w / 2 < s.width)
        targetPoint.x = s.width - w / 2;
    if(targetPoint.x - w / 2 > 0)
        targetPoint.x = w / 2;
    if(targetPoint.y + h / 2 < s.height)
        targetPoint.y = s.height - h / 2;
    if(targetPoint.y - h /2 > 0)
        targetPoint.y = h / 2;
    
    return targetPoint;
}

CCPoint kSceneInterface::pointToLayerSystem(const cocos2d::CCPoint& point,cocos2d::CCLayer* layer)
{
    CCPoint targetPoint;
    CCPoint anchorPoint = layer->getAnchorPoint();
    int w = layer->getContentSize().width;
    int h = layer->getContentSize().height;
    int systemOriginx = -( w * anchorPoint.x );
    int systemOriginy = ( h * anchorPoint.y );
    
    targetPoint.x = systemOriginx + point.x;
    targetPoint.y = systemOriginy - point.y;
    return targetPoint;
}

CCPoint kSceneInterface::layerSystemToASSystem(const cocos2d::CCPoint& point,cocos2d::CCLayer* layer)
{
    CCPoint targetPoint;
    CCPoint anchorPoint = layer->getAnchorPoint();
    int w = layer->getContentSize().width;
    int h = layer->getContentSize().height;
    int systemOriginx = -( w * anchorPoint.x );
    int systemOriginy = ( h * anchorPoint.y );
    
    targetPoint.x = point.x - systemOriginx;
    targetPoint.y = systemOriginy - point.y;
    return targetPoint;
}

cocos2d::CCPoint kSceneInterface::pointToLayerSystem(const cocos2d::CCPoint& point,int scrollWidth,int scrollHeight,const CCPoint& anchorPoint)
{
    CCPoint targetPoint;
    int systemOriginx = -( scrollWidth * anchorPoint.x );
    int systemOriginy = ( scrollHeight * anchorPoint.y );
    targetPoint.x = systemOriginx + point.x;
    targetPoint.y = systemOriginy - point.y;
    return targetPoint;
}

cocos2d::CCPoint kSceneInterface::layerSystemToASSystem(const cocos2d::CCPoint& point,int scrollWidth,int scrollHeight,const CCPoint& anchorPoint)
{
    CCPoint targetPoint;
    int systemOriginx = -( scrollWidth * anchorPoint.x );
    int systemOriginy = ( scrollHeight * anchorPoint.y );
    
    targetPoint.x = point.x - systemOriginx;
    targetPoint.y = systemOriginy - point.y;
    return targetPoint;
}