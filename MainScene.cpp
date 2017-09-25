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
    
    auto bgSp=Sprite::create("res/launchPage.png");
    bgSp->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    float scaleOfbgSp=visibleSize.width/bgSp->getContentSize().width/2;
    bgSp->setScale(scaleOfbgSp,scaleOfbgSp);
    
    //load title
    auto titleSp=Sprite::create("res/title.png");
    titleSp->setPosition(Vec2(visibleSize.width/2,visibleSize.height-titleSp->getContentSize().height/2-30));
    float scaleOftitleSp=visibleSize.width/3/titleSp->getContentSize().width;
    titleSp->setScale(scaleOftitleSp,scaleOftitleSp);
    
    /*
    auto startBtn = Button::create("res/startbtnPressed.png","res/startbtn.png");
    float scaleOfStartBtn=visibleSize.width/4/startBtn->getContentSize().width;
    startBtn->setScale(scaleOfStartBtn,scaleOfStartBtn);
    startBtn->setPosition(Vec2(visibleSize.width/2,30+startBtn->getBoundingBox().size.height/2));
    //为按钮添加触摸事件监听
    startBtn->addClickEventListener([&](Ref* sender){
    
        CCLOG("click start btn");
        //判断当前关卡进度
        //如果关卡无进度，则为首次玩家，播放storyScene
        //跳转去地图
        //Director::getInstance()->replaceScene(MapScene::createScene());
        
    });
    */
    auto startSp=Sprite::create("res/startbtn.png");
    float scaleOfStartBtn=visibleSize.width/4/startSp->getContentSize().width;
    startSp->setScale(scaleOfStartBtn,scaleOfStartBtn);
    startSp->setPosition(Vec2(visibleSize.width/2,30+startSp->getBoundingBox().size.height/2));
    Blink * blink = Blink::create(120.0f,80);
    startSp->runAction(blink);
    
    layercolor->addChild(bgSp,0);
    layercolor->addChild(titleSp,1);
    layercolor->addChild(startSp,2);
    
    auto listen =EventListenerTouchOneByOne::create();
    listen->onTouchBegan =CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listen->onTouchMoved =CC_CALLBACK_2(MainScene::onTouchMoved, this);
    listen->onTouchEnded =CC_CALLBACK_2(MainScene::onTouchEnded, this);
    listen->setSwallowTouches(true);//如果不加入此句消息依旧会向下传递
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen,this);
    
    return true;
}
bool MainScene::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    //判断当前关卡进度
    //如果关卡无进度，则为首次玩家，播放storyScene
    //跳转去地图
    Director::getInstance()->replaceScene(MapScene::createScene());
    
    return true;  //可以传递到moved和ended
};
void MainScene::onTouchMoved(Touch* pTouch, Event* pEvent){

    
};
void MainScene::onTouchEnded(Touch* pTouch, Event* pEvent){
  
    
};
