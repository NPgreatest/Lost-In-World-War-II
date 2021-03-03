#ifndef PLAYER_H
#define PLAYER_H
#include "All.h"
#include"PlayerBullet1.h"
#include"PlayerBullet2.h"
#include"playerbullet3.h"
#include"Skill.h"
#include<QImage>
#include<QRect>
class PlayerBullet1;
class Player
{
private:
    int HP,MP,WeaponLv,Material,Process=0;
    PlayerBullet1 B1[Edit_Max];
    PlayerBullet2 B2[Edit_Max];
    PlayerBullet3 B3;
    QImage MeImage;
    QRect MeRect;
    int B1Count,speed;
    HEAD head;
    bool dead;
    bool slow=false;
    void UpdateIm(HEAD head);
public:
    PlayerBullet1& GetB1(int x){return B1[x];}
    PlayerBullet2& GetB2(int x){return B2[x];}
    PlayerBullet3& GetB3(){return this->B3;}
    Player(QRect MeRect,int hp,int mp,int WeaponLv,int Material,int B1Count);
    Player();
    QImage& GetImage() {return MeImage;}
    QRect& GetRect() {return MeRect;}
    void Player_Move(int step);
    void Player_ChangeHead(const int dire);
    void Player_UnderAttack(const int damage){this->HP-=damage;}
    HEAD GetHead(){return head;}
    int GetHP(){return HP;}
    int GetSpeed() const {return speed;}
    int GetMP() const {return MP;}
    int GetWeaponLv() const {return WeaponLv;}
    int GetMaterial() const {return Material;}
    int GetProcess() const {return Process;}
    void Player_ProcessOn(int x){Process+=x;}
    void Player_Slow(){slow=true;}
    void Player_UnSlow(){slow=false;}
    void Strengthen(int HP,int MP,int WeaponLv,int Material,int speed,int B1Count);
    void SetPos(QRect MeRect){this->MeRect=MeRect;}
    bool Player_B1Fire();
    bool Player_B2Fire(double Direction);
    bool Player_B3Fire();
    int Damage(SkillName skillname);
};
#endif // PLAYER_H
