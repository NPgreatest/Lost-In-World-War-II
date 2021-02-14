#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"
BattleWindow::BattleWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::BattleWindow){


    ui->setupUi(this);
    setPalette(QPalette(Qt::yellow));
    setAutoFillBackground(true);
    this->setStyleSheet("#BattleWindow{border-image:url(:/Images/Images/BattleGround.png);}");
    setWindowIcon(QIcon(":/Images/Images/icon.png"));
}

void BattleWindow::Load_Map(QString Address){
    int i=0,read=0,tlv,tmat,tb1c;
    bool me=false;
    XY P;int thp,tmp;
    XY pos[Edit_Max]={0,0};
    XY area[Edit_Max]={0,0};
    int type[Edit_Max]={0};
    int skin[Edit_Max]={0};
    int hp[Edit_Max]={1};
    int e_hp[Edit_Max]={0};
    int e_speed[Edit_Max]={0};
    int e_bullet_speed[Edit_Max]={0};
    XY e_pos[Edit_Max]={0,0},e_area[Edit_Max]={0,0};
    int e_skin[Edit_Max]={0};


    QFile file(Address);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(nullptr,tr("提示"),tr("加载地图失败"), tr("好"));
        this->~BattleWindow();backto=new MainWindow;
        backto->setMouseTracking(true);backto->show();return;
    }
    QTextStream input(&file);
    while(!input.atEnd()){
        QString line=input.readLine();
        QStringList list=line.split(" ");
        if(line=="CObject:"){
            read=1;i=0;
        continue;
        }
        if(line=="CPlayer:"){
            me=true;
            read=2;i=0;
        continue;
        }
        if(line=="CEnemy:"){
            read=3;i=0;
            continue;
        }
        switch (read) {
        case 1:
            type[i]=list[0].toInt();
            pos[i].x=list[1].toInt();
            pos[i].y=list[2].toInt();
            area[i].x=list[3].toInt();
            area[i].y=list[4].toInt();
            hp[i]=list[5].toInt();
            skin[i]=list[6].toInt();
            i++;break;
        case 2:
            P.x=list[0].toInt();
            P.y=list[1].toInt();
            thp=list[2].toInt();
            tmp=list[3].toInt();
            tlv=list[4].toInt();
            tmat=list[5].toInt();
            tb1c=list[6].toInt();
            break;
        case 3:
            e_pos[i].x=list[0].toInt();
            e_pos[i].y=list[1].toInt();
            e_area[i].x=list[2].toInt();
            e_area[i].y=list[3].toInt();
            e_hp[i]=list[4].toInt();
            e_speed[i]=list[5].toInt();
            e_bullet_speed[i]=list[6].toInt();
            e_skin[i]=list[7].toInt();
            i++;break;
        default:break;
        }
    }
    file.close();
    qDebug()<<"1!!!!";
    if(me==true)
        new(&P1)Player(P,thp,tmp,tlv,tmat,tb1c);
    for(i=0;i<Edit_Max;i++){
        CreateObject(pos[i],area[i],type[i],skin[i],hp[i]);
    }

for(i=0;i<Edit_Max;i++){
     if(e_area[i].x==0||e_area[i].y==0)continue;
     CreatePartical(e_pos[i],e_area[i],10,1);
     CreateEnemy(e_pos[i],e_area[i],e_hp[i],e_speed[i],e_bullet_speed[i],e_skin[i]);
    }

}


