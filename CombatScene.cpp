#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "CombatScene.h"

USING_NS_CC;

Scene* CombatScene::createScene(int stageNum)
{

    auto scene = Scene::createWithPhysics();
    
    
    //创建物理世界场景

    //对物理世界场景进行需要的设置（略，根据需要添加）
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    CCLOG("origin.y:%f",origin.y);
    /*
    auto lowerLayer=CCLayerColor::create(ccc4(255,255,255,255), visibleSize.width, visibleSize.height);
    lowerLayer->setPosition(ccp(origin.x, origin.y));
    scene->addChild(lowerLayer,0);
    */
     
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
    physicLayer->setTag(2);
    
    //还需要加上bg2，立体
    
    auto ctrlLayer=CombatCtrlLayer::create();
    //ctrlLayer->setPosition(ccp(origin.x, origin.y));
    scene->addChild(ctrlLayer,3);
    //ctrlLayer->_physicLayer=physicLayer;//ctrlLayer中可以控制physicLayer;
    ctrlLayer->setStageNum(stageNum);
    ctrlLayer->setTag(1);
    
    

    return scene;
    //return CombatScene::create();
 
}


#endif

