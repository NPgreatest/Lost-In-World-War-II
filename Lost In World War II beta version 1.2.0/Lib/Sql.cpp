#include "Sql.h"

Sql::Sql()
{

}
void Sql::AddObject(Object_Sql object){
    Object_List.append(object);
}
void Sql::AddEnemy(Enemy_Sql enemy){
    Enemy_List.append(enemy);
}

void Sql::AddPartical(Object_Sql Partical){
    Object_List.append(Partical);
}
/*void Sql::PoPPartical(Object_Sql Partical){
    Object_List.removeOne(Partical);
}
void Sql::PoPObject(Object_Sql object){
    Object_List.removeOne(object);
}
void Sql::PopEnemy(Enemy_Sql enemy){
    Enemy_List.removeOne(enemy);
}*/
