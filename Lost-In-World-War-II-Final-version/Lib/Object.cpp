#include "Object.h"
#include <QDebug>
Object::Object(QRect MeRect, int skin, int type) : skin(skin), type(type)
{
    this->MeRect = MeRect;
    this->Alive = true;
    this->Status = 0;
}

Wall::Wall(QRect MeRect, int skin, int HP) : Object(MeRect, skin, 1)
{
    Alive = true;
    this->HP = HP;
    MeImage.load(":/Images/Object/Wall1.png");
}
void Wall::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/Wall1.png");
        break;
    case 1:
        MeImage.load(":/Images/Object/Wall2.png");
        break;
    case 2:
        MeImage.load(":/Images/Object/Wall3.png");
        break;
    default:
        break;
    }
}
bool Wall::Hit()
{
    HP--;
    if (HP == 1)
    {
        MeImage.load(":/Images/Object/Wall2.png");
        this->Status = 1;
    }
    if (HP == 0)
    {
        MeImage.load(":/Images/Object/Wall3.png");
        this->Status = 2;
    }
    if (HP < 0)
    {
        this->Alive = false;
    }
    return true;
}
void BedRock::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/BedRock1.png");
        break;
    case 1:
        MeImage.load(":/Images/Object/BedRock2.png");
        break;
    default:
        break;
    }
}

BedRock::BedRock(QRect MeRect, int skin) : Object(MeRect, skin, 2)
{
    Alive = true;
    this->flash = 1;
    MeImage.load(":/Images/Object/BedRock1.png");
}
void BedRock::Flash()
{
    if (this->flash == -1)
    {
        MeImage.load(":/Images/Object/BedRock1.png");
        this->flash = 1;
        this->Status = 0;
    }
}
bool BedRock::Hit()
{
    MeImage.load(":/Images/Object/BedRock2.png");
    this->flash = -1;
    this->Status = 1;
    return true;
}
River::River(QRect MeRect, int skin) : Object(MeRect, skin, 3), flash(1)
{
    Alive = true;
    MeImage.load(":/Images/Object/River1.png");
    Backup.load(":/Images/Object/River2.png");
}
void River::Flash()
{
    flash = -flash;
    if (flash == 1)
    {
        this->Status = 1;
    }
    else
    {
        this->Status = 0;
    }
}
void River::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 1:
        MeImage.load(":/Images/Object/River1.png");
        break;
    case 0:
        MeImage.load(":/Images/Object/River2.png");
        break;
    default:
        break;
    }
}

Portal::Portal(QRect MeRect) : Object(MeRect, 0, 4), flash(1)
{
    Alive = true;
    MeImage.load(":/Images/Object/Portal.png");
}
void Portal::Flash()
{
    flash = -flash;
    if (flash == 1)
    {
        MeImage.load(":/Images/Object/Portal.png");
        this->Status = 1;
    }
    else
    {
        MeImage.load(":/Images/Object/Portal2.png");
        this->Status = 0;
    }
}
void Portal::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/Portal.png");
        break;
    case 1:
        MeImage.load(":/Images/Object/Portal2.png");
        break;
    default:
        break;
    }
}
Camp::Camp(QRect MeRect, int skin, int HP) : Object(MeRect, skin, 5)
{
    this->HP = HP;
    Alive = true;
    switch (skin)
    {
    case 1:
        Remain = 3;
        MeImage.load(":/Images/Object/Camp1.jpg");
        this->Status = 0;
        break;
    case 2:
        Remain = 5;
        MeImage.load(":/Images/Object/Camp2.jpg");
        this->Status = 1;
        break;
    case 3:
        Remain = 7;
        MeImage.load(":/Images/Object/Camp3.jpg");
        this->Status = 2;
        break;
    default:
        break;
    }
}

bool Camp::Hit()
{
    this->HP--;
    if (HP < 0)
    {
        this->Dead();
    }
    return true;
}

void Camp::SetOther()
{
    Remain--;
    if (Remain <= 0)
    {
        this->Dead();
    }
}

