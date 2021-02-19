#include "Partical.h"

Partical::Partical()
{
    Alive=false;flash=0;
}
Partical::Partical(XY p,XY a,Type type)
    :pos(p),area(a),type(type){
    Alive=true;
    flash=1;
    MeRect.setRect(pos.x,pos.y,area.x,area.y);
    switch (type) {
    case Object_Hit:MeImage.load(":/Images/Particals/Boom1.png");flash_max=6;break;
    case Player_B3:MeImage.load(":/Images/Particals/Shot3_1.png");flash_max=4;break;
    case Player_Damage:MeImage.load(":/Images/Particals/Damage1.png");flash_max=7;break;
    case Mist:MeImage.load(":/Images/Particals/Mist1.png");flash_max=5;break;
    }//6475
}
void Partical::FLash(){
    flash++;
    if(flash>=flash_max)
     this->Dead();
    switch (type) {
    case Object_Hit:
        switch (flash) {
        case 1:MeImage.load(":/Images/Particals/Boom1.png");break;
        case 2:MeImage.load(":/Images/Particals/Boom2.png");break;
        case 3:MeImage.load(":/Images/Particals/Boom3.png");break;
        case 4:MeImage.load(":/Images/Particals/Boom4.png");break;
        case 5:MeImage.load(":/Images/Particals/Boom5.png");break;
        case 6:MeImage.load(":/Images/Particals/Boom6.png");break;
        default:break;
        } break;
    case Player_B3:
        switch (flash) {
        case 1:MeImage.load(":/Images/Particals/Shot3_1.png");break;
        case 2:MeImage.load(":/Images/Particals/Shot3_2.png");break;
        case 3:MeImage.load(":/Images/Particals/Shot3_3.png");break;
        case 4:MeImage.load(":/Images/Particals/Shot3_4.png");break;
        default:break;
        } break;
    case Player_Damage:
        switch (flash) {
          case 1:  MeImage.fill(QColor(255,255,255,150));break;
          case 2:  MeImage.fill(QColor(255,200,200,150));break;
          case 3:  MeImage.fill(QColor(255,150,150,150));break;
          case 4:  MeImage.fill(QColor(255,150,150,200));break;
          case 5:  MeImage.fill(QColor(255,100,100,200));break;
          case 6:  MeImage.fill(QColor(255,50,50,210));break;
          case 7:  MeImage.fill(QColor(255,0,0,255));break;
          default:break;
        }break;
    case Mist:
        switch (flash) {
        case 1:MeImage.load(":/Images/Particals/Mist5.png");break;
        case 2:MeImage.load(":/Images/Particals/Mist4.png");break;
        case 3:MeImage.load(":/Images/Particals/Mist3.png");break;
        case 4:MeImage.load(":/Images/Particals/Mist2.png");break;
        case 5:MeImage.load(":/Images/Particals/Mist1.png");break;
        default:break;
        } break;
    }

}
