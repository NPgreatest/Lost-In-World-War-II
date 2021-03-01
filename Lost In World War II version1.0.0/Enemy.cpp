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
    switch (skin) {
    case 1:MeImage.load(":/Images/Tank/EnemyUp_1.png");break;
    case 2:MeImage.load(":/Images/Tank/EnemyUp_2.png");break;
    case 3:MeImage.load(":/Images/Tank/EnemyUp_3.png");break;
    case 4:MeImage.load(":/Images/Tank/EnemyUp_4.png");break;
    case 5:MeImage.load(":/Images/Tank/EnemyUp_5.png");break;
    }
}
Enemy::Enemy()
{
    pos.x=0;pos.y=0;HP=100;skin=1;
    a.x=50;a.y=50;speed=5;B1Speed=10;
    head=UP;alive=false;
}
void Enemy::Me_ChangeHead(HEAD head){
    this->head=head;
    switch (head) {
    case UP:
        switch (this->skin) {
        case 1:MeImage.load(":/Images/Tank/EnemyUp_1.png");break;
        case 2:MeImage.load(":/Images/Tank/EnemyUp_2.png");break;
        case 3:MeImage.load(":/Images/Tank/EnemyUp_3.png");break;
        case 4:MeImage.load(":/Images/Tank/EnemyUp_4.png");break;
        case 5:MeImage.load(":/Images/Tank/EnemyUp_5.png");break;
        }break;
    case DOWN:
        switch (this->skin) {
        case 1:MeImage.load(":/Images/Tank/EnemyDown_1.png");break;
        case 2:MeImage.load(":/Images/Tank/EnemyDown_2.png");break;
        case 3:MeImage.load(":/Images/Tank/EnemyDown_3.png");break;
        case 4:MeImage.load(":/Images/Tank/EnemyDown_4.png");break;
        case 5:MeImage.load(":/Images/Tank/EnemyDown_5.png");break;
        }break;
    case LEFT:
        switch (this->skin) {
        case 1:MeImage.load(":/Images/Tank/EnemyLeft_1.png");break;
        case 2:MeImage.load(":/Images/Tank/EnemyLeft_2.png");break;
        case 3:MeImage.load(":/Images/Tank/EnemyLeft_3.png");break;
        case 4:MeImage.load(":/Images/Tank/EnemyLeft_4.png");break;
        case 5:MeImage.load(":/Images/Tank/EnemyLeft_5.png");break;
        }break;
    case RIGHT:
        switch (this->skin) {
        case 1:MeImage.load(":/Images/Tank/EnemyRight_1.png");break;
        case 2:MeImage.load(":/Images/Tank/EnemyRight_2.png");break;
        case 3:MeImage.load(":/Images/Tank/EnemyRight_3.png");break;
        case 4:MeImage.load(":/Images/Tank/EnemyRight_4.png");break;
        case 5:MeImage.load(":/Images/Tank/EnemyRight_5.png");break;
        }break;
    }
}
void Enemy::Enemy_Move(int step){
    if(this->slow==true&&step>0){step+=5;}
    switch (head){
        case UP:pos.y-=step;break;
        case DOWN:pos.y+=step;break;
        case LEFT:pos.x-=step;break;
        case RIGHT:pos.x+=step;break;
            }
    MeRect.setRect(this->pos.x,this->pos.y,this->a.x,this->a.y);
}
void Enemy::Enemy_RndChangeHead(){
    int x = QRandomGenerator::global()->generate();
    switch (x%4) {
    case UP:this->Me_ChangeHead(UP);break;
    case DOWN:this->Me_ChangeHead(DOWN);break;
    case LEFT:this->Me_ChangeHead(LEFT);break;
    case RIGHT:this->Me_ChangeHead(RIGHT);break;
    }
}
Enemy::~Enemy(){};
void Enemy::Enemy_ChangeHead(int dire){
    switch (dire){
        case 0:this->Me_ChangeHead(UP);break;
        case 1:this->Me_ChangeHead(DOWN);break;
        case 2:this->Me_ChangeHead(LEFT);break;
        case 3:this->Me_ChangeHead(RIGHT);break;
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
