#include "PlayerBullet2.h"

void PlayerBullet2::Init(QRect MeRect,double Direction,int type,int HP){
    this->Alive=true;
    this->MeRect=MeRect;
    this->Direction=Direction;
    this->type=type;
    this->HP=HP;
    switch (type) {
    case 1:MeImage.load(":/Images/Tank/Shot.png");break;
    case 2:MeImage.load(":/Images/Tank/Shot2.png");break;
    case 3:MeImage.load(":/Images/Tank/Shot3.png");break;
    case 4:MeImage.load(":/Images/Tank/Shot4.png");break;
    default:MeImage.load(":/Images/Tank/Shot.png");break;
    }
}

void PlayerBullet2::PlayerBullet2_Move(int step){
    if(!Alive)   return;
    double temp=step;
    this->MeRect.adjust(temp*sin(this->Direction),
                        temp*cos(this->Direction),
                        temp*sin(this->Direction),
                        temp*cos(this->Direction));
    if(MeRect.x()>X_Max||MeRect.x()<0||MeRect.y()<0||MeRect.y()>Y_Max)
    this->PlayerBullet2_Dead();
}

void PlayerBullet2::Hit(){
    HP--;
    if(HP<0){
        this->PlayerBullet2_Dead();
    }
}
