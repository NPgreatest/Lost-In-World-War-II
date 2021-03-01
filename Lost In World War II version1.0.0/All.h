#ifndef ALL_H
#define ALL_H
#define X_Max 1500
#define Y_Max 1000
#define Edit_Max 1000
#define Edit_Min 50
enum HEAD{
    UP,DOWN,LEFT,RIGHT
};
enum Type{Object_Hit,
          Player_B3_UP,
          Player_B3_DOWN,
          Player_B3_LEFT,
          Player_B3_RIGHT,
          Player_Damage,
          Mist,
          Dialog1,Dialog2,Dialog3,Dialog4,Dialog5,Dialog6,Dialog7,Dialog8,DialogEnd,
          RedZone_Flash,
          Boss_Fire,
          Boss_Fire_D
};
enum SkillName{
    MainWeapon,SubWeapon,Fire
};

struct XY{
    int x,y;
    XY():x(),y(){}
    XY(int x,int y):x(x),y(y){}
    XY operator-(const XY& value) const {
        XY temp;
        temp.x=x-value.x;
        temp.y=y-value.y;
        return temp;
    }
    XY operator+(const XY& value) const {
        XY temp;
        temp.x=x+value.x;
        temp.y=y+value.y;
        return temp;
    }
    XY operator*(const int& value) const {
        XY temp;
        temp.x=this->x*value;
        temp.y=this->y*value;
        return temp;
    }
    XY operator/(const int& value) const {
        XY temp;
        temp.x=this->x/value;
        temp.y=this->y/value;
        return temp;
    }
    XY operator+(const int &value) const {
        XY temp;
        temp.x=this->x+value;
        temp.y=this->y+value;
        return temp;
    }
    XY operator-(const int &value) const {
        XY temp;
        temp.x=this->x-value;
        temp.y=this->y-value;
        return temp;
    }
};



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
 *
 *
  */
