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
    case Player_B3_UP:MeImage.load(":/Images/Particals/ShotUp3_1.png");flash_max=8;break;
    case Player_B3_DOWN:MeImage.load(":/Images/Particals/ShotDown3_1.png");flash_max=8;break;
    case Player_B3_LEFT:MeImage.load(":/Images/Particals/ShotLeft3_1.png");flash_max=8;break;
    case Player_B3_RIGHT:MeImage.load(":/Images/Particals/ShotRight3_1.png");flash_max=8;break;
    case Player_Damage:MeImage.load(":/Images/Particals/Damage1.png");flash_max=7;break;
    case Mist:MeImage.load(":/Images/Particals/Mist1.png");flash_max=5;break;
    case Dialog1:MeImage.load(":/Images/Mission/Dialog1.jpg");flash_max=80;break;
    case Dialog2:MeImage.load(":/Images/Mission/Dialog2.jpg");flash_max=60;break;
    case Dialog3:MeImage.load(":/Images/Mission/Dialog3.jpg");flash_max=60;break;
    case Dialog4:MeImage.load(":/Images/Mission/Dialog4.jpg");flash_max=60;break;
    case Dialog5:MeImage.load(":/Images/Mission/Dialog5.jpg");flash_max=60;break;
    case Dialog6:MeImage.load(":/Images/Mission/Dialog6.jpg");flash_max=60;break;
    case Dialog7:MeImage.load(":/Images/Mission/Dialog7.jpg");flash_max=60;break;
    case Dialog8:MeImage.load(":/Images/Mission/Dialog8.jpg");flash_max=60;break;
    case DialogEnd:MeImage.load(":/Images/Mission/Dialog8_0.jpg");flash_max=200;break;
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
    case Player_B3_UP:
        switch (flash) {
        case 1:MeImage.load(":/Images/Particals/ShotUp3_1.png");break;
        case 2:MeImage.load(":/Images/Particals/ShotUp3_2.png");break;
        case 3:MeImage.load(":/Images/Particals/ShotUp3_3.png");break;
        case 4:MeImage.load(":/Images/Particals/ShotUp3_4.png");break;
            case 5:MeImage.load(":/Images/Particals/ShotUp3_5.png");break;
            case 6:MeImage.load(":/Images/Particals/ShotUp3_6.png");break;
            case 7:MeImage.load(":/Images/Particals/ShotUp3_7.png");break;
            case 8:MeImage.load(":/Images/Particals/ShotUp3_8.png");break;
        default:break;
        } break;
    case Player_B3_DOWN:
        switch (flash) {
        case 1:MeImage.load(":/Images/Particals/ShotDown3_1.png");break;
        case 2:MeImage.load(":/Images/Particals/ShotDown3_2.png");break;
        case 3:MeImage.load(":/Images/Particals/ShotDown3_3.png");break;
        case 4:MeImage.load(":/Images/Particals/ShotDown3_4.png");break;
            case 5:MeImage.load(":/Images/Particals/ShotDown3_5.png");break;
            case 6:MeImage.load(":/Images/Particals/ShotDown3_6.png");break;
            case 7:MeImage.load(":/Images/Particals/ShotDown3_7.png");break;
            case 8:MeImage.load(":/Images/Particals/ShotDown3_8.png");break;
        default:break;
        } break;
    case Player_B3_LEFT:
        switch (flash) {
        case 1:MeImage.load(":/Images/Particals/ShotLeft3_1.png");break;
        case 2:MeImage.load(":/Images/Particals/ShotLeft3_2.png");break;
        case 3:MeImage.load(":/Images/Particals/ShotLeft3_3.png");break;
        case 4:MeImage.load(":/Images/Particals/ShotLeft3_4.png");break;
            case 5:MeImage.load(":/Images/Particals/ShotLeft3_5.png");break;
            case 6:MeImage.load(":/Images/Particals/ShotLeft3_6.png");break;
            case 7:MeImage.load(":/Images/Particals/ShotLeft3_7.png");break;
            case 8:MeImage.load(":/Images/Particals/ShotLeft3_8.png");break;
        default:break;
        } break;
    case Player_B3_RIGHT:
        switch (flash) {
        case 1:MeImage.load(":/Images/Particals/ShotRight3_1.png");break;
        case 2:MeImage.load(":/Images/Particals/ShotRight3_2.png");break;
        case 3:MeImage.load(":/Images/Particals/ShotRight3_3.png");break;
        case 4:MeImage.load(":/Images/Particals/ShotRight3_4.png");break;
            case 5:MeImage.load(":/Images/Particals/ShotRight3_5.png");break;
            case 6:MeImage.load(":/Images/Particals/ShotRight3_6.png");break;
            case 7:MeImage.load(":/Images/Particals/ShotRight3_7.png");break;
            case 8:MeImage.load(":/Images/Particals/ShotRight3_8.png");break;
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
    case Dialog1:break;
    case Dialog2:
    case Dialog3:
    case Dialog4:
    case Dialog5:
    case Dialog6:
    case Dialog7:
    case Dialog8:MeImage=Image_Transparent(MeImage,this->flash>20?382-6*flash:20*flash);break;
    case DialogEnd:
        switch (flash) {
        case 20:MeImage.load(":/Images/Mission/Dialog8 _1.jpg");break;
        case 40:MeImage.load(":/Images/Mission/Dialog8 _2.jpg");break;
        case 60:MeImage.load(":/Images/Mission/Dialog8 _3.jpg");break;
        case 80:MeImage.load(":/Images/Mission/Dialog8 _4.jpg");break;
        case 100:MeImage.load(":/Images/Mission/Dialog8 _5.jpg");break;
        case 120:MeImage.load(":/Images/Mission/Dialog8 _6.jpg");break;
        }
        break;
    }

}
QImage Partical::Image_Transparent(QImage image,int x){
                  if(x>255)x=255;
                      image = image.convertToFormat(QImage::Format_ARGB32);
                      union myrgb
                      {
                          uint rgba;
                          uchar rgba_bits[4];
                      };
                      myrgb* mybits =(myrgb*) image.bits();
                      int len = image.width()*image.height();
                      while(len --> 0)
                      {
                          mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:x;
                          mybits++;
                      }
                      return image;
}
