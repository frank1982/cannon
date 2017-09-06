#include "MainScene.h"
#include <stdio.h>
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init()
{
    
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto layercolor = CCLayerColor::create(ccc4(255, 255, 255, 255), visibleSize.width, visibleSize.height);
    layercolor->setCascadeColorEnabled(false);
    layercolor->setPosition(ccp(origin.x, origin.y));
    this->addChild(layercolor, 0);
    
    auto bgSp=Sprite::create("res/mainbg.png");
    bgSp->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    float scaleXOfbgSp=visibleSize.width/bgSp->getContentSize().width;
    float scaleYOfbgSp=visibleSize.height/bgSp->getContentSize().height;
    bgSp->setScale(scaleXOfbgSp, scaleYOfbgSp);
    
    //load title
    auto titleSp=Sprite::create("res/title.png");
    titleSp->setPosition(Vec2(visibleSize.width/2,visibleSize.height-titleSp->getContentSize().height/2-10));
    float scaleOftitleSp=visibleSize.width/3/titleSp->getContentSize().width;
    titleSp->setScale(scaleOftitleSp,scaleOftitleSp);
    
    //load startBtn
    auto startBtn = Button::create("res/startBtnPressed.png","res/startBtn.png");
    float scaleOfStartBtn=visibleSize.width/4/startBtn->getContentSize().width;
    startBtn->setScale(scaleOfStartBtn,scaleOfStartBtn);
    startBtn->setPosition(Vec2(visibleSize.width/2,visibleSize.height/3));
    //为按钮添加触摸事件监听
    startBtn->addClickEventListener([&](Ref* sender){
    
        CCLOG("click start btn");
        //判断当前关卡进度
        //如果关卡无进度，则为首次玩家，播放storyScene
        //跳转去地图
        Director::getInstance()->replaceScene(MapScene::createScene());
        
    });
    
    layercolor->addChild(bgSp,0);
    layercolor->addChild(titleSp,1);
    layercolor->addChild(startBtn,2);
    
    return true;
}

