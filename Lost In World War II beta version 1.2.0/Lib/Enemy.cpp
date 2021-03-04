#include "Enemy.h"
#include<QRandomGenerator>
#include "Enemy.h"
#include <QMessageBox>
#include<QtDebug>
Enemy::Enemy(QRect MeRect,int hp,int speed,int bullet_speed,int skin)
{
    this->HP=hp;
    this->skin=skin;
    B1Speed=bullet_speed;
    this->speed=speed;
    head=UP;
    Alive=true;
    this->MeRect=MeRect;
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
    Alive=false;
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
        case UP:MeRect.adjust(0,-step,0,-step);break;
        case DOWN:MeRect.adjust(0,step,0,step);break;
        case LEFT:MeRect.adjust(-step,0,-step,0);break;
        case RIGHT:MeRect.adjust(step,0,step,0);break;
            }
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
        Alive=false;
    }
}

void Enemy::Enemy_B1Fire(){
    int i;
    QRect temp(MeRect.x()-10+MeRect.width()/2,MeRect.y()-10+MeRect.height()/2,30,30);

    for(i=0;i<5;i++){
    if(B1[i].GetAlive()==false){
        B1[i].Init(temp,this->head,QRandomGenerator::global()->bounded(1,4));
        return;
        }
    }
    return;
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
