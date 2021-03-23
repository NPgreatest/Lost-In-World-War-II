#include "Skill.h"

Skill::Skill()
{
    MeImage.load(":/Images/Tank/Bullet1.png");
    MeRect.setRect(100, 1000, 80, 80);
    skill = SkillName::MainWeapon;
}
void Skill::SkillChange()
{
    switch (skill)
    {
    case SkillName::MainWeapon:
        this->skill = SkillName::SubWeapon;
        MeImage.load(":/Images/Tank/Bullet2.png");
        break;
    case SkillName::SubWeapon:
        this->skill = SkillName::Fire;
        MeImage.load(":/Images/Tank/Bullet3.png");
        break;
    case SkillName::Fire:
        this->skill = SkillName::MainWeapon;
        MeImage.load(":/Images/Tank/Bullet1.png");
        break;
    }
}