void BattleWindow::Load_Status(bool intro,int x){
    XY temp={200,200};
   // new(boss1)Boss1(temp,100,1);
  //  boss1->Boss1_ChangeHead(2);
    Mission=x;
    int i,k;
    Object_Number[0][0].load(":/Images/Tank/TankUp.png");
    Object_Number[0][1].load(":/Images/Tank/TankDown.png");
    Object_Number[0][2].load(":/Images/Tank/TankLeft.png");
    Object_Number[0][3].load(":/Images/Tank/TankRight.png");
    Object_Number[1][1].load(":/Images/Object/Wall1.png");
    Object_Number[1][2].load(":/Images/Object/Wall2.png");
    Object_Number[2][1].load(":/Images/Object/BedRock1.png");
    Object_Number[2][2].load(":/Images/Object/BedRock2.png");
    Object_Number[3][1].load(":/Images/Object/River1.jpg");
    Object_Number[3][2].load(":/Images/Object/River2.jpg");
    Object_Number[4][1].load(":/Images/Object/Portal.png");
    Object_Number[5][1].load(":/Images/Object/Camp1.jpg");
    Object_Number[6][1].load(":/Images/Object/FirstAid1.png");
    Object_Number[7][1].load(":/Images/Object/Weapon1.png");
    Object_Number[8][1].load(":/Images/Object/Camp2.jpg");
    Object_Number[9][1].load(":/Images/Object/FirstAid2.png");
    Object_Number[10][1].load(":/Images/Object/Weapon2.png");
    Object_Number[11][1].load(":/Images/Object/Camp3.jpg");
    Object_Number[12][1].load(":/Images/Object/FirstAid3.png");
    Object_Number[13][1].load(":/Images/Object/Weapon3.png");
    Object_Number[14][1].load(":/Images/Object/Ruins1.png");
    Object_Number[14][2].load(":/Images/Object/Ruins2.png");
    Object_Number[15][1].load(":/Images/Object/Grass1.png");
    Object_Number[15][12].load(":/Images/Object/Grass2.png");
    Object_Number[16][1].load(":/Images/Object/Nail1.png");
    Object_Number[16][2].load(":/Images/Object/Nail2.png");
    Object_Number[17][1].load(":/Images/Object/ice1.png");
    Object_Number[17][2].load(":/Images/Object/ice2.png");
    for(i=1;i<20;i++)
        for(k=0;k<10;k++)
            Object_Number[i][k]=Image_Cut(Object_Number[i][k]);
    RedZone_Image[0].load(":/Images/Tank/RedZone1.png");
    RedZone_Image[1].load(":/Images/Tank/RedZone1.png");
    RedZone_Image[2].load(":/Images/Tank/RedZone1.png");
    RedZone_Image[3].load(":/Images/Tank/RedZone1.png");
    RedZone_Image[4].load(":/Images/Tank/RedZone1.png");
    RedZone_Image[5].load(":/Images/Tank/RedZone2.png");
    RedZone_Image[0]=Image_Transparent(RedZone_Image[0],50);
    RedZone_Image[1]=Image_Transparent(RedZone_Image[1],100);
    RedZone_Image[2]=Image_Transparent(RedZone_Image[2],150);
    RedZone_Image[3]=Image_Transparent(RedZone_Image[3],200);
    RedZone_Image[4]=Image_Transparent(RedZone_Image[4],255);
    RedZone_Image[5]=Image_Transparent(RedZone_Image[5],255);
    Partical_Image[1][1].load(":/Images/Particals/Boom1.png");
    Partical_Image[1][2].load(":/Images/Particals/Boom2.png");
    Partical_Image[1][3].load(":/Images/Particals/Boom3.png");
    Partical_Image[1][4].load(":/Images/Particals/Boom4.png");
    Partical_Image[1][5].load(":/Images/Particals/Boom5.png");
    Partical_Image[1][6].load(":/Images/Particals/Boom6.png");
    Partical_Image[2][1].load(":/Images/Particals/Shot3_1.png");
    Partical_Image[2][2].load(":/Images/Particals/Shot3_2.png");
    Partical_Image[2][3].load(":/Images/Particals/Shot3_3.png");
    Partical_Image[2][4].load(":/Images/Particals/Shot3_4.png");//粒子图片

    Partical_Image[3][1].load(":/Images/Particals/Damage1.png");//粒子图片
    Partical_Image[3][2].load(":/Images/Particals/Damage2.png");//粒子图片
    Partical_Image[3][3].load(":/Images/Particals/Damage3.png");//粒子图片
    Partical_Image[3][4].load(":/Images/Particals/Damage4.png");//粒子图片
    Partical_Image[3][5].load(":/Images/Particals/Damage5.png");//粒子图片
    Partical_Image[3][6].load(":/Images/Particals/Damage6.png");//粒子图片
    Partical_Image[3][7].load(":/Images/Particals/Damage7.png");//粒子图片

    Partical_Image[3][1].fill(QColor(255,255,255,150));
    Partical_Image[3][2].fill(QColor(255,200,200,150));
    Partical_Image[3][3].fill(QColor(255,150,150,150));
    Partical_Image[3][4].fill(QColor(255,150,150,200));
    Partical_Image[3][5].fill(QColor(255,100,100,200));
    Partical_Image[3][6].fill(QColor(255,50,50,210));
    Partical_Image[3][7].fill(QColor(255,0,0,255));


    Partical_Image[4][1].load(":/Images/Particals/Mist1");//粒子图片
    Partical_Image[4][2].load(":/Images/Particals/Mist2");//粒子图片
    Partical_Image[4][3].load(":/Images/Particals/Mist3");//粒子图片
    Partical_Image[4][4].load(":/Images/Particals/Mist4");//粒子图片
    Partical_Image[4][5].load(":/Images/Particals/Mist5");//粒子图片
    Partical_Image[4][6].load(":/Images/Particals/Mist6");//粒子图片
    Partical_Image[4][7].load(":/Images/Particals/Mist7");//粒子图片
    Partical_Image[4][8].load(":/Images/Particals/Mist8");//粒子图片
    Partical_Image[4][9].load(":/Images/Particals/Mist9");//粒子图片
    Partical_Image[4][10].load(":/Images/Particals/Mist10");//粒子图片
  //  Partical_Image[5][1].load();

    Enemy_Image[0][0].load(":/Images/Tank/EnemyUp_1.png");
    Enemy_Image[0][1].load(":/Images/Tank/EnemyDown_1.png");
    Enemy_Image[0][2].load(":/Images/Tank/EnemyLeft_1.png");
    Enemy_Image[0][3].load(":/Images/Tank/EnemyRight_1.png");
    Enemy_Image[1][0].load(":/Images/Tank/EnemyUp_1.png");
    Enemy_Image[1][1].load(":/Images/Tank/EnemyDown_1.png");
    Enemy_Image[1][2].load(":/Images/Tank/EnemyLeft_1.png");
    Enemy_Image[1][3].load(":/Images/Tank/EnemyRight_1.png");
    Enemy_Image[2][0].load(":/Images/Tank/EnemyUp_2.png");
    Enemy_Image[2][1].load(":/Images/Tank/EnemyDown_2.png");
    Enemy_Image[2][2].load(":/Images/Tank/EnemyLeft_2.png");
    Enemy_Image[2][3].load(":/Images/Tank/EnemyRight_2.png");
    Enemy_Image[3][0].load(":/Images/Tank/EnemyUp_3.png");
    Enemy_Image[3][1].load(":/Images/Tank/EnemyDown_3.png");
    Enemy_Image[3][2].load(":/Images/Tank/EnemyLeft_3.png");
    Enemy_Image[3][3].load(":/Images/Tank/EnemyRight_3.png");
    Enemy_Image[4][0].load(":/Images/Tank/EnemyUp_4.png");
    Enemy_Image[4][1].load(":/Images/Tank/EnemyDown_4.png");
    Enemy_Image[4][2].load(":/Images/Tank/EnemyLeft_4.png");
    Enemy_Image[4][3].load(":/Images/Tank/EnemyRight_4.png");
    Enemy_Image[5][0].load(":/Images/Tank/EnemyUp_5.png");
    Enemy_Image[5][1].load(":/Images/Tank/EnemyDown_5.png");
    Enemy_Image[5][2].load(":/Images/Tank/EnemyLeft_5.png");
    Enemy_Image[5][3].load(":/Images/Tank/EnemyRight_5.png");
    Bar[0].load(":/Images/Images/Bar1.png");
    Bar[1].load(":/Images/Images/Bar2.png");
    Bar[2].load(":/Images/Images/Bar3.png");
    Bar[3].load(":/Images/Images/Bar4.png");
    Bar[4].load(":/Images/Images/Bar5.png");
    Skill_Select[0].load(":/Images/Images/SkillSelect.png");
    Skill_Select[1].load(":/Images/Tank/Bullet1.png");
    Skill_Select[2].load(":/Images/Tank/Bullet2.png");
    Skill_Select[3].load(":/Images/Tank/Bullet3.png");
    Bullet_Sound->setMedia(QUrl("qrc:/sounds/sounds/Player_Hit1.mp3"));
    RedZone_Sound->setMedia(QUrl("qrc:/sounds/sounds/RedZone.mp3"));
    MPOut->setMedia(QUrl("qrc:/sounds/sounds/Wrong.mp3"));



    QTimer *timer = new QTimer(this);//QTImer启动
    QTimer *flash = new QTimer(this);
    QTimer *enemymove = new QTimer(this);
    QTimer *enemyall = new QTimer(this);
    QTimer *generate = new QTimer(this);
    QTimer *boom = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(bulletfly()));//出大问题
    connect(flash, SIGNAL(timeout()), this, SLOT(Flash()));
    connect(&move, SIGNAL(timeout()), this, SLOT(Move()));
    connect(&fix,  SIGNAL(timeout()), this, SLOT(P1_Fix()));
    connect(enemymove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
    connect(enemymove, SIGNAL(timeout()), this, SLOT(Boss_Move()));
    connect(enemyall, SIGNAL(timeout()), this, SLOT(Enemy_All()));
    connect(generate, SIGNAL(timeout()), this, SLOT(Enemy_Generate()));
    connect(boom, SIGNAL(timeout()), this, SLOT(Flash2()));

      boom->start(50);
      timer->start(10);
      flash->start(1000);
      enemymove->start(50);
      enemyall->start(100);
      generate->start(5000);//QTimer



    if(intro==true){this->Load_Introduce();QTimer *timer = new QTimer(this);//介绍模式
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(10);
        return;}
    BackGroundMusic->setMedia(QUrl("qrc:/sounds/sounds/BattleMusic1.mp3"));
    BackGroundMusic->setVolume(100);
    BackGroundMusic->play();
    switch (x) {
    case 1:Mission1();return;
    case 2:Mission2();return;
    case 100:MissionRougueLike();return;
    }

    Red_Zone_Fre=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸频率/ms"),5000,100,20000,100,nullptr,nullptr);
    Red_Zone=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸几率%"),50,0,100,1,nullptr,nullptr);
    QString Address = QFileDialog::getOpenFileName(this,tr("选择地图"),nullptr, tr("Image Files (*.txt)"));
    Load_Map(Address);
    //QTimer
      QTimer *redzone=new QTimer(this);
      connect(redzone, SIGNAL(timeout()), this, SLOT(RedZone_Generate()));
      redzone->start(Red_Zone_Fre);

}

