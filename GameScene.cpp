
#include <stdio.h>
#include "GameScene.h"


using namespace cocos2d::ui;
USING_NS_CC;


Scene* GameScene::createScene()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCSize visibleSize = Director::getInstance()->getVisibleSize();
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto bgLayer=CCLayerColor::create(ccc4(255,255,255,255), visibleSize.width, visibleSize.height);
    bgLayer->setPosition(ccp(origin.x, origin.y));
    scene->addChild(bgLayer,0);
    auto layer = GameScene::create();
    layer->setPosition(ccp(origin.x, origin.y));
    scene->addChild(layer,1);
    Vect gravity(0, -250.0f);
    scene->getPhysicsWorld()->setGravity(gravity);;
    
    return scene;
}

bool GameScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    bombRadius=0.0;
    //this->scheduleUpdate();
    this->schedule(schedule_selector(GameScene::Update),0.1f);
 
    groundLayer = CCLayerColor::create(ccc4(0, 0, 0, 255), visibleSize.width, 50);
    groundLayer->setCascadeColorEnabled(false);
    groundLayer->setPosition(0,0);
    this->addChild(groundLayer, 0);
    
    //loadCannon();
    //loadDriver();
 	
    
    // Load DragonBones Data.
    const auto dragonBonesData = factory.loadDragonBonesData("res/skeleton/demo_ske.json");
    factory.loadTextureAtlasData("res/skeleton/demo_tex.json");
    _armatureDisplay = nullptr;
    _armatureDisplay = factory.buildArmatureDisplay("pirate");
    _armatureDisplay->setPosition(visibleSize.width/2,visibleSize.height/2);
    _armatureDisplay->setScale(0.1f);
    this->addChild(_armatureDisplay,1);
    auto move=CCMoveBy::create(300,ccp(-500,0));
    _armatureDisplay->runAction(move);
    _armatureDisplay->getAnimation().gotoAndPlayByTime("walk");
    //_armatureDisplay->getAnimation().gotoAndPlayByTime("onHit");
    
    
    auto listen =EventListenerTouchOneByOne::create();
    listen->onTouchBegan =CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listen->onTouchMoved =CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listen->onTouchEnded =CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listen->setSwallowTouches(true);//如果不加入此句消息依旧会向下传递
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen,this);
    
    /*
    //定义世界的边界
    auto body = PhysicsBody::createEdgeBox(visibleSize,
                                           PHYSICSBODY_MATERIAL_DEFAULT,5.0f);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    edgeNode->setPhysicsBody(body);
    this->addChild(edgeNode);
    */
    
    return true;
}
void GameScene::Update(float dt)
{
    //CCLOG("update");
    //碰撞检测
    //返回bool。相交为true
    //auto pSize=CCRect(_armatureDisplay->getPosition().x-,,,)
    //rect1.intersectsRect(rect2);
        if(bombSp){
        
            if(bombSp->getBoundingBox().containsPoint(_armatureDisplay->getPosition())){
                CCLOG("knock");
                _armatureDisplay->stopAllActions();
                _armatureDisplay->runAction(Sequence::create(CCJumpBy::create(1,ccp(50,50),50,1),CallFunc::create([=](){
                    _armatureDisplay->removeFromParent();
                }), nullptr));
                _armatureDisplay->getAnimation().gotoAndPlayByTime("onHit");
                
            }
            //CCLOG("width: %f,height: %f",_armatureDisplay->getContentSize().width/10,_armatureDisplay->getContentSize().height/10);
    };//不一定存在

}

void GameScene::onEnter(){
    
    Layer::onEnter();//不写会黑屏；需要调一下父类的方法
    CCLOG("now stage num: %d",_nowStageNum);
    
};

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    driverAngle=0.0;
    tmpTouchPointCatched = pTouch->getLocation();//返回点击的位置
    return true;  //可以传递到moved和ended
};
void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent){
    
    auto nowTouchPoint=pTouch->getLocation();
    /*
    float tan=(nowTouchPoint.y-tmpTouchPointCatched.y)/(nowTouchPoint.x-tmpTouchPointCatched.x);
    float  arc=atan(tan);//h弧度
    float  angle=(arc*360)/(2*3.14);//化成角度了
    CCLOG("%f",angle);
    */
    float distance=sqrt(pow((nowTouchPoint.x-tmpTouchPointCatched.x),2)+pow((nowTouchPoint.y-tmpTouchPointCatched.y),2));
    auto tmpdriverAngle = distance/3;
    if(tmpdriverAngle > 60.0){
        driverAngle=60.0;
    }else if(tmpdriverAngle <= 60.0 && tmpdriverAngle > 0){
        driverAngle=tmpdriverAngle;
    }else{
        driverAngle=0;
    }
    driverPointerSp->setRotation(-driverAngle);
    cannonGunSp->setRotation(-driverAngle);

};
void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent){
    
    //CCLOG("onTouchEnd");

};

