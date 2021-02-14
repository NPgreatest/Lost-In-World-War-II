#ifndef PLAYERBULLET2_H
#define PLAYERBULLET2_H
#include"All.h"

class PlayerBullet2
{
private:
    int level,distance=0;
    XY area;
    HEAD head;
    XY pos;
    bool Alive=false;
public:
    PlayerBullet2(XY position,int lv,HEAD h);
    void Init(XY position,int lv,HEAD h);
    PlayerBullet2(){Alive=false;};
    ~PlayerBullet2(){};
    void PlayerBullet2_Move(int step);
    bool PlayerBullet2_Hit(XY p, XY s);
    XY GetPos(){return pos;}
    HEAD GetHead(){return head;}
    bool GetAlive(){return Alive;}
    void PlayerBullet2_Dead(){this->Alive=false;distance=0;pos.x=-1000;pos.y=-1000;}
};

#endif
