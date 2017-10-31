

#include <stdio.h>
#include "CombatCtrlLayer.h"
USING_NS_CC;



bool CombatCtrlLayer::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    CCLOG("init game ctrl layer");
 
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
    _waveNum=0;
    CANLOADSHELL=true;
    

    pauseBtn=Button::create("res/pauseBtn.png");
    pauseBtn->setScale(visibleSize.width/pauseBtn->getContentSize().width/16);
    pauseBtn->setPosition(Vec2(visibleSize.width-20-pauseBtn->getBoundingBox().size.width*5/2,visibleSize.height+origin.y-10-pauseBtn->getBoundingBox().size.height/2));
    pauseBtn->setTag(1000);
    pauseBtn->addClickEventListener([=](Ref* sender){
        
        //pause
        if(Director::getInstance()->isPaused()){
            
            Director::getInstance()->resume();
            pauseBtn->loadTextureNormal("res/pauseBtn.png");

        }else{
            
            Director::getInstance()->pause();
            pauseBtn->loadTextureNormal("res/pausedBtn.png");

        }
    });
    resetBtn=Button::create("res/resetBtn.png");
    resetBtn->setScale(visibleSize.width/pauseBtn->getContentSize().width/16);
    resetBtn->setPosition(Vec2(visibleSize.width-15-pauseBtn->getBoundingBox().size.width*3/2,visibleSize.height+origin.y-10-pauseBtn->getBoundingBox().size.height/2));
    resetBtn->setTag(1001);
    
    backBtn=Button::create("res/backBtn.png");
    backBtn->setScale(visibleSize.width/pauseBtn->getContentSize().width/16);
    backBtn->setPosition(Vec2(visibleSize.width-10-pauseBtn->getBoundingBox().size.width/2,visibleSize.height+origin.y-10-pauseBtn->getBoundingBox().size.height/2));
    backBtn->setTag(1002);
    backBtn->addClickEventListener([=](Ref* sender){

        Director::getInstance()->popScene();
        
    });
    
    this->addChild(pauseBtn,0);
    this->addChild(resetBtn,0);
    this->addChild(backBtn,0);
    
   
    //炮弹放置的甲板
    auto dockSp=Sprite::create("res/dock.png");
    dockSp->setScale(visibleSize.width/dockSp->getContentSize().width/3);
    dockSp->setPosition(Vec2(5+dockSp->getBoundingBox().size.width/2,visibleSize.height+origin.y-10-dockSp->getBoundingBox().size.height/2));
    dockSp->setTag(2000);
    this->addChild(dockSp,0);
    
    //随机生成炮弹并放置到甲板上
    this->schedule(schedule_selector(CombatCtrlLayer::createShells), 2.0);
    
    
    loadWaveProcess();
    
    //触摸响应
    auto listen =EventListenerTouchOneByOne::create();
    listen->onTouchBegan =CC_CALLBACK_2(CombatCtrlLayer::onTouchBegan, this);
    listen->onTouchMoved =CC_CALLBACK_2(CombatCtrlLayer::onTouchMoved, this);
    listen->onTouchEnded =CC_CALLBACK_2(CombatCtrlLayer::onTouchEnded, this);
    listen->setSwallowTouches(true);//如果不加入此句消息依旧会向下传递
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen,this);
    
    
    return true;
}


void CombatCtrlLayer::createShells(float dt){
    
    if(SHELL_MAP.size() < 3){//未满
        
        if(SHELL_MAP[0].empty()){
            
            loadShell(0,nut);

        }else if(SHELL_MAP[1].empty()){
            
            loadShell(1,nut);
            
        }else{
            
            loadShell(2,nut);
            
        }
       

    }else{
        
        //CCLOG("炮弹已满3格");
    }
    
}

void CombatCtrlLayer::loadShell(int num,ShellType shellType){
 
    //暂时先不用shellType
    //先加载炮弹数据
    ShellOfNut nut = ShellOfNut();
    ShellOfNut *nutPtr = &nut;//new ShellOfNut()
    SHELL_MAP[num] = "coconut";
    //CCLOG("num : %d",num);
    
    //显示加载炮弹动画
    auto nutSp=nutPtr->SHELL_SP;
    auto dockScale=this->getChildByTag(2000)->getScale();
    auto shellScale=(this->getChildByTag(2000)->getContentSize().width-60)/nutSp->getContentSize().width/3;
    nutSp->setScale(shellScale*dockScale, shellScale*dockScale);
    float PX=5+this->getChildByTag(2000)->getBoundingBox().size.width/6+num*this->getChildByTag(2000)->getBoundingBox().size.width/3;
    //nutSp->setPosition(PX,this->getChildByTag(2000)->getPositionY());
    nutSp->setPosition(PX,visibleSize.height+origin.y);
  
    
    auto shengziSp=Sprite::create("res/shengzi.png");
    shengziSp->setPosition(nutSp->getContentSize().width/2,nutSp->getContentSize().height/2+shengziSp->getContentSize().height/2);
    shengziSp->setTag(3001);
    nutSp->addChild(shengziSp,-1);
    
    this->addChild(nutSp,1);
    SHELL_SP[num]=nutSp;
    
    //nut move
    //CCEaseOut由快至慢
    auto moveTo=CCMoveTo::create(2, Vec2(PX,this->getChildByTag(2000)->getPositionY()));
    auto ease=CCEaseBounceOut::create(moveTo);
    auto seq=CCSequence::create(ease,CallFunc::create(CC_CALLBACK_0(CombatCtrlLayer::shellLoadCallFunc, this, num)),nullptr);
    nutSp->runAction(seq);
    
};