BattleWindow::~BattleWindow(){}

void BattleWindow::RedZone_Generate(){
    int i,x,r,type;
    XY pos;
    x = QRandomGenerator::global()->generate();
    if(x%(100/Red_Zone)!=0)return;
    for(i=0;i<Edit_Min;i++){
    if(redzone[i].GetAlive()==true)continue;
    pos.x=QRandomGenerator::global()->bounded(0,X_Max);
    pos.y=QRandomGenerator::global()->bounded(0,Y_Max);
    r=QRandomGenerator::global()->bounded(50,200);
    type=QRandomGenerator::global()->bounded(1,4);
    new(&redzone[i])RedZone(pos,r,type);
    redzone[i].Flash_Begin();
    return;
}
}


void BattleWindow::Flash(){//1秒刷新一次
    int i;
    Total_Time++;
    CreatePartical(P1.GetPos(),P1.GetArea(),11,4);
    switch (Mission) {
    case 1:Mission1_J();break;
    }
    for(i=0;i<Edit_Max;i++){//物体动画
        if(object[i].GetAlive()==false)continue;
        if(object[i].GetHP()==-1&&object[i].GetType()==2){object[i].Hit();}
        if(object[i].GetType()==3) object[i].Hit();
        if(object[i].GetType()==17) object[i].Hit();
        if(object[i].GetType()==16) {object[i].Hit();object[i].SetOther(0);}
    }
    for(i=0;i<Edit_Min;i++){//轰炸区动画
        if(redzone[i].GetAlive()==false)continue;
        if(redzone[i].GetFlash()==-1)continue;
        if(redzone[i].GetFlash()==4)RedZoneBoom(i);
        redzone[i].Flash();
    }
    for(i=0;i<Edit_Min;i++){//敌人AI
        if(enemy[i].GetAlive()==false)continue;
        if(enemy[i].GetSkin()==3||enemy[i].GetSkin()==4){
            enemy[i].Enemy_ChangeHead(AI1(P1.GetPos(),enemy[i].GetPos()));
        }
    }
    if(boss1->GetAlive()==true)boss1->Boss1_ChangeHead(AI1(P1.GetPos(),boss1->GetPos()));//boss AI
     if(QRandomGenerator::global()->generate()%2==0&&boss1->GetAlive()==true){
         boss1->Boss1_B3Fire();
         XY t1=boss1->GetPos();XY t2=boss1->GetPos();
         switch (boss1->GetHead()) {
         case UP:t1.y=0;t2={150,boss1->GetPos().y}; CreatePartical(t1,t2,10,1);break;
         case DOWN:t2={150,1000};CreatePartical(t1,t2,10,1);break;
         case LEFT:t1.x=0;t2={boss1->GetPos().x,150};CreatePartical(t1,t2,10,1);break;
         case RIGHT:t2={10000,150};CreatePartical(t1,t2,10,1);break;
         }
     }

     //判断敌人是否
    Win=true;
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==true)Win=false;
        if(object[i].GetAlive()==true&&(object[i].GetType()==5||object[i].GetType()==8||object[i].GetType()==11))Win=false;
    }
    if(Win==true){
        switch (Mission) {
        case 1:{XY t={0,0};ClearMap(t);Load_Map(":/maps/maps/1_2.txt");Mission++;break;}
        case 100:MissionRougueLike_Continue();return;
        }

        }
     /*   QMessageBox::information(nullptr,tr("恭喜"),tr("您赢了"), tr("好"));
        this->~BattleWindow();backto=new MainWindow;
        backto->setMouseTracking(true);backto->show();*/
}


void BattleWindow::Flash2(){
    int i;
    P1.Player_Bullet3Flash();
    boss1->Boss1_Bullet3Flash();
    for(i=0;i<Edit_Max;i++){
        if(partical[i].GetAlive()==false)continue;
        partical[i].FLash();
    }
}


