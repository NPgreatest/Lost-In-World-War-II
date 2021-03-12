#include "Player.h"
#include<QtDebug>
Player::Player(QRect MeRect,int HP,int WeaponLv)
{
    this->HP=HP;
    this->MP=0;
    this->MeRect=MeRect;
    this->WeaponLv=WeaponLv;
    this->WeaponLv=WeaponLv;
    this->head=HEAD::NO;
    this->speed=3;
    this->Choose=0;
    this->Activate=true;
    this->MeImage.load(":/Images/Tank/TankUp.png");
}
Player::Player()
{
    this->Activate=false;
    this->HP=0;
    this->MP=0;
    this->MeRect.setRect(-100,-100,10,10);
    this->WeaponLv=1;
    this->WeaponLv=1;
    this->Choose=0;
    this->head=HEAD::NO;
    this->MeImage.load(":/Images/Tank/TankUp.png");
}
void Player::Player_Move(int step){
   if( (this->Choose==1||slow) && step!=-1)step+=2;
    switch (head){
        case UP:MeRect.adjust(0,-step,0,-step);break;
        case DOWN:MeRect.adjust(0,step,0,step);break;
        case LEFT:MeRect.adjust(-step,0,-step,0);break;
        case RIGHT:MeRect.adjust(step,0,step,0);break;
        case NO:break;
            }
    this->UpdateIm(this->head);
}
void Player::UpdateIm(HEAD head){
    if(slow||this->Choose==1)
    switch (head){
        case UP:MeImage.load(":/Images/Tank/TankUp_2.png");break;
        case DOWN:MeImage.load(":/Images/Tank/TankDown_2.png");break;
        case LEFT:MeImage.load(":/Images/Tank/TankLeft_2.png");break;
        case RIGHT:MeImage.load(":/Images/Tank/TankRight_2.png");break;
            }
    else
     switch (head){
        case UP:MeImage.load(":/Images/Tank/TankUp.png");break;
        case DOWN:MeImage.load(":/Images/Tank/TankDown.png");break;
        case LEFT:MeImage.load(":/Images/Tank/TankLeft.png");break;
        case RIGHT:MeImage.load(":/Images/Tank/TankRight.png");break;
             }
}
void Player::Player_ChangeHead(int dire){
    switch (dire){
        case 0:head=UP;this->UpdateIm(this->head);break;
        case 1:head=DOWN;this->UpdateIm(this->head);break;
        case 2:head=LEFT;this->UpdateIm(this->head);break;
        case 3:head=RIGHT;this->UpdateIm(this->head);break;
            }
}


bool Player::Player_B1Fire(){
    return true;//无限子弹
    if(MP<10)
        return false;
    this->MP-=10;
    return true;
}
bool Player::Player_B2Fire(){

        return true;
}
bool Player::Player_B3Fire(){
    if(B3.GetAlive()==true) return false;
    QRect temp;
    temp=MeRect;
    switch (this->head) {
        case UP:temp.adjust(-50,-100,60,-40);B3.Init(temp,10);break;
        case DOWN:temp.adjust(-50,40,60,100);B3.Init(temp,10);break;
        case LEFT:temp.adjust(-100,-50,-40,60);B3.Init(temp,10);break;
        case RIGHT:temp.adjust(40,-50,110,60);B3.Init(temp,10);break;
    }
    return true;
}


void Player::Strengthen(int HP,int MP,int WeaponLv,int speed){
    this->HP+=HP;
    this->MP+=MP;
    this->speed+=speed;
    this->WeaponLv+=WeaponLv;
}

int Player::Damage(SkillName skillname){
    switch (skillname) {
    case SkillName::MainWeapon:
        switch (this->WeaponLv) {
        case 1:return 6;
        case 2:return 11;
        case 3:return 16;
        case 4:return 25;
        case 5:return 30;
        default:return 99999;
        }
        break;
    case SkillName::SubWeapon:
        switch (this->WeaponLv) {
        case 1:return 2;
        case 2:return 5;
        case 3:return 10;
        case 4:return 15;
        case 5:return 20;
        default:return 99999;
        }
        break;
    case SkillName::Fire:
        switch (this->WeaponLv) {
        case 1:return 1;
        case 2:return 3;
        case 3:return 5;
        case 4:return 10;
        case 5:return 15;
        default:return 99999;
        }
        break;
    }
}
