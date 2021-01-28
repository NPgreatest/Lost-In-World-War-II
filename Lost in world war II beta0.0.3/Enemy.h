#ifndef ENEMY_H
#define ENEMY_H
#include"All.h"
#include"PlayerBullet1.h"
class Enemy
{
private:
    int HP,MP,WeapenLv,B1Speed,skin;
    XY a;   //敌人长宽
    PlayerBullet1 B1[5];
    int speed;
    HEAD head;
    XY pos;
    bool alive=false;
    int flash=-1;
public:
    Enemy(XY p,XY area,int hp,int speed,int bullet_speed,int skin);
    Enemy();
    ~Enemy();
    void Enemy_Move(int step);
    void Enemy_ChangeHead(int dire);
    void Enemy_RndChangeHead();
    void Enemy_B1Fire();
    void Enemy_B2Fire();
    void Enemy_UnderAttack(int damage);
    void Enemy_B1_Move();
    void Enemy_B1_Hit(int x){B1[x].PlayerBullet1_Dead();}
    bool Enemy_Hit(XY p,XY s);
    int GetMoveSpeed(){return speed;}
    bool Enemy_BulletHit(int n,XY p,XY s){return B1[n].PlayerBullet1_Hit(p,s);}
    XY GetPos() const{return pos;}
    HEAD GetHead(){return head;}
    bool GetBulletAlive(int x){return B1[x].GetAlive();}
    XY GetBulletPos(int x){return B1[x].GetPos();}
    bool GetAlive(){return alive;}
    XY GetArea(){return a;}
    void Flash();
    void Flash_Begin(){flash=0;}
    int GetFlash(){return flash;}
    int GetSkin(){return skin;}
    void Dead(){alive=false;}
};

#endif // ENEMY_H
