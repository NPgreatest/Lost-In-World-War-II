#include "playerbullet3.h"
#include<QDebug>

void PlayerBullet3::Init(QRect MeRect,int flash_max){
    this->MeRect=MeRect;
    this->Alive=true;
    this->flash=1;
    this->flash_max=flash_max;
}
void PlayerBullet3::Flash(){
    if(flash!=0)
        flash++;
    if(flash>=this->flash_max){
        flash=0;
        Alive=false;
    }
}
