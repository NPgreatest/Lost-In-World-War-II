#ifndef PARTICAL_H
#define PARTICAL_H
#include "All.h"
#include <QImage>
#include <QRect>
#include <QPixmap>
#include <QPainter>
class Partical
{
private:
    int flash = 0;
    bool Alive = false;
    int flash_max;
    QImage MeImage;
    QRect MeRect;
    Type type;

public:
    QImage GetImage() { return MeImage; }
    QRect GetRect() { return MeRect; }
    Partical(QRect MeRect, Type t);
    Partical();
    ~Partical() {}
    int GetFlash() const { return flash; }
    int GetType() const { return type; }
    bool GetAlive() const { return Alive; }
    void FLash();
    void Dead()
    {
        Alive = false;
        flash = 0;
    }
};

#endif // PARTICAL_H
