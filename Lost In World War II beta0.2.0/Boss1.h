#ifndef BOSS1_H
#define BOSS1_H
#include"All.h"
#include"PlayerBullet1.h"
#include"playerbullet3.h"
class Boss1
{
private:
    int HP,skin;
    PlayerBullet1 B1[Edit_Min];
    PlayerBullet3 B3;
    XY a={150,150};
    HEAD head;
    XY pos;
    bool alive=false;
public:
    Boss1(XY p,int hp,int skin);
    Boss1(){alive=false;}
    ~Boss1(){}
    void Boss1_Move(int step);
    void Boss1_ChangeHead(int dire);
    void Boss1_RndChangeHead();
    void Boss1_B1Fire();
    void Boss1_B3Fire();
    void Boss1_UnderAttack(int damage);
    void Boss1_B1_Move();
    void Boss1_B1_Hit(int x){B1[x].PlayerBullet1_Dead();}
    void Boss1_B3_Hit(){B3.PlayerBullet3_Dead();}
    bool Boss1_Hit(XY p,XY s);
    bool Boss1_BulletHit(int n,XY p,XY s){return B1[n].PlayerBullet1_Hit(p,s);}
    void Boss1_Bullet3Flash(){B3.Flash();}
    int GetBullet3Flash(){return B3.GetFlash();}
    XY GetBullet3Pos(){return B3.GetPos();}
    XY GetBullet3Area(){return B3.GetArea();}
    XY GetPos() const{return pos;}
    HEAD GetHead(){return head;}
    bool GetBulletAlive(int x){return B1[x].GetAlive();}
    XY GetBulletPos(int x){return B1[x].GetPos();}
    bool GetAlive(){return alive;}
    XY GetArea(){return a;}
    int GetSkin(){return skin;}
    void Dead(){alive=false;}
};

#endif // BOSS1_H
