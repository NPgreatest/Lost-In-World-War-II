#include "Object.h"
#include<QDebug>
void Object::Init(XY p,XY a,int type)
{
if(a.x==0&&a.y==0&&type==0)return;
pos=p;this->a=a;
switch (type) {
case 1:this->type=type;HP=1;break;
case 2:this->type=type;HP=1;break;
case 3:this->type=type;HP=1;break;
case 5:this->type=type;HP=10;break;
case 6:this->type=type;HP=1;break;
case 7:this->type=type;HP=1;break;
//case 8:this->type=type;HP=1;break;
default:break;
}
Alive=true;
}
void Object::Flash(){
    flash++;
    if(flash>5)flash=-1;
}

void Object::Hit(){
    switch (this->type) {
    case 1:HP--;
        if(HP<0){
            Alive=false;
            pos.x=-10000;
            pos.y=-10000;
            a.x=1;a.y=1;
       }break;
    case 2:HP=-HP;break;
    case 3:HP=-HP;break;
    case 5:HP--;
        if(HP<0){
            Alive=false;type=0;break;
       }break;
    case 6:
        Alive=false;
        pos.x=-10000;
        pos.y=-10000;
        a.x=1;a.y=1;break;
    case 7:
        Alive=false;
        pos.x=-10000;
        pos.y=-10000;
        a.x=1;a.y=1;break;
    default:break;
    }
}
Object::Object(){Alive=false;}
Object::Object(XY p,XY a,int type){
    if(a.x==0&&a.y==0&&type==0){pos.x=-10000;pos.y=-10000;a.x=1;a.y=1;Alive=false;return;}
    this->pos=p;this->a=a;
    switch (type) {
    case 1:this->type=type;HP=1;break;
    case 2:this->type=type;HP=1;break;
    case 3:this->type=type;HP=1;break;
    case 5:this->type=type;HP=10;break;
    case 6:this->type=type;HP=1;break;
    case 7:this->type=type;HP=1;break;
    }
    Alive=true;}
Object::~Object(){}
