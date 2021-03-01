#include "playerbullet3.h"
#include<QDebug>
bool PlayerBullet3::PlayerBullet3_Hit(XY p,XY s){
    if(pos.x + area.x >= p.x && pos.x <= p.x + s.x && pos.y <= p.y + s.y && p.y <= pos.y + area.y){   //检测是否碰撞
        return true;
    }else{
        return false;
    }
}
void PlayerBullet3::Init(XY position,XY area,int flash_max){
    this->pos=position;this->area=area;
    Alive=true;flash=1;
    this->flash_max=flash_max;
}
void PlayerBullet3::Flash(){
//    qDebug()<<this->flash;
    if(flash!=0)
        flash++;
    if(flash>=this->flash_max){
        flash=0;
        Alive=false;
    }
}
