
#include <stdio.h>
#include "CombatBgLayer.h"

USING_NS_CC;


bool CombatBgLayer::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("init game bg layer");
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCSize visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bgSp=Sprite::create("res/combatBg.png");
    bgSp->setScaleX(visibleSize.width/bgSp->getContentSize().width);
    bgSp->setScaleY(visibleSize.height/bgSp->getContentSize().height);
    bgSp->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bgSp,0);
    
    //cloud move
    auto cloud1=Sprite::create("res/cloud1.png");
    cloud1->setScale(visibleSize.width/cloud1->getContentSize().width/6);
    cloud1->setPosition(visibleSize.width*2/3,visibleSize.height*5/6);
    this->addChild(cloud1,1);
    auto cloud2=Sprite::create("res/cloud2.png");
    cloud2->setScale(visibleSize.width/cloud2->getContentSize().width/8);
    cloud2->setPosition(visibleSize.width/3,visibleSize.height*4/5);
    this->addChild(cloud2,1);
    auto action11=MoveTo::create(40,ccp(visibleSize.width+cloud1->getBoundingBox().size.width,cloud1->getPosition().y));
    auto action12=MoveTo::create(120,ccp(-cloud1->getBoundingBox().size.width,cloud1->getPosition().y));
    auto action13=MoveTo::create(80,ccp(visibleSize.width*2/3,cloud1->getPosition().y));
    auto seq1=Sequence::create(action11,action12,action13,nullptr);
    auto repeat1=RepeatForever::create(seq1);
    cloud1->runAction(repeat1);
    
    auto action21=MoveTo::create(100,ccp(visibleSize.width+cloud2->getBoundingBox().size.width,cloud2->getPosition().y));
    auto action22=MoveTo::create(150,ccp(-cloud2->getBoundingBox().size.width,cloud2->getPosition().y));
    auto action23=MoveTo::create(50,ccp(visibleSize.width/3,cloud2->getPosition().y));
    auto seq2=Sequence::create(action21,action22,action23,nullptr);
    auto repeat2=RepeatForever::create(seq2);
    cloud2->runAction(repeat2);
    

    
    return true;
}
