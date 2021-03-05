#ifndef PLAYERBULLET1_H
#define PLAYERBULLET1_H
#include"All.h"
#include<QRect>
#include<QImage>
class PlayerBullet1{
private:
    int type;
    HEAD head;
    QImage MeImage;
    QRect MeRect;
    bool Alive=false;
public:
    PlayerBullet1();
    ~PlayerBullet1(){}
    QImage GetImage() const {return MeImage;}
    QRect GetRect() const {return MeRect;}
    void Init(QRect const MeRect,HEAD const h,int const type);
    void PlayerBullet1_Move(int step);
    HEAD GetHead() const {return head;}
    bool GetAlive() const {return Alive;}
    void PlayerBullet1_Dead(){this->Alive=false;MeRect.setRect(-1000,-1000,10,10);}
};

#endif // PLAYERBULLET1_H
