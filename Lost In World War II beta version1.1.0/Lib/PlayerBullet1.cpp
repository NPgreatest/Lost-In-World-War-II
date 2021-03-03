#include"PlayerBullet1.h"
#include"All.h"
#include<QDebug>
PlayerBullet1::PlayerBullet1(){
    this->Alive=false;
    head=HEAD::UP;
    this->MeRect.setRect(-1000,-1000,10,10);
}

void PlayerBullet1::Init(QRect MeRect,HEAD h,int type){
    this->head=h;
    this->Alive=true;
    this->MeRect=MeRect;
    switch (type) {
    case 1:MeImage.load(":/Images/Tank/Shot.png");break;
    case 2:MeImage.load(":/Images/Tank/Shot2.png");break;
    case 3:MeImage.load(":/Images/Tank/Shot3.png");break;
    case 4:MeImage.load(":/Images/Tank/Shot4.png");break;
    default:MeImage.load(":/Images/Tank/Shot.png");break;
    }
}
void PlayerBullet1::PlayerBullet1_Move(int step){
    if(!Alive)  return;
    switch (head){
        case UP:this->MeRect.adjust(0,-step,0,-step);break;
        case DOWN:this->MeRect.adjust(0,step,0,step);break;
        case LEFT:this->MeRect.adjust(-step,0,-step,0);break;
        case RIGHT:this->MeRect.adjust(step,0,step,0);break;
            }
        if(MeRect.x()>X_Max||MeRect.x()<0||MeRect.y()<0||MeRect.y()>Y_Max)
        this->PlayerBullet1_Dead();
}
