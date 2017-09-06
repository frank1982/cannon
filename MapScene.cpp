
#include <stdio.h>
#include "MapScene.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;


USING_NS_CC;


Scene* MapScene::createScene()
{
    return MapScene::create();
}

bool MapScene::init()
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
    layercolor->setTag(1000);
    this->addChild(layercolor, 0);

    auto bgSp=Sprite::create("res/mapBg.png");
    bgSp->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    float scaleXOfbgSp=visibleSize.width/bgSp->getContentSize().width;
    float scaleYOfbgSp=visibleSize.height/bgSp->getContentSize().height;
    bgSp->setScale(scaleXOfbgSp, scaleYOfbgSp);
    bgSp->setTag(1001);
    layercolor->addChild(bgSp, 0);

    
    //load pathes
    //loadFullPathes();
    
    int nowProcess = 0;//now stage process;nowProcess 最小 = -1
    loadPathAndStageFlag(nowProcess);
    
    return true;
}

void MapScene::loadPathAndStageFlag(int nowProcess){
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    std::vector<cocos2d::Vec2> pathCenterPointsVect;
    cocos2d::Vec2 position0=Vec2(visibleSize.width*120/500,visibleSize.height*290/500);
    pathCenterPointsVect.push_back(position0);
    cocos2d::Vec2 position1=Vec2(visibleSize.width*160/500,visibleSize.height*352/500);
    pathCenterPointsVect.push_back(position1);
    cocos2d::Vec2 position2=Vec2(visibleSize.width*202/500,visibleSize.height*332/500);
    pathCenterPointsVect.push_back(position2);
    cocos2d::Vec2 position3=Vec2(visibleSize.width*190/500,visibleSize.height*262/500);
    pathCenterPointsVect.push_back(position3);
    cocos2d::Vec2 position4=Vec2(visibleSize.width*247/500,visibleSize.height*252/500);
    pathCenterPointsVect.push_back(position4);
    cocos2d::Vec2 position5=Vec2(visibleSize.width*332/500,visibleSize.height*252/500);
    pathCenterPointsVect.push_back(position5);
    cocos2d::Vec2 position6=Vec2(visibleSize.width*393/500,visibleSize.height*187/500);
    pathCenterPointsVect.push_back(position6);
    cocos2d::Vec2 position7=Vec2(visibleSize.width*303/500,visibleSize.height*176/500);
    pathCenterPointsVect.push_back(position7);
    //load path
    for(int i=0;i<=nowProcess;i++){
        
        //int 转 std::string
        char temp[50];
        sprintf(temp, "res/path%d.png", i, 50);
        std::string str = temp;
        auto path=Sprite::create(str);
        path->setPosition(pathCenterPointsVect[i]);
        path->setScale(this->getChildByTag(1000)->getChildByTag(1001)->getScaleX(), this->getChildByTag(1000)->getChildByTag(1001)->getScaleY());
        this->getChildByTag(1000)->addChild(path, 1);
        
    }
    
    //load stage flags
    //暂时没有判断关卡的得分
    std::vector<cocos2d::Vec2> flagCenterPointsVect;
    cocos2d::Vec2 flagPosition0=Vec2(visibleSize.width*103/500,visibleSize.height*251/500);
    flagCenterPointsVect.push_back(flagPosition0);
    cocos2d::Vec2 flagPosition1=Vec2(visibleSize.width*140/500,visibleSize.height*328/500);
    flagCenterPointsVect.push_back(flagPosition1);
    for(int i = -1;i<=nowProcess;i++){
        
        auto flagBtn = Button::create("res/flag_combat.png","res/flag_combat.png");
        flagBtn->setPosition(flagCenterPointsVect[i+1]);
        float scaleOfFlag=visibleSize.width/flagBtn->getContentSize().width/12;
        flagBtn->setScale(scaleOfFlag, scaleOfFlag);
        this->getChildByTag(1000)->addChild(flagBtn, 2);
        flagBtn->addClickEventListener([=](Ref* sender){
        
            CCLOG("enter %d stage",(i+1));
            auto gameScene=GameScene::createScene();
            //gameScene->_nowStageNum = i+1;
            Director::getInstance()->pushScene(gameScene);

            
        });
    }
};

void MapScene::loadFullPathes(){
    
    //cocos2d::Vec2 position;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    std::vector<cocos2d::Vec2> pointVect;
    cocos2d::Vec2 position0=Vec2(visibleSize.width*120/500,visibleSize.height*290/500);
    pointVect.push_back(position0);
    cocos2d::Vec2 position1=Vec2(visibleSize.width*160/500,visibleSize.height*352/500);
    pointVect.push_back(position1);
    cocos2d::Vec2 position2=Vec2(visibleSize.width*202/500,visibleSize.height*332/500);
    pointVect.push_back(position2);
    cocos2d::Vec2 position3=Vec2(visibleSize.width*190/500,visibleSize.height*262/500);
    pointVect.push_back(position3);
    cocos2d::Vec2 position4=Vec2(visibleSize.width*247/500,visibleSize.height*252/500);
    pointVect.push_back(position4);
    cocos2d::Vec2 position5=Vec2(visibleSize.width*332/500,visibleSize.height*252/500);
    pointVect.push_back(position5);
    cocos2d::Vec2 position6=Vec2(visibleSize.width*393/500,visibleSize.height*187/500);
    pointVect.push_back(position6);
    cocos2d::Vec2 position7=Vec2(visibleSize.width*303/500,visibleSize.height*176/500);
    pointVect.push_back(position7);
  
    for(int i=0;i<pointVect.size();i++){
        
        //int 转 std::string
        char temp[50];
        sprintf(temp, "res/path%d.png", i, 50);
        std::string str = temp;
        auto path=Sprite::create(str);
        path->setPosition(pointVect[i]);
        path->setScale(this->getChildByTag(1000)->getChildByTag(1001)->getScaleX(), this->getChildByTag(1000)->getChildByTag(1001)->getScaleY());
        this->getChildByTag(1000)->addChild(path, 1);
        
    }
};


