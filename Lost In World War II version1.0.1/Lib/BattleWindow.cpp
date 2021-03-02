#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"
BattleWindow::BattleWindow(QWidget  *parent,int Mission) : QMainWindow(parent),ui(new Ui::BattleWindow),Mission(Mission){
    ui->setupUi(this);
    setPalette(QPalette(Qt::yellow));
    setAutoFillBackground(true);
    this->setStyleSheet("#BattleWindow{border-image:url(:/Images/Images/BattleGround.png);}");
    setWindowIcon(QIcon(":/Images/Images/icon.png"));

    this->Mission=Mission;

    int i;
    for(i=0;i<Edit_Max;i++){//实例化物体
        object[i]=new Temp();
    }


//实例化槽类
    bar[0] = new Bar(1500,100,100,1);
    bar[1] = new Bar(1580,100,100,2);
    bar[2] = new Bar(1660,100,5,3);
    bar[3] = new Bar(1740,100,100,4);
    bar[4] = new Bar(1820,100,100,5);
//实例化槽类

    Shot1_Image.load(":/Images/Tank/Shot.png");
    Shot2_Image.load(":/Images/Tank/Shot2.png");
    Shot3_Image.load(":/Images/Tank/Shot3.png");
    Shot4_Image.load(":/Images/Tank/Shot4.png");

    Bullet_Sound->setMedia(QUrl("qrc:/sounds/sounds/Player_Hit1.mp3"));
    Bullet_Sound_2->setMedia(QUrl("qrc:/sounds/sounds/Player_Hit2.mp3"));

    for(i=0;i<Edit_Min;i++){
    RedZone_Pre[i].setMedia(QUrl("qrc:/sounds/sounds/RedZone_Pre.mp3"));
    RedZone_Sound[i].setMedia(QUrl("qrc:/sounds/sounds/RedZone.mp3"));
    }
    MPOut->setMedia(QUrl("qrc:/sounds/sounds/ .mp3"));
    BackGroundMusic->setMedia(QUrl("qrc:/sounds/sounds/BattleMusic1.mp3"));

    //connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    GLWidGet *openGL = new GLWidGet(this, this);

    openGL->setGeometry(0, 0, 2000, 1000);
    openGL->lower();

    connect(&timer, &QTimer::timeout, openGL, &GLWidGet::animate);



    connect(&timer, SIGNAL(timeout()), this, SLOT(bulletfly()));//出大问题
    connect(&flash, SIGNAL(timeout()), this, SLOT(Flash()));
    connect(&move, SIGNAL(timeout()), this, SLOT(Move()));
    connect(&fix,  SIGNAL(timeout()), this, SLOT(P1_Fix()));
    connect(&enemymove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
    connect(&enemymove, SIGNAL(timeout()), this, SLOT(Boss_Move()));
    connect(&enemyall, SIGNAL(timeout()), this, SLOT(Enemy_All()));
    connect(&generate, SIGNAL(timeout()), this, SLOT(Enemy_Generate()));
    connect(&boom, SIGNAL(timeout()), this, SLOT(Flash2()));
    connect(&Rain, SIGNAL(timeout()), this, SLOT(RainFire()));

    if(Mission==0){//介绍模式
        this->Load_Introduce();
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, openGL, &GLWidGet::animate);
        timer->start(10);
        return;
    }//介绍模式

      boom.start(50);
      timer.start(10);
      flash.start(1000);
      enemymove.start(50);
      enemyall.start(100);
      generate.start(5000);//QTimer

    switch (Mission) {
    case 1:MissionTeach();return;
    case 2:MissionRougueLike();return;
    default:
        QString Address = QFileDialog::getOpenFileName(this,tr("选择地图"),nullptr, tr("Image Files (*.txt)"));
        Load_Map(Address);
        break;
    }

}

