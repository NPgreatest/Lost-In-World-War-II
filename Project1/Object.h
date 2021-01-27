#ifndef OBJECT_H
#define OBJECT_H
#include "All.h"

class Object
{
private:
    int HP,type;
    XY pos;
    XY a;
    bool Alive=false;
    int flash=-1;
public:
    Object(XY p,XY a,int type);
    Object();
    ~Object();
    XY GetPos() {return pos;}
    XY GetArea()const{return a;}
    int GetType()const{return type;}
    bool GetAlive()const{return Alive;}
    void Init(XY p,XY a,int type);
    void Hit();
    void Flash();
    void Flash_Begin(){flash=0;}
    int GetFlash(){return flash;}
    int GetHP(){return HP;}
    void Dead(){Alive=false;type=0;}
};

#endif // OBJECT_H
