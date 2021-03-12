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
    Target target;
    int Damage;
    int master;
    int Speed;
    bool Alive=false;
public:
    PlayerBullet2(){Alive=false;}
    QImage GetImage() const {return MeImage;}
    QRect GetRect() const {return MeRect;}
    void Init(QRect const MeRect,
              double const Direction,
              int const type,
              int const Damage,
              Target const target,
              int const master,
              int const Speed,
              int const HP);
    ~PlayerBullet2(){};
    void PlayerBullet2_Move();
    bool GetAlive(){return Alive;}
    void Hit();
    void PlayerBullet2_Dead(){this->Alive=false;MeRect.setRect(-1000,-1000,10,10);}
    int GetType()const{return this->type;}
    int GetMaster() const {return master;}
    Target GetTarget() const {return target;}
    int GetDamage() const {return Damage;}
    void SetRect(QRect const Rect){this->MeRect=Rect;}
    int GetSpeed() const {return Speed;}
};

#endif
