

#ifndef CombatCtrlLayer_h
#define CombatCtrlLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PhysicLayer.h"
#include "Constant.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class CombatCtrlLayer : public cocos2d::Layer
{
    
public:
  
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(CombatCtrlLayer);
    Button* pauseBtn;
    Button* resetBtn;
    Button* backBtn;
    Button* forwardBtn;
    Button* backwardBtn;
    Vec2 origin;
    CCSize visibleSize;
    float newAngle;

    
    std::vector<Button*> btnVector;
    void shellSelect(Ref* pSender,int btnNum);
    int _shellNumSelected;
    Sprite* stageProcess;
    Label* processLabel;
    
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    
    CCPoint tmpTouchPointCatched;
    
    PhysicLayer* _physicLayer;
 
    
    int _waveNum;
    int _stageNum;
    
    void setStageNum(int stageNum);
    void loadWaveProcess();

};

#endif /* CombatCtrlLayer_h */
