#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"


void BattleWindow::MissionRougueLike(){
Load_Map(":/RougeLike/RougeLike/1_1_0.txt");
LevelB++;
}
void BattleWindow::MissionRougueLike_Win(){
    if (Win==false)return;
    switch (LevelA) {
    case 1: Map=LevelB;
            Total_Time=0;
            switch (LevelB) {
            case 2:ClearMap(QRect(0,600,40,40));Load_Map(":/RougeLike/RougeLike/1_2_0.txt");LevelB++;break;
            case 3:ClearMap(QRect(300,950,40,40));Load_Map(":/RougeLike/RougeLike/1_3_0.txt");LevelB++;break;
            case 4:ClearMap(QRect(1450,500,40,40));Load_Map(":/RougeLike/RougeLike/1_4_0.txt");LevelB++;break;
            case 5:ClearMap(QRect(200,950,40,40));Load_Map(":/RougeLike/RougeLike/1_5_0.txt");LevelB++;break;
            case 6:ClearMap(QRect(0,800,40,40));Load_Map(":/RougeLike/RougeLike/1_6_0.txt");LevelB++;break;
            case 7:ClearMap(QRect(200,950,40,40));Load_Map(":/RougeLike/RougeLike/1_7_0.txt");LevelB++;break;
            case 8:ClearMap(QRect(750,950,40,40));Load_Map(":/RougeLike/RougeLike/1_8_0.txt");LevelB++;break;
            case 9:QMessageBox::information(nullptr,tr("恭喜"),tr("您通关了"), tr("好"));
                this->~BattleWindow();backto=new MainWindow;
                backto->setMouseTracking(true);backto->show();break;
            }
    case 2:break;
    }
}
void BattleWindow::MissionRougueLike_Continue(){
    switch (LevelA) {
    case 1:
        switch (Map) {
        case 3:Map++;Load_Map(":/RougeLike/RougeLike/1_3_1.txt");break;
        case 8:Map++;Load_Map(":/RougeLike/RougeLike/1_8_1.txt");break;
        case 9:{Map++;Load_Map(":/RougeLike/RougeLike/1_8_2.txt");
            CreateRedZone(QRect(700,400,300,300),75,1);
            new(boss1)Boss1(QRect(100,300,150,150),100,1);
            break;}
        }

    }
}
void BattleWindow::MissionTeach(){
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    EnemyAll.stop();
   Load_Map(":/maps/maps/1_1.txt");
   CreatePartical(QRect(0,0,2000,1000),Type::Dialog1);
}

void BattleWindow::MissionTeach_Win(){
    if(LevelB==3||LevelB==4)return;
        LevelB++;
    switch (LevelB) {
    case 2:
        ClearMap(QRect(100,950,40,40));
        Load_Map(":/maps/maps/1_2.txt");
        Total_Time=0;Process=0;
        break;
    case 3:
        ClearMap(QRect(300,450,40,40));
        Load_Map(":/maps/maps/1_3.txt");
        Total_Time=0;Process=0;
        break;
    }
}

