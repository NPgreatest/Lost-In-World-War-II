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
    int HP,MP,WeaponLv,Process=0;
    PlayerBullet1 B1[PLAYER_B1_NUMBER];
    PlayerBullet2 B2[PLAYER_B2_NUMBER];
    PlayerBullet3 B3;
    Skill myskill;
    int Choose;
    QImage MeImage;
    QRect MeRect;
    int speed;
    HEAD head;
    bool Activate;
    bool slow=false;

    void UpdateIm(HEAD head);
public:
    PlayerBullet1& GetB1(int x){return B1[x];}
    PlayerBullet2& GetB2(int x){return B2[x];}
    PlayerBullet3& GetB3(){return this->B3;}
    Skill& GetSkill(){return this->myskill;}
    Player(QRect MeRect,int HP,int MP,int WeaponLv);
    Player();
    ~Player(){}
    int GetChoose()const{return Choose;}
    void SetChoose(int x){this->Choose=x;}
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
    int GetProcess() const {return Process;}
    void Player_ProcessOn(int x){Process+=x;}
    void Player_Slow(){slow=true;}
    void Player_UnSlow(){slow=false;}
    bool GetSlow()const{return slow;}
    void Strengthen(int HP,int MP,int WeaponLv,int speed);
    void SetPos(QRect MeRect){this->MeRect=MeRect;}
    bool Player_B1Fire();
    bool Player_B2Fire(double Direction);
    bool Player_B3Fire();
    int Damage(SkillName skillname);
    bool GetActivate(){return Activate;}
};
#endif // PLAYER_H