void BattleWindow::RedZoneBoom(int x){
    Play_RedZone();
    int i;
    for(i=0;i<Edit_Max;i++){
    if(object[i].GetAlive()==false)continue;
    if(redzone[x].Object_Hit(object[i].GetPos(),object[i].GetArea())==true){
        object[i].Dead();
    }
}
    for(i=0;i<Edit_Max;i++){
    if(enemy[i].GetAlive()==false)continue;
    if(redzone[x].Object_Hit(enemy[i].GetPos(),enemy[i].GetArea())==true){
        enemy[i].Dead();
    }
}
    if(redzone[x].Object_Hit(P1.GetPos(),P1.GetArea())==true){
        P1.Player_UnderAttack(100);

    }
}
void BattleWindow::bulletfly(){//子弹
int i;
P1.Player_B1_Move();
P1.Player_B2_Move();
for(i=0;i<Edit_Max;i++){
    enemy[i].Enemy_B1_Move();
}
if(boss1->GetAlive()==true){
        boss1->Boss1_B1_Move();
}
Bullet_HitCheck();
}
void BattleWindow::Bullet_HitCheck(){
    int i,k,j;XY temp={50,50};bool B3=false;
    for(i=0;i<Edit_Max;i++){//子弹命中敌人
    if(enemy[i].GetAlive()==false)continue;
    for(k=0;k<P1.GetBulletC();k++){//for
    if(P1.Player_Bullet1Hit(k,enemy[i].GetPos(),enemy[i].GetArea())==true){
        enemy[i].Enemy_UnderAttack(P1.GetWeaponLv()+5);//子弹等级+5
        P1.Player_B1_Hit(k);
            if(enemy[i].GetAlive()==false)CreatePartical(enemy[i].GetPos()-temp,enemy[i].GetArea()+temp+temp,5,1);
            else {CreatePartical(enemy[i].GetPos(),enemy[i].GetArea(),5,1);}
        }
    }//end for
    if(P1.Player_Bullet2Hit(enemy[i].GetPos(),enemy[i].GetArea())==true){
        enemy[i].Enemy_UnderAttack(P1.GetWeaponLv());//子弹等级
            if(enemy[i].GetAlive()==false)CreatePartical(enemy[i].GetPos()-temp,enemy[i].GetArea()+temp+temp,5,1);
            else {CreatePartical(enemy[i].GetPos(),enemy[i].GetArea(),5,1);}

        }
    if(P1.GetBullet3Flash()==3&&P1.GetBullet3Alive()==true){
        if(P1.Player_Bullet3Hit(enemy[i].GetPos(),enemy[i].GetArea())==true){
            enemy[i].Enemy_UnderAttack(P1.GetWeaponLv()/5==0?1:P1.GetWeaponLv()/5);//子弹等级除以5
            B3=true;
            }
        }
    }//子弹命中敌人
    if(B3==true)P1.Player_B3_Hit();
    for(i=0;i<P1.GetBulletC();i++){//玩家打中boss判定
        if(P1.Player_Bullet1Hit(i,boss1->GetPos(),boss1->GetArea())==true){
            P1.Player_B1_Hit(i);boss1->Boss1_UnderAttack(P1.GetWeaponLv()+5);
            CreatePartical(boss1->GetPos(),boss1->GetArea(),10,1);
        }
    }
    if(P1.Player_Bullet2Hit(boss1->GetPos(),boss1->GetArea())==true){
        boss1->Boss1_UnderAttack(P1.GetWeaponLv());
        CreatePartical(boss1->GetPos(),boss1->GetArea(),10,1);
    }
    if(P1.GetBullet3Flash()==3&&P1.GetBullet3Alive()==true&&P1.Player_Bullet3Hit(boss1->GetPos(),boss1->GetArea())==true){
       boss1->Boss1_UnderAttack(P1.GetWeaponLv()/5==0?1:P1.GetWeaponLv()/5);
        CreatePartical(boss1->GetPos(),boss1->GetArea(),10,1);
    }//玩家打中boss判定

    for(i=0;i<Edit_Max;i++){//子弹打方块
    if(object[i].GetAlive()==false)continue;
    switch (object[i].GetType()) {
    case 1:
    case 5:
    case 8:
    case 11:
        for(k=0;k<P1.GetBulletC();k++){//for
        if(P1.Player_Bullet1Hit(k,object[i].GetPos(),object[i].GetArea())==true){
            object[i].Hit();P1.Player_B1_Hit(k);Play_PlayerHit();
                CreatePartical(object[i].GetPos(),object[i].GetArea(),5,1);
            }
        }
        break;//end for
    case 2:
        for(k=0;k<P1.GetBulletC();k++){//for
        if(P1.Player_Bullet1Hit(k,object[i].GetPos(),object[i].GetArea())==true){
            Play_PlayerHit();
                CreatePartical(object[i].GetPos(),object[i].GetArea(),5,1);
                P1.Player_B1_Hit(k);if(object[i].GetHP()==1)object[i].Hit();
            }
        }break;//end for
    }//子弹打方块


    for(j=0;j<Edit_Max;j++){//敌人子弹打方块
        if(enemy[j].GetAlive()==false)continue;
        switch (object[i].GetType()) {
        case 1:
            for(k=0;k<5;k++){//for
            if(enemy[j].Enemy_BulletHit(k,object[i].GetPos(),object[i].GetArea())==true){
                    object[i].Hit();enemy[j].Enemy_B1_Hit(k);
                }
            }break;//end for
        case 2:
            for(k=0;k<5;k++){//for
            if(enemy[j].Enemy_BulletHit(k,object[i].GetPos(),object[i].GetArea())==true){
                    enemy[j].Enemy_B1_Hit(k);if(object[i].GetHP()==1)object[i].Hit();
                }
            }break;//end for
        }
    }//敌人子弹打方块
}//子弹打方块
//Boss子弹命中玩家

    XY t={30,30};
    for(i=0;i<Edit_Min;i++){
        if(P1.Player_Hit(boss1->GetBulletPos(i),t)==true&&boss1->GetAlive()==true){
            P1.Player_UnderAttack(10);
            CreatePartical(P1.GetPos(),P1.GetArea(),10,3);
            boss1->Boss1_B1_Hit(i);
        }
    }
    if(P1.Player_Hit(boss1->GetBullet3Pos(),boss1->GetBullet3Area())==true&&boss1->GetBullet3Flash()>=8&&boss1->GetAlive()==true){//boss技能判定
        P1.Player_UnderAttack(100);
        CreatePartical(P1.GetPos(),P1.GetArea(),10,2);
        boss1->Boss1_B3_Hit();
    }
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==false)continue;
        for(k=0;k<5;k++){
            if(enemy[i].Enemy_BulletHit(k,P1.GetPos(),P1.GetArea())==true){
                P1.Player_UnderAttack(1);
                CreatePartical(P1.GetPos(),P1.GetArea(),15,3);
                enemy[i].Enemy_B1_Hit(k);
                if(P1.Player_Dead()==true){
                    QMessageBox::information(nullptr,tr("提示"),tr("您失败了"), tr("好"));
                    this->~BattleWindow();
                    backto=new MainWindow;
                    backto->setMouseTracking(true);
                    backto->show();
                    return;
                }
            }
        }
    }

}




