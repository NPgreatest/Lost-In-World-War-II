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
        this->~BattleWindow();
        backto=new MainWindow;
        backto->setMouseTracking(true);backto->show();return;
    }//加载地图失败

    //加载地图
    QTextStream input(&file);
    while(!input.atEnd()){
        QString line=input.readLine();
        QStringList list=line.split(" ");
        if(line=="CObject:"){
            read=1;
            i=0;
            continue;
        }
        else if(line=="CPlayer:"){
            me=true;
            read=2;
            i=0;
            continue;
        }
        else if(line=="CEnemy:"){
            read=3;
            i=0;
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
            i++;
            break;
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
            i++;
            break;
        default:QMessageBox::information(nullptr,tr("提示"),tr("加载地图失败"), tr("好"));break;
        }
    }
    file.close();
    //加载地图


    if(me==true)
        new(&P1)Player(P,thp,tmp,tlv,tmat,tb1c);//玩家初始化

    for(i=0;i<Edit_Max;i++){//创建物体
        CreateObject(pos[i],area[i],type[i],skin[i],hp[i]);
    }

    for(i=0;i<Edit_Max;i++){//创建敌人
         if(e_area[i].x==0||e_area[i].y==0)continue;
         CreatePartical(e_pos[i],e_area[i],Type::Object_Hit);
         CreateEnemy(e_pos[i],e_area[i],e_hp[i],e_speed[i],e_bullet_speed[i],e_skin[i]);
    }

}


void BattleWindow::Load_Status(int Mission){//初始化
    this->Mission=Mission;

    int i;
    for(i=0;i<Edit_Max;i++){//实例化物体
        object[i]=new Temp();
    }

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
    Bullet_Sound_2->setMedia(QUrl("qrc:/sounds/sounds/Player_Hit2.mp3"));
    RedZone_Sound->setMedia(QUrl("qrc:/sounds/sounds/RedZone.mp3"));
    MPOut->setMedia(QUrl("qrc:/sounds/sounds/ .mp3"));
    BackGroundMusic->setMedia(QUrl("qrc:/sounds/sounds/BattleMusic1.mp3"));


    if(Mission==0){//介绍模式
        this->Load_Introduce();
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(10);
        return;
    }//介绍模式


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
    connect(&Rain, SIGNAL(timeout()), this, SLOT(RainFire()));

      boom->start(50);
      timer->start(10);
      flash->start(1000);
      enemymove->start(50);
      enemyall->start(100);
      generate->start(5000);//QTimer

    switch (Mission) {
    case 1:MissionTeach();return;
    case 2:MissionRougueLike();return;
    default:break;
    }


    QString Address = QFileDialog::getOpenFileName(this,tr("选择地图"),nullptr, tr("Image Files (*.txt)"));
    Load_Map(Address);

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
        QRect P2_Bullet_Rect[Edit_Min];
        QRect Enemy_Bullet_Rect[Edit_Max][5];


        painter.drawImage(QRect(1500,0,100,100),Skill_Select[0]);
        switch (Skill) {
        case 1:painter.drawImage(QRect(1500,0,100,100),Skill_Select[1]);break;
        case 2:painter.drawImage(QRect(1500,0,100,100),Skill_Select[2]);break;
        case 3:painter.drawImage(QRect(1500,0,100,100),Skill_Select[3]);break;
        }


        for(i=0;i<Edit_Max;i++){//创建物体
            if(!object[i]->GetAlive())continue;
            painter.drawImage(object[i]->GetRect(),object[i]->GetImage());
        }

        for(i=0;i<Edit_Max;i++){//画敌人
            if(enemy[i].GetAlive()==false)continue;


            for(k=0;k<5;k++){
                if(enemy[i].GetBulletAlive(k)==false)continue;
                Enemy_Bullet_Rect[i][k].setRect(enemy[i].GetBulletPos(k).x-10,enemy[i].GetBulletPos(k).y-10,30,30);
                painter.drawImage(Enemy_Bullet_Rect[i][k],P1_Bullet_Image);
            }
            switch (enemy[i].GetHead()) {
            case UP:painter.drawImage(QRect(enemy[i].GetPos().x,enemy[i].GetPos().y,enemy[i].GetArea().x,enemy[i].GetArea().y),Enemy_Image[enemy[i].GetSkin()][0]);break;
            case DOWN:painter.drawImage(QRect(enemy[i].GetPos().x,enemy[i].GetPos().y,enemy[i].GetArea().x,enemy[i].GetArea().y),Enemy_Image[enemy[i].GetSkin()][1]);break;
            case LEFT:painter.drawImage(QRect(enemy[i].GetPos().x,enemy[i].GetPos().y,enemy[i].GetArea().x,enemy[i].GetArea().y),Enemy_Image[enemy[i].GetSkin()][2]);break;
            case RIGHT:painter.drawImage(QRect(enemy[i].GetPos().x,enemy[i].GetPos().y,enemy[i].GetArea().x,enemy[i].GetArea().y),Enemy_Image[enemy[i].GetSkin()][3]);break;
            }
        }//画敌人




        painter.drawImage(P1.GetRect(),P1.GetImage());//画玩家

        drawBar(painter);//画血槽

        for(i=0;i<Edit_Max;i++){//创建粒子
            if(partical[i].GetAlive()==false)continue;
            painter.drawImage(partical[i].GetRect(),partical[i].GetImage());
        }




        for(i=0;i<P1.GetBulletC();i++){
            if(P1.GetBulletAlive(i)==true){
            painter.drawImage(QRect(P1.GetBulletPos(i).x-10,P1.GetBulletPos(i).y-10,30,30),P1_Bullet_Image);
            }
        }
            if(P1.GetBullet2Alive()==true){
            P2_Bullet_Rect[i].setRect(P1.GetBullet2Pos().x,P1.GetBullet2Pos().y,30,30);
            painter.drawImage(P2_Bullet_Rect[i],P2_Bullet_Image);
        }



        //paint RedZone
        for(i=0;i<Edit_Min;i++){
            if(redzone[i].GetAlive()==false)continue;
            QRect temp(redzone[i].GetPos().x-redzone[i].GetR(),redzone[i].GetPos().y-redzone[i].GetR(),redzone[i].GetR()*2,redzone[i].GetR()*2);
            painter.drawImage(temp,RedZone_Image[redzone[i].GetFlash()]);
        }
//paint Introduce
        if(IntroduceP!=0)drawIntroduce(painter);
}

