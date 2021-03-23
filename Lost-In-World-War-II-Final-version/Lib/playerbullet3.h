#ifndef PLAYERBULLET3_H
#define PLAYERBULLET3_H
#include "All.h"
#include <QRect>
class PlayerBullet3
{
private:
    int flash = 0, flash_max;
    QRect MeRect;
    bool Alive = false;

public:
    PlayerBullet3() { Alive = false; };
    ~PlayerBullet3(){};
    QRect GetRect() const { return MeRect; }
    void Init(QRect MeRect, int flash_max);
    bool GetAlive() { return Alive; }
    void PlayerBullet3_Dead() { MeRect.setRect(-1000, -1000, 10, 10); }
    int GetFlash() { return flash; }
    void Flash();
};

#endif // PLAYERBULLET3_H
