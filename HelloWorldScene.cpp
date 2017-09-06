#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace dragonBones;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    // Load DragonBones Data.
    const auto dragonBonesData = factory.loadDragonBonesData("res/NewProject_ske.json");
    factory.loadTextureAtlasData("res/NewProject_tex.json");
    _armatureDisplay = nullptr;
    _armatureDisplay = factory.buildArmatureDisplay("Armature");
    CCLOG("000");
    _armatureDisplay->setPosition(100.f, 100.f);
    _armatureDisplay->setScale(0.3f);
    CCLOG("111");
    this->addChild(_armatureDisplay);
    CCLOG("222");
    _armatureDisplay->getAnimation().gotoAndPlayByTime("fly",1,99);
    CCLOG("333");

    CCLOG("%d",_armatureDisplay->getPosition().x);
    CCLOG("%d",_armatureDisplay->getPosition().y);
    
    return true;
}

