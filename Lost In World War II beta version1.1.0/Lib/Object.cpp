#include "Object.h"
#include<QDebug>
Object::Object(QRect MeRect,int skin,int type):skin(skin),type(type){
    this->MeRect=MeRect;
    this->Alive=true;
}

Wall::Wall(QRect MeRect,int skin,int HP):Object(MeRect,skin,1){
    Alive=true;
    this->HP=HP;
    MeImage.load(":/Images/Object/Wall1.png");
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


BedRock::BedRock(QRect MeRect,int skin):Object(MeRect,skin,2){
    Alive=true;
    this->flash=1;
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
River::River(QRect MeRect,int skin):Object(MeRect,skin,3),flash(1){
    Alive=true;
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
Portal::Portal(QRect MeRect):Object(MeRect,0,4),flash(1){
    Alive=true;
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
Camp::Camp(QRect MeRect,int skin,int HP):Object(MeRect,skin,5){
    this->HP=HP;
    Alive=true;
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
FirstAid::FirstAid(QRect MeRect,int skin):Object(MeRect,skin,6){
    Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/FirstAid1.png");break;
    case 2:MeImage.load(":/Images/Object/FirstAid2.png");break;
    case 3:MeImage.load(":/Images/Object/FirstAid3.png");break;
    default:break;
    }
}
Weapon::Weapon(QRect MeRect,int skin):Object(MeRect,skin,7){
    Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/Weapon1.png");break;
    case 2:MeImage.load(":/Images/Object/Weapon2.png");break;
    case 3:MeImage.load(":/Images/Object/Weapon3.png");break;
    default:break;
    }
}
Ruins::Ruins(QRect MeRect,int skin):Object(MeRect,skin,8){
    Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/Ruins1.png");break;
    case 2:MeImage.load(":/Images/Object/Ruins2.png");break;
    default:MeImage.load(":/Images/Object/Ruins2.png");break;
    }
}
Grass::Grass(QRect MeRect,int skin):Object(MeRect,skin,9){
    Alive=true;
    switch (skin) {
    case 1:MeImage.load(":/Images/Object/Grass1.png");break;
    case 2:MeImage.load(":/Images/Object/Grass2.png");break;
    default:break;
    }
}
Nail::Nail(QRect MeRect):Object(MeRect,1,10){
    this->Active=false;Alive=true;
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

Ice::Ice(QRect MeRect):Object(MeRect,1,11){
    this->flash=1;Alive=true;
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
