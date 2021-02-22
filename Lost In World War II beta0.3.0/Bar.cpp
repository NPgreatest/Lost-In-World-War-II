#include "Bar.h"

Bar::Bar(int x,int y,int Max,int type):Max(Max),type(type){
    MeRect1.setRect(x,y,80,900);
    switch (type) {
    case 1:MeImage.load(":/Images/Images/Bar1.png");break;
    case 2:MeImage.load(":/Images/Images/Bar2.png");break;
    case 3:MeImage.load(":/Images/Images/Bar3.png");break;
    case 4:MeImage.load(":/Images/Images/Bar4.png");break;
    case 5:MeImage.load(":/Images/Images/Bar5.png");break;
    }
    this->CutImage();
}
void Bar::SetValue(int Value){
    this->Value=Value;
    this->CutImage();
}
void Bar::CutImage(){
    MeImage2=MeImage.copy(0,0,21,Value>=Max?300:(Value*300)/Max);
    MeImage1=MeImage.copy(21,0,21,300);
    MeRect2.setRect(MeRect1.x(),MeRect1.y(),80,Value>=Max?900:(Value*900)/Max);
}
