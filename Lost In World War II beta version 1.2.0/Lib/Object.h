#ifndef OBJECT_H
#define OBJECT_H
#include "All.h"
#include<QImage>
#include<QRect>

class Object
{
protected:
    int skin=0,type;
    bool Alive=false;
    QRect MeRect;
    QImage MeImage;
public:
    bool GetAlive(){return Alive;}
    Object(QRect MeRect,int skin,int type);
    Object(){Alive=false;}
    virtual ~Object(){}
    int GetType()const{return type;}
    int GetSkin()const{return skin;}
  //  bool GetAlive()const{return Alive;}
    virtual bool Hit() = 0;//主要虚函数
    virtual bool Contact() = 0;//主要虚函数
    virtual void Flash(){}
    virtual int GetOther(){return 0;}
    virtual void SetOther(){}
 //   virtual int GetHP(){return HP;}
    QRect& GetRect(){return MeRect;}
    QImage& GetImage(){return MeImage;}
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
    Wall(QRect MeRect,int skin,int HP);
    virtual bool Hit();
    virtual bool Contact(){return true;}
    int GetHP(){return HP;}
    virtual ~Wall(){}
};
class BedRock:public Object{
private:
    int flash;
public:
    BedRock(QRect MeRect,int skin);
    virtual bool Hit();
    virtual void Flash();
    virtual bool Contact(){return true;}
    virtual ~BedRock(){}
};
class River:public Object{
private:
    int flash;
public:
    River(QRect MeRect,int skin);
    virtual bool Hit(){return false;}
    virtual void Flash();
    virtual bool Contact(){return true;}
    virtual ~River(){}
};
class Portal:public Object{
private:
    int flash;
public:
    Portal(QRect MeRect);
    virtual bool Hit(){return false;}
    virtual void Flash();
    virtual bool Contact(){return true;}
    virtual ~Portal(){}
};
class Camp:public Object{
private:
    int Remain,HP;
public:
    Camp(QRect MeRect,int skin,int HP);
    virtual bool Hit();
    virtual bool Contact(){return true;}
    virtual int GetOther(){return Remain;}
    virtual void SetOther();

    virtual ~Camp(){}
};
class FirstAid:public Object{
public:
    FirstAid(QRect MeRect,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){this->Dead();return true;}
    virtual ~FirstAid(){}
};
class Weapon:public Object{
public:
    Weapon(QRect MeRect,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){this->Dead();return true;}
    virtual ~Weapon(){}
};
class Ruins:public Object{
public:
    Ruins(QRect MeRect,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){Alive=false;return false;}
    virtual ~Ruins(){}
};
class Grass:public Object{
public:
    Grass(QRect MeRect,int skin);
    virtual bool Hit(){return false;}
    virtual bool Contact(){return false;}
    virtual ~Grass(){}
};
class Nail:public Object{
private:
    bool Active=false;
public:
    Nail(QRect MeRect);
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
    Ice(QRect MeRect);
    virtual bool Hit(){return false;}
    virtual bool Contact(){return true;}
    virtual void Flash();
    virtual ~Ice(){}
};
#endif // OBJECT_H