void CombatCtrlLayer::shellLoadCallFunc(int num){
    
    SHELL_SP[num]->getChildByTag(3001)->removeFromParent();
    //准备选择炮弹及动画
    SHELL_READY_FLAG[num]=true;//这个位置炮弹装载完毕
};

void CombatCtrlLayer::loadWaveProcess(){
    
    stageProcess=Sprite::create("res/stageProcess.png");
    stageProcess->setScale(visibleSize.width/stageProcess->getContentSize().width/4);
    stageProcess->setPositionX(visibleSize.width/2);
    stageProcess->setPositionY(visibleSize.height+origin.y-10-stageProcess->getBoundingBox().size.height/2);
    std::string str = "0/" + std::to_string(MAX_WAVE_NUM[0]);
    //std::string str = "0/8";
    processLabel=Label::create(str, "Aria", 12);
    processLabel->setTextColor(ccc4(251,166,35,255));
    processLabel->setPositionX(stageProcess->getContentSize().width*2/3);
    processLabel->setPositionY(stageProcess->getContentSize().height/2);
    processLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    stageProcess->addChild(processLabel);
    this->addChild(stageProcess,1);

};


void CombatCtrlLayer::setStageNum(int stageNum){
    
    _stageNum=stageNum;
};




void CombatCtrlLayer::onEnter(){
    
    Layer::onEnter();//不写会黑屏；需要调一下父类的方法
  
};


//计算发射角度
bool CombatCtrlLayer::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    //CCLOG("touch begin");
    tmpTouchPointCatched = pTouch->getLocation();//返回点击的位置
    //判断物理层的大炮是否处于可装填炮弹的状态
    //auto physicLayer=(PhysicLayer*)Director::getInstance()->getRunningScene()->getChildByTag(2);
    
    
    
    if(this->getChildByTag(2000)->getBoundingBox().containsPoint(tmpTouchPointCatched)){//点击甲板区不会导致控制大炮,中间可能存在一个垂直位移
        //CCLOG("点击时的size: %d",SHELL_SP.size());
        map<int ,Sprite*>::iterator it;
        it = SHELL_SP.begin();
        while(it != SHELL_SP.end()){
            
            
            if(it->second->getBoundingBox().containsPoint(tmpTouchPointCatched)){
                
                CCLOG("第 %d 枚炮弹被选中",it->first);
                //播放炮弹装入大炮的动画;
                if(SHELL_READY_FLAG[it->first] && CANLOADSHELL){//该炮弹已装载完毕，并且当前出于可射击状态
                    
                    CANLOADSHELL=false;//防止重复装入炮弹到大炮
                    auto physicLayer=(PhysicLayer*)Director::getInstance()->getRunningScene()->getChildByTag(2);

                    auto moveTo=CCMoveTo::create(1.0f, Vec2(physicLayer->cannonBase->getPositionX(),physicLayer->cannonBase->getPositionY()+origin.y));
                    auto scaleBy=CCScaleBy::create(1.0f, 0.3f);
                    auto seq=Sequence::create(CCSpawn::create(moveTo,scaleBy,NULL),CallFunc::create([=](){
                        
                        CCLOG("炮弹装载动画完毕");
                        it->second->removeFromParent();
                        SHELL_READY_FLAG[it->first]=false;
                        
                        //从map删除
                        SHELL_SP.erase(it);
                        /*
                        map<int,Sprite*>::iterator key = SHELL_SP.find(it->first);
                        if(key!=SHELL_SP.end())
                        {
                            SHELL_SP.erase(key);  
                        }
                        */
                        //SHELL_MAP
                        map<int,std::string>::iterator key2 = SHELL_MAP.find(it->first);
                        if(key2!=SHELL_MAP.end())
                        {
                            SHELL_MAP.erase(key2);
                        }
                        CCLOG("删除后的size: %d",SHELL_SP.size());
                        
                        
                    }), NULL);
                    it->second->runAction(seq);
                }
             
            }
        
            it++;
        }
        return false;
    }
    
    
    return true;  //可以传递到moved和ended
};
void CombatCtrlLayer::onTouchMoved(Touch* pTouch, Event* pEvent){
    
    //rotate the gun
    
    auto nowTouchPoint=pTouch->getLocation();
    float distance=sqrt(pow((nowTouchPoint.x-tmpTouchPointCatched.x),2)+pow((nowTouchPoint.y-tmpTouchPointCatched.y),2));
    auto addAngle = distance/3;
    auto physicLayer=(PhysicLayer*)Director::getInstance()->getRunningScene()->getChildByTag(2);
    float angle=physicLayer->cannonGun->getRotation();
    if(nowTouchPoint.x < tmpTouchPointCatched.x){//调高角度
        
        newAngle=angle-addAngle;
        if(newAngle <= -MAX_ANGLE){
            
            newAngle = -MAX_ANGLE;
        }
        physicLayer->cannonGun->setRotation(newAngle);
        
    }else{//调低角度
        newAngle=angle+addAngle;
        if(newAngle >= MIN_ANGLE){
            
            newAngle = MIN_ANGLE;
        }
        physicLayer->cannonGun->setRotation(newAngle);

    }
    
};
void CombatCtrlLayer::onTouchEnded(Touch* pTouch, Event* pEvent){

    //shoot
    auto physicLayer=(PhysicLayer*)Director::getInstance()->getRunningScene()->getChildByTag(2);
    physicLayer->cannonShoot(-newAngle);
};
