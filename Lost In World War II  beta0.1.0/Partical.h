#ifndef PARTICAL_H
#define PARTICAL_H
#include"All.h"

class Partical
{
private:
    int flash=0,type=0;
    XY pos;
    XY area;
    bool Alive=false;
    int flash_max;
public:
    Partical(XY pos,XY area,int flash_max,int type);
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
