#include"PlayerBullet1.h"
#include"All.h"
#include<QDebug>
PlayerBullet1::PlayerBullet1(){
    alive=false;head=UP;level=1;a.x=10;a.y=10;
    pos.x=-10000;pos.y=-10000;
       head=UP;
}
PlayerBullet1::~PlayerBullet1(){
 /*   qDebug()<<"子弹碰撞!";
   this->pos.x=-10000;this->pos.y=-10000;
   this->alive=false; count--;对于析构函数的使用错误
*/
}
void PlayerBullet1::PlayerBullet1_Dead(){
    this->pos.x=-10000;this->pos.y=-10000;
    this->alive=false;
}

void PlayerBullet1::Init(XY position,int lv,HEAD h){
    pos.x=position.x+25;    level=lv;     head=h;
      pos.y=position.y+25;
    alive=true;
    a.x=10;a.y=10;
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
    if(pos.x + a.x >= p.x && pos.x <= p.x + s.x && pos.y <= p.y + s.y && p.y <= pos.y + a.y){   //检测是否碰撞
        this->~PlayerBullet1();
        return true;
    }else{
        return false;
    }
}
