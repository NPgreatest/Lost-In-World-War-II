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
    QRect Player_Rect;
    int thp,tmp;

    QRect Object_Rect[Edit_Max];
    int type[Edit_Max];
    int skin[Edit_Max];
    int hp[Edit_Max];

    int e_hp[Edit_Max];
    int e_speed[Edit_Max];
    int e_bullet_speed[Edit_Max];
    QRect Enemy_Rect[Edit_Max];
    int e_skin[Edit_Max];

    for(i=0;i<Edit_Max;i++){
        Player_Rect.setRect(0,0,0,0);
        Enemy_Rect->setRect(0,0,0,0);
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
            Object_Rect[i].setRect(list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt());
            hp[i]=list[5].toInt();
            skin[i]=list[6].toInt();
            i++;
            break;
        case 2:
            Player_Rect.setRect(list[0].toInt(),list[1].toInt(),40,40);
            thp=list[2].toInt();
            tmp=list[3].toInt();
            tlv=list[4].toInt();
            tmat=list[5].toInt();
            tb1c=list[6].toInt();
            break;
        case 3:
            Enemy_Rect[i].setRect(list[0].toInt(),list[1].toInt(),list[2].toInt(),list[3].toInt());
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
        new(&P1)Player(Player_Rect,thp,tmp,tlv,tmat,tb1c);//玩家初始化

    for(i=0;i<Edit_Max;i++){//创建物体
        CreateObject(Object_Rect[i],type[i],skin[i],hp[i]);
    }

    for(i=0;i<Edit_Max;i++){//创建敌人
         if(!Enemy_Rect[i].width()||!Enemy_Rect[i].height())continue;
         CreatePartical(Enemy_Rect[i],Type::Object_Hit);
         CreateEnemy(Enemy_Rect[i],e_hp[i],e_speed[i],e_bullet_speed[i],e_skin[i]);
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
            painter->drawImage(boss1->GetB2(i).GetRect(),boss1->GetB2(i).GetImage());
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
                painter->drawImage(enemy[i].GetB1(k).GetRect(),Shot1_Image);
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
            painter->drawImage(P1.GetB1(i).GetRect().adjusted(-10,-10,20,20),Shot4_Image);
            }
        }
        for(i=0;i<Edit_Max;i++){
            if(P1.GetB2(i).GetAlive()){
            painter->drawImage(P1.GetB2(i).GetRect().adjusted(-10,-10,20,20),Shot3_Image);
            }
        }


        if(IntroduceP!=0)drawIntroduce(*painter);//介绍模式

}


void BattleWindow::Move(){//玩家移动
    P1.Player_Move(P1.GetSpeed());
    Player_HitCheck();
}