void BattleWindow::Player_HitCheck(){
    int i;
    P1.Player_UnSlow();
    if(P1.GetPos().x<0||P1.GetPos().x+50>X_Max||P1.GetPos().y<0||P1.GetPos().y+50>Y_Max){//玩家边界判断
        P1.Player_Move(-1);
        Player_HitCheck();//递归处理
    }
    for(i=0;i<Edit_Max;i++){//墙判断
        if(object[i].GetAlive()==false)continue;
        if(P1.Player_Hit(object[i].GetPos(),object[i].GetArea())==true){
        switch (object[i].GetType()) {
        case 1:
        case 2:
        case 3:
        case 5:
        case 8:
        case 11:
                P1.Player_Move(-1);
                Player_HitCheck();break;//递归处理
        case 6:P1.Strengthen(2,0,0,0,0,0);object[i].Hit();break;
        case 7:P1.Strengthen(0,20,0,20,0,0);object[i].Hit();break;
        case 9:P1.Strengthen(10,0,0,0,0,0);object[i].Hit();break;
        case 10:P1.Strengthen(0,50,0,50,0,0);object[i].Hit();break;
        case 12:P1.Strengthen(50,0,0,0,0,0);object[i].Hit();break;
        case 13:P1.Strengthen(0,100,0,100,0,0);object[i].Hit();break;
        case 14:object[i].Hit();break;
        case 16:
            if(object[i].GetHP()==-1&&object[i].GetOther()==0){
            P1.Player_UnderAttack(1);object[i].SetOther(1);}break;
        case 17:P1.Player_Slow();break;
        case 4:MissionRougueLike_Win();break;
        }
        }
    }//墙end
}

void BattleWindow::Boss_Move(){
    if(boss1->GetAlive()==false)return;
    int i;bool hit=false;
    boss1->Boss1_Move(5);
a:   if(boss1->GetPos().x<0||boss1->GetPos().x+boss1->GetArea().x>X_Max||  //边界碰撞
           boss1->GetPos().y<0||boss1->GetPos().y+boss1->GetArea().y>Y_Max){
       boss1->Boss1_Move(-1);hit=true;goto a;
   }//边界碰撞
    for(i=0;i<Edit_Max;i++){
        if(object[i].GetAlive()==false)continue;

    b:    if(boss1->Boss1_Hit(object[i].GetPos(),object[i].GetArea())==true){
            switch (object[i].GetType()){
            case 2:boss1->Boss1_Move(-1);hit=true;goto b;break;
            case 1:
            case 3:
            case 14:
            case 15:
            case 16:object[i].Dead();break;
            }
        }
    }
    if(hit==true)boss1->Boss1_RndChangeHead();
}


void BattleWindow::Enemy_Move(){
    int i,k;
    for(i=0;i<Edit_Max;i++){
        bool ice=false,hit=false;
        if(enemy[i].GetAlive()==false)continue;//敌人死了就跳出

        enemy[i].Enemy_Move(enemy[i].GetMoveSpeed());
             a:   if(enemy[i].GetPos().x<0||enemy[i].GetPos().x+enemy[i].GetArea().x>X_Max||  //边界碰撞
                        enemy[i].GetPos().y<0||enemy[i].GetPos().y+enemy[i].GetArea().y>Y_Max){
                    enemy[i].Enemy_Move(-1);hit=true;goto a;
                //    enemy[i].Enemy_RndChangeHead();
                }//边界碰撞
        for(k=0;k<Edit_Max;k++){
            if(object[k].GetAlive()==false)continue;

        b:    if(enemy[i].Enemy_Hit(object[k].GetPos(),object[k].GetArea())==true){hit=true;
                switch (object[k].GetType()){
                case 16:hit=false;break;
                case 1:
                case 2:
                case 3:
                case 5:
                case 8:
                case 11:
                    enemy[i].Enemy_Move(-1);hit=true;goto b;
                    break;
                case 14:object[k].Hit();break;
                case 17:enemy[i].Enemy_Slow();ice=true;break;
                }
            }
        }
        if(ice==false)enemy[i].Enemy_UnSlow();
        if(hit==true&&ice==false)enemy[i].Enemy_RndChangeHead();
    }
}


