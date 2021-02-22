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
   if(slow==true&&step!=-1)step+=2;
    switch (head){
        case UP:pos.y-=step;break;
        case DOWN:pos.y+=step;break;
        case LEFT:pos.x-=step;break;
        case RIGHT:pos.x+=step;break;
            }
    MeRect.setRect(pos.x,pos.y,a.x,a.y);

}
void Player::Player_ChangeHead(int dire){
    switch (dire){
        case 0:head=UP;MeImage.load(":/Images/Tank/TankUp.png");break;
        case 1:head=DOWN;MeImage.load(":/Images/Tank/TankDown.png");break;
        case 2:head=LEFT;MeImage.load(":/Images/Tank/TankLeft.png");break;
        case 3:head=RIGHT;MeImage.load(":/Images/Tank/TankRight.png");break;
            }
}
void Player::Player_UnderAttack(int damage){
    HP-=damage;
}
bool Player::Player_Dead(){
    if(HP<0){dead=true;return true;}
    else {dead=false;return false;}
}

bool Player::Player_B1Fire(){
int i;
XY t1=this->pos,t2={15,15};
if(MP<=0){MP=0;return false;}
for(i=0;i<B1Count;i++){
if(B1[i].GetAlive()==false){
    B1[i].Init(t1+t2,WeaponLv,head);
   this->MP-=1;
    return true;
}
}
}
bool Player::Player_B2Fire(){
    if(MP<=0){MP=0;return false;}
if(B2.GetAlive()==true)return true;
    B2.Init(pos,WeaponLv,head);
return true;
}
bool Player::Player_B3Fire(){
if(B3.GetAlive()==true)return false;
XY a=pos,b={50,100},c={150,100},d={-50,50},e={100,50},f={100,150},g={50,-50};
switch (this->head) {
case UP:{B3.Init(a-b,c);break;}
case DOWN:{B3.Init(a+d,c);break;}
case LEFT:{B3.Init(a-e,f);break;}
case RIGHT:{B3.Init(a+g,f);break;}
}

return true;
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
        B2.PlayerBullet2_Move(10);
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
