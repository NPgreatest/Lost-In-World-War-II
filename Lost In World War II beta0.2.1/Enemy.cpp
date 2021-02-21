#include "Enemy.h"
#include<QRandomGenerator>
#include "Enemy.h"
#include <QMessageBox>
#include<QtDebug>
Enemy::Enemy(XY p,XY area,int hp,int speed,int bullet_speed,int skin)
{
    this->pos=p;HP=hp;this->a=area;this->skin=skin;
    B1Speed=bullet_speed;this->speed=speed;
    head=UP;alive=true;
}
Enemy::Enemy()
{
    pos.x=0;pos.y=0;HP=100;skin=1;
    a.x=50;a.y=50;speed=5;B1Speed=10;
    head=UP;alive=false;
}
void Enemy::Enemy_Move(int step){
    if(this->slow==true&&step>0){step+=5;}
    switch (head){
        case UP:pos.y-=step;break;
        case DOWN:pos.y+=step;break;
        case LEFT:pos.x-=step;break;
        case RIGHT:pos.x+=step;break;
            }
}
void Enemy::Enemy_RndChangeHead(){
    int x = QRandomGenerator::global()->generate();
    switch (x%4) {
    case 0:head=UP;break;
    case 1:head=DOWN;break;
    case 2:head=LEFT;break;
    case 3:head=RIGHT;break;
    }
}
Enemy::~Enemy(){};
void Enemy::Enemy_ChangeHead(int dire){
    switch (dire){
        case 0:head=UP;break;
        case 1:head=DOWN;break;
        case 2:head=LEFT;break;
        case 3:head=RIGHT;break;
            }
}
void Enemy::Enemy_UnderAttack(int damage){
    HP-=damage;
    if(HP<0){
        alive=false;
    }
}

void Enemy::Enemy_B1Fire(){
int i;
XY t1=this->pos,t2=this->a;
t1.x+=t2.x/2-5;
t1.y+=t2.y/2-5;
for(i=0;i<5;i++){
if(B1[i].GetAlive()==false){
    B1[i].Init(t1,1,head);
    return;
}
}

}
void Enemy::Enemy_B1_Move(){
    if(this->GetAlive()==false)return;
    int i;
    for(i=0;i<5;i++){
        if(B1[i].GetAlive()==true){
        B1[i].PlayerBullet1_Move(B1Speed);
        }
    }
}
bool Enemy::Enemy_Hit(XY p,XY s){
    if(pos.x + a.x > p.x && pos.x < p.x + s.x && pos.y < p.y + s.y && p.y < pos.y + a.y){   //检测是否碰撞
        return true;
    }else{
        return false;
    }
}
