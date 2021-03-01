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
            case 2:ClearMap(XY(0,600));Load_Map(":/RougeLike/RougeLike/1_2_0.txt");LevelB++;break;
            case 3:ClearMap(XY(300,950));Load_Map(":/RougeLike/RougeLike/1_3_0.txt");LevelB++;break;
            case 4:ClearMap(XY(1450,500));Load_Map(":/RougeLike/RougeLike/1_4_0.txt");LevelB++;break;
            case 5:ClearMap(XY(200,950));Load_Map(":/RougeLike/RougeLike/1_5_0.txt");LevelB++;break;
            case 6:ClearMap(XY(0,800));Load_Map(":/RougeLike/RougeLike/1_6_0.txt");LevelB++;break;
            case 7:ClearMap(XY(200,950));Load_Map(":/RougeLike/RougeLike/1_7_0.txt");LevelB++;break;
            case 8:ClearMap(XY(750,950));Load_Map(":/RougeLike/RougeLike/1_8_0.txt");LevelB++;break;
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
            CreateRedZone(XY(700,400),75,1);
            new(boss1)Boss1(XY(100,300),100,1);
            break;}
        }

    }
}
void BattleWindow::MissionTeach(){
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    enemyall.stop();
   Load_Map(":/maps/maps/1_1.txt");
   CreatePartical(XY(0,0),XY(2000,1000),Type::Dialog1);
}

void BattleWindow::MissionTeach_Win(){
    if(LevelB==3||LevelB==4)return;
        LevelB++;
    switch (LevelB) {
    case 2:
        ClearMap(XY(100,950));
        Load_Map(":/maps/maps/1_2.txt");
        Total_Time=0;Process=0;
        break;
    case 3:
        ClearMap(XY(300,450));
        Load_Map(":/maps/maps/1_3.txt");
        Total_Time=0;Process=0;
        break;
    }
}

void BattleWindow::MissionTick(int Mission){
    if(Mission==1){
    switch (LevelB) {
    case 1:
    {
        if(Total_Time==11){
            Process++;
            CreatePartical(XY(0,500),XY(1500,500),Type::Dialog2);
            P1.SetPos(XY(50,450));
            enemyall.start(100);

        }
        if(P1.GetPos().x<350&&P1.GetPos().y<400&&Process==1){
            Process++;
            CreatePartical(XY(0,500),XY(1500,500),Type::Dialog3);
        }
        if(P1.GetPos().x<350&&P1.GetPos().y>550&&Process==2){
            Process++;
            CreatePartical(XY(0,500),XY(1500,500),Type::Dialog4);
        }
        if(P1.GetPos().x>950&&Process==3){
            Process++;
            XY t={1300,500};
            CreateRedZone(t,100,1);
            CreatePartical(XY(0,500),XY(1500,500),Type::Dialog5);
        }break;}
        break;
    case 2:
        if(Process==0){
            Process++;
            enemyall.stop();
            enemymove.stop();
            CreatePartical(XY(0,500),XY(1500,500),Type::Dialog6);
        }
        if(Process==1&&Total_Time==7){
            enemyall.start(100);
            enemymove.start(50);
        }
        if(P1.GetPos().x>550&&Process==1){
            Process++;
            CreatePartical(XY(0,500),XY(1500,500),Type::Dialog7);
        }
        break;
    case 3:
        if(Process==0){
            Process++;
            CreatePartical(XY(0,500),XY(1500,500),Type::Dialog8);
        }
        if(Total_Time==5){
            Rain.start(400);
        }
        if(Total_Time==22){
            LevelB++;
            XY temp={0,450};
            ClearMap(temp);
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
            P1.Strengthen(-P1.GetHP()+100,0,0,0,0,0);
        }
        if(Process==0&&Total_Time==20){
            P1.Strengthen(-P1.GetHP()+80,0,0,0,0,0);
        }
        if(Process==0&&Total_Time==22){
            P1.Strengthen(-P1.GetHP()+60,0,0,0,0,0);
        }
        if(Process==0&&Total_Time==24){
            P1.Strengthen(-P1.GetHP()+30,0,0,0,0,0);
        }
        if(Process==0&&Total_Time==26){
            P1.Strengthen(-P1.GetHP()+10,0,0,0,0,0);
        }
        if(Process==0&&Total_Time==28){
            P1.Strengthen(-P1.GetHP()-10000,0,0,0,0,0);
        }


        if(Process==1&&Total_Time>=10){
            if(Total_Time==2){
                CreateRedZone(XY(1100,400),300,1);
            }
            QMessageBox::information(nullptr,tr("提示"),tr("新手任务结束"), tr("好"));
            this->~BattleWindow();backto=new MainWindow;
            backto->setMouseTracking(true);backto->show();
        }
        break;
    }
    }
    else if(Mission==2){
        switch (LevelB) {
        case 2:
            if(Total_Time==15){
            CreateRedZone(XY(500,400),150,1);
            }
            if(Total_Time==20){
            CreateRedZone(XY(1168,387),150,1);
            }
            if(Total_Time==25){
            CreateRedZone(XY(767,638),150,1);
            }
            if(Total_Time==30){
            CreateRedZone(XY(176,529),150,1);
            }
            if(Total_Time==33){
            CreateRedZone(XY(150,248),100,1);
            CreateRedZone(XY(550,248),100,1);
            CreateRedZone(XY(950,248),100,1);
            CreateRedZone(XY(1350,248),100,1);
            }
            break;
        case 3:
            if(Total_Time==15){
            CreateRedZone(XY(694,600),150,1);
            }
            if(Total_Time==20){
            CreateRedZone(XY(566,300),150,1);
            }
            if(Total_Time==25){
            CreateRedZone(XY(252,544),100,1);
            }
            if(Total_Time==30){
            CreateRedZone(XY(455,846),100,1);
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
    enemyall.stop();
    P1.SetPos(XY(-1000,-1000));
    LevelB=4;
    Total_Time=0;
    Process=1;
    P1.Strengthen(100000,0,0,0,0,0);
    ClearMap(XY(0,0));
    CreatePartical(XY(0,0),XY(2000,1000),Type::DialogEnd);

}
