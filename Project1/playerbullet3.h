#ifndef PLAYERBULLET3_H
#define PLAYERBULLET3_H
#include"All.h"

class PlayerBullet3
{
private:
    int flash=0;
    XY area;
    XY pos;
    bool Alive=false;
public:
    void Init(XY position,XY area);
    PlayerBullet3(){Alive=false;};
    ~PlayerBullet3(){};
    bool PlayerBullet3_Hit(XY p, XY s);
    XY GetPos(){return pos;}
    XY GetArea(){return area;}
    bool GetAlive(){return Alive;}
    void PlayerBullet3_Dead(){this->Alive=false;pos.x=-1000;pos.y=-1000;flash=0;}
    int GetFlash(){return flash;}
    void Flash();
};

#endif // PLAYERBULLET3_H
