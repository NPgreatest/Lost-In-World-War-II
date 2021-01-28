#ifndef PLAYERBULLET1_H
#define PLAYERBULLET1_H
#include"All.h"
class PlayerBullet1{
private:
    int level;
    XY a;
    HEAD head;
    XY pos;
    bool alive=false;
public:
    PlayerBullet1();
    ~PlayerBullet1();
    void Init(XY position,int lv,HEAD h);
    void PlayerBullet1_Move(int step);
    bool PlayerBullet1_Hit(XY p, XY s);
    XY GetPos(){return pos;}
    HEAD GetHead(){return head;}
    bool GetAlive(){return alive;}
    void PlayerBullet1_Dead();
};

#endif // PLAYERBULLET1_H