void BattleWindow::MissionTick(){
    //qDebug()<<LevelB;
    if(Mission==1){
    switch (LevelB) {
    case 1:
    {
        if(Total_Time==11){
            Process++;
            CreatePartical(QRect(0,500,1500,500),Type::Dialog2);
            P1[0].SetPos(QRect(50,450,40,40));
            EnemyAll.start(100);
        }
        if(P1[0].GetRect().x()<350&&P1[0].GetRect().y()<400&&Process==1){
            Process++;
            CreatePartical(QRect(0,500,1500,500),Type::Dialog3);
        }
        if(P1[0].GetRect().x()<350&&P1[0].GetRect().y()>550&&Process==2){
            Process++;
            CreatePartical(QRect(0,500,1500,500),Type::Dialog4);
        }
        if(P1[0].GetRect().x()>950&&Process==3){
            Process++;
            CreateRedZone(QRect(1300,500,100,100),100,1);
            CreatePartical(QRect(0,500,1500,500),Type::Dialog5);
        }break;}
        break;
    case 2:
        if(Process==0){
            Process++;
            EnemyAll.stop();
            EnemyMove.stop();
            CreatePartical(QRect(0,500,1500,500),Type::Dialog6);
        }
        if(Process==1&&Total_Time==7){
            EnemyAll.start(100);
            EnemyMove.start(50);
        }
        if(P1[0].GetRect().x()>550&&Process==1){
            Process++;
            CreatePartical(QRect(0,500,1500,500),Type::Dialog7);
        }
        break;
    case 3:
        if(Process==0){
            Process++;
            CreatePartical(QRect(0,500,1500,500),Type::Dialog8);
        }
        if(Total_Time==5){
            Rain.start(400);
        }
        if(Total_Time==22){
            LevelB++;
            ClearMap(QRect(0,450,40,40));
            Load_Map(":/maps/maps/1_4.txt");
            Total_Time=0;
            Process=0;
        }
        break;
    case 4:
        if(Process==0&&Total_Time==5){
            Load_Map(":/maps/maps/1_5.txt");
            Load_Map(":/maps/maps/1_5.txt");
        }
        if(Process==0&&Total_Time==10){
            Load_Map(":/maps/maps/1_6.txt");
        }
        if(Process==0&&Total_Time==15){
            P1[0].Strengthen(-P1[0].GetHP()+100,0,0,0);
        }
        if(Process==0&&Total_Time==20){
            P1[0].Strengthen(-P1[0].GetHP()+80,0,0,0);
        }
        if(Process==0&&Total_Time==22){
            P1[0].Strengthen(-P1[0].GetHP()+60,0,0,0);
        }
        if(Process==0&&Total_Time==24){
            P1[0].Strengthen(-P1[0].GetHP()+30,0,0,0);
        }
        if(Process==0&&Total_Time==26){
            P1[0].Strengthen(-P1[0].GetHP()+10,0,0,0);
        }
        if(Process==0&&Total_Time==28){
            P1[0].Strengthen(-P1[0].GetHP()-10000,0,0,0);
        }


        if(Process==1&&Total_Time>=10){
            if(Total_Time==2){
                CreateRedZone(QRect(1100,400,40,40),300,1);
            }
            QMessageBox::information(nullptr,tr("提示"),tr("新手任务结束"), tr("好"));
            this->~BattleWindow();backto=new MainWindow;
            backto->setMouseTracking(true);backto->show();
        }
        break;
    }
    }
    if(Mission==2){
        switch (LevelB) {
        case 2:
            if(Total_Time==15){         
            CreateRedZone(QRect(500,400,40,40),150,1);
            }
            if(Total_Time==20){
            CreateRedZone(QRect(1168,387,40,40),150,1);
            }
            if(Total_Time==25){
            CreateRedZone(QRect(767,638,40,40),150,1);
            }
            if(Total_Time==30){
            CreateRedZone(QRect(176,529,40,40),150,1);
            }
            if(Total_Time==33){
            CreateRedZone(QRect(150,248,40,40),100,1);
            CreateRedZone(QRect(550,248,40,40),100,1);
            CreateRedZone(QRect(950,248,40,40),100,1);
            CreateRedZone(QRect(1350,248,40,40),100,1);
            }
            break;
        case 3:
            if(Total_Time==15){
            CreateRedZone(QRect(694,600,40,40),150,1);
            }
            if(Total_Time==20){
            CreateRedZone(QRect(566,300,40,40),150,1);
            }
            if(Total_Time==25){
            CreateRedZone(QRect(252,544,40,40),100,1);
            }
            if(Total_Time==30){
            CreateRedZone(QRect(455,846,40,40),100,1);
            }
        case 4:
        case 5:
        case 6:
        case 7:break;
        case 8:break;
        }
    }
}
void BattleWindow::MissionTechEnd(){
    EnemyAll.stop();
    P1[0].SetPos(QRect(-1000,-1000,40,40));
    LevelB=4;
    Total_Time=0;
    Process=1;
    P1[0].Strengthen(100000,0,0,0);
    ClearMap(QRect(0,0,40,40));
    CreatePartical(QRect(0,0,2000,1000),Type::DialogEnd);

}