void BattleWindow::paintEvent(QPaintEvent *event){//画界面
        int i,k;
        QPainter painter(this);//Qpainter
        //QImage
        QImage P1_Bullet_Image(":/Images/Tank/Shot.png");
        QImage P2_Bullet_Image(":/Images/Tank/Shot2.png");
        QImage Enemy_Bullet_Image(":/Images/Tank/Shot.png");



        QImage Boss_Image[4];
        Boss_Image[0].load(":/Images/Tank/BossUp.png");
        Boss_Image[1].load(":/Images/Tank/BossDown.png");
        Boss_Image[2].load(":/Images/Tank/BossLeft.png");
        Boss_Image[3].load(":/Images/Tank/BossRight.png");
        QRect Boss_Rect(boss1->GetPos().x,boss1->GetPos().y,150,150);
        QRect Boss_Bullet_Rect[Edit_Min];
        if(boss1->GetAlive()==true){
        switch (boss1->GetHead()) {
        case UP:painter.drawImage(Boss_Rect,Boss_Image[0]);break;
        case DOWN:painter.drawImage(Boss_Rect,Boss_Image[1]);break;
        case LEFT:painter.drawImage(Boss_Rect,Boss_Image[2]);break;
        case RIGHT:painter.drawImage(Boss_Rect,Boss_Image[3]);break;
        }
        for(i=0;i<Edit_Min;i++){
            Boss_Bullet_Rect[i].setRect(boss1->GetBulletPos(i).x,boss1->GetBulletPos(i).y,30,30);
            painter.drawImage(Boss_Bullet_Rect[i],P2_Bullet_Image);
        }
        }


        //QRect
        QRect P1_Rect(P1.GetPos().x,P1.GetPos().y,50,50);
        QRect P1_Bullet_Rect[10];
        QRect P2_Bullet_Rect[Edit_Min];
        QRect Enemy_Rect[Edit_Max];
        QRect Enemy_Bullet_Rect[Edit_Max][5];
        QRect *ObjectRect=new QRect[Edit_Max];

        QRect SkillR(1500,0,100,100);
        painter.drawImage(SkillR,Skill_Select[0]);
        switch (Skill) {
        case 1:painter.drawImage(SkillR,Skill_Select[1]);break;
        case 2:painter.drawImage(SkillR,Skill_Select[2]);break;
        case 3:painter.drawImage(SkillR,Skill_Select[3]);break;
        }

        drawBar(painter);


        for(i=0;i<Edit_Max;i++){
            if(object[i].GetAlive()==false)continue;
            new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
            switch (object[i].GetType()) {
            case 1:
                if(object[i].GetHP()==0)
            painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][2]);
                else
            painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][1]);
            break;
            case 2:
                if(object[i].GetHP()==1) painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][1]);
                else painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][2]);break;
            case 3:
                if(object[i].GetHP()==1) painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][1]);
                else painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][2]);break;
            case 14:
                if(object[i].GetHP()==1) painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][1]);
                else painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][2]);break;
            case 16:
                if(object[i].GetHP()==1) painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][1]);
                else painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][2]);break;
            case 17:
                if(object[i].GetHP()==1) painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][1]);
                else painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][2]);break;
            default:painter.drawImage(ObjectRect[i],Object_Number[object[i].GetType()][1]);break;
            }
        }
        switch (P1.GetHead()) {//画玩家
        case UP:painter.drawImage(P1_Rect,Object_Number[0][0]);break;
        case DOWN:painter.drawImage(P1_Rect,Object_Number[0][1]);break;
        case LEFT:painter.drawImage(P1_Rect,Object_Number[0][2]);break;
        case RIGHT:painter.drawImage(P1_Rect,Object_Number[0][3]);break;
        }
        for(i=0;i<Edit_Max;i++){
            if(enemy[i].GetAlive()==false)continue;
            Enemy_Rect[i].setRect(enemy[i].GetPos().x,enemy[i].GetPos().y,enemy[i].GetArea().x,enemy[i].GetArea().y);

            for(k=0;k<5;k++){
                if(enemy[i].GetBulletAlive(k)==false)continue;
                Enemy_Bullet_Rect[i][k].setRect(enemy[i].GetBulletPos(k).x,enemy[i].GetBulletPos(k).y,30,30);
                painter.drawImage(Enemy_Bullet_Rect[i][k],P1_Bullet_Image);
            }
            switch (enemy[i].GetHead()) {
            case UP:painter.drawImage(Enemy_Rect[i],Enemy_Image[enemy[i].GetSkin()][0]);break;
            case DOWN:painter.drawImage(Enemy_Rect[i],Enemy_Image[enemy[i].GetSkin()][1]);break;
            case LEFT:painter.drawImage(Enemy_Rect[i],Enemy_Image[enemy[i].GetSkin()][2]);break;
            case RIGHT:painter.drawImage(Enemy_Rect[i],Enemy_Image[enemy[i].GetSkin()][3]);break;
            }
        }

        for(i=0;i<P1.GetBulletC();i++){
            if(P1.GetBulletAlive(i)==true){
            P1_Bullet_Rect[i].setRect(P1.GetBulletPos(i).x,P1.GetBulletPos(i).y,30,30);
            painter.drawImage(P1_Bullet_Rect[i],P1_Bullet_Image);}
        }
            if(P1.GetBullet2Alive()==true){
            P2_Bullet_Rect[i].setRect(P1.GetBullet2Pos().x,P1.GetBullet2Pos().y,30,30);
            painter.drawImage(P2_Bullet_Rect[i],P2_Bullet_Image);}




        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==false)continue;
            QRect Partical_Rect(partical[i].GetPos().x,partical[i].GetPos().y,partical[i].GetArea().x,partical[i].GetArea().y);
            switch (partical[i].GetType()) {
            case 1:painter.drawImage(Partical_Rect,Partical_Image[1][partical[i].GetFlash()+1]);break;
            case 2:{
                QImage temp;
                switch (P1.GetHead()) {
                case UP:temp=Partical_Image[2][partical[i].GetFlash()+1].mirrored(false,false);break;
                case DOWN:temp=Partical_Image[2][partical[i].GetFlash()+1].mirrored(true,true);break;
                case LEFT:temp=Partical_Image[2][partical[i].GetFlash()+1].mirrored(true,false);break;
                case RIGHT:temp=Partical_Image[2][partical[i].GetFlash()+1].mirrored(false,true);break;
                }
                painter.drawImage(Partical_Rect,temp);break;}
            case 3:painter.drawImage(Partical_Rect,Partical_Image[3][partical[i].GetFlash()]);break;
            case 4:painter.drawImage(Partical_Rect,Partical_Image[4][partical[i].GetFlash()]);break;
            }
        }

        //paint RedZone
        for(i=0;i<Edit_Min;i++){
            if(redzone[i].GetAlive()==false)continue;
            QRect temp(redzone[i].GetPos().x-redzone[i].GetR(),redzone[i].GetPos().y-redzone[i].GetR(),redzone[i].GetR()*2,redzone[i].GetR()*2);
            painter.drawImage(temp,RedZone_Image[redzone[i].GetFlash()]);
        }
