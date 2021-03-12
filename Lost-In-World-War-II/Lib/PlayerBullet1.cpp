#include"PlayerBullet1.h"
#include"All.h"
#include<QDebug>
PlayerBullet1::PlayerBullet1(){
    this->Alive=false;
    head=HEAD::UP;
    this->MeRect.setRect(-1000,-1000,10,10);
}

void PlayerBullet1::Init(QRect const MeRect,HEAD const h,int const type,int const Damage,Target target,int master,int Speed){
    this->head=h;
    this->Alive=true;
    this->MeRect=MeRect;
    this->type=type;
    this->Damage=Damage;
    this->target=target;
    this->master=master;
    this->Speed=Speed;
    switch (type) {
    case 1:MeImage.load(":/Images/Tank/Shot.png");break;
    case 2:MeImage.load(":/Images/Tank/Shot2.png");break;
    case 3:MeImage.load(":/Images/Tank/Shot3.png");break;
    case 4:MeImage.load(":/Images/Tank/Shot4.png");break;
    default:MeImage.load(":/Images/Tank/Shot.png");break;
    }
}
void PlayerBullet1::PlayerBullet1_Move(){
    if(!Alive)  return;
    switch (head){
        case UP:this->MeRect.adjust(0,-Speed,0,-Speed);break;
        case DOWN:this->MeRect.adjust(0,Speed,0,Speed);break;
        case LEFT:this->MeRect.adjust(-Speed,0,-Speed,0);break;
        case RIGHT:this->MeRect.adjust(Speed,0,Speed,0);break;
    default:break;
            }
        if(MeRect.x()>X_Max||MeRect.x()<-this->MeRect.width()-50||MeRect.y()<-this->MeRect.height()-50||MeRect.y()>Y_Max)
        this->PlayerBullet1_Dead();
}