void BattleWindow::drawBar(QPainter &painter){
    int i;
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



void BattleWindow::Move(){//玩家移动
    P1.Player_Move(P1.GetSpeed());
    Player_HitCheck();
}

void BattleWindow::Enemy_All(){//敌人转向和开火
    int i,x;
    for (i=0;i<Edit_Max ;i++ ){
        if(enemy[i].GetAlive()==false)continue;
        x = QRandomGenerator::global()->generate();
        if(x%6==0){
            if(enemy[i].GetSkin()!=3||enemy[i].GetSkin()!=4){
           enemy[i].Enemy_RndChangeHead();}
        }
        if(x%5==0)
            enemy[i].Enemy_B1Fire();

     }

    x = QRandomGenerator::global()->generate();
    if(boss1->GetAlive()==true&&x%10==0)boss1->Boss1_B1Fire();

}//function end

void BattleWindow::keyPressEvent(QKeyEvent *event){
      //qDebug()<<event->key();
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
                        case UP:CreatePartical(a-b,c,Type::Player_B3);break;
                        case DOWN:CreatePartical(a+d,c,Type::Player_B3);break;
                        case LEFT:CreatePartical(a-e,f,Type::Player_B3);break;
                        case RIGHT:CreatePartical(a+g,f,Type::Player_B3);break;
                        }
                    }break;
                }break;
            case 74:
                P1.Player_ProcessOn(-P1.GetProcess());
                fix.start(10);
                Fix_Mod=10;break;
            case 75:
                P1.Player_ProcessOn(-P1.GetProcess());
                fix.start(15);
                Fix_Mod=15;break;
            case 76:
                if(Fix_Mod==1){
                    fix.stop();
                    P1.Strengthen(0,0,0,-10,0,0);
                    P1.Player_ProcessOn(-P1.GetProcess());
                    Fix_Mod=0;
                    return;
                }
                P1.Player_ProcessOn(-P1.GetProcess());
                fix.start(10);
                Fix_Mod=1;break;
            case 16777248:Skill++;if(Skill==4){Skill=1;}break;
      //      case 61:Win=true;MissionRougueLike_Win();break;//跳关
            case 45:P1.Strengthen(10,10,0,0,0,0);break;
            case 48:P1.Strengthen(0,0,10,10,0,0);break;
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
void BattleWindow::Play_PlayerHit_2(){
    if(Bullet_Sound_2->state()==QMediaPlayer::PlayingState){
        Bullet_Sound_2->stop();
        Bullet_Sound_2->setVolume(50);
        Bullet_Sound_2->play();
    }
    Bullet_Sound_2->setVolume(50);
    Bullet_Sound_2->play();
}
void BattleWindow::Play_BackMusic(){
    if(BackGroundMusic->state()!=QMediaPlayer::PlayingState&&(this->Mission!=0&&this->Mission!=1)){
    BackGroundMusic->setVolume(50);
    BackGroundMusic->play();
    }
}

