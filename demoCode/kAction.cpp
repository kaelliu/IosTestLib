#include "kAction.h"
#include "kAstar.h"
#include "kBaseScene.h"
#include "kSharedData.h"
#include "kSceneInterface.h"
#include "kTestLayer.h"
#include "kSprite.h"
// pos is position in maplayer's position
cocos2d::CCPoint transWorldTo45degree(const cocos2d::CCPoint& pos,int ts = 30)
{
    int loc_3 = 0;
    int loc_4 = 0;
    float loc_5 = 0;
    float loc_6 = 0;
    int loc_7 = 0;
    int loc_8 = 0;
    float loc_9 = 0.5f;// constant ratio
    float loc_10 = ts / 2;
    loc_3 = int(pos.x/(ts*2)) * 2 + 1;
    loc_4 = pos.y / ts;
    loc_5 = (float)(int(pos.x) % (ts*2)) - (float)((ts*2)/2);
    loc_6 = (float)(int(pos.y) / ts) - (float)(ts/2);
    loc_9 = (loc_6!=0 && loc_5/loc_6>0)?(-loc_9):(loc_9);
    loc_10 = loc_6>0?(loc_10):(-loc_10);
    if(fabs(loc_6) > fabs(loc_9 * loc_5 + loc_10))
    {
        loc_7 = loc_5 / fabs(loc_5);
        if(loc_6 > 0)
        {
            loc_8 = 1;
        }
    }
    return cocos2d::CCPoint(loc_4 + loc_8,loc_3 + loc_7);// row,column
}

// pos is the index of each grid
cocos2d::CCPoint trans45DegreeToWorld(const cocos2d::CCPoint& pos,int tileW = 60,int tileH = 30)
{
    return cocos2d::CCPoint(pos.x * tileW / 2,(2 * pos.y +int(pos.x) % 2) * tileH / 2);
}

