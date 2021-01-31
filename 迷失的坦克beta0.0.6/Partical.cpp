#include "Partical.h"

Partical::Partical()
{
    Alive=false;flash=0;
}
Partical::Partical(XY pos,XY area,int flash_max,int type){
    this->pos=pos;this->area=area;this->flash_max=flash_max;this->type=type;
    Alive=true;
}
void Partical::FLash(){
    flash++;
    if(flash>=flash_max)
     this->Dead();
}