void BattleWindow::CreatePartical(XY pos,XY area,Type type){
    int i;
    for(i=0;i<Edit_Max;i++){//创建爆炸粒子
        if(partical[i].GetAlive()==true)continue;
                partical[i].~Partical();
               new(&partical[i])Partical(pos,area,type);
        break;
    }//创建爆炸粒子
}
void BattleWindow::CreateEnemy(XY pos,XY area,int hp,int speed,int bulletspeed,int skin){
    if(area.x==0&&area.y==0)return;
    if(pos.x+area.x>X_Max||pos.y+area.y>Y_Max||pos.x<0||pos.y<0)return;
    int i;
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==true)continue;
        new(&enemy[i])Enemy(pos,area,hp,speed,bulletspeed,skin);break;
    }
}
void BattleWindow::CreateObject(XY pos,XY area,int type,int skin,int hp){
    if(type==0)return;
    int i;
    for(i=0;i<Edit_Max;i++){//创建物体
        if(object[i]->GetAlive()==false){
        object[i]->~Object();
        break;
        }

    }//创建物体
    switch (type) {
    case 1:object[i]=new Wall(pos,area,skin,hp);break;
    case 2:object[i]=new BedRock(pos,area,skin);break;
    case 3:object[i]=new River(pos,area,skin);break;
    case 4:object[i]=new Portal(pos,area);break;
    case 5:object[i]=new Camp(pos,area,1,hp);break;
    case 6:object[i]=new FirstAid(pos,area,1);break;
    case 7:object[i]=new Weapon(pos,area,1);break;
    case 8:object[i]=new Camp(pos,area,2,hp);break;
    case 9:object[i]=new FirstAid(pos,area,2);break;
    case 10:object[i]=new Weapon(pos,area,2);break;
    case 11:object[i]=new Camp(pos,area,3,hp);break;
    case 12:object[i]=new FirstAid(pos,area,3);break;
    case 13:object[i]=new Weapon(pos,area,3);break;
    case 14:object[i]=new Ruins(pos,area,skin);break;
    case 15:object[i]=new Grass(pos,area,skin);break;
    case 16:object[i]=new Nail(pos,area);break;
    case 17:object[i]=new Ice(pos,area);break;
    default:qDebug()<<"sonethings wrong..";break;
    }
}
void BattleWindow::CreateRedZone(XY pos,int R,int type){
    int i;
    for(i=0;i<Edit_Min;i++){
        if(redzone[i].GetAlive()==true)continue;
        new(&redzone[i])RedZone(pos,R,type);
        redzone[i].Flash_Begin();
        break;
    }
}
void BattleWindow::ClearMap(XY pos){//清理地图
    int i;
    for(i=0;i<Edit_Max;i++){
        enemy[i].Dead();
        if(object[i]->GetAlive())
        object[i]->Dead();
    }
    P1.SetPos(pos);
}

BattleWindow::~BattleWindow(){
    Bullet_Sound->~QMediaPlayer();
    RedZone_Sound->~QMediaPlayer();
    BackGroundMusic->~QMediaPlayer();
    MPOut->~QMediaPlayer();
}
void BattleWindow::RainFire(){
    static int num=0;
    int r;
    XY pos;
    pos.x=QRandomGenerator::global()->bounded(0,X_Max);
    pos.y=QRandomGenerator::global()->bounded(0,Y_Max);
    r=QRandomGenerator::global()->bounded(50,200);
    CreateRedZone(pos,r,1);
    num++;
    if(num==100){
        Rain.stop();
        num=0;
    }
}
/*    QTimer *redzone=new QTimer(this);
    connect(redzone, SIGNAL(timeout()), this, SLOT(RedZone_Generate()));
    redzone->start(Red_Zone_Fre);*/
/* Red_Zone_Fre=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸频率/ms"),5000,100,20000,100,nullptr,nullptr);
 Red_Zone=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸几率%"),50,0,100,1,nullptr,nullptr);*/
