#ifndef PLAYERBULLET2_H
#define PLAYERBULLET2_H
#include"All.h"
#include<QRect>
#include<QImage>
#include <complex>
#include<cmath>
class PlayerBullet2
{
private:
    QImage MeImage;
    QRect MeRect;
    int type,HP;
    double Direction;
    bool Alive=false;
public:
    PlayerBullet2(){Alive=false;}
    QImage GetImage() const {return MeImage;}
    QRect GetRect() const {return MeRect;}
    void Init(QRect MeRect,double Drection,int type,int HP);
    ~PlayerBullet2(){};
    void PlayerBullet2_Move(int step);
    bool GetAlive(){return Alive;}
    void Hit();
    void PlayerBullet2_Dead(){this->Alive=false;MeRect.setRect(-1000,-1000,10,10);}
};

#endif