void BattleWindow::Load_Map(QString Address){
    int i=0,read=0,tlv,tmat,tb1c;
    bool me=false;
    XY P;int thp,tmp;
    XY pos[Edit_Max];
    XY area[Edit_Max];
    int type[Edit_Max];
    int skin[Edit_Max];
    int hp[Edit_Max];
    int e_hp[Edit_Max];
    int e_speed[Edit_Max];
    int e_bullet_speed[Edit_Max];
    XY e_pos[Edit_Max],e_area[Edit_Max];
    int e_skin[Edit_Max];
    for(i=0;i<Edit_Max;i++){
        pos[i]={0,0};
        area[i]={0,0};
        e_pos[i]={0,0};
        e_area[i]={0,0};
        type[i]=0;
        skin[i]=0;
        hp[i]=1;
        e_hp[i]=0;
        e_speed[i]=0;
        e_bullet_speed[i]=0;
        e_skin[i]=0;
    }


    QFile file(Address);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(nullptr,tr("提示"),tr("加载地图失败"), tr("好"));
        this->~BattleWindow();
        backto=new MainWindow;
        backto->show();
        return;
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
        default:QMessageBox::information(nullptr,tr("提示"),tr("加载地图失败"), tr("好"));
            this->~BattleWindow();
            backto=new MainWindow;
            backto->setMouseTracking(true);
            backto->show();
            break;
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



void BattleWindow::paint(QPainter *painter, QPaintEvent *event){
        int i,k;


        QImage temp(":/Images/Images/BattleGround.png");
        switch (LevelB) {
        case 2:
        case 3:
        case 4:temp.load(":/Images/Images/BattleGround.png");break;
        case 5:
        case 6:temp.load(":/Images/Images/BattleGround_2.png");break;
        case 7:
        case 8:temp.load(":/Images/Images/BattleGround_3.png");break;
        case 9:temp.load(":/Images/Images/BattleGround_4.png");break;
        }
        painter->drawImage(QRect(0,0,2000,1000),temp);


        bar[0]->SetValue(P1.GetHP());
        bar[1]->SetValue(P1.GetMP());
        bar[2]->SetValue(P1.GetWeaponLv());
        bar[3]->SetValue(P1.GetMaterial());
        bar[4]->SetValue(P1.GetProcess());
        for(i=0;i<5;i++){
           painter->drawImage(bar[i]->GetRect1(),bar[i]->GetImage1());
           painter->drawImage(bar[i]->GetRect2(),bar[i]->GetImage2());
        }

        //画boss及其子弹
        if(boss1->GetAlive()==true){
        painter->drawImage(boss1->GetRect(),boss1->GetImage());
        for(i=0;i<Edit_Min;i++){
            painter->drawImage(QRect(boss1->GetBulletPos(i).x,boss1->GetBulletPos(i).y,30,30),Shot2_Image);
            }
        }
        //画boss及其子弹



        painter->drawImage(myskill.GetRect(),myskill.GetImage());//画技能槽

        for(i=0;i<Edit_Max;i++){//创建物体
            if(!object[i]->GetAlive())continue;
            painter->drawImage(object[i]->GetRect(),object[i]->GetImage());
        }

        for(i=0;i<Edit_Max;i++){//画敌人
            if(enemy[i].GetAlive()==false)continue;
            painter->drawImage(enemy[i].GetRect(),enemy[i].GetImage());
            for(k=0;k<5;k++){
                if(enemy[i].GetBulletAlive(k)==false)continue;
                painter->drawImage(QRect(enemy[i].GetBulletPos(k).x-10,enemy[i].GetBulletPos(k).y-10,30,30),Shot1_Image);
            }
        }//画敌人

        if(!move.isActive())
            painter->drawImage(P1.GetRect(),P1.GetImage());//画玩家
        else{
            if(P1.GetHead()==UP||P1.GetHead()==DOWN)
            painter->drawImage(QRect(P1.GetRect().x()+QRandomGenerator::global()->bounded(-2,2),
                                    P1.GetRect().y(),40,40),P1.GetImage());//画玩家
            else
            painter->drawImage(QRect(P1.GetRect().x(),
                                    P1.GetRect().y()+QRandomGenerator::global()->bounded(-2,2),40,40),P1.GetImage());//画玩家

        }

        //paint RedZone
        for(i=0;i<Edit_Min;i++){
            if(redzone[i].GetAlive()==false)continue;
            painter->drawImage(redzone[i].GetRect(),redzone[i].GetImage());
        }
        //paint Introduce

        for(i=0;i<Edit_Max;i++){//创建粒子
            if(partical[i].GetAlive()==false)continue;
            painter->drawImage(partical[i].GetRect(),partical[i].GetImage());
        }

        for(i=0;i<Edit_Max;i++){
            if(P1.GetB1(i).GetAlive()){
            painter->drawImage(QRect(P1.GetB1(i).GetPos().x-10,P1.GetB1(i).GetPos().y-10,30,30),Shot4_Image);
            }
        }
            if(P1.GetB2().GetAlive()){
            painter->drawImage(QRect(P1.GetB2().GetPos().x-10,P1.GetB2().GetPos().y-10,30,30),Shot3_Image);
        }


        if(IntroduceP!=0)drawIntroduce(*painter);//介绍模式

}


void BattleWindow::Move(){//玩家移动
    P1.Player_Move(P1.GetSpeed());
    Player_HitCheck();
}



void BattleWindow::keyPressEvent(QKeyEvent *event){
    if(P1.GetPos().x<0||P1.GetPos().y<0||P1.GetPos().x>X_Max-40||P1.GetPos().y>Y_Max-40)return;
      //qDebug()<<event->key();
        if(!event->isAutoRepeat()){
            if(event->key()==87||event->key()==83||event->key()==65||event->key()==68)Key=event->key();
            switch (event->key()) {//wsad space
            case 87:P1.Player_ChangeHead(0);move.start(10);break;
            case 83:P1.Player_ChangeHead(1);move.start(10);break;
            case 65:P1.Player_ChangeHead(2);move.start(10);break;
            case 68:P1.Player_ChangeHead(3);move.start(10);break;
            case 32:
                switch (myskill.GetSkill()) {
                case SkillName::MainWeapon:if(P1.Player_B1Fire()==false)Play_MPOut();break;
                case SkillName::SubWeapon:if(P1.Player_B2Fire()==false)Play_MPOut();break;
                case SkillName::Fire:if(P1.Player_B3Fire()==true){
                        switch (P1.GetHead()) {
                        case UP:CreatePartical(P1.GetPos()-XY(50,100),XY(150,100),Type::Player_B3_UP);break;
                        case DOWN:CreatePartical(P1.GetPos()+XY(-50,50),XY(150,100),Type::Player_B3_DOWN);break;
                        case LEFT:CreatePartical(P1.GetPos()-XY(100,50),XY(100,150),Type::Player_B3_LEFT);break;
                        case RIGHT:CreatePartical(P1.GetPos()+XY(50,-50),XY(100,150),Type::Player_B3_RIGHT);break;
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
                    P1.Strengthen(0,0,0,-2,0,0);
                    P1.Player_ProcessOn(-P1.GetProcess());
                    Fix_Mod=0;
                    P1.Player_UnSlow();
                    return;
                }
                P1.Player_ProcessOn(-P1.GetProcess());
                fix.start(10);
                Fix_Mod=1;
                break;
            case 16777248:myskill.SkillChange();break;
            case 61:
                this->Command(QInputDialog::getText(this,"指令","请输入指令",QLineEdit::Normal,"/help",nullptr,Qt::WindowFlags(1),Qt::ImhNone));
                break;
            case 45:P1.Strengthen(10,10,0,0,0,0);break;
            case 48:P1.Strengthen(0,0,1,10,0,0);break;
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


void BattleWindow::Play_RedZone(int x){
    int i;
    for(i=0;i<Edit_Min;i++){
        if(RedZone_Sound[i].state()==QMediaPlayer::PlayingState) continue;
        RedZone_Sound[i].setVolume(x);
        RedZone_Sound[i].play();
        break;
    }
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
void BattleWindow::Play_RedZone_Pre(int x){
    int i;
    for(i=0;i<Edit_Min;i++){
        if(RedZone_Pre[i].state()==QMediaPlayer::PlayingState) continue;
        RedZone_Pre[i].setVolume(x);
        RedZone_Pre[i].play();
        break;
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
    CreatePartical(pos-R,XY(2*R,2*R),Type::RedZone_Flash);
    this->Play_RedZone_Pre(redzone[i].GetR()/10);
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
    if(num==25){
        Rain.stop();
        num=0;
    }
}
/*    QTimer *redzone=new QTimer(this);
    connect(redzone, SIGNAL(timeout()), this, SLOT(RedZone_Generate()));
    redzone->start(Red_Zone_Fre);*/
/* Red_Zone_Fre=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸频率/ms"),5000,100,20000,100,nullptr,nullptr);
 Red_Zone=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸几率%"),50,0,100,1,nullptr,nullptr);*/

void BattleWindow::on_dial_actionTriggered(int action)
{
    Fire=!Fire;
}
