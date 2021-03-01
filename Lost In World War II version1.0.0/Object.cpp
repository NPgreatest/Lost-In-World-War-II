#include "Object.h"
#include<QDebug>
Object::Object(XY p,XY a,int skin,int type){
    this->pos=p;
    this->area=a;
    this->skin=skin;
    this->type=type;
}

Wall::Wall(XY p,XY a,int skin,int HP):Object(p,a,skin,1){
    Alive=true;
    this->HP=HP;
    MeRect.setRect(pos.x,pos.y,area.x,area.y);
    switch (this->HP) {
    case 1:MeImage.load(":/Images/Object/Wall2.png");break;
    case 0:MeImage.load(":/Images/Object/Wall3.png");break;
    default:MeImage.load(":/Images/Object/Wall1.png");break;
    }
}
bool Wall::Hit(){
    HP--;
    if(HP==1)MeImage.load(":/Images/Object/Wall2.png");
    if(HP==0)MeImage.load(":/Images/Object/Wall3.png");
    if(HP<0){
        this->Alive=false;
    }
    return true;
}


BedRock::BedRock(XY p,XY a,int skin):Object(p,a,skin,2){
    Alive=true;
    this->flash=1;
    MeRect.setRect(pos.x,pos.y,area.x,area.y);
    MeImage.load(":/Images/Object/BedRock1.png");
}
void BedRock::Flash(){
    if(this->flash==-1){
    MeImage.load(":/Images/Object/BedRock1.png");
    this->flash=1;
    }
}
bool BedRock::Hit(){
    MeImage.load(":/Images/Object/BedRock2.png");
    this->flash=-1;
    return true;
}
River::River(XY p,XY a,int skin):Object(p,a,skin,3),flash(1){
    Alive=true;
    MeRect.setRect(pos.x,pos.y,area.x,area.y);
    MeImage.load(":/Images/Object/River1.jpg");
}
void River::Flash(){
    flash=-flash;
    if(flash==1){
        MeImage.load(":/Images/Object/River1.jpg");
    }else{
        MeImage.load(":/Images/Object/River2.jpg");
    }
}
Portal::Portal(XY p,XY a):Object(p,a,0,4),flash(1){
    MeRect.setRect(pos.x,pos.y,area.x,area.y);Alive=true;
    MeImage.load(":/Images/Object/Portal.png");
}
void Portal::Flash(){
    flash=-flash;
    if(flash==1){
        MeImage.load(":/Images/Object/Portal.png");
    }else{
        MeImage.load(":/Images/Object/Portal2.png");
    }
}
Camp::Camp(XY p,XY a,int skin,int HP):Object(p,a,skin,5){
    this->HP=HP;
    Alive=true;
    MeRect.setRect(pos.x,pos.y,area.x,area.y);
    switch (skin) {
    case 1:Remain=3;MeImage.load(":/Images/Object/Camp1.jpg");break;
    case 2:Remain=5;MeImage.load(":/Images/Object/Camp2.jpg");break;
    case 3:Remain=7;MeImage.load(":/Images/Object/Camp3.jpg");break;
    default:break;
    }
}

bool Camp::Hit(){
    this->HP--;
    if(HP<0){
        this->Dead();
    }
    return true;
}

