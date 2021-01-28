#ifndef OBJECT_H
#define OBJECT_H
#include "All.h"

class Object
{
private:
    int HP,type,skin=0,other=0;//other：可能用到的其它变量
    XY pos;
    XY area;
    bool Alive=false;

public:
    Object(XY p,XY a,int type,int skin,int HP);
    Object();
    ~Object();
    XY GetPos() {return pos;}
    XY GetArea()const{return area;}
    int GetType()const{return type;}
    bool GetAlive()const{return Alive;}
    void Hit();
    int GetHP(){return HP;}
    void Dead(){Alive=false;type=0;}
};

#endif // OBJECT_H