//paint Introduce
        if(IntroduceP!=0)drawIntroduce(painter);
        switch (Mission) {
        case 1:drawMission1(painter);break;
        }
}

void BattleWindow::drawBar(QPainter &painter){
    int i;
  /*  QImage BarF(":/images/FlagMeter.png");
    QImage Bar1,Bar2;
    QImage Barp(":/images/FlagMeterParts.png");
    QRect temp(1500,0,300,30);
    QRect temp2(1500,0,P1.GetHP()>300?300:P1.GetHP(),30);
    Bar1=BarF.copy(0,0,100,27);
    Bar2=BarF.copy(0,27,P1.GetHP()>300?100:P1.GetHP()/3,27);
    painter.drawImage(temp,Bar1);
    painter.drawImage(temp2,Bar2);*/
    ui->label->setText(QString::number(P1.GetHP(),10));
    ui->label_2->setText(QString::number(P1.GetMP(),10));
    ui->label_3->setText(QString::number(P1.GetWeaponLv(),10));
    ui->label_4->setText(QString::number(P1.GetMaterial(),10));
    ui->label_5->setText(QString::number(P1.GetProcess(),10));
    BarC[5]=Bar[0].copy(0,0,21,P1.GetHP()>300?300:P1.GetHP());
    BarC[6]=Bar[1].copy(0,0,21,P1.GetMP()>300?300:P1.GetMP());
    BarC[7]=Bar[2].copy(0,0,21,P1.GetWeaponLv()*9>300?300:P1.GetWeaponLv()*9);
    BarC[8]=Bar[3].copy(0,0,21,P1.GetMaterial()>300?300:P1.GetMaterial());
    BarC[9]=Bar[4].copy(0,0,21,P1.GetProcess()>300?300:P1.GetProcess());
    BarC[0]=Bar[0].copy(21,0,21,300);
    BarC[1]=Bar[1].copy(21,0,21,300);
    BarC[2]=Bar[2].copy(21,0,21,300);
    BarC[3]=Bar[3].copy(21,0,21,300);
    BarC[4]=Bar[4].copy(21,0,21,300);
    for(i=0;i<5;i++)
    BarR[i].setRect(1500+(i*80),100,80,900);
    BarR[5].setRect(1500,100,80,(P1.GetHP()>300?300:P1.GetHP())*3);
    BarR[6].setRect(1580,100,80,(P1.GetMP()>300?300:P1.GetMP())*3);
    BarR[7].setRect(1660,100,80,(P1.GetWeaponLv()*9>300?300:P1.GetWeaponLv())*9);
    BarR[8].setRect(1740,100,80,(P1.GetMaterial()>300?300:P1.GetMaterial())*3);
    BarR[9].setRect(1820,100,80,(P1.GetProcess()*3>300?300:P1.GetProcess())*9);
    for(i=0;i<5;i++){
        painter.drawImage(BarR[i],BarC[i]);
        painter.drawImage(BarR[i+5],BarC[i+5]);
    }


}

    void BattleWindow::Enemy_Generate(){//兵营生成敌人
        int i,x,y;
        XY t1,t2={50,50};
        for(i=0;i<Edit_Max;i++){
            if(object[i].GetType()!=5&&object[i].GetType()!=8&&object[i].GetType()!=11)continue;
            x = QRandomGenerator::global()->generate();
            y = QRandomGenerator::global()->generate();
                t1=object[i].GetPos();
               if(x%2==1)t1.x-=50;
               else t1.x+=50;
               if(y%2==1)t1.y-=50;
               else t1.y+=50;
               switch (object[i].GetType()) {
               case 5:if(object[i].GetOther()>=10){
                   CreatePartical(object[i].GetPos(),object[i].GetArea(),10,1);
                   object[i].Dead();break;
                   }
                   object[i].SetOther(object[i].GetOther()+1);
                   CreateEnemy(t1,t2,2,10,4,2);break;
               case 8:if(object[i].GetOther()>=15){
                       CreatePartical(object[i].GetPos(),object[i].GetArea(),10,1);
                       object[i].Dead();break;
                       }
                       object[i].SetOther(object[i].GetOther()+1);CreateEnemy(t1,t2,10,10,4,3);break;
               case 11:if(object[i].GetOther()>=20){
                       CreatePartical(object[i].GetPos(),object[i].GetArea(),10,1);
                       object[i].Dead();break;
                       }
                       object[i].SetOther(object[i].GetOther()+1);CreateEnemy(t1,t2,50,10,4,4);break;
               default:break;
               }

        }
    }
    void BattleWindow::Move(){//玩家移动
        P1.Player_Move(P1.GetSpeed());Player_HitCheck();
    }
    void BattleWindow::Enemy_All(){//敌人其它判定
        int i;
        for (i=0;i<Edit_Max ;i++ ) {
            if(enemy[i].GetAlive()==false)continue;
        int x = QRandomGenerator::global()->generate();
        if(x%6==0){
            if(enemy[i].GetSkin()!=3||enemy[i].GetSkin()!=4){
           enemy[i].Enemy_RndChangeHead();}
        }
        if(x%5==0)
            enemy[i].Enemy_B1Fire();

        }
        int x = QRandomGenerator::global()->generate();
        if(boss1->GetAlive()==true&&x%10==0)boss1->Boss1_B1Fire();
    }

      void BattleWindow::keyPressEvent(QKeyEvent *event){
          qDebug()<<event->key();
        if(!event->isAutoRepeat()){
            if(event->key()==87||event->key()==83||event->key()==65||event->key()==68)Key=event->key();
            switch (event->key()) {//wsad space
            case 87:P1.Player_ChangeHead(0);move.start(10);break;
            case 83:P1.Player_ChangeHead(1);move.start(10);break;
            case 65:P1.Player_ChangeHead(2);move.start(10);break;
            case 68:P1.Player_ChangeHead(3);move.start(10);break;
            case 32://
                switch (Skill) {
                case 1:if(P1.Player_B1Fire()==false)Play_MPOut();break;
                case 2:if(P1.Player_B2Fire()==false)Play_MPOut();break;
                case 3:if(P1.Player_B3Fire()==true){
                        XY a=P1.GetPos(),b={50,100},c={150,100},d={-50,50},e={100,50},f={100,150},g={50,-50};
                        switch (P1.GetHead()) {
                        case UP:CreatePartical(a-b,c,4,2);break;
                        case DOWN:CreatePartical(a+d,c,4,2);break;
                        case LEFT:CreatePartical(a-e,f,4,2);break;
                        case RIGHT:CreatePartical(a+g,f,4,2);break;
                        }
                    }break;
                }break;
            case 74:
                P1.Player_ProcessOn(-P1.GetProcess());
                fix.start(10);
                Fix_Mod=10;break;
            case 75:
                P1.Player_ProcessOn(-P1.GetProcess());
                fix.start(100);
                Fix_Mod=100;break;
            case 76:
                P1.Player_ProcessOn(-P1.GetProcess());
                fix.start(300);
                Fix_Mod=300;break;
            case 16777248:Skill++;if(Skill==4){Skill=1;}break;
            case 61:Win=true;MissionRougueLike_Win();//跳关
            case 45:P1.Strengthen(10,10,0,0,0,0);
            case 48:P1.Strengthen(0,0,10,0,0,0);
            }
         }
    }

