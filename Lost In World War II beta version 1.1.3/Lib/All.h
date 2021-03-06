#ifndef ALL_H
#define ALL_H
#include<QImage>
#include<QPixmap>
#include<QPainter>
#include<QRect>
#define X_Max 1500
#define Y_Max 1000
#define Edit_Max 1000
#define ENEMY_BULLET_NEMBER 10
#define ENEMY_NUMBER 1010
#define OBJECT_NUMBER 1020
#define PARTICAL_NUMBER 1030
#define REDZONE_NUMBER 50
#define PLAYER_B1_NUMBER 40
#define PLAYER_B2_NUMBER 30
#define PLAYER_NUMBER_MAX 10
#define Edit_Min 50

enum HEAD{
    UP=0,DOWN=1,LEFT=2,RIGHT=3,NO=4
};

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
          Boss_Fire_D=19
};
enum SkillName{
    MainWeapon,SubWeapon,Fire
};
enum Message{
    Load_Object=INT_MAX,
    Load_Partical=INT_MIN,
    Load_Enemy=INT_MAX-1,
    Load_Bullet=INT_MAX-2,
    Load_Player=INT_MAX-3,
    Player_Join=INT_MAX-4,
    Player_Join_Is_Success=INT_MAX-6,
    KEYBOARD_PUSHD=INT_MAX-5,
    KEYBOARD_RELEASED=INT_MAX-7,
    KEYBOARD_OTHER=INT_MAX-8

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
    Object_Sql(){}
    Object_Sql(QRect MeRect,int type):MeRect(MeRect),type(type){}
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
struct Bullet_Sql{
    QRect MeRect;
    int type;
    Bullet_Sql(){}
    Bullet_Sql(QRect MeRect,int type):MeRect(MeRect),type(type){}
};




enum Command{
    DrawObject,DrawPartical,DrawEnemy,DrawBullet
};

QImage Image_Transparent(QImage image,int x);

QImage SetAlpha(QImage img, int alpha);

HEAD AI1(QRect Player,QRect Enemy);



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
