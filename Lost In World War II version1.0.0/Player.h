#ifndef PLAYER_H
#define PLAYER_H
#include "All.h"
#include"PlayerBullet1.h"
#include"PlayerBullet2.h"
#include"playerbullet3.h"
#include"Skill.h"
#include <QImage>
#include<QRect>
class PlayerBullet1;
class Player
{
private:
    int HP,MP,WeaponLv,Material,Process=0;
    XY a;   //坦克长宽
    PlayerBullet1 B1[10];
    PlayerBullet2 B2;
    PlayerBullet3 B3;
    QImage MeImage;
    QRect MeRect;
    int B1Count,speed;
    HEAD head;
    XY pos;
    bool dead;
    bool slow=false;
public:

    Player(XY p,int hp,int mp,int WeaponLv,int Material,int B1Count);
    Player();
    QImage GetImage(){return MeImage;}
    QRect GetRect(){return MeRect;}
    void Player_Move(int step);
    void Player_ChangeHead(int dire);
    bool Player_B1Fire();
    bool Player_B2Fire();
    bool Player_B3Fire();
    void Player_UnderAttack(int damage);
    bool Player_Dead();
    void Player_B1_Move();
    void Player_B2_Move();
    void Player_B1_Hit(int x){B1[x].PlayerBullet1_Dead();}
    bool Player_Hit(XY p,XY s);
    bool Player_Bullet1Hit(int n,XY p,XY s){return B1[n].PlayerBullet1_Hit(p,s);}
    bool Player_Bullet2Hit(XY p,XY s){return B2.PlayerBullet2_Hit(p,s);}
    bool Player_Bullet3Hit(XY p,XY s){return B3.PlayerBullet3_Hit(p,s);}
    XY GetPos() const{return pos;}
    XY GetArea()const{return a;}
    HEAD GetHead(){return head;}
    int GetHP(){return HP;}
    XY GetBulletPos(int x){return B1[x].GetPos();}
    XY GetBullet2Pos(){return B2.GetPos();}
    XY GetBullet3Pos(){return B3.GetPos();}
    HEAD GetBulletHaed(int x){return B1[x].GetHead();}
    HEAD GetBullet2Haed(){return B2.GetHead();}
    bool GetBulletAlive(int x){return B1[x].GetAlive();}
    bool GetBullet2Alive(){return B2.GetAlive();}
    bool GetBullet3Alive(){return B3.GetAlive();}
    void Player_Bullet3Flash(){B3.Flash();}
    int GetBullet3Flash(){return B3.GetFlash();}
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
    void SetPos(XY pos){this->pos=pos;MeRect.setRect(pos.x,pos.y,a.x,a.y);}
    void Player_B3_Hit(){B3.PlayerBullet3_Dead();}
    int Damage(SkillName skillname);
};
#endif // PLAYER_H
