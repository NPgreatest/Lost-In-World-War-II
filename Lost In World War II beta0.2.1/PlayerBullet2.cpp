#include "PlayerBullet2.h"
PlayerBullet2::PlayerBullet2(XY position,int lv,HEAD h){
    pos.x=position.x+25;    level=lv;     head=h;
      pos.y=position.y+25;
    Alive=true;
    area.x=10;area.y=10;
}
void PlayerBullet2::Init(XY position,int lv,HEAD h){
    pos.x=position.x+25;    level=lv;     head=h;
      pos.y=position.y+25;
    Alive=true;
    area.x=10;area.y=10;
}

void PlayerBullet2::PlayerBullet2_Move(int step){
    if(Alive==false)   return;
    switch (head){
        case UP:pos.y-=step;distance+=step;goto a;
        case DOWN:pos.y+=step;distance+=step;goto a;
        case LEFT:pos.x-=step;distance+=step;goto a;
        case RIGHT:pos.x+=step;distance+=step;goto a;
            }
    a:    if(distance>200)
        this->PlayerBullet2_Dead();
}
bool PlayerBullet2::PlayerBullet2_Hit(XY p,XY s){
    if(pos.x + area.x >= p.x && pos.x <= p.x + s.x && pos.y <= p.y + s.y && p.y <= pos.y + area.y){   //检测是否碰撞
        this->pos.x=-100;this->pos.y=-100;
        return true;
    }else{
        return false;
    }
}
