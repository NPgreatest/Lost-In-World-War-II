#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"

void BattleWindow::Bullet_HitCheck(){
    int i,k,j;
    bool B3[PLAYER_NUMBER_MAX]={0,0,0,0,0,0,0,0,0,0};
    //子弹命中敌人

    //新B1子弹所有判定
    for(i=0;i<PLAYER_B1_NUMBER;i++){
        if(!bullet1[i].GetAlive()) continue;
    //未激活则下一个

        //方块判定
        for(k=0;k<OBJECT_NUMBER;k++){
                if(!object[k]->GetAlive()||(bullet1[i].GetMaster()==-1&&object[k]->GetType()==5)) continue;//敌人不会打兵营
                if(bullet1[i].GetRect().intersects(object[k]->GetRect())&&object[k]->Hit()){
                        CreatePartical(object[k]->GetRect(),Type::Object_Hit);
                        bullet1[i].PlayerBullet1_Dead();
                        allmusic.PlayHitMusic(settings.sound);
                }
        }
        //方块判定

        //玩家和敌人判定
        switch (bullet1[i].GetTarget()){
        case Target::OBJECT:break;
        case Target::ALL:
        case Target::ENEMY:
            for(k=0;k<ENEMY_NUMBER;k++){//子弹打中敌人
                if(!enemy[k].GetAlive())continue;
                if(bullet1[i].GetRect().intersects(enemy[k].GetRect())){
                    enemy[k].Enemy_UnderAttack(bullet1[i].GetDamage());
                    bullet1[i].PlayerBullet1_Dead();
                    allmusic.PlayHit2Music(settings.sound);
                    if(!enemy[k].GetAlive())CreatePartical(enemy[k].GetRect().adjusted(-50,-50,100,100),Type::Object_Hit);
                    else {CreatePartical(enemy[k].GetRect(),Type::Object_Hit);}
                    }
            }
                    if(bullet1[i].GetAlive() && boss1->GetAlive() && bullet1[i].GetRect().intersects(boss1->GetRect())){
                        bullet1[i].PlayerBullet1_Dead();
                        boss1->Boss1_UnderAttack(bullet1[i].GetDamage());
                        CreatePartical(boss1->GetRect(),Type::Object_Hit);
                    }

            if(bullet1[i].GetTarget()==Target::ENEMY)break;
        case Target::PLAYER:
            for(k=0;k<PLAYER_NUMBER_MAX;k++){
                if(!P1[k].GetActivate()||k==bullet1[i].GetMaster())continue;//玩家友伤不会命中自己
                if(bullet1[i].GetRect().intersects(P1[k].GetRect())){
                    P1[k].Player_UnderAttack(bullet1[i].GetDamage(),settings.gamemode==0?true:false);
                    CreatePartical(P1[k].GetRect(),Type::Player_Damage);
                    CreatePartical(P1[k].GetRect(),Type::Explotion);
                    bullet1[i].PlayerBullet1_Dead();
                    allmusic.PlayHit2Music(settings.sound);
                }
            }
            if(bullet1[i].GetTarget()==Target::PLAYER)break;
        }
        //玩家和敌人判定
     }





    //B2子弹
    for(i=0;i<PLAYER_B2_NUMBER;i++){
        if(!bullet2[i].GetAlive()) continue;//未激活则下一个
        //方块判定
        for(k=0;k<OBJECT_NUMBER;k++){
                if(!object[k]->GetAlive()||(bullet2[i].GetMaster()==100&&object[k]->GetType()==5))continue;//敌人不会打兵营
                if(bullet2[i].GetRect().intersects(object[k]->GetRect())&&object[k]->Hit()){
                        CreatePartical(object[k]->GetRect(),Type::Object_Hit);
                        bullet2[i].PlayerBullet2_Dead();
                        allmusic.PlayHitMusic(settings.sound);
                }
        }
        //方块判定

        //玩家和敌人判定
        switch (bullet2[i].GetTarget()){
        case Target::OBJECT:break;
        case Target::ALL:
        case Target::ENEMY:
            for(k=0;k<ENEMY_NUMBER;k++){//子弹打中敌人
                if(!enemy[k].GetAlive())continue;
                if(bullet2[i].GetRect().intersects(enemy[k].GetRect())){
                    enemy[k].Enemy_UnderAttack(bullet2[i].GetDamage());
                    bullet2[i].PlayerBullet2_Dead();
                    allmusic.PlayHit2Music(settings.sound);
                    if(!enemy[k].GetAlive())CreatePartical(enemy[k].GetRect().adjusted(-50,-50,100,100),Type::Object_Hit);
                    else {CreatePartical(enemy[k].GetRect(),Type::Object_Hit);}
                    }
            }
                 if(boss1->GetAlive()&&bullet2[i].GetRect().intersects(boss1->GetRect())){
                     boss1->Boss1_UnderAttack(bullet2[i].GetDamage());
                     CreatePartical(boss1->GetRect(),Type::Object_Hit);
                     bullet2[i].Hit();
                     allmusic.PlayHit2Music(settings.sound);
                 }
            if(bullet2[i].GetTarget()==Target::ENEMY)break;
        case Target::PLAYER:
            for(k=0;k<PLAYER_NUMBER_MAX;k++){
                if(!P1[k].GetActivate()||k==bullet2[i].GetMaster())continue;//玩家友伤不会命中自己
                if(bullet2[i].GetRect().intersects(P1[k].GetRect())){
                    P1[k].Player_UnderAttack(bullet2[i].GetDamage(),settings.gamemode==0?true:false);
                    CreatePartical(P1[k].GetRect(),Type::Player_Damage);
                    CreatePartical(P1[k].GetRect(),Type::Explotion);
                    bullet2[i].PlayerBullet2_Dead();
                    allmusic.PlayHit2Music(settings.sound);
                }
            }
            if(bullet2[i].GetTarget()==Target::PLAYER)break;
        }
        //玩家和敌人判定
    }



    //子弹命中敌人B3
    for(i=0;i<ENEMY_NUMBER;i++){//
    if(!enemy[i].GetAlive())continue;
    for(j=0;j<PLAYER_NUMBER_MAX;j++){
        if(!P1[j].GetActivate()) continue;
    if(P1[j].GetB3().GetFlash()==3&&P1[j].GetB3().GetAlive()){
        if(P1[j].GetB3().GetRect().intersects(enemy[i].GetRect())){
            enemy[i].Enemy_UnderAttack(P1[j].Damage(SkillName::Fire));
            CreatePartical(enemy[i].GetRect(),Type::Player_Damage);
            B3[j]=true;
            }
        }
    }
    }
    //子弹命中敌人B3

    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate()) continue;
    if(boss1->GetAlive()&&P1[i].GetB3().GetFlash()==3&&
                             P1[i].GetB3().GetAlive()&&
            P1[i].GetB3().GetRect().intersects(boss1->GetRect())){
       boss1->Boss1_UnderAttack(P1[i].Damage(SkillName::Fire));
        CreatePartical(boss1->GetRect(),Type::Player_Damage);
        B3[i]=true;
    }//玩家打中boss判定
    if(B3[i])P1[i].GetB3().PlayerBullet3_Dead();
    if(P1[i].GetRect().intersects(boss1->GetB3().GetRect())&&boss1->GetB3().GetFlash()>=50&&boss1->GetAlive()){//boss技能判定
        P1[i].Player_UnderAttack(100,settings.gamemode==0?true:false);
        allmusic.PlayHit2Music(settings.sound);
        CreatePartical(P1[i].GetRect(),Type::Player_Damage);
        boss1->GetB3().PlayerBullet3_Dead();
    }//Boss子弹命中玩
    }

}//function end
