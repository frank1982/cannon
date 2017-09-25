
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
    
    layercolor = CCLayerColor::create(ccc4(51, 202, 244, 255), visibleSize.width, visibleSize.height);
    layercolor->setCascadeColorEnabled(false);
    layercolor->setPosition(ccp(origin.x, origin.y));
    layercolor->setTag(1000);
    this->addChild(layercolor, 0);
    
    auto navSp=Sprite::create("res/mapNav.png");
    float scaleXOfNavSp=visibleSize.width/navSp->getContentSize().width;
    navSp->setScale(scaleXOfNavSp,scaleXOfNavSp);
    navSp->setPosition(Vec2(visibleSize.width/2,visibleSize.height-navSp->getBoundingBox().size.height/2));
    layercolor->addChild(navSp, 2);

    auto upgradeBtn=Button::create("res/upgrade.png","res/upgrade.png");
    upgradeBtn->setScale(scaleXOfNavSp);
    upgradeBtn->setPosition(Vec2(visibleSize.width-upgradeBtn->getBoundingBox().size.width/2,visibleSize.height-upgradeBtn->getBoundingBox().size.height/2));
    upgradeBtn->setTag(1);
    layercolor->addChild(upgradeBtn, 3);
    upgradeBtn->addClickEventListener([=](Ref* sender){
    
        //按钮缩进
        auto move=CCMoveBy::create(0.4,Vec2(0,layercolor->getChildByTag(1)->getBoundingBox().size.height/2));
        layercolor->getChildByTag(1)->runAction(Sequence::create(move,CallFunc::create([&](){CCLOG("enter upgrade scene...");}),nullptr));
    
    });
    
    auto islandSp=Sprite::create("res/island.png");
    float scaleXOfIslandSp=visibleSize.width/islandSp->getContentSize().width;
    islandSp->setScale(scaleXOfIslandSp);
    islandSp->setTag(1000);
    islandSp->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    layercolor->addChild(islandSp, 1);
    
    
    
    //load pathes
    loadFullPathes();
    
    //int nowProcess = 0;//now stage process;nowProcess 最小 = -1
    //loadPathAndStageFlag(nowProcess);
    
    return true;
}
/*
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
*/
void MapScene::loadFullPathes(){
    
    //cocos2d::Vec2 position;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    std::vector<cocos2d::Vec2> pointVect;
    cocos2d::Vec2 position0=Vec2(visibleSize.width*110/500,visibleSize.height*353/500);
    pointVect.push_back(position0);
    
    std::vector<cocos2d::Vec2> flagPointVect;
    cocos2d::Vec2 flagPosition0=Vec2(visibleSize.width*139/500,visibleSize.height*383/500);
    flagPointVect.push_back(flagPosition0);

  
  
    for(int i=0;i<pointVect.size();i++){
        
        //int 转 std::string
        char temp[50];
        sprintf(temp, "res/roads/road%d.png", i, 50);
        std::string str = temp;
        auto path=Sprite::create(str);
        path->setPosition(pointVect[i]);
        path->setScale(layercolor->getChildByTag(1000)->getScaleX());
        layercolor->addChild(path, 2);
        
        char tempFlag[50];
        if(i%3 == 0){
            sprintf(tempFlag, "res/flag_combat.png", i, 50);
        }else if(i%3 == 1){
            sprintf(tempFlag, "res/flag_bonus.png", i, 50);
        }else{
            sprintf(tempFlag, "res/flag_bonus2.png", i, 50);
        }
        std::string strFlag = tempFlag;
        auto flagSp=Button::create(strFlag);
        flagSp->setScale(visibleSize.width/flagSp->getContentSize().width/30);
        flagSp->setPosition(flagPointVect[i]);
        layercolor->addChild(flagSp, 3);
        
        flagSp->addClickEventListener([=](Ref* sender){
            
            auto combatScene=CombatScene::createScene(0);
            //auto combatScene=GameScene::createScene();
            auto reScene = CCTransitionFadeBL::create(0.6f,combatScene);
            Director::getInstance()->pushScene(reScene);
   
        });
    }
};
