#ifndef BAR_H
#define BAR_H
#include "All.h"
#include <QImage>
#include <QRect>
class Bar
{
private:
    int Max, Value, type;
    QImage MeImage;
    QRect MeRect1;
    QImage MeImage1;
    QRect MeRect2;
    QImage MeImage2;
    void CutImage();

public:
    Bar(int x, int y, int Max, int type);
    void SetValue(int Value);
    QRect GetRect1() { return MeRect1; }
    QImage GetImage1() { return MeImage1; }
    QRect GetRect2() { return MeRect2; }
    QImage GetImage2() { return MeImage2; }
    ~Bar() {}
};

#endif // BAR_H
