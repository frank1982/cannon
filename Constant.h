

#ifndef Constant_h
#define Constant_h


const float MIN_ANGLE=0;
const float MAX_ANGLE=60;
const int MAX_WAVE_NUM[8]={4,8,8,8,12,12,16,16};


const enum MonsterStatus
{
    NORMAL,DEAD,ONHIT
};
enum MonsterType
{
    PIRATE,
};
enum ShellType
{
    nut,Wood,
};
enum ShellDamageType
{
    SCOPE,POINT,LINE,
};
enum CannonStatus{
    
    readyForLoadShell,
    loadingShell,//正在装填炮弹，防止重复装填;
    readyForFire,
    coldingDown
};

#endif /* Constant_h */
