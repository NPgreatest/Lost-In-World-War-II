#include "RedZone.h"
#include<QDebug>
void RedZone::Init(XY p,int r,int type)
{
pos=p;this->r=r;
this->type=type;
Alive=true;
MeImage.load(":/Images/Tank/RedZone1.png");
MeRect.setRect(p.x-r,p.y-r,2*r,2*r);
}
void RedZone::Flash(){
    flash++;
    switch (flash) {
    case 0:MeImage.load(":/Images/Tank/RedZone1.png");break;
    case 1:MeImage.load(":/Images/Tank/RedZone2.png");break;
    case 2:MeImage.load(":/Images/Tank/RedZone3.png");break;
    case 3:MeImage.load(":/Images/Tank/RedZone4.png");break;
    case 4:MeImage.load(":/Images/Tank/RedZone5.png");break;
    case 5:MeImage.load(":/Images/Tank/RedZone6.png");break;
    }
    if(flash>5){flash=-1;
    Alive=false;
    }
}

RedZone::RedZone(){Alive=false;}
RedZone::RedZone(XY p,int r,int type){
     pos=p;this->r=r;
     this->type=type;
     Alive=true;
     MeImage.load(":/Images/Tank/RedZone1.png");
     MeRect.setRect(p.x-r,p.y-r,2*r,2*r);
}
RedZone::~RedZone(){}
bool RedZone::Object_Hit(XY p,XY s){//物体与圆形区域碰撞
    XY t1,t2,t3,t4;
    t1=p;
    t2.x=p.x+s.x;t2.y=p.y;
    t3.x=p.x;t3.y=p.y+s.y;
    t4.x=p.x+s.x;t4.y=p.y+s.y;
    if(this->CircleFunction(t1)==true||this->CircleFunction(t2)==true||this->CircleFunction(t3)==true||this->CircleFunction(t4)==true){   //检测是否碰撞
        return true;
    }else{
        return false;
    }
}

bool RedZone::CircleFunction(XY p){//圆方程计算
    if((p.x-pos.x)*(p.x-pos.x)+(p.y-pos.y)*(p.y-pos.y)<=r*r){//检测是否碰撞
      return true;
    }else{
     return false;
    }
}
