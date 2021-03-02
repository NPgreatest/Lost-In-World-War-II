#ifndef REDZONE_H
#define REDZONE_H
#include"All.h"
#include<QImage>
#include<QRect>
class RedZone
{
private:
    XY pos;
    int r;
    bool Alive=false;
    int type=0;
    int flash=-1;
    QRect MeRect;
    QImage MeImage;
public:
    RedZone(XY p,int r,int type);
    RedZone();
    ~RedZone();
    QRect GetRect(){return MeRect;}
    QImage GetImage(){return MeImage;}
    XY GetPos() {return pos;}
    int GetR()const{return r;}
    int GetType()const{return type;}
    bool GetAlive()const{return Alive;}
    void Init(XY p,int r,int type);
    void Flash();
    void Flash_Begin(){flash=0;}
    int GetFlash()const{return flash;}
    bool Object_Hit(XY p,XY s);
    bool CircleFunction(XY p);
};

#endif // REDZONE_H
