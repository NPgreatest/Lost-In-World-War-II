#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"

void BattleWindow::Bullet_HitCheck(){
    int i,k,j,l;
    bool B3[PLAYER_NUMBER_MAX]={0,0,0,0,0,0,0,0,0,0};

    //子弹命中敌人
    for(i=0;i<ENEMY_NUMBER;i++){
    if(!enemy[i].GetAlive())continue;
    for(j=0;j<PLAYER_NUMBER_MAX;j++){
        if(!P1[j].GetActivate()) continue;
    for(k=0;k<PLAYER_B1_NUMBER;k++){//B1
    if(P1[j].GetB1(k).GetAlive()&&P1[j].GetB1(k).GetRect().intersects(enemy[i].GetRect())){
        enemy[i].Enemy_UnderAttack(P1[j].Damage(SkillName::MainWeapon));
        P1[j].GetB1(k).PlayerBullet1_Dead();
        Play_PlayerHit();
            if(!enemy[i].GetAlive())CreatePartical(enemy[i].GetRect().adjusted(-50,-50,100,100),Type::Object_Hit);
            else {CreatePartical(enemy[i].GetRect(),Type::Object_Hit);}
        }
    }//B1
    for(k=0;k<PLAYER_B2_NUMBER;k++){//B1
    if(P1[j].GetB2(k).GetRect().intersects(enemy[i].GetRect())){//B2
        enemy[i].Enemy_UnderAttack(P1[j].Damage(SkillName::SubWeapon));
        P1[j].GetB2(k).Hit();
            if(!enemy[i].GetAlive())CreatePartical(enemy[i].GetRect().adjusted(-50,-50,100,100),Type::Object_Hit);
            else {CreatePartical(enemy[i].GetRect(),Type::Object_Hit);}

        }//B2
    }
    if(P1[j].GetB3().GetFlash()==3&&P1[j].GetB3().GetAlive()){
        if(P1[j].GetB3().GetRect().intersects(enemy[i].GetRect())){
            enemy[i].Enemy_UnderAttack(P1[j].Damage(SkillName::Fire));
            CreatePartical(enemy[i].GetRect(),Type::Player_Damage);
            B3[j]=true;
            }
        }
    }
    }
    //子弹命中敌人

    for(k=0;k<PLAYER_NUMBER_MAX;k++){
        if(!P1[k].GetActivate()) continue;
    for(i=0;i<PLAYER_B1_NUMBER;i++){//玩家打中boss判定
        if(P1[k].GetB1(i).GetAlive() && boss1->GetAlive() && P1[k].GetB1(i).GetRect().intersects(boss1->GetRect())){
            P1[k].GetB1(i).PlayerBullet1_Dead();
            boss1->Boss1_UnderAttack(P1[k].Damage(SkillName::MainWeapon));
            CreatePartical(boss1->GetRect(),Type::Object_Hit);
        }
    }
    for(i=0;i<PLAYER_B2_NUMBER;i++){//玩家打中boss判定
        if(boss1->GetAlive()&&P1[k].GetB2(i).GetRect().intersects(boss1->GetRect())){
            boss1->Boss1_UnderAttack(P1[k].Damage(SkillName::SubWeapon));
            CreatePartical(boss1->GetRect(),Type::Object_Hit);
        }
    }
    if(boss1->GetAlive()&&P1[k].GetB3().GetFlash()==3&&
                             P1[k].GetB3().GetAlive()&&
            P1[k].GetB3().GetRect().intersects(boss1->GetRect())){
       boss1->Boss1_UnderAttack(P1[k].Damage(SkillName::Fire));
        CreatePartical(boss1->GetRect(),Type::Player_Damage);
        B3[k]=true;
    }//玩家打中boss判定
    if(B3[k])P1[k].GetB3().PlayerBullet3_Dead();
    }



    for(i=0;i<OBJECT_NUMBER;i++){//B1子弹打方块判定
    if(!object[i]->GetAlive())continue;
    for(l=0;l<PLAYER_NUMBER_MAX;l++){
        if(!P1[l].GetActivate()) continue;
    for(k=0;k<PLAYER_B1_NUMBER;k++){
    if(P1[l].GetB1(k).GetRect().intersects(object[i]->GetRect())){
        if(object[i]->Hit()){
            CreatePartical(object[i]->GetRect(),Type::Object_Hit);
            P1[l].GetB1(k).PlayerBullet1_Dead();
            Play_PlayerHit();
        }
    }
    }
    }
    }//B1子弹打方块判定


    for(i=0;i<OBJECT_NUMBER;i++){//B2子弹打方块判定
    if(!object[i]->GetAlive())continue;
    for(l=0;l<PLAYER_NUMBER_MAX;l++){
        if(!P1[l].GetActivate()) continue;
    for(k=0;k<PLAYER_B2_NUMBER;k++){
    if(P1[l].GetB2(k).GetRect().intersects(object[i]->GetRect())){
        if(object[i]->Hit()){
            CreatePartical(object[i]->GetRect(),Type::Object_Hit);
            P1[l].GetB1(k).PlayerBullet1_Dead();
            Play_PlayerHit();
            P1[l].GetB2(k).Hit();
        }
    }
    }
    }
    }//B2子弹打方块判定

    for(i=0;i<OBJECT_NUMBER;i++){
        if(!object[i]->GetAlive()||object[i]->GetType()==5)continue;
        for(j=0;j<ENEMY_NUMBER;j++){//敌人子弹打方块
            if(!enemy[j].GetAlive())continue;
            for(k=0;k<ENEMY_BULLET_NEMBER;k++){
            if(enemy[j].GetB1(k).GetRect().intersects(object[i]->GetRect())&&object[i]->Hit()){
                enemy[j].GetB1(k).PlayerBullet1_Dead();
                CreatePartical(object[i]->GetRect(),Type::Object_Hit);
            }
            }
        }
    }//子弹打方块


    /*for(i=0;i<Edit_Min;i++){//Boss子弹命中玩家
        if(P1.GetRect().intersects(boss1->GetB2(i).GetRect())&&boss1->GetAlive()){
            P1.Player_UnderAttack(10);
            CreatePartical(P1.GetRect(),Type::Player_Damage);
            boss1->GetB2(i).PlayerBullet2_Dead();
        }
    }
    if(P1.GetRect().intersects(boss1->GetB3().GetRect())&&boss1->GetB3().GetFlash()>=50&&boss1->GetAlive()){//boss技能判定
        P1.Player_UnderAttack(100);
        CreatePartical(P1.GetRect(),Type::Player_Damage);
        boss1->GetB3().PlayerBullet3_Dead();
    }//Boss子弹命中玩家*/


    for(i=0;i<ENEMY_NUMBER;i++){//敌人子弹命中玩家
        if(!enemy[i].GetAlive())continue;
        for(k=0;k<ENEMY_BULLET_NEMBER;k++){
            for(j=0;j<PLAYER_NUMBER_MAX;j++){
                if(!P1[j].GetActivate()) continue;
            if(enemy[i].GetB1(k).GetRect().intersects(P1[j].GetRect())){
                P1[j].Player_UnderAttack(1);
                CreatePartical(P1[j].GetRect(),Type::Player_Damage);
                enemy[i].GetB1(k).PlayerBullet1_Dead();
                Play_PlayerHit_2();
            }
        }
        }
    }//敌人子弹命中玩家f


}//function end
