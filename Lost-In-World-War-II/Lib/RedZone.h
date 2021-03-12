#ifndef REDZONE_H
#define REDZONE_H
#include"All.h"
#include<QImage>
#include<QRect>
#include<QPoint>
class RedZone
{
private:
    int r;
    bool Alive=false;
    int type=0;
    int flash=-1;
    QRect MeRect;
    bool CircleFunction(QPoint Point) ;
public:
    RedZone(QRect MeRect,int r,int type);
    RedZone();
    ~RedZone();
    QRect GetRect(){return MeRect;}
    int GetR()const{return r;}
    int GetType()const{return type;}
    bool GetAlive()const{return Alive;}
    void Flash();
    void Flash_Begin(){flash=0;}
    int GetFlash()const{return flash;}
    bool Object_Hit(QRect Rect);
};

#endif // REDZONE_H
