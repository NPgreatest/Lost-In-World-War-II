#ifndef PARTICAL_H
#define PARTICAL_H
#include"All.h"
#include<QImage>
#include<QRect>
class Partical
{
private:
    int flash=0;
    XY pos;
    XY area;
    bool Alive=false;
    int flash_max;
    QImage MeImage;
    QRect MeRect;
    Type type;
    QImage Image_Transparent(QImage image,int x);
public:
    QImage GetImage(){return MeImage;}
    QRect GetRect(){return MeRect;}
    Partical(XY p,XY a,Type t);
    Partical();
    ~Partical(){}
    XY GetPos() {return pos;}
    XY GetArea()const{return area;}
    int GetFlash()const{return flash;}
    int GetType()const{return type;}
    bool GetAlive()const{return Alive;}
    void FLash();
    void Dead(){Alive=false;flash=0;}
};

#endif // PARTICAL_H
