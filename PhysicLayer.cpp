

#include <stdio.h>
#include "PhysicLayer.h"
#include "Demo.h"

USING_NS_CC;


bool PhysicLayer::init()
{
    
    if ( !LayerColor::init() )
    {
        return false;
    }
    
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
    _inExplosion=false;

  
    
    
    CCLOG("load PhysicLayer");
    CCLOG("width: %f",visibleSize.width);
    
    //load cannon
    loadCannon();
    loadLife();
    loadBarrier();
    

    this->scheduleUpdate();
    

    return true;
}
void PhysicLayer::onEnter(){
    
    Layer::onEnter();//不写会黑屏；需要调一下父类的方法

    monsterManagerWork();
};

//调度monster的生成
void PhysicLayer::monsterManagerWork(){
    
    switch(STAGENUM){
            
        case 0:{
           
            this->scheduleOnce([&](float dt){
                
                addMonster(PIRATE,Vec2(100,100));
                
            }, 3.0f,"随便起个名字");
            
            break;
        }
        default:{
            
            break;

        }
            
    }
    
}


void PhysicLayer::addMonster(MonsterType monsterType,Vec2 position){

    //auto priate1=new Pirate();//delete 释放内存
    Pirate pirate1=Pirate();
    pirate1.SETSCALE(0.05);
    pirate1.PUTATPOSITION(Vec2(visibleSize.width-20,20));
    this->addChild(pirate1.MONSTER_ARMATURE_DISPLAY,16);
    pirate1.MONSTER_ARMATURE_DISPLAY->getAnimation().gotoAndPlayByTime("walk");
    _monsterVectors.push_back(pirate1);
    
}


void PhysicLayer::loadCannon(){
    
    cannonBase=Sprite::create("res/cannonBase.png");
    cannonBase->setScale(visibleSize.width/cannonBase->getContentSize().width/16);
    cannonBase->setPositionX(10+cannonBase->getBoundingBox().size.width/2);
    cannonBase->setPositionY(20+cannonBase->getBoundingBox().size.height/2);
    this->addChild(cannonBase,0);
    
    cannonGun=Sprite::create("res/cannonGun.png");
    //cannonGun->setScale(cannonBase->getScale());
    cannonGun->setAnchorPoint(Vec2(0.4,0.2));
    cannonGun->setPositionX(cannonBase->getContentSize().width*80/100);
    cannonGun->setPositionY(cannonBase->getContentSize().height*70/100);
    
    cannonBase->addChild(cannonGun,-1);
    

}

void PhysicLayer::cannonShoot(float shootAngle){//发射间隔要大于爆炸的粒子效果持续时间！
    
    _inExplosion=false;

    if(cannonBase->getChildByTag(1099)){
        cannonBase->getChildByTag(1099)->removeFromParent();
    }
    _shellSp=Sprite::create("res/shell.png");
    float bombRadius=cannonGun->getContentSize().height*2/3;
    float scaleOfBomb=bombRadius/_shellSp->getContentSize().height;
    _shellSp->setScale(scaleOfBomb);


    Vec2 midPointOfcannonGun=Vec2();//gun的几何中心点（0.6,0.5位置处，随着旋转要计算出来）
    midPointOfcannonGun.x=cannonGun->getPosition().x-cannonGun->getContentSize().height*sin(shootAngle*3.14/180)*0.3;
    midPointOfcannonGun.y=cannonGun->getPosition().y+cannonGun->getContentSize().height*cos(shootAngle*3.14/180)*0.3;
    //float c=cannonGun->getContentSize().width*0.6+bombRadius/2;
    float c=cannonGun->getContentSize().width*0.6;
    float bombX = midPointOfcannonGun.x + c*cos(shootAngle*3.14/180);
    float bombY = midPointOfcannonGun.y + c*sin(shootAngle*3.14/180);
    _shellSp->setPosition(bombX,bombY);
    _shellSp->setTag(1099);
    CCLOG("shootAngle:%f",shootAngle);
    cannonBase->addChild(_shellSp,0);
    
    auto body = PhysicsBody::createCircle(bombRadius/2);
    _shellSp->setPhysicsBody(body);
    int velocity=visibleSize.width*0.52;
    _shellSp->getPhysicsBody()->setVelocity(Vec2(velocity*cos(shootAngle*3.14/180), velocity*sin(shootAngle*3.14/180))); //给一个向上的初速度
    
    //爆炸效果
    //CCParticleFire* ps = CCParticleFire::create();
    //ps->setPosition(Point(bombX,bombY));
    //cannonBase->addChild(ps,10);
    
    ParticleSystemQuad *particle = ParticleSystemQuad::create("res/particles/p2.plist");
    particle->setPosition(Vec2(bombX,bombY));
    cannonBase->addChild(particle, 10);

};

void PhysicLayer::update(float dt){
    
    if(_shellSp){
        
        auto PositionOfShellInWorld=cannonBase->convertToWorldSpace(_shellSp->getPosition());

        
        if(PositionOfShellInWorld.y <= 20 && !_inExplosion){
            
            _inExplosion=true;
            ParticleSystemQuad *particle = ParticleSystemQuad::create("res/particles/p3.plist");
            particle->setScale(0.1);
            particle->setPosition(PositionOfShellInWorld);
            this->addChild(particle, 10);
        }
    }
    
    //状态机
    statusManagerWork();
};

//状态机
void PhysicLayer::statusManagerWork(){
    
    //CCLOG("%d",_monsterVectors.size());
    
};

void PhysicLayer::loadLife(){
    
    for(int i=0;i<5;i++){
        
        auto lifeSp=Sprite::create("res/life.png");
        lifeSp->setScale(cannonBase->getBoundingBox().size.height/lifeSp->getContentSize().height/4);
        auto rightBorderCannonBase=cannonBase->getPositionX()+cannonBase->getBoundingBox().size.width/2;
        lifeSp->setPositionX(rightBorderCannonBase-lifeSp->getBoundingBox().size.width/2-i*(3+lifeSp->getBoundingBox().size.width));
        lifeSp->setPositionY(cannonBase->getPositionY()-cannonBase->getBoundingBox().size.height/2-3-lifeSp->getBoundingBox().size.height/2);
        this->addChild(lifeSp,0);
        _lifeVector.push_back(lifeSp);
    }
}
void PhysicLayer::loadBarrier(){
    
    barrierSp=Sprite::create("res/barrier.png");
    barrierSp->setScale(cannonBase->getBoundingBox().size.width/barrierSp->getContentSize().height/2);
    auto rightBorderCannonBase=cannonBase->getPositionX()+cannonBase->getBoundingBox().size.width/2;
    barrierSp->setPositionX(rightBorderCannonBase+20-barrierSp->getBoundingBox().size.width/2);
    barrierSp->setPositionY(cannonBase->getPositionY()-10);
    this->addChild(barrierSp,1);

}
