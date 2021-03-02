#include "Player.h"
#include <QMessageBox>
Player::Player(XY p,int hp,int mp,int WeaponLv,int Material,int B1Count)
{
    pos=p;HP=hp;MP=mp;
    a.x=40;a.y=40;
    this->WeaponLv=WeaponLv;this->Material=Material;this->B1Count=B1Count;
    WeaponLv=1;Material=0;B1Count=2;head=UP;
    MeImage.load(":/Images/Tank/TankUp.png");
    MeRect.setRect(pos.x,pos.y,a.x,a.y);
}
Player::Player()
{
    pos.x=0;pos.y=0;HP=100;MP=100;
    a.x=50;a.y=50;speed=2;
    WeaponLv=1;Material=0;B1Count=2;head=UP;
}
void Player::Player_Move(int step){
   if(slow&&step!=-1)step+=2;
    switch (head){
        case UP:pos.y-=step;break;
        case DOWN:pos.y+=step;break;
        case LEFT:pos.x-=step;break;
        case RIGHT:pos.x+=step;break;
            }
    MeRect.setRect(pos.x,pos.y,a.x,a.y);
    this->UpdateIm(this->head);
}
void Player::UpdateIm(HEAD head){
    if(slow)
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
void Player::Player_UnderAttack(int damage){
    HP-=damage;
}

bool Player::Player_B1Fire(){
int i;
if(MP<=0){MP=0;return false;}
for(i=0;i<Edit_Max;i++){
if(!B1[i].GetAlive()){
    B1[i].Init(this->pos+15,WeaponLv,head);
    this->MP-=1;
    return true;
}
}
return false;
}
bool Player::Player_B2Fire(){
if(B2.GetAlive()==true)return true;
    B2.Init(this->pos+15,WeaponLv,head);
return false;
}
bool Player::Player_B3Fire(){
if(B3.GetAlive()==true)return false;
XY a=pos,b={50,100},d={-50,50},e={100,50},f={100,150},g={50,-50};
switch (this->head) {
case UP:{B3.Init(a-b,XY(150,100),10);break;}
case DOWN:{B3.Init(a+d,XY(150,100),10);break;}
case LEFT:{B3.Init(a-e,XY(100,150),10);break;}
case RIGHT:{B3.Init(a+g,XY(100,150),10);break;}
}

return true;
}


void Player::Strengthen(int HP,int MP,int WeaponLv,int Material,int speed,int B1Count){
    this->Material+=Material;
    this->HP+=HP;
    this->MP+=MP;
    this->speed+=speed;
    this->WeaponLv+=WeaponLv;
    this->B1Count+=B1Count;
    if(B1Count<1){B1Count=1;return;}
    if(B1Count>=10){B1Count=10;return;}
}
bool Player::Player_Hit(XY p,XY s){
    if(pos.x + a.x > p.x && pos.x < p.x + s.x && pos.y < p.y + s.y && p.y < pos.y + a.y){   //检测是否碰撞
        return true;
    }else{
        return false;
    }
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
