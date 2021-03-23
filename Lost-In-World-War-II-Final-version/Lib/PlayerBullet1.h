#ifndef PLAYERBULLET1_H
#define PLAYERBULLET1_H
#include "All.h"
#include <QRect>
#include <QImage>
class PlayerBullet1
{
private:
    int type;
    HEAD head;
    QImage MeImage;
    QRect MeRect;
    bool Alive = false;
    Target target;
    int Damage;
    int master;
    int Speed;

public:
    PlayerBullet1();
    ~PlayerBullet1() {}
    QImage GetImage() const { return MeImage; }
    QRect GetRect() const { return MeRect; }
    void Init(QRect const MeRect, HEAD const h, int const type, int const Damage, Target target, int master, int Speed);
    void PlayerBullet1_Move();
    HEAD GetHead() const { return head; }
    bool GetAlive() const { return Alive; }
    void PlayerBullet1_Dead()
    {
        this->Alive = false;
        MeRect.setRect(-1000, -1000, 10, 10);
    }
    int GetType() const { return this->type; }
    int GetMaster() const { return master; }
    Target GetTarget() const { return target; }
    int GetDamage() const { return Damage; }
    void SetRect(QRect const Rect) { this->MeRect = Rect; }
    int GetSpeed() const { return Speed; }
};

#endif // PLAYERBULLET1_H
