#include "Enemy.h"
#include<QRandomGenerator>
#include "Enemy.h"
#include <QMessageBox>
#include<QtDebug>
Enemy::Enemy(XY p,XY area,int hp,int mp)
{
    pos=p;HP=hp;MP=mp;a=area;
    a.x=50;a.y=50;B1Speed=10;speed=5;
    WeapenLv=1;Material=0;head=UP;alive=true;
}
Enemy::Enemy()
{
    pos.x=0;pos.y=0;HP=100;MP=100;
    a.x=50;a.y=50;speed=5;B1Speed=10;
    WeapenLv=1;Material=0;head=UP;alive=false;
}
void Enemy::Enemy_Move(int step){
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
        pos.x=-10000;
        pos.y=-10000;
        a.x=1;a.y=1;
    }
}

void Enemy::Enemy_B1Fire(){
int i;
for(i=0;i<5;i++){
if(B1[i].GetAlive()==false){
    B1[i].Init(pos,WeapenLv,head);
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