void Camp::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/Camp1.jpg");
        break;
    case 1:
        MeImage.load(":/Images/Object/Camp2.jpg");
        break;
    case 2:
        MeImage.load(":/Images/Object/Camp3.jpg");
        break;
    default:
        break;
    }
}

FirstAid::FirstAid(QRect MeRect, int skin) : Object(MeRect, skin, 6)
{
    Alive = true;
    switch (skin)
    {
    case 1:
        MeImage.load(":/Images/Object/FirstAid1.png");
        this->Status = 0;
        break;
    case 2:
        MeImage.load(":/Images/Object/FirstAid2.png");
        this->Status = 1;
        break;
    case 3:
        MeImage.load(":/Images/Object/FirstAid3.png");
        this->Status = 2;
        break;
    default:
        break;
    }
}
void FirstAid::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/FirstAid1.png");
        break;
    case 1:
        MeImage.load(":/Images/Object/FirstAid2.png");
        break;
    case 2:
        MeImage.load(":/Images/Object/FirstAid3.png");
        break;
    default:
        break;
    }
}
Weapon::Weapon(QRect MeRect, int skin) : Object(MeRect, skin, 7)
{
    Alive = true;
    switch (skin)
    {
    case 1:
        MeImage.load(":/Images/Object/Weapon1.png");
        this->Status = 0;
        break;
    case 2:
        MeImage.load(":/Images/Object/Weapon2.png");
        this->Status = 1;
        break;
    case 3:
        MeImage.load(":/Images/Object/Weapon3.png");
        this->Status = 2;
        break;
    default:
        break;
    }
}
void Weapon::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/Weapon1.png");
        break;
    case 1:
        MeImage.load(":/Images/Object/Weapon2.png");
        break;
    case 2:
        MeImage.load(":/Images/Object/Weapon3.png");
        break;
    default:
        break;
    }
}
Ruins::Ruins(QRect MeRect, int skin) : Object(MeRect, skin, 8)
{
    Alive = true;
    switch (skin)
    {
    case 1:
        MeImage.load(":/Images/Object/Ruins1.png");
        break;
    case 2:
        MeImage.load(":/Images/Object/Ruins2.png");
        break;
    default:
        MeImage.load(":/Images/Object/Ruins2.png");
        break;
    }
}
Grass::Grass(QRect MeRect, int skin) : Object(MeRect, skin, 9)
{
    Alive = true;
    switch (skin)
    {
    case 1:
        MeImage.load(":/Images/Object/Grass1.png");
        break;
    case 2:
        MeImage.load(":/Images/Object/Grass2.png");
        break;
    default:
        break;
    }
}
Nail::Nail(QRect MeRect) : Object(MeRect, 1, 10)
{
    this->Active = false;
    Alive = true;
    MeImage.load(":/Images/Object/Nail1.png");
}

void Nail::Flash()
{
    Active = !Active;
    if (Active)
    {
        MeImage.load(":/Images/Object/Nail2.png");
        this->Status = 1;
    }
    else
    {
        MeImage.load(":/Images/Object/Nail1.png");
        this->Status = 0;
    }
}
void Nail::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/Nail1.png");
        break;
    case 1:
        MeImage.load(":/Images/Object/Nail2.png");
        break;
    default:
        break;
    }
}
Ice::Ice(QRect MeRect) : Object(MeRect, 1, 11)
{
    this->flash = 1;
    Alive = true;
    MeImage.load(":/Images/Object/Ice1.png");
    Backup.load(":/Images/Object/Ice2.png");
}
void Ice::Flash()
{
    flash = -flash;
    if (flash == 1)
    {
        this->Status = 1;
    }
    else
    {
        this->Status = 0;
    }
    return;
}
void Ice::SetStatue(int x)
{
    this->Object::SetStatue(x);
    switch (x)
    {
    case 0:
        MeImage.load(":/Images/Object/Ice1.png");
        break;
    case 1:
        MeImage.load(":/Images/Object/Ice2.png");
        break;
    default:
        break;
    }
}
