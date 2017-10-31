

#ifndef CombatCtrlLayer_h
#define CombatCtrlLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PhysicLayer.h"
#include "Constant.h"
#include "Shell.h"
#include "ShellOfNut.h"
#include <stdio.h>
#include "Pirate.h"
//#include "cocos/base/CCMap.h"

using namespace cocos2d::ui;
using namespace cocos2d;
using namespace std;

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
    
    //PhysicLayer* _physicLayer;
 
    
    int _waveNum;
    int _stageNum;
    
    void setStageNum(int stageNum);
    void loadWaveProcess();
    
    //生成炮弹并放置到甲板
    void createShells(float dt);
    void loadShell(int num,ShellType shellType);
    
    
    //用以下数据来完成炮弹类型的选择
    map<int,std::string> SHELL_MAP;//甲板上炮弹的类型
    map<int,Sprite*> SHELL_SP;//甲板上炮弹的精灵
    map<int,bool> SHELL_READY_FLAG;//甲板上炮弹是否装载完毕
    
    
    void shellLoadCallFunc(int num);
    bool CANLOADSHELL;
    bool LOADSHELLFINISH;//播放炮弹装载动画是否完毕？由ctrlLayer控制；
};

#endif /* CombatCtrlLayer_h */
