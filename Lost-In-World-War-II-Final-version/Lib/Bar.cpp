#include "Bar.h"

Bar::Bar(int x, int y, int Max, int type) : Max(Max), type(type)
{
    MeRect1.setRect(x, y, 400, 80);
    switch (type)
    {
    case 1:
        MeImage.load(":/Images/Images/Bar1.png");
        break;
    case 2:
        MeImage.load(":/Images/Images/Bar2.png");
        break;
    case 3:
        MeImage.load(":/Images/Images/Bar3.png");
        break;
    }
    this->CutImage();
}
void Bar::SetValue(int Value)
{
    this->Value = Value;
    this->CutImage();
}
void Bar::CutImage()
{
    MeImage2 = MeImage.copy(0, 0, Value >= Max ? 1000 : (Value * 1000) / Max, 100);
    MeImage1 = MeImage.copy(0, 100, 1000, 100);
    MeRect2.setRect(MeRect1.x(), MeRect1.y(), (Value >= Max ? 400 : (Value * 400) / Max), 80);
}
//dffdf
