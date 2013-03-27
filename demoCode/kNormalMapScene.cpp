//
//  kNormalMapScene.cpp
//
//  Created by kael on 12/26/12.
//
//
#include "kBaseScene.h"
#include "kSharedData.h"
#include "kNormalMapScene.h"
#include "kConstDefine.h"
#include "datastruct/kCommonStruct.h"
#include "datastruct/kMapXmlParserDelegate.h"
#include "kSprite.h"
#include "kRapidXmlParser.h"
#include "kTestLayer.h"
#include "kAction.h"
#include "kAstar.h"
#include "kNpcSpriteContainer.h"
USING_NS_CC;
bool kNormalMapScene::init()
{
    _tag = KNORMALMAP_TAG;
    map_parser = new kMapXmlParserDelegate();
    map_datastruct = new kMapStruct;
    curAutomaticAction = NULL;
    return true;
}

kNormalMapScene::~kNormalMapScene()
{
    CC_SAFE_DELETE(map_parser);
    CC_SAFE_DELETE(map_datastruct);
    CC_SAFE_DELETE(kastar);
}

void kNormalMapScene::initAstarAlgorithm()
{
    if(map_datastruct != NULL)
    {
        // 37 for temp
//        int row = map_datastruct->walkArr.size() / 37;
        int row = map_datastruct->walkArr.size() / map_datastruct->column;
        kastar = new kAstarAlgorithm(row,map_datastruct->column,TYPE_45DEGREE);
//        kastar = new kAstarAlgorithm(row,37,TYPE_45DEGREE);
        kastar->createMap(map_datastruct->walkArr.c_str());
    }
}

void kNormalMapScene::onLoadScene(const char* filename)
{
    // did load map from config file
    char xml[16];
    sprintf(xml,"%s.xml",filename);
    char jpg[16];
    sprintf(jpg,"%s.jpg",filename);
    kRapidXmlParser rxp(xml,map_parser);
    rxp.toStruct(map_datastruct);
    // init the map path finding data
    initAstarAlgorithm();
    // load map picture to cache
    mapbg = CCSprite::create(jpg);
    this->addChild(mapbg,0);
    // load npc
    int i = 0;
    for(std::map<unsigned short, kNpcStruct>::iterator it = map_datastruct->npclist.begin();
        it != map_datastruct->npclist.end();++it)
    {
        // xml use for npc load
//        sprintf(xml,"npc/%d",it->second.id);
//        sprintf(xml,"npc/n%d",2);
        sprintf(xml,"npc/gb");
        kNpcSpriteContainer* npcya = kNpcSpriteContainer::create();
        CCPoint pos = kSceneInterface::pointToLayerSystem(ccp(it->second.x,it->second.y),(CCLayer*)mapbg);
        it->second.x = pos.x;it->second.y = pos.y;
        npcya->loadFromConfiguration(xml,&it->second);
        npcs[i++]=npcya;
        this->addChild(npcya);
//        CCLabelTTF * sss = CCLabelTTF::create("x1", "arial", 13);
//        sss->cocos2d::CCNode::setPosition(kSceneInterface::pointToLayerSystem(ccp(it->second.x,it->second.y),(CCLayer*)mapbg));
//        this->addChild(sss);
    }
    // load portal point
    
    // load players
    player = kTestLayer::create();
    player->loadFromConfiguration("g2");
    // load other players
    // coord should be changed in mapbg's system
    // if no valid position,set to spawn point
    if (kBaseScene::ksd->rd.x == 0 && kBaseScene::ksd->rd.y == 0) {
        kBaseScene::ksd->rd.x = map_datastruct->initx;
        kBaseScene::ksd->rd.y = map_datastruct->inity;
    }
    CCPoint rolePosition = kSceneInterface::pointToLayerSystem(ccp(kBaseScene::ksd->rd.x,kBaseScene::ksd->rd.y),(CCLayer*)mapbg);
    player->setPosition(rolePosition);
    this->addChild(player,2);
    this->setPosition(centerView(rolePosition,(CCLayer*)mapbg));
    onRegisterListeners();
}

void kNormalMapScene::onUnloadScene()
{
    onUnRegisterListeners();
    this->removeAllChildrenWithCleanup(true);
}

void kNormalMapScene::onUpdate()
{
    // do collide and z swap,actully no need collide detect here,fbmap scene need to trigger war
}

void kNormalMapScene::onRunOneStepAutomatic()
{
    // is here auto matic action?
    if(curAutomaticAction!=NULL)
    {
        if(!curAutomaticAction->working)
        {
            if(curAutomaticAction->_type == AUTOMATIC_ACTION_MOVE_TO)
            {
                kAMoveTo* kam = (kAMoveTo*)curAutomaticAction;
                kPathFindBehaviour::onBeginToGo(player,
                                                ccp(kam->x,kam->y),this,
                                                CCCallFunc::create(this,callfunc_selector(kNormalMapScene::onRunOver)),
                                                mapbg->getContentSize().width,
                                                mapbg->getContentSize().height);
            }
            else if (curAutomaticAction->_type == AUTOMATIC_ACTION_OPEN_UI)
            {
                // open world map?
            }
            curAutomaticAction->working = true;
        }
    }
}

void kNormalMapScene::onRunAllOver()
{
    player->stopAllAction();
    player->role->getSprite()->setFlipX(false);
    player->role->setAnimation("idle");
    // if have current action now,stop it
    for(std::list<kAction*>::iterator it = kBaseScene::ksd->automatic_actions.begin();
            it != kBaseScene::ksd->automatic_actions.end();++it)
    {
        if(*it != NULL)
        {
            delete *it;
            *it = NULL;
        }
    }
    kBaseScene::ksd->automatic_actions.clear();
    curAutomaticAction = NULL;
}

void kNormalMapScene::onRunOver()
{
    CC_SAFE_DELETE(curAutomaticAction);
    kBaseScene::ksd->automatic_actions.pop_front();
    if(kBaseScene::ksd->automatic_actions.size() <= 0)
    {
        onRunAllOver();
    }
    else
    {
        std::list<kAction*>::iterator began = kBaseScene::ksd->automatic_actions.begin();
        curAutomaticAction = *began;
        if(curAutomaticAction)
            curAutomaticAction->working = false;
        onRunOneStepAutomatic();
    }
}

void kNormalMapScene::onRegisterListeners()
{
    // EXTRA:register touch
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_MAPVIEW,true);
}

void kNormalMapScene::onUnRegisterListeners()
{
    // EXTRA:ungister touch
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void kNormalMapScene::onBroadcast(void* data)
{
    
}

bool kNormalMapScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void kNormalMapScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint p3;
    CCPoint ooo3 = kSceneInterface::layerSystemToASSystem(this->convertToNodeSpace(pTouch->getLocation()),(CCLayer*)mapbg);
    CCPoint playerpos = kSceneInterface::layerSystemToASSystem(player->getPosition(),(CCLayer*)mapbg);
    // stop before action
    onRunAllOver();
    // get new path
    curAutomaticAction = kPathFindBehaviour::onTouchEnd(kastar, playerpos, ooo3, (CCLayer*)mapbg);
    if(curAutomaticAction)
        curAutomaticAction->working = false;
    onRunOneStepAutomatic();
}