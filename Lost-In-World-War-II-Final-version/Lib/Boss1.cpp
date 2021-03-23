#include "Boss1.h"
#include <QRandomGenerator>
#include <QDebug>
Boss1::Boss1(QRect MeRect, int hp, int skin) : HP(hp), skin(skin)
{
    this->MeRect = MeRect;
    Alive = true;
    this->head = HEAD::UP;
    MeImage.load(":/Images/Tank/BossUp.png");
}
void Boss1::Me_ChangeHead(HEAD head)
{
    this->head = head;
    switch (head)
    {
    case UP:
        MeImage.load(":/Images/Tank/BossUp.png");
        break;
    case DOWN:
        MeImage.load(":/Images/Tank/BossDown.png");
        break;
    case LEFT:
        MeImage.load(":/Images/Tank/BossLeft.png");
        break;
    case RIGHT:
        MeImage.load(":/Images/Tank/BossRight.png");
        break;
    }
}
void Boss1::Boss1_B3Fire()
{
    if (B3.GetAlive())
        return;
    QRect temp;
    switch (this->head)
    {
    case UP:
        temp.setRect(MeRect.x(), 0, 150, MeRect.y());
        B3.Init(temp, 70);
        break;
    case DOWN:
        temp.setRect(MeRect.x(), MeRect.y(), 150, 1000 - MeRect.y());
        B3.Init(temp, 70);
        break;
    case LEFT:
        temp.setRect(0, MeRect.y(), MeRect.x(), 150);
        B3.Init(temp, 70);
        break;
    case RIGHT:
        temp.setRect(MeRect.x() + 150, MeRect.y(), 2000 - MeRect.y(), 150);
        B3.Init(temp, 70);
        break;
    }
    return;
}
void Boss1::Boss1_Move(int step)
{
    switch (head)
    {
    case UP:
        MeRect.adjust(0, -step, 0, -step);
        break;
    case DOWN:
        MeRect.adjust(0, step, 0, step);
        break;
    case LEFT:
        MeRect.adjust(-step, 0, -step, 0);
        break;
    case RIGHT:
        MeRect.adjust(step, 0, step, 0);
        break;
    }
}
void Boss1::Boss1_RndChangeHead()
{
    int x = QRandomGenerator::global()->generate();
    switch (x % 4)
    {
    case 0:
        this->Me_ChangeHead(HEAD::UP);
        break;
    case 1:
        this->Me_ChangeHead(HEAD::DOWN);
        break;
    case 2:
        this->Me_ChangeHead(HEAD::LEFT);
        break;
    case 3:
        this->Me_ChangeHead(HEAD::RIGHT);
        break;
    }
}
void Boss1::Boss1_ChangeHead(int dire)
{
    switch (dire)
    {
    case 0:
        this->Me_ChangeHead(HEAD::UP);
        break;
    case 1:
        this->Me_ChangeHead(HEAD::DOWN);
        break;
    case 2:
        this->Me_ChangeHead(HEAD::LEFT);
        break;
    case 3:
        this->Me_ChangeHead(HEAD::RIGHT);
        break;
    }
}
void Boss1::Boss1_UnderAttack(int damage)
{
    HP -= damage;
    if (HP < 0)
    {
        Alive = false;
    }
}
