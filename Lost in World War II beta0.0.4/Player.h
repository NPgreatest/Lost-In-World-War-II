#ifndef PLAYER_H
#define PLAYER_H
#include "All.h"
#include"PlayerBullet1.h"
class PlayerBullet1;
class Player
{
private:
    int HP,MP,WeaponLv,Material,Process=0;
    XY a;   //坦克长宽
    PlayerBullet1 B1[10];
    int B1Count,speed;
    HEAD head;
    XY pos;
    bool dead;
    bool slow=false;
public:
    Player(XY p,int hp,int mp);
    Player();
    void Player_Move(int step);
    void Player_ChangeHead(int dire);
    bool Player_B1Fire();
    bool Player_B2Fire();
    void Player_UnderAttack(int damage);
    bool Player_Dead();
    void Player_B1_Move();
    void Player_B1_Hit(int x){B1[x].PlayerBullet1_Dead();}
    bool Player_Hit(XY p,XY s);
    bool Player_BulletHit(int n,XY p,XY s){return B1[n].PlayerBullet1_Hit(p,s);}
    XY GetPos() const{return pos;}
    XY GetArea()const{return a;}
    HEAD GetHead(){return head;}
    int GetHP(){return HP;}
    XY GetBulletPos(int x){return B1[x].GetPos();}
    HEAD GetBulletHaed(int x){return B1[x].GetHead();}
    bool GetBulletAlive(int x){return B1[x].GetAlive();}
    int GetBulletC(){return B1Count;}
    int GetSpeed()const{return speed;}
    int GetMP()const{return MP;}
    int GetWeaponLv()const{return WeaponLv;}
    int GetMaterial()const{return Material;}
    int GetProcess()const{return Process;}
    void Player_ProcessOn(int x){Process+=x;}
    void Player_Slow(){slow=true;}
    void Player_UnSlow(){slow=false;}
    void Strengthen(int HP,int MP,int WeaponLv,int Material,int speed,int B1Count);
};
#endif // PLAYER_H
