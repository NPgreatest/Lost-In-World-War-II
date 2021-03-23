#ifndef ENEMY_H
#define ENEMY_H
#include "All.h"
#include "PlayerBullet1.h"
#include <QImage>
#include <QRect>
class Enemy
{
private:
    int HP, B1Speed, skin;
    int speed;
    HEAD head;
    bool Alive = false;
    bool slow = false;
    QRect MeRect;
    QImage MeImage;
    void Me_ChangeHead(HEAD head);

public:
    Enemy(QRect MeRect, int hp, int speed, int bullet_speed, int skin);
    Enemy();
    ~Enemy();
    QRect &GetRect() { return MeRect; }
    QImage &GetImage() { return MeImage; }
    void Enemy_Move(const int step);
    void Enemy_ChangeHead(const int dire);
    void Enemy_RndChangeHead();
    void Enemy_UnderAttack(int damage);
    int GetMoveSpeed() const { return speed; }
    HEAD GetHead() const { return head; }
    bool GetAlive() const { return Alive; }
    int GetSkin() const { return skin; }
    int GetB1Speed() const { return this->B1Speed; }
    void Enemy_Slow() { slow = true; }
    void Enemy_UnSlow() { slow = false; }
    void Dead() { Alive = false; }
};

#endif // ENEMY_H
