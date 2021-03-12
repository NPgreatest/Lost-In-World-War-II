#include "RedZone.h"
#include<QDebug>

void RedZone::Flash(){
    flash++;
    if(flash>80)
    {flash=-1;
    Alive=false;
    }
}


RedZone::RedZone(){Alive=false;}
RedZone::RedZone(QRect MeRect,int r,int type){
     //this->MeRect=MeRect;
     this->r=r;
     this->type=type;
     this->Alive=true;
     this->MeRect.setRect(MeRect.x()-r,MeRect.y()-r,2*r,2*r);
}
RedZone::~RedZone(){}
bool RedZone::Object_Hit(QRect Rect){//物体与圆形区域碰撞
    if(this->CircleFunction(Rect.topLeft())
            ||this->CircleFunction(Rect.topRight())
            ||this->CircleFunction(Rect.bottomLeft())
            ||this->CircleFunction(Rect.bottomRight()))
        //检测是否碰撞
    return true;
    return false;
}

bool RedZone::CircleFunction(QPoint Point){//圆方程计算
    if((this->MeRect.center().x()-Point.x())*(this->MeRect.center().x()-Point.x())+
            (this->MeRect.center().y()-Point.y())*(this->MeRect.center().y()-Point.y())<=r*r){//检测是否碰撞
      return true;
    }else{
     return false;
    }
}
