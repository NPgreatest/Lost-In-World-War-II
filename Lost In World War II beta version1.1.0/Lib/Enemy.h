#ifndef ENEMY_H
#define ENEMY_H
#include"All.h"
#include"PlayerBullet1.h"
#include<QImage>
#include<QRect>
class Enemy
{
private:
    int HP,B1Speed,skin;
    PlayerBullet1 B1[5];
    int speed;
    HEAD head;
    bool Alive=false;
    bool slow=false;
    QRect MeRect;
    QImage MeImage;
    void Me_ChangeHead(HEAD head);
public:
    Enemy(QRect MeRect,int hp,int speed,int bullet_speed,int skin);
    Enemy();
    ~Enemy();
    QRect& GetRect(){return MeRect;}
    QImage& GetImage(){return MeImage;}
    PlayerBullet1& GetB1(const int x) {return B1[x];}
    void Enemy_Move(const int step);
    void Enemy_ChangeHead(const int dire);
    void Enemy_RndChangeHead();
    void Enemy_B1Fire();
    void Enemy_B1_Move();
    void Enemy_UnderAttack(int damage);
    int GetMoveSpeed() const {return speed;}
    HEAD GetHead(){return head;}
    bool GetBulletAlive(int x){return B1[x].GetAlive();}
    bool GetAlive(){return Alive;}
    int GetSkin(){return skin;}
    void Enemy_Slow(){slow=true;}
    void Enemy_UnSlow(){slow=false;}
    void Dead(){Alive=false;}
};

#endif // ENEMY_H