void Camp::SetOther(){
    Remain--;
    if(Remain<=0){
        this->Dead();
    }
}
FirstAid::FirstAid(XY p,XY a,int skin):Object(p,a,skin,6){
    MeRect.setRect(pos.x,pos.y,area.x,area.y);Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/FirstAid1.png");break;
    case 2:MeImage.load(":/Images/Object/FirstAid2.png");break;
    case 3:MeImage.load(":/Images/Object/FirstAid3.png");break;
    default:break;
    }
}
Weapon::Weapon(XY p,XY a,int skin):Object(p,a,skin,7){
    MeRect.setRect(pos.x,pos.y,area.x,area.y);Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/Weapon1.png");break;
    case 2:MeImage.load(":/Images/Object/Weapon2.png");break;
    case 3:MeImage.load(":/Images/Object/Weapon3.png");break;
    default:break;
    }
}
Ruins::Ruins(XY p,XY a,int skin):Object(p,a,skin,8){
    MeRect.setRect(pos.x,pos.y,area.x,area.y);Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/Ruins1.png");break;
    case 2:MeImage.load(":/Images/Object/Ruins2.png");break;
    default:MeImage.load(":/Images/Object/Ruins2.png");break;
    }
}
Grass::Grass(XY p,XY a,int skin):Object(p,a,skin,9){
    MeRect.setRect(pos.x,pos.y,area.x,area.y);Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/Grass1.png");break;
    case 2:MeImage.load(":/Images/Object/Grass2.png");break;
    default:break;
    }
}
Nail::Nail(XY p,XY a):Object(p,a,1,10){
    this->Active=false;Alive=true;
    MeRect.setRect(pos.x,pos.y,area.x,area.y);
    MeImage.load(":/Images/Object/Nail1.png");
}

void Nail::Flash(){
    Active=!Active;
    if(Active==true){
        MeImage.load(":/Images/Object/Nail2.png");
    }else{
        MeImage.load(":/Images/Object/Nail1.png");
    }
}

Ice::Ice(XY p,XY a):Object(p,a,1,11){
    this->flash=1;Alive=true;
    MeRect.setRect(pos.x,pos.y,area.x,area.y);
    MeImage.load(":/Images/Object/Ice1.png");
}
void Ice::Flash(){
    flash=-flash;
    if(flash==1){
        MeImage.load(":/Images/Object/Ice1.png");
    }else{
        MeImage.load(":/Images/Object/Ice2.png");
    }return;
}
/*void Object::Hit(){
    switch (this->type) {
    case 1:HP--;if(HP<0)Alive=false;break;
    case 2:HP=-HP;break;
    case 3:HP=-HP;break;
    case 4:Alive=false;break;
    case 5:HP--;if(HP<0){Alive=false;type=0;}break;
    case 6:Alive=false;break;
    case 7:Alive=false;break;
    case 8:HP--;if(HP<0){Alive=false;type=0;}break;
    case 9:Alive=false;break;
    case 10:Alive=false;break;
    case 11:HP--;if(HP<0){Alive=false;type=0;}break;
    case 12:Alive=false;break;
    case 13:Alive=false;break;
    case 14:Alive=false;break;
    case 15:HP=-HP;break;
    case 16:HP=-HP;break;
    case 17:HP=-HP;break;
    default:break;
    }
}
Object::Object(){Alive=false;}
Object::Object(XY p,XY a,int type,int HP,int skin){
    if(a.x==0&&a.y==0){Alive=false;return;}
    this->pos=p;this->area=a;Alive=true;this->skin=skin;this->type=type;this->HP=HP;this->other=0;
    switch (type) {
    case 1:break;//house
    case 2:HP=1;break;//BedRock
    case 3:HP=1;break;//river
    case 4:HP=1;break;//portal
    case 5:other=0;break;//enemy response 1 -> can further setting
    case 6:HP=1;break;//first aid 1 -> can further setting
    case 7:HP=1;break;//Weapon Box 1 -> can further setting
    case 8:other=0;break;//enemy response 2 -> can further setting
    case 9:HP=1;break;//first aid 2 -> can further setting
    case 10:HP=1;break;//Weapon Box 2 -> can further setting
    case 11:other=0;break;//enemy response 3 -> can further setting
    case 12:HP=1;break;//first aid 3 -> can further setting
    case 13:HP=1;break;//Weapon Box 3 -> can further setting
    case 14:HP=0;break;//grass(can destroy)
    case 15:HP=1;break;//grass(can't destroy)
    case 16:HP=1;break;//nail
    case 17:HP=1;break;//ice
    default:Alive=false;return;
    }
    }
Object::~Object(){}/*/