void BattleWindow::keyPressEvent(QKeyEvent *event){
    if(P1.GetRect().x()<0||P1.GetRect().y()<0||
            P1.GetRect().x()>X_Max-40||P1.GetRect().y()>Y_Max-40)return;
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
                case SkillName::MainWeapon:if(!P1.Player_B1Fire())Play_MPOut();break;
                case SkillName::SubWeapon:
                    double t1,t2,result;
                    t1=Mouse_Point.x()-P1.GetRect().center().x();
                    t2=Mouse_Point.y()-P1.GetRect().center().y();
                    result=atan(t1/t2);
                    if(t2<0) result+=3.1415926;
                    if(!P1.Player_B2Fire(result))Play_MPOut();break;
                case SkillName::Fire:if(P1.Player_B3Fire()){
                        switch (P1.GetHead()) {
                        case UP:CreatePartical(P1.GetRect().adjusted(-40,-40,40,-40),Type::Player_B3_UP);break;
                        case DOWN:CreatePartical(P1.GetRect().adjusted(-40,40,40,40),Type::Player_B3_DOWN);break;
                        case LEFT:CreatePartical(P1.GetRect().adjusted(-40,-40,-80,40),Type::Player_B3_LEFT);break;
                        case RIGHT:CreatePartical(P1.GetRect().adjusted(40,-40,40,40),Type::Player_B3_RIGHT);break;
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
void BattleWindow::CreatePartical(QRect Rect,Type type){
    int i;
    for(i=0;i<Edit_Max;i++){//创建爆炸粒子
        if(partical[i].GetAlive()==true)continue;
                partical[i].~Partical();
               new(&partical[i])Partical(Rect,type);
        break;
    }//创建爆炸粒子
}


void BattleWindow::CreateEnemy(QRect Rect,int hp,int speed,int bulletspeed,int skin){
    if(!Rect.width()||!Rect.height()) return;
    if(Rect.topRight().x()>X_Max||Rect.bottom()>Y_Max||Rect.x()<0||Rect.y()<0)return;
    int i;
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==true)continue;
        new(&enemy[i])Enemy(Rect,hp,speed,bulletspeed,skin);break;
    }
}

void BattleWindow::CreateObject(QRect Rect,int type,int skin,int hp){
    if(type==0)return;
    int i;
    for(i=0;i<Edit_Max;i++){//创建物体
        if(object[i]->GetAlive()==false){
        object[i]->~Object();
        break;
        }

    }//创建物体
    switch (type) {
    case 1:object[i]=new Wall(Rect,skin,hp);break;
    case 2:object[i]=new BedRock(Rect,skin);break;
    case 3:object[i]=new River(Rect,skin);break;
    case 4:object[i]=new Portal(Rect);break;
    case 5:object[i]=new Camp(Rect,1,hp);break;
    case 6:object[i]=new FirstAid(Rect,1);break;
    case 7:object[i]=new Weapon(Rect,1);break;
    case 8:object[i]=new Camp(Rect,2,hp);break;
    case 9:object[i]=new FirstAid(Rect,2);break;
    case 10:object[i]=new Weapon(Rect,2);break;
    case 11:object[i]=new Camp(Rect,3,hp);break;
    case 12:object[i]=new FirstAid(Rect,3);break;
    case 13:object[i]=new Weapon(Rect,3);break;
    case 14:object[i]=new Ruins(Rect,skin);break;
    case 15:object[i]=new Grass(Rect,skin);break;
    case 16:object[i]=new Nail(Rect);break;
    case 17:object[i]=new Ice(Rect);break;
    default:qDebug()<<"sonethings wrong..";break;
    }
}
void BattleWindow::CreateRedZone(QRect Rect,int R,int type){
    int i;
    for(i=0;i<Edit_Min;i++){
        if(redzone[i].GetAlive()==true)continue;
        new(&redzone[i])RedZone(Rect,R,type);
        redzone[i].Flash_Begin();
        CreatePartical(redzone[i].GetRect(),Type::RedZone_Flash);
        break;
    }

    this->Play_RedZone_Pre(redzone[i].GetR()/10);
}

void BattleWindow::ClearMap(QRect Rect){//清理地图
    int i;
    for(i=0;i<Edit_Max;i++){
        enemy[i].Dead();
        if(object[i]->GetAlive())
        object[i]->Dead();
    }
    P1.SetPos(Rect);
}

BattleWindow::~BattleWindow(){
    Bullet_Sound->~QMediaPlayer();
    BackGroundMusic->~QMediaPlayer();
    MPOut->~QMediaPlayer();
}
void BattleWindow::RainFire(){
    static int num=0;
    int r;
    QRect Rect;
    Rect.setRect(QRandomGenerator::global()->bounded(0,X_Max),
                 QRandomGenerator::global()->bounded(0,X_Max),
                 QRandomGenerator::global()->bounded(50,500),
                 QRandomGenerator::global()->bounded(50,500));
    r=QRandomGenerator::global()->bounded(50,200);
    CreateRedZone(Rect,r,1);
    num++;
    if(num == 25){
        Rain.stop();
        num = 0;
    }
}
/*    QTimer *redzone=new QTimer(this);
    connect(redzone, SIGNAL(timeout()), this, SLOT(RedZone_Generate()));
    redzone->start(Red_Zone_Fre);*/
/* Red_Zone_Fre=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸频率/ms"),5000,100,20000,100,nullptr,nullptr);
 Red_Zone=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸几率%"),50,0,100,1,nullptr,nullptr);*/