kAction* kPathFindBehaviour::onTouchEnd(kAstarAlgorithm* algo,const cocos2d::CCPoint& start,
                           const cocos2d::CCPoint& target,cocos2d::CCLayer* parentLayer)
{
    kAction* ka = NULL;
    cocos2d::CCPoint startindex = transWorldTo45degree(start);
    cocos2d::CCPoint endindex = transWorldTo45degree(target);
    // do 45 degree swap
//    if (algo->type == TYPE_45DEGREE) {
//        // x for row,y for column
//        if((int)startindex.x % 2 == 0)// even
//            startindex.x = (int)startindex.x * 2;
//        else// odd
//            startindex.x = (int)startindex.x * 2 + 1;
//        if((int)endindex.x % 2 == 0)// even
//            endindex.x = (int)endindex.x * 2 ;
//        else// odd
//            endindex.x = (int)endindex.x * 2 + 1;
//        startindex.y = (int)startindex.y / 2;
//        endindex.y = (int)endindex.y / 2;
//    }
    kAstarNode* start_n = algo->getNode(startindex.y,startindex.x);
    kAstarNode* end_n = algo->getNode(endindex.y,endindex.x);
    if(end_n->b == 1) // is be blocked
    {
        return NULL;
    }
    // path finding
    algo->AStarSearchRun(start_n, end_n);
   // algo->TravelOutputResult();
    // make path action
    kAstarNode* endNode = algo->getCurrNode();
    if(NULL == endNode) // is be blocked
    {
        return NULL;
    }
    kAstarNode* p = endNode;
    kAMoveTo* move;
	while( p && p != start_n)
	{
        move = new kAMoveTo;
        move->working = false;
        cocos2d::CCPoint tar = kSceneInterface::pointToLayerSystem(trans45DegreeToWorld(cocos2d::CCPoint(p->column_index,p->row_index)),parentLayer);
        move->x = tar.x;
        move->y = tar.y;
        kBaseScene::ksd->automatic_actions.push_front(move);
		p = p->parent;
	}
    ka = move;
    return ka;
}
int kPathFindBehaviour::towards = 0;
void kPathFindBehaviour::onBeginToGo(cocos2d::CCLayer* target,
                        const cocos2d::CCPoint& end,cocos2d::CCLayer* parentLayer,cocos2d::CCCallFunc* overCallback,int layerscrollwidth,int layerscrollheight)
{
    kTestLayer* player = (kTestLayer*)target;
    
    float offX = end.x - player->getPosition().x;
    float offY = end.y - player->getPosition().y;
    // suppose base on (0,0) in local ,angle with vector(1,0),A dot B = |A|*|B|*cos(angle with A and B)
    float sqrtOff = sqrt(offX * offX + offY * offY);
    offX = offX / sqrtOff;
    offY = offY / sqrtOff;
    float norm_b = sqrt(offX * offX + offY * offY);
    float timeCost = sqrtOff / float(SPEED_PER_PIXEL);
    float dot = offX * 1 ;//+ offY * 0
    float arc = acosf(dot / norm_b);
    // arc to angle angle = arc * 180 / pi
    int angle = int(arc * 180 / 3.1415926);
    unsigned char next_towards = 0;// 1 - down 2 - left 3 - right 4 - up
    if(angle >= 0  && angle <= 45)// right
    {
        next_towards = 3;
    }
    else if(angle > 45 && angle <= 90)//
    {
        if(offY > 0)
            next_towards = 4;
        else
            next_towards = 1;
    }
    else if(angle > 90 && angle <= 135)//
    {
        if(offY > 0) // up
            next_towards = 4;
        else
            next_towards = 1;// down
    }
    else if(angle >135 && angle <=180)// left
    {
        next_towards = 2;
    }
    if (next_towards == 3) {
        player->role->getSprite()->setFlipX(true);
    }
    else
        player->role->getSprite()->setFlipX(false);
    
    
    unsigned char indexStart = 8;
    unsigned char indexEnd = 16;
    if(next_towards == 2 || next_towards == 3)
    {
        indexStart = 16;
        indexEnd = 24;
    }
    else if(next_towards == 4)
    {
        indexStart = 24;
        indexEnd = 32;
    }
    
    //if(next_towards != towards)
    {
        player->stopAllAction();
        towards = next_towards;
        if(next_towards == 2 || next_towards == 3)
            player->role->setAnimation("standleft");
        else if(next_towards == 1)
            player->role->setAnimation("standup");
        else if(next_towards == 4)
            player->role->setAnimation("standdown");
    }
    
    cocos2d::CCActionInterval *actionTo=cocos2d::CCMoveTo::create(timeCost,end);
    cocos2d::CCAction *moveToAction=cocos2d::CCSequence::create(
                                              actionTo,
                                              overCallback,
                                              NULL
                                              );
    player->runAction(moveToAction);
    
    // make the screen scroll with role,actually is let the camera move
    // in flash called scrollRect,make the map layer go same distance as role go,
    // here opengl view left-down conner is 0,0,we place the map in half of screen
    // and anchor point 0.5 in the initial,and so map 's boundary is
    // 1080 * 960's half in opengl's half screen ,here is 480*320,so is 240,160,
    // boundary x is 240 - 1080 / 2 = -300,so is y
    // .-> (-300,-320) in opengl view
    // --------------------------------
    //          --------------
    //
    //               .->picture center
    //          .->(0,0) in opengl view,also screen's down-left
    //          ---------------
    // --------------------------------
    cocos2d::CCRect scene_rect;
    cocos2d::CCSize s = cocos2d::CCDirector::sharedDirector()->getWinSize();

    scene_rect.origin.x = -(layerscrollwidth / 2);
    scene_rect.origin.y = -(layerscrollheight / 2);
    scene_rect.size.width = layerscrollwidth;
    scene_rect.size.height = layerscrollheight;
    // let the layer go with player
    parentLayer->runAction(cocos2d::CCFollow::create(player,scene_rect));
}