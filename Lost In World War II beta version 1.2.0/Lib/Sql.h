#ifndef SQL_H
#define SQL_H
#include "All.h"
#include <QRect>
#include<QImage>
#include <QList>
class Sql
{
private:
    Player_Sql P1,P2;
    //QList<Player> Player_List;
    QList<Object_Sql> Object_List;
    QList<Object_Sql> Partical_List;
    QList<Enemy_Sql> Enemy_List;
public:
    Sql();
    ~Sql(){Object_List.~QList();Enemy_List.~QList();Partical_List.~QList();}

    void AddObject(Object_Sql object);
    void AddPartical(Object_Sql Partical);
    void AddEnemy(Enemy_Sql enemy);

    /*void PoPObject(Object_Sql object);
    void PoPObject(int x){Object_List.removeAt(x);}
    void AddPartical(Object_Sql Partical);
    void PoPPartical(Object_Sql Partical);
    void AddEnemy(Enemy_Sql enemy);
    void PopEnemy(Enemy_Sql enemy);*/


    Object_Sql GetObject(int x){return Object_List.at(x);}
    Enemy_Sql GetEnemey(int x){return Enemy_List.at(x);}
    Object_Sql GetPartical(int x){return Object_List.at(x);}

    int GetObject_Num() const {return Object_List.count();}
    int GetEnemy_Num() const {return Enemy_List.count();}
    int GetPartical_Num() const {return Partical_List.count();}


    void ObjectClear(){Object_List.clear();}
    void PartivalClear(){Partical_List.clear();}
    void EnemyClear(){Enemy_List.clear();}
    //bool GetIsObject(Object_Sql& object){return Object_List.contains(object);}
    //bool GetIsEnemy(Enemy_Sql Enemy){return Enemy_List.contains(Enemy);}
    //bool GetIsPartical(Object_Sql Partical){return Object_List.contains(Partical);}

};

#endif // SQL_H
