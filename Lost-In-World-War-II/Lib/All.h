#ifndef ALL_H
#define ALL_H
#include<QImage>
#include<QPixmap>
#include<QPainter>
#include<QRect>
#include<cmath>
#define X_Max 1900
#define Y_Max 1000
#define Edit_Max 1000
#define ENEMY_BULLET_NEMBER 10
#define ENEMY_NUMBER 1010
#define OBJECT_NUMBER 1020
#define PARTICAL_NUMBER 1030
#define REDZONE_NUMBER 50
#define PLAYER_B1_NUMBER 500
#define PLAYER_B2_NUMBER 200
#define PLAYER_NUMBER_MAX 10
#define MEDIA_MAX 50
#define Edit_Min 50


enum HEAD{
    UP=0,DOWN=1,LEFT=2,RIGHT=3,NO=4
};

enum Target{
    ALL,//对所有造成伤害
    OBJECT,//只对方块造成伤害
    ENEMY,//只对敌人造成伤害
    PLAYER//只对玩家造成伤害
};//所有类型均对方块造成伤害



enum Type{Object_Hit=1,
          Player_B3_UP=2,
          Player_B3_DOWN=3,
          Player_B3_LEFT=4,
          Player_B3_RIGHT=5,
          Player_Damage=6,
          Mist=7,
          Dialog1=8,Dialog2=9,Dialog3=10,Dialog4=11,Dialog5=121,Dialog6=13,Dialog7=14,Dialog8=15,DialogEnd=16,
          RedZone_Flash=17,
          Boss_Fire=18,
          Boss_Fire_D=19,
          Explotion=20
};

enum SkillName{
    MainWeapon,SubWeapon,Fire
};

enum Message{
    Load_Object=INT_MAX,
    Load_Partical=INT_MIN,
    Load_Enemy=INT_MAX-1,
    Load_Bullet=INT_MAX-2,
    Dead_Bullet=INT_MAX-9,
    Load_Bullet2=INT_MAX-10,
    Load_Player=INT_MAX-3,
    Player_Join=INT_MAX-4,
    Player_Join_Is_Success=INT_MAX-6,
    KEYBOARD_PUSHD=INT_MAX-5,
    KEYBOARD_RELEASED=INT_MAX-7,
    KEYBOARD_OTHER=INT_MAX-8,
    Load_Bar=INT_MAX-11
};

enum KEYBOARD_CONTROLL{
    PCHANGE,
    PFIRE,
    PNO
};

struct Player_Sql{
    QRect MeRect;
    HEAD head;
    int number;
    bool slow;
    Player_Sql(){}
    Player_Sql(QRect MeRect,HEAD head,int number,bool slow)
        :MeRect(MeRect),head(head),number(number),slow(slow){}
};

struct Object_Sql{
    QRect MeRect;
    int type;
    int Status;
    Object_Sql(){}
    Object_Sql(QRect MeRect,int type,int Status):MeRect(MeRect),type(type),Status(Status){}
};

struct Partical_Sql{
    QRect MeRect;
    Type type;
    Partical_Sql(){}
    Partical_Sql(QRect MeRect,Type type):MeRect(MeRect),type(type){}
};

struct Enemy_Sql{
    QRect MeRect;
    int type;
    HEAD head;
    Enemy_Sql(){}
    Enemy_Sql(QRect MeRect,HEAD head,int type)
              :MeRect(MeRect),type(type),head(head){}
};

struct Settings{
    public:
    int gamemode;
    int backsound;
    int sound;
    int internetmode;
    int W;
    int S;
    int A;
    int D;
    int Space;
    int Shift;
    int L;

};



QImage Image_Transparent(QImage image,int x);

QImage SetAlpha(QImage img, int alpha);

HEAD AI1(QRect Player,QRect Enemy);

double GetAngle(int x,int y);


#endif // ALL_H
/*图鉴
 * Object:
 * 1:房子（可被打烂） HP 0-10不等
 * 2.基岩(只能被轰炸区炸毁)
 * 3.河
 * 4. (Portal)传送到地图下个位置
 * 5.敌方兵营1
 * 6.急救包1
 * 7.武器箱1
 * 8.敌方兵营2
 * 9.急救包2
 * 10.武器箱2
 * 11.地方兵营3
 * 12.急救包3
 * 13.武器箱3
 * 14：草，小建筑（一压就没
 * 15.树林（纯遮挡视线）
 * 16.车钉子（踩上去掉血）
 * 17.冰面(减速)
 *
 *
  */
