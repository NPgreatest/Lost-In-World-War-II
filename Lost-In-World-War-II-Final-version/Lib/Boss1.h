#ifndef BOSS1_H
#define BOSS1_H
#include "All.h"
#include "PlayerBullet2.h"
#include "playerbullet3.h"
#include <QImage>
#include <QRect>
class Boss1
{
private:
    int HP, skin;
    PlayerBullet3 B3;
    HEAD head;
    bool Alive = false;
    QRect MeRect;
    QImage MeImage;
    void Me_ChangeHead(HEAD head);

public:
    Boss1(QRect MeRect, int hp, int skin);
    Boss1() { Alive = false; }
    ~Boss1() {}
    QRect GetRect() { return MeRect; }
    QImage GetImage() const { return MeImage; }
    PlayerBullet3 &GetB3() { return B3; }
    void Boss1_Move(int step);
    void Boss1_ChangeHead(int dire);
    void Boss1_RndChangeHead();
    void Boss1_B3Fire();
    void Boss1_UnderAttack(int damage);
    bool Boss1_Hit(const QRect rect) const;
    int GetBullet3Flash() { return B3.GetFlash(); }
    HEAD GetHead() { return head; }
    bool GetAlive() { return Alive; }
    int GetSkin() { return skin; }
    void Dead() { Alive = false; }
};

#endif // BOSS1_H
