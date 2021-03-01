#ifndef OBJECT_H
#define OBJECT_H
#include "All.h"
#include<QImage>
#include<QRect>
#include<QTimer>
#include<QTime>
class Object
{
protected:
    int skin=0,type;//,other=0;//other：可能用到的其它变量
    XY pos;
    XY area;
    bool Alive=false;
    QRect MeRect;
    QImage MeImage;
public:
    bool GetAlive(){return Alive;}
    Object(XY p,XY a,int skin,int type);
    Object(){Alive=false;}
    virtual ~Object(){}
    XY GetPos() {return pos;}
    XY GetArea()const{return area;}
    int GetType()const{return type;}
    int GetSkin()const{return skin;}
  //  bool GetAlive()const{return Alive;}
    virtual bool Hit() = 0;//主要虚函数
    virtual bool Contact() = 0;//主要虚函数
    virtual void Flash(){}
    virtual int GetOther(){return 0;}
    virtual void SetOther(){}
 //   virtual int GetHP(){return HP;}
    QRect GetRect(){return MeRect;}
    QImage GetImage(){return MeImage;}
    void Dead(){Alive=false;}
};

class Temp:public Object{
public:
    Temp():Object(){Alive=false;}
    virtual bool Hit(){return false;}
    virtual bool Contact(){return false;}
    virtual ~Temp(){}
};
class Wall:public Object{
private:
    int HP;
public:
    Wall(XY p,XY a,int skin,int HP);
    virtual bool Hit();
    virtual bool Contact(){return true;}
    int GetHP(){return HP;}
    virtual ~Wall(){}
};
class BedRock:public Object{
private:
    int flash;
public:
    BedRock(XY p,XY a,int skin);
    virtual bool Hit();
    virtual void Flash();
    virtual bool Contact(){return true;}
    virtual ~BedRock(){}
};
class River:public Object{
private:
    int flash;
public:
    River(XY p,XY a,int skin);
    virtual bool Hit(){return false;}
    virtual void Flash();
    virtual bool Contact(){return true;}
    virtual ~River(){}
};
class Portal:public Object{
private:
    int flash;
public:
    Portal(XY p,XY a);
    virtual bool Hit(){return false;}
    virtual void Flash();
    virtual bool Contact(){return true;}
    virtual ~Portal(){}
};
class Camp:public Object{
private:
    int Remain,HP;
public:
    Camp(XY p,XY a,int skin,int HP);
    virtual bool Hit();
    virtual bool Contact(){return true;}
    virtual int GetOther(){return Remain;}
    virtual void SetOther();

    virtual ~Camp(){}
};
class FirstAid:public Object{
public:
    FirstAid(XY p,XY a,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){this->Dead();return true;}
    virtual ~FirstAid(){}
};
class Weapon:public Object{
public:
    Weapon(XY p,XY a,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){this->Dead();return true;}
    virtual ~Weapon(){}
};
class Ruins:public Object{
public:
    Ruins(XY p,XY a,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){Alive=false;return false;}
    virtual ~Ruins(){}
};
class Grass:public Object{
public:
    Grass(XY p,XY a,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){return false;}
    virtual ~Grass(){}
};
class Nail:public Object{
private:
    bool Active=false;
public:
    Nail(XY p,XY a);
    virtual bool Hit(){return false;}
    virtual bool Contact(){return true;}
    virtual void Flash();
    virtual int GetOther (){return Active;}
    virtual ~Nail(){}
};
class Ice:public Object{
private:
    int flash;
public:
    Ice(XY p,XY a);
    virtual bool Hit(){return false;}
    virtual bool Contact(){return true;}
    virtual void Flash();
    virtual ~Ice(){}
};
#endif // OBJECT_H
