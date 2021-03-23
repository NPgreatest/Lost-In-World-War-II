#ifndef SKILL_H
#define SKILL_H
#include "All.h"
#include <QImage>
#include <QRect>

class Skill
{
private:
    SkillName skill;
    QRect MeRect;
    QImage MeImage;

public:
    Skill();
    ~Skill() {}
    void SkillChange();
    SkillName GetSkill() { return skill; }
    QRect GetRect() { return MeRect; }
    QImage GetImage() { return MeImage; }
};

#endif // SKILL_H
