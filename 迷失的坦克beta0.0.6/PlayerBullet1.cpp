#include"PlayerBullet1.h"
#include"All.h"
#include<QDebug>
PlayerBullet1::PlayerBullet1(){
    alive=false;head=UP;level=1;area.x=10;area.y=10;
    pos.x=-10000;pos.y=-10000;
       head=UP;
}
PlayerBullet1::~PlayerBullet1(){
}

void PlayerBullet1::Init(XY position,int lv,HEAD h){
    pos.x=position.x+25;    level=lv;     head=h;
      pos.y=position.y+25;
    alive=true;
    area.x=10;area.y=10;
}
void PlayerBullet1::PlayerBullet1_Move(int step){
    if(alive==false)   return;
    switch (head){
        case UP:pos.y-=step;goto a;
        case DOWN:pos.y+=step;goto a;
        case LEFT:pos.x-=step;goto a;
        case RIGHT:pos.x+=step;goto a;
            }
    a:    if(pos.x>X_Max||pos.x<0||pos.y<0||pos.y>Y_Max)
        this->PlayerBullet1_Dead();
}
bool PlayerBullet1::PlayerBullet1_Hit(XY p,XY s){
    if(pos.x + area.x >= p.x && pos.x <= p.x + s.x && pos.y <= p.y + s.y && p.y <= pos.y + area.y){   //检测是否碰撞
        this->~PlayerBullet1();
        return true;
    }else{
        return false;
    }
}