void GameScene::loadCannon(){
    
    auto cannonBaseSp=Sprite::create("res/cannon_base.png");
    float scaleOfCannonBase=visibleSize.width/cannonBaseSp->getContentSize().width/12;
    cannonBaseSp->setScale(scaleOfCannonBase);
    cannonBaseSp->setPosition(cannonBaseSp->getContentSize().width/2*scaleOfCannonBase+10,50+cannonBaseSp->getContentSize().height/2*scaleOfCannonBase);
    cannonBaseSp->setVisible(false);
    this->addChild(cannonBaseSp,2);
    
    cannonGunSp=Sprite::create("res/cannon_gun.png");
    float scaleOfCannonGun=visibleSize.width/cannonBaseSp->getContentSize().width/12;
    cannonGunSp->setScale(scaleOfCannonGun);
    cannonGunSp->setAnchorPoint(ccp(0.5,0.5));
        cannonGunSp->setPosition(cannonBaseSp->getPosition().x+cannonBaseSp->getContentSize().width*scaleOfCannonBase/4,cannonBaseSp->getPosition().y+cannonBaseSp->getContentSize().height*scaleOfCannonBase/5);
    this->addChild(cannonGunSp,1);
    
    //创建DrawNode
    DrawNode* drawNode = DrawNode::create();
    this->addChild(drawNode,0);
    //圆点
    drawNode->drawDot(cannonGunSp->getPosition(),cannonGunSp->getBoundingBox().size.width/2, Color4F::RED);
    
    
    bombRadius=cannonGunSp->getBoundingBox().size.height*2/3;
    
};

void GameScene::loadDriver(){

    driverBgSp=Sprite::create("res/driverBg.png");
    float scaleOfDriverBg=visibleSize.width/driverBgSp->getContentSize().width/7;
    driverBgSp->setScale(scaleOfDriverBg);
    driverBgSp->setPosition(driverBgSp->getContentSize().width*scaleOfDriverBg/2+5,visibleSize.height-driverBgSp->getContentSize().height*scaleOfDriverBg/2-5);
    this->addChild(driverBgSp,3);
    
    auto fireBtn = Button::create("res/fire.png","res/fired.png");
    float scaleOfFireBtn=scaleOfDriverBg;
    fireBtn->setScale(scaleOfFireBtn);
    fireBtn->setPosition(driverBgSp->getPosition());
    this->addChild(fireBtn,5);
    fireBtn->addClickEventListener([=](Ref* sender){
        
        CCLOG("go to fire");
        //driverPointerSp->setRotation(0);
        //cannonGunSp->setRotation(0);
        
        //shoot the bomb;
        if(bombSp)bombSp->removeFromParent();
        bombSp=Sprite::create("res/bomb.png");
        float scaleOfBomb=bombRadius/bombSp->getContentSize().height;
        bombSp->setScale(scaleOfBomb);
        float c=cannonGunSp->getContentSize().width*cannonGunSp->getScale()/2+bombRadius/2;//boundingBox旋转后不一样
        auto py=c*sin(driverAngle*3.14/180);
        auto px=c*cos(driverAngle*3.14/180);
        bombSp->setPosition(cannonGunSp->getPosition().x+px,cannonGunSp->getPosition().y+py);
        bombSp->setTag(1000);
        this->addChild(bombSp,5);
        auto body = PhysicsBody::createCircle(bombSp->getBoundingBox().size.width/2);
        bombSp->setPhysicsBody(body);
        int velocity=300;
        bombSp->getPhysicsBody()->setVelocity(Vec2(velocity*cos(driverAngle*3.14/180), velocity*sin(driverAngle*3.14/180))); //给一个向上的初速度
    });
    
    driverPointerSp=Sprite::create("res/driverPointer.png");
    float scaleOfDriverPointer=scaleOfDriverBg;
    driverPointerSp->setScale(scaleOfDriverPointer);
    driverPointerSp->setAnchorPoint(ccp(0,0.5));
    driverPointerSp->setPosition(driverBgSp->getPosition());
    //driverPointerSp->setRotation(driverAngle);
    this->addChild(driverPointerSp,4);
    
};
