#include "Player.h"
#include <QMessageBox>
Player::Player(XY p,int hp,int mp,int WeaponLv,int Material,int B1Count)
{
    pos=p;HP=hp;MP=mp;
    a.x=50;a.y=50;
    this->WeaponLv=WeaponLv;this->Material=Material;this->B1Count=B1Count;
    WeaponLv=1;Material=0;B1Count=2;head=UP;
}
Player::Player()
{
    pos.x=0;pos.y=0;HP=100;MP=100;
    a.x=50;a.y=50;speed=2;
    WeaponLv=1;Material=0;B1Count=2;head=UP;
}
void Player::Player_Move(int step){
   if(slow==true&&step!=-1)step+=2;
    switch (head){
        case UP:pos.y-=step;break;
        case DOWN:pos.y+=step;break;
        case LEFT:pos.x-=step;break;
        case RIGHT:pos.x+=step;break;
            }
}
void Player::Player_ChangeHead(int dire){
    switch (dire){
        case 0:head=UP;break;
        case 1:head=DOWN;break;
        case 2:head=LEFT;break;
        case 3:head=RIGHT;break;
            }
}
void Player::Player_UnderAttack(int damage){
    HP-=damage;
}
bool Player::Player_Dead(){
    if(HP<0){dead=true;return true;}
    else {dead=false;return false;}
}

void Player::Player_B1Fire(){
int i;
for(i=0;i<B1Count;i++){
if(B1[i].GetAlive()==false){
    B1[i].Init(pos,WeaponLv,head);
   return;
}
}
}
void Player::Player_B2Fire(){
int i;
for(i=0;i<Edit_Min;i++){
if(B2[i].GetAlive()==true)continue;
    B2[i].Init(pos,WeaponLv,head);
    break;
}
return;
}
void Player::Player_B1_Move(){
    int i;
    for(i=0;i<B1Count;i++){
        if(B1[i].GetAlive()==true){
        B1[i].PlayerBullet1_Move(10);
        }
    }
}
void Player::Player_B2_Move(){
    int i;
    for(i=0;i<Edit_Min;i++){
        if(B2[i].GetAlive()==false)continue;
        B2[i].PlayerBullet2_Move(10);
    }
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
