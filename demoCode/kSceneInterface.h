//
//  kSceneInterface.h
//
//  Created by kael on 12/26/12.
//
//

#ifndef _kSceneInterface_h
#define _kSceneInterface_h

#include"cocos2d.h"
class kAstarAlgorithm;
class kSceneInterface:public cocos2d::CCLayer
{
public:
    virtual ~kSceneInterface(){}
    virtual void onLoadScene(const char* filename=NULL)=0;
    virtual void onUnloadScene()=0;
    // also need implete the touch event
    // the SERVER broadcast message if needed
    virtual void onBroadcast(void* data){}
    virtual void onUpdate()=0;
    // each scene keep each model for view' s showing
    // protected:
    //    kSceneDataModel* bla
    // center screen with role,targetlayer will follow postion when position changed
    cocos2d::CCPoint centerView(const cocos2d::CCPoint& rolePostion,cocos2d::CCLayer* targetLayer);
    // get coord system transformation
    // for example: a map backpicture,with anchor(0.5,0.5),1080*960 size
    // in this system,the Coordinate origin is -540,480,your point is 259,114,to this system is
    // from -281,366
    static cocos2d::CCPoint pointToLayerSystem(const cocos2d::CCPoint& point,cocos2d::CCLayer* layer);
    static cocos2d::CCPoint layerSystemToASSystem(const cocos2d::CCPoint& point,cocos2d::CCLayer* layer);
    
    static cocos2d::CCPoint pointToLayerSystem(const cocos2d::CCPoint& point,int scrollWidth,int scrollHeight,const cocos2d::CCPoint& anchorPoint=cocos2d::CCPoint(0.5,0.5));
    static cocos2d::CCPoint layerSystemToASSystem(const cocos2d::CCPoint& point,int scrollWidth,int scrollHeight,const cocos2d::CCPoint& anchorPoint=cocos2d::CCPoint(0.5,0.5));
    // astar algorithm helper,you should init this at scene begin
    // if no rewrite this,kastar is null and no use path finding method,such as the activity scene
    // will make it's own way of role walk
    virtual void initAstarAlgorithm(){kastar = NULL;}
    // about anchor point and parent/child node
    // anchor point is what point in child you want to put your node in your parent node,
    // such as a picture with(100,100) as size,anchor point is 0.5,0.5,you put the child node
    // in the position at parent node is (100,100),the point 50,50 in child will at parent's 100,100
    // each layer is start from left-down conner as origin point(0,0).
protected:
    unsigned char _tag;
    kAstarAlgorithm* kastar;
};

#endif
