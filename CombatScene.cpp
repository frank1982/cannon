#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "CombatScene.h"

USING_NS_CC;

Scene* CombatScene::createScene(int stageNum)
{
    stageNum=stageNum;
    //创建物理世界场景
    auto scene = Scene::createWithPhysics();
    //对物理世界场景进行需要的设置（略，根据需要添加）
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto lowerLayer=CCLayerColor::create(ccc4(255,255,255,255), visibleSize.width, visibleSize.height);
    lowerLayer->setPosition(ccp(origin.x, origin.y));
    scene->addChild(lowerLayer,0);
    
    CCLOG("this is combat scene");
    auto bgLayer=CombatBgLayer::create();
    bgLayer->setPosition(ccp(origin.x, origin.y));
    scene->addChild(bgLayer,1);
    
    
    auto physicLayer=PhysicLayer::create();
    physicLayer->setPosition(ccp(origin.x, origin.y));
    physicLayer->m_world=scene->getPhysicsWorld();
    physicLayer->m_world->setGravity(Vect(0,-175));
    scene->addChild(physicLayer,2);
    physicLayer->STAGENUM=stageNum;
    
    auto ctrlLayer=CombatCtrlLayer::create();
    ctrlLayer->setPosition(ccp(origin.x, origin.y));
    scene->addChild(ctrlLayer,3);
    ctrlLayer->_physicLayer=physicLayer;//ctrlLayer中可以控制physicLayer;
    ctrlLayer->setStageNum(stageNum);

    
    return scene;
    //return CombatScene::create();
 
}

/*
bool CombatScene::init()
{
    
    if ( !Scene::init() )
    {
        return false;
    }
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto lowerLayer=CCLayerColor::create(ccc4(255,255,255,255), visibleSize.width, visibleSize.height);
    lowerLayer->setPosition(ccp(origin.x, origin.y));
    this->addChild(lowerLayer,0);
    
    CCLOG("this is combat scene");
    bgLayer=CombatBgLayer::create();
    bgLayer->setPosition(ccp(origin.x, origin.y));
    this->addChild(bgLayer,1);
    
    
    physicLayer=PhysicLayer::create();
    physicLayer->setPosition(ccp(origin.x, origin.y));
    this->addChild(physicLayer,2);
    
    
    ctrlLayer=CombatCtrlLayer::create();
    ctrlLayer->setPosition(ccp(origin.x, origin.y));
    this->addChild(ctrlLayer,3);
    ctrlLayer->_physicLayer=physicLayer;//ctrlLayer中可以控制physicLayer;
    
    
    
    return true;
}
 */

#endif