void BattleWindow::keyReleaseEvent(QKeyEvent *event){
   if(!event->isAutoRepeat()){
        if(event->key()==Key )move.stop();
   }
}

QImage BattleWindow::Image_Cut(QImage image){
            image = image.convertToFormat(QImage::Format_ARGB32);
            union myrgb
            {
                uint rgba;
                uchar rgba_bits[4];
            };
            myrgb* mybits =(myrgb*) image.bits();
     int len = image.width()*image.height();
      while(len --> 0)
      {
        mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:255;
        mybits++;
      }
   return image;
}
QImage BattleWindow::Image_Transparent(QImage image,int x){
        if(x>255)x=255;
            image = image.convertToFormat(QImage::Format_ARGB32);
            union myrgb
            {
                uint rgba;
                uchar rgba_bits[4];
            };
            myrgb* mybits =(myrgb*) image.bits();
            int len = image.width()*image.height();
            while(len --> 0)
            {
                mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:x;
                mybits++;
            }
            return image;
}

void BattleWindow::P1_Fix(){
    if(P1.GetMaterial()<=0){
        P1.Strengthen(0,0,0,-P1.GetMaterial(),0,0);
        fix.stop();return;
    }
    P1.Player_ProcessOn(1);
    switch (Fix_Mod) {
    case 100:P1.Strengthen(0,0,0,-1,0,0);break;
    case 300:P1.Strengthen(0,0,0,-1,0,0);break;
    case 10:break;
    }
    if(P1.GetProcess()>=100){
        P1.Player_ProcessOn(-P1.GetProcess());
        fix.stop();
        switch (Fix_Mod) {
        case 100:P1.Strengthen(0,100,0,0,0,0);break;
        case 300:P1.Strengthen(0,0,1,0,0,0);break;
        case 10:P1.Strengthen(1,0,0,-10,0,0);break;
        }
    }
}
void BattleWindow::Play_RedZone(){
    if(RedZone_Sound->state()==QMediaPlayer::PlayingState){
        RedZone_Sound->stop();
        RedZone_Sound->setVolume(100);
        RedZone_Sound->play();
    }
    RedZone_Sound->setVolume(100);
    RedZone_Sound->play();
}
void BattleWindow::Play_PlayerHit(){
    if(Bullet_Sound->state()==QMediaPlayer::PlayingState){
        Bullet_Sound->stop();
        Bullet_Sound->setVolume(50);
        Bullet_Sound->play();
    }
    Bullet_Sound->setVolume(50);
    Bullet_Sound->play();
}
void BattleWindow::Play_MPOut(){
    if(MPOut->state()==QMediaPlayer::PlayingState){
        MPOut->stop();
        MPOut->setVolume(50);
        MPOut->play();
    }
    MPOut->setVolume(50);
    MPOut->play();
}
HEAD BattleWindow::AI1(XY player,XY enemy){
    int d[5],i,n=0;
    d[0]=(enemy.y-player.y)*(enemy.y-player.y)+(enemy.x-player.x)*(enemy.x-player.x);
    d[1]=(enemy.y+10-player.y)*(enemy.y+10-player.y)+(enemy.x-player.x)*(enemy.x-player.x);
    d[2]=(enemy.y-10-player.y)*(enemy.y-10-player.y)+(enemy.x-player.x)*(enemy.x-player.x);
    d[3]=(enemy.y+-player.y)*(enemy.y-player.y)+(enemy.x-10-player.x)*(enemy.x-10-player.x);
    d[4]=(enemy.y-player.y)*(enemy.y-player.y)+(enemy.x+10-player.x)*(enemy.x+10-player.x);
    for(i=1;i<5;i++){
            if(d[n]>d[i])n=i;
    }
    switch (n) {
    case 2:return UP;break;
    case 1:return DOWN;break;
    case 3:return LEFT;break;
    case 4:return RIGHT;break;
    default:qDebug()<<"wrong";return UP;
    }
}
void BattleWindow::CreatePartical(XY pos,XY area,int flash,int type){
    int i;
    for(i=0;i<Edit_Max;i++){//创建爆炸粒子
        if(partical[i].GetAlive()==true)continue;
               new(&partical[i])Partical(pos,area,flash,type);
        break;
    }//创建爆炸粒子
}
void BattleWindow::CreateEnemy(XY pos,XY area,int hp,int speed,int bulletspeed,int skin){
    if(pos.x+area.x>X_Max||pos.y+area.y>Y_Max||pos.x<0||pos.y<0)return;
    int i;
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==true)continue;
        new(&enemy[i])Enemy(pos,area,hp,speed,bulletspeed,skin);break;
    }
}
void BattleWindow::CreateObject(XY pos,XY area,int type,int skin,int hp){
    int i;
    for(i=0;i<Edit_Max;i++){//创建物体
        if(object[i].GetAlive()==true)continue;
               new(&object[i])Object(pos,area,type,skin,hp);
        break;
    }//创建物体
}
void BattleWindow::ClearMap(XY pos){//清理地图
    int i;
    for(i=0;i<Edit_Max;i++){
        enemy[i].Dead();
        object[i].Dead();
    }
    P1.SetPos(pos);
}
int BattleWindow::RndLevel(int x){
    return 1;

}
