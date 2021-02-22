#include "Boss1.h"
#include<QRandomGenerator>
Boss1::Boss1(XY p,int hp,int skin)
{
this->pos=p;
 this->HP=hp;
    this->skin=skin;
    alive=true;
    this->head=UP;
MeImage.load(":/Images/Tank/BossUp.png");
MeRect.setRect(this->pos.x,this->pos.y,150,150);
}
void Boss1::Me_ChangeHead(HEAD head){
    this->head=head;
    switch (head) {
    case UP:
        MeImage.load(":/Images/Tank/BossUp.png");break;
    case DOWN:
        MeImage.load(":/Images/Tank/BossDown.png");break;
    case LEFT:
        MeImage.load(":/Images/Tank/BossLeft.png");break;
    case RIGHT:
        MeImage.load(":/Images/Tank/BossRight.png");break;
    }
}
void Boss1::Boss1_B3Fire(){
if(B3.GetAlive()==true)return;
XY t1=this->pos;XY t2=this->pos;
switch (this->head) {
case UP:t1.y=0;t2={150,this->pos.y};B3.Init(t1,t2);break;
case DOWN:t2={150,1000};B3.Init(t1,t2);break;
case LEFT:t1.x=0;t2={this->pos.x,150};B3.Init(t1,t2);break;
case RIGHT:t2={1000,150};B3.Init(t1,t2);break;
}
}
void Boss1::Boss1_Move(int step){
    switch (head){
        case UP:pos.y-=step;break;
        case DOWN:pos.y+=step;break;
        case LEFT:pos.x-=step;break;
        case RIGHT:pos.x+=step;break;
            }
    MeRect.setRect(this->pos.x,this->pos.y,150,150);
}
void Boss1::Boss1_RndChangeHead(){
    int x = QRandomGenerator::global()->generate();
    switch (x%4) {
    case 0:this->Me_ChangeHead(HEAD::UP);break;
    case 1:this->Me_ChangeHead(HEAD::DOWN);break;
    case 2:this->Me_ChangeHead(HEAD::LEFT);break;
    case 3:this->Me_ChangeHead(HEAD::RIGHT);break;
    }
}
void Boss1::Boss1_ChangeHead(int dire){
    switch (dire){
    case 0:this->Me_ChangeHead(HEAD::UP);break;
    case 1:this->Me_ChangeHead(HEAD::DOWN);break;
    case 2:this->Me_ChangeHead(HEAD::LEFT);break;
    case 3:this->Me_ChangeHead(HEAD::RIGHT);break;
            }
}
void Boss1::Boss1_UnderAttack(int damage){
    HP-=damage;
    if(HP<0){
        alive=false;
    }
}

void Boss1::Boss1_B1Fire(){
int i,k=0;
XY temp=this->pos;
for(i=0;i<Edit_Min;i++){
if(k>=5)return;
if(B1[i].GetAlive()==false){
    temp=this->pos;
    switch (this->head) {
    case UP:temp.x+=k*30;B1[i].Init(temp,1,head);k++;break;
    case DOWN:temp.y+=150;temp.x+=k*30;B1[i].Init(temp,1,head);k++;break;
    case LEFT:temp.y+=k*30;B1[i].Init(temp,1,head);k++;break;
    case RIGHT:temp.x+=150;temp.y+=k*30;B1[i].Init(temp,1,head);k++;break;
    }
        }
    }
}
void Boss1::Boss1_B1_Move(){
    if(this->GetAlive()==false)return;
    int i;
    for(i=0;i<Edit_Min;i++){
        if(B1[i].GetAlive()==true){
        B1[i].PlayerBullet1_Move(2);
        }
    }
}
bool Boss1::Boss1_Hit(XY p,XY s){
    if(pos.x + a.x > p.x && pos.x < p.x + s.x && pos.y < p.y + s.y && p.y < pos.y + a.y){   //检测是否碰撞
        return true;
    }else{
        return false;
    }
}

