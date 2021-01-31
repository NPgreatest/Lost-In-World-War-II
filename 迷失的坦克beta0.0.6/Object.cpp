#include "Object.h"
#include<QDebug>



void Object::Hit(){
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
    case 16:Alive=false;break;
    case 17:HP=-HP;break;
    default:break;
    }
}
Object::Object(){Alive=false;}
Object::Object(XY p,XY a,int type,int HP,int skin){
    if(a.x==0&&a.y==0){Alive=false;return;}
    this->pos=p;this->area=a;Alive=true;this->skin=skin;this->type=type;this->HP=HP;
    switch (type) {
    case 1:break;//house
    case 2:HP=1;break;//BedRock
    case 3:HP=1;break;//river
    case 4:HP=1;break;//portal
    case 5:other=10;break;//enemy response 1 -> can further setting
    case 6:HP=1;break;//first aid 1 -> can further setting
    case 7:HP=1;break;//Weapon Box 1 -> can further setting
    case 8:other=20;break;//enemy response 2 -> can further setting
    case 9:HP=1;break;//first aid 2 -> can further setting
    case 10:HP=1;break;//Weapon Box 2 -> can further setting
    case 11:other=30;break;//enemy response 3 -> can further setting
    case 12:HP=1;break;//first aid 3 -> can further setting
    case 13:HP=1;break;//Weapon Box 3 -> can further setting
    case 14:HP=0;break;//grass(can destroy)
    case 15:HP=1;break;//grass(can't destroy)
    case 16:HP=0;break;//nail
    case 17:HP=1;break;//ice
    default:Alive=false;return;
    }
    }
Object::~Object(){}
