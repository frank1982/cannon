

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

    

    pauseBtn=Button::create("res/pauseBtn.png");
    pauseBtn->setScale(visibleSize.width/pauseBtn->getContentSize().width/16);
    pauseBtn->setPosition(Vec2(visibleSize.width-20-pauseBtn->getBoundingBox().size.width*5/2,visibleSize.height-10-pauseBtn->getBoundingBox().size.height/2));
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
    resetBtn->setPosition(Vec2(visibleSize.width-15-pauseBtn->getBoundingBox().size.width*3/2,visibleSize.height-10-pauseBtn->getBoundingBox().size.height/2));
    resetBtn->setTag(1001);
    
    backBtn=Button::create("res/backBtn.png");
    backBtn->setScale(visibleSize.width/pauseBtn->getContentSize().width/16);
    backBtn->setPosition(Vec2(visibleSize.width-10-pauseBtn->getBoundingBox().size.width/2,visibleSize.height-10-pauseBtn->getBoundingBox().size.height/2));
    backBtn->setTag(1002);
    backBtn->addClickEventListener([=](Ref* sender){

        Director::getInstance()->popScene();
        
    });
    
    this->addChild(pauseBtn,0);
    this->addChild(resetBtn,0);
    this->addChild(backBtn,0);
    
    
    //load shell list
    _shellNumSelected=-1;
    auto solidShellBtn=Button::create("res/shells/solid.png","res/shells/solid.png");
    solidShellBtn->setName("solid");
    auto scatterShellBtn=Button::create("res/shells/scatter.png","res/shells/scatter.png");
    scatterShellBtn->setName("scatter");
    auto blastShellBtn=Button::create("res/shells/blast.png","res/shells/blast.png");
    blastShellBtn->setName("blast");
    btnVector.push_back(solidShellBtn);
    btnVector.push_back(scatterShellBtn);
    btnVector.push_back(blastShellBtn);

    for(int i=0;i<btnVector.size();i++){
        
        Button* btn = btnVector[i];
        btn->setScale(visibleSize.width/pauseBtn->getContentSize().width/18);
        btn->setPositionX(10+i*(btn->getBoundingBox().size.width+2.5)+btn->getBoundingBox().size.width/2);
        btn->setPositionY(visibleSize.height-10-btn->getBoundingBox().size.height/2);
        btn->addClickEventListener(CC_CALLBACK_1(CombatCtrlLayer::shellSelect,this,i));
        this->addChild(btn,1);
    }
    
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

void CombatCtrlLayer::loadWaveProcess(){
    
    stageProcess=Sprite::create("res/stageProcess.png");
    stageProcess->setScale(visibleSize.width/stageProcess->getContentSize().width/4);
    stageProcess->setPositionX(visibleSize.width/2);
    stageProcess->setPositionY(visibleSize.height-10-stageProcess->getBoundingBox().size.height/2);
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
/*
void CombatCtrlLayer::loadForwardBackwardBtns(){
    
    forwardBtn=Button::create("res/forward.png");
    forwardBtn->setScale(visibleSize.height/forwardBtn->getContentSize().height/12);
    forwardBtn->setPositionX(visibleSize.width-5-forwardBtn->getBoundingBox().size.width/2);
    forwardBtn->setPositionY(visibleSize.height/2);
    forwardBtn->addClickEventListener([&](Ref* sender){
    
        forwardBtn->setVisible(false);
        auto move=MoveBy::create(0.6,Vec2(-visibleSize.width, 0));
        auto seq=Sequence::create(move,CallFunc::create([&](){
            
             backwardBtn->setVisible(true);
            
        }), NULL);
        _physicLayer->runAction(seq);
        
    });
    this->addChild(forwardBtn,2);
    
    backwardBtn=Button::create("res/backward.png");
    backwardBtn->setScale(visibleSize.height/backwardBtn->getContentSize().height/12);
    backwardBtn->setPositionX(5+backwardBtn->getBoundingBox().size.width/2);
    backwardBtn->setPositionY(visibleSize.height/2);
    backwardBtn->setVisible(false);
    backwardBtn->addClickEventListener([&](Ref* sender){
        
        backwardBtn->setVisible(false);
        auto move=MoveBy::create(0.6,Vec2(visibleSize.width, 0));
        auto seq=Sequence::create(move,CallFunc::create([&](){
            
            forwardBtn->setVisible(true);
            
        }), NULL);
        _physicLayer->runAction(seq);
        
    });
    this->addChild(backwardBtn,2);

};
*/
void CombatCtrlLayer::shellSelect(Ref* pSender,int btnNum){
    
    for(int i=0;i<btnVector.size();i++){
        btnVector[i]->setTouchEnabled(false);
    }
    std::string textureName="";
    //之前选择的炮弹是否存在？如果存在则缩回
    if(_shellNumSelected>=0){//之前有选择
        
        //之前选中的缩回
        textureName=btnVector[_shellNumSelected]->getName().c_str();
        btnVector[_shellNumSelected]->loadTextureNormal("res/shells/"+textureName+".png");
        //btnVector[_shellNumSelected]->setPositionY(btnVector[_shellNumSelected]->getPositionY()+btnVector[_shellNumSelected]->getBoundingBox().size.height/3);
        CCActionInterval *easeElasticOut = CCEaseElasticOut::create(MoveBy::create(0.6,Vec2(0,btnVector[_shellNumSelected]->getBoundingBox().size.height/5)));
        btnVector[_shellNumSelected]->runAction(easeElasticOut);
    }

    _shellNumSelected=btnNum;
    textureName=btnVector[_shellNumSelected]->getName().c_str();
    btnVector[_shellNumSelected]->loadTextureNormal("res/shells/"+textureName+"2.png");
    CCActionInterval *easeElasticOut = CCEaseElasticOut::create(MoveBy::create(0.6,Vec2(0,-btnVector[_shellNumSelected]->getBoundingBox().size.height/5)));
    auto seq=Sequence::create(easeElasticOut,CallFunc::create([&](){
        
        for(int i=0;i<btnVector.size();i++){
            btnVector[i]->setTouchEnabled(true);
        }
        
    }), NULL);
    btnVector[_shellNumSelected]->runAction(seq);
    
};
//计算发射角度
bool CombatCtrlLayer::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    //CCLOG("touch begin");
    tmpTouchPointCatched = pTouch->getLocation();//返回点击的位置
    
    return true;  //可以传递到moved和ended
};
void CombatCtrlLayer::onTouchMoved(Touch* pTouch, Event* pEvent){
    
    //rotate the gun
    auto nowTouchPoint=pTouch->getLocation();
    float distance=sqrt(pow((nowTouchPoint.x-tmpTouchPointCatched.x),2)+pow((nowTouchPoint.y-tmpTouchPointCatched.y),2));
    auto addAngle = distance/3;
    float angle=_physicLayer->cannonGun->getRotation();
    if(nowTouchPoint.x < tmpTouchPointCatched.x){//调高角度
        
        newAngle=angle-addAngle;
        if(newAngle <= -MAX_ANGLE){
            
            newAngle = -MAX_ANGLE;
        }
        _physicLayer->cannonGun->setRotation(newAngle);
        
    }else{//调低角度
        newAngle=angle+addAngle;
        if(newAngle >= MIN_ANGLE){
            
            newAngle = MIN_ANGLE;
        }
        _physicLayer->cannonGun->setRotation(newAngle);

    }
  
};
void CombatCtrlLayer::onTouchEnded(Touch* pTouch, Event* pEvent){

    //shoot
    _physicLayer->cannonShoot(-newAngle);
};
