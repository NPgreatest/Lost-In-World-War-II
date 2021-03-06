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
    for(i=0;i<OBJECT_NUMBER;i++){//实例化物体
        object[i]=new Temp();
    }


//实例化槽类
    bar[0] = new Bar(1500,100,100,1);
    bar[1] = new Bar(1580,100,100,2);
    bar[2] = new Bar(1660,100,5,3);
    bar[3] = new Bar(1740,100,100,4);
//实例化槽类


    Bullet_Sound->setMedia(QUrl("qrc:/sounds/sounds/Player_Hit1.mp3"));
    Bullet_Sound_2->setMedia(QUrl("qrc:/sounds/sounds/Player_Hit2.mp3"));

    for(i=0;i<REDZONE_NUMBER;i++){
    RedZone_Pre[i].setMedia(QUrl("qrc:/sounds/sounds/RedZone_Pre.mp3"));
    RedZone_Sound[i].setMedia(QUrl("qrc:/sounds/sounds/RedZone.mp3"));
    }
    MPOut->setMedia(QUrl("qrc:/sounds/sounds/ .mp3"));
    BackGroundMusic->setMedia(QUrl("qrc:/sounds/sounds/BattleMusic1.mp3"));

    //connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    GLWidGet *openGL = new GLWidGet(this, this);

    openGL->setGeometry(0, 0, 2000, 1000);
    openGL->lower();

    connect(&Timer, &QTimer::timeout, openGL, &GLWidGet::animate);



    connect(&Timer, SIGNAL(timeout()), this, SLOT(Bullet_Fly()));
    connect(&One_Sec, SIGNAL(timeout()), this, SLOT(Flash()));
    connect(&move, SIGNAL(timeout()), this, SLOT(Move()));
    connect(&FinalWeapon,  SIGNAL(timeout()), this, SLOT(P1_Weapon()));
    connect(&EnemyMove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
    connect(&EnemyMove, SIGNAL(timeout()), this, SLOT(Boss_Move()));
    connect(&EnemyAll, SIGNAL(timeout()), this, SLOT(Enemy_All()));
    connect(&ParticalTick, SIGNAL(timeout()), this, SLOT(Flash2()));
    connect(&Rain, SIGNAL(timeout()), this, SLOT(RainFire()));
    connect(&UploadData, SIGNAL(timeout()), this, SLOT(Write_Sql()));

    if(Mission==0){//介绍模式
        this->Load_Introduce();
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, openGL, &GLWidGet::animate);
        timer->start(10);
        return;
    }//介绍模式


      ParticalTick.start(50);
      Timer.start(10);
      One_Sec.start(1000);
      EnemyMove.start(50);
      EnemyAll.start(100);
      move.start(10);
      UploadData.start(100);



      udp_socket = new QUdpSocket(this);
      port = 10080;
      last_recv = 0;


      udp_socket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);//设置udp 端口
      connect(udp_socket, &QUdpSocket::readyRead,
              this, &BattleWindow::Recive);





    switch (Mission) {
    case 1:MissionTeach();return;
    case 2:MissionRougueLike();return;
    default:
        QString Address = QFileDialog::getOpenFileName(this,tr("Choose Map"),nullptr, tr("Image Files (*.txt)"));

        Load_Map(Address);
        break;
    }

}

void BattleWindow::Load_Map(QString Address){
    int i=0,read=0,tlv;
    bool me=false;
    QRect Player_Rect;
    int thp,tmp;

    QRect Object_Rect[OBJECT_NUMBER];
    int type[OBJECT_NUMBER];
    int skin[OBJECT_NUMBER];
    int hp[OBJECT_NUMBER];

    int e_hp[ENEMY_NUMBER];
    int e_speed[ENEMY_NUMBER];
    int e_bullet_speed[ENEMY_NUMBER];
    QRect Enemy_Rect[ENEMY_NUMBER];
    int e_skin[ENEMY_NUMBER];

    Player_Rect.setRect(0,0,0,0);
    for(i = 0; i < ENEMY_NUMBER; i++){
        e_hp[i]=0;
        e_speed[i]=0;
        e_bullet_speed[i]=0;
        e_skin[i]=0;
    }
    for(i=0;i<OBJECT_NUMBER;i++){
        type[i]=0;
        skin[i]=0;
        hp[i]=1;
    }


    QFile file(Address);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(nullptr,tr("Warning"),tr("Failed to load map"), tr("OK"));
        this->~BattleWindow();
        backto=new MainWindow;
        backto->setMouseTracking(true);
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


    if(me)
        new(&P1)Player(Player_Rect,thp,tmp,tlv);//玩家初始化

    for(i=0;i<OBJECT_NUMBER;i++){//创建物体
        CreateObject(Object_Rect[i],type[i],skin[i],hp[i]);
    }

    for(i=0;i<ENEMY_NUMBER;i++){//创建敌人
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


        //bar[0]->SetValue(P1.GetHP());
        //bar[1]->SetValue(P1.GetMP());
        //bar[2]->SetValue(P1.GetWeaponLv());
        //bar[3]->SetValue(P1.GetProcess());
        for(i=0;i<4;i++){
           painter->drawImage(bar[i]->GetRect1(),bar[i]->GetImage1());
           painter->drawImage(bar[i]->GetRect2(),bar[i]->GetImage2());
        }

        //画boss及其子弹
        if(boss1->GetAlive()){
        painter->drawImage(boss1->GetRect(),boss1->GetImage());
        for(i=0;i<Edit_Min;i++){
            painter->drawImage(boss1->GetB2(i).GetRect(),boss1->GetB2(i).GetImage());
            }
        }
        //画boss及其子弹


        for(i=0;i<PLAYER_NUMBER_MAX;i++){
            if(!P1[i].GetActivate())continue;
            painter->drawImage(P1[i].GetSkill().GetRect(),P1[i].GetSkill().GetImage());//画技能槽
        }

        for(i=0;i<OBJECT_NUMBER;i++){//创建物体
            if(!object[i]->GetAlive())continue;
            painter->drawImage(object[i]->GetRect(),object[i]->GetImage());
        }

        for(i=0;i<ENEMY_NUMBER;i++){//画敌人
            if(enemy[i].GetAlive()==false)continue;
            painter->drawImage(enemy[i].GetRect(),enemy[i].GetImage());
            for(k=0;k<5;k++){
                if(enemy[i].GetBulletAlive(k)==false)continue;
                painter->drawImage(enemy[i].GetB1(k).GetRect(),enemy[i].GetB1(k).GetImage());
            }
        }//画敌人

        for(i=0;i<PLAYER_NUMBER_MAX;i++){
            if(!P1[i].GetActivate())continue;
        if(!move.isActive())
            painter->drawImage(P1[i].GetRect(),P1[i].GetImage());//画玩家
        else{
            if(P1[i].GetHead()==UP||P1[i].GetHead()==DOWN)
            painter->drawImage(QRect(P1[i].GetRect().x()+QRandomGenerator::global()->bounded(-2,2),
                                    P1[i].GetRect().y(),40,40),P1[i].GetImage());//画玩家
            else
            painter->drawImage(QRect(P1[i].GetRect().x(),
                                    P1[i].GetRect().y()+QRandomGenerator::global()->bounded(-2,2),40,40),P1[i].GetImage());//画玩家

        }
        }

        //paint RedZone
        for(i=0;i<REDZONE_NUMBER;i++){
            if(!redzone[i].GetAlive())continue;
            painter->drawImage(redzone[i].GetRect(),redzone[i].GetImage());
        }
        //paint Introduce

        for(i=0;i<PARTICAL_NUMBER;i++){//创建粒子
            if(!partical[i].GetAlive())continue;
            painter->drawImage(partical[i].GetRect(),partical[i].GetImage());
        }

        for(k=0;k<PLAYER_NUMBER_MAX;k++){
            if(!P1[k].GetActivate())continue;
        for(i=0;i<PLAYER_B1_NUMBER;i++){
            if(P1[k].GetB1(i).GetAlive()){
            painter->drawImage(P1[k].GetB1(i).GetRect().adjusted(-10,-10,20,20),P1[k].GetB1(i).GetImage());
            }
        }
        for(i=0;i<PLAYER_B2_NUMBER;i++){
            if(P1[k].GetB2(i).GetAlive()){
            painter->drawImage(P1[k].GetB2(i).GetRect().adjusted(-10,-10,20,20),P1[k].GetB2(i).GetImage());
            }
        }
        }

        if(!Mission)drawIntroduce(*painter);//   draw  介绍模式

}


void BattleWindow::Move(){//玩家移动
    int i;
    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate())continue;
        if(Key[i]==UP||Key[i]==DOWN||Key[i]==LEFT||Key[i]==RIGHT)
        P1[i].Player_Move(P1[i].GetSpeed());
        Player_HitCheck(i);
    }

}

void BattleWindow::Controller(int number,KEYBOARD_CONTROLL key,HEAD head){
    int i;
    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate())continue;
        if(number==i)break;
        if(i==PLAYER_NUMBER_MAX)return;
    }
    Key[number]=head;

    switch (head) {
    case UP:P1[number].Player_ChangeHead(0);break;
    case DOWN:P1[number].Player_ChangeHead(1);break;
    case LEFT:P1[number].Player_ChangeHead(2);break;
    case RIGHT:P1[number].Player_ChangeHead(3);break;
    case NO:break;
    }
    switch (key) {
    case PCHANGE:P1[number].GetSkill().SkillChange();break;
    case PFIRE:
        switch (P1[number].GetSkill().GetSkill()) {
        case SkillName::MainWeapon:if(!P1[number].Player_B1Fire())Play_MPOut();break;
        case SkillName::SubWeapon:
            if(P1[number].GetProcess()!=100){
                Play_MPOut();
                return;
            }
            double t1,t2,result;
            t1=Mouse_Point.x()-P1[number].GetRect().center().x();
            t2=Mouse_Point.y()-P1[number].GetRect().center().y();
            result=atan(t1/t2);
            if(t2<0) result+=3.1415926;
            P1[number].Player_B2Fire(result);
            P1[number].SetChoose(2);
            break;
        case SkillName::Fire:if(P1[number].Player_B3Fire()){
                switch (P1[number].GetHead()) {
                case UP:CreatePartical(P1[number].GetRect().adjusted(-50,-100,60,-40),Type::Player_B3_UP);break;
                case DOWN:CreatePartical(P1[number].GetRect().adjusted(-50,40,60,100),Type::Player_B3_DOWN);break;
                case LEFT:CreatePartical(P1[number].GetRect().adjusted(-100,-50,-40,60),Type::Player_B3_LEFT);break;
                case RIGHT:CreatePartical(P1[number].GetRect().adjusted(40,-50,110,60),Type::Player_B3_RIGHT);break;
                }
            }break;
        }break;
    default:break;
    }

}

void BattleWindow::keyPressEvent(QKeyEvent *event){
    if(P1[0].GetRect().x()<0||P1[0].GetRect().y()<0||
            P1[0].GetRect().x()>X_Max-40||P1[0].GetRect().y()>Y_Max-40)return;

    int i;
    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if(!P1[i].GetActivate()) continue;
        if(!event->isAutoRepeat()){
            qDebug()<<"press"<<event->key();
            switch (event->key()) {//wsad space[
            case 87:this->Controller(0,PNO,UP);break;
            case 83:this->Controller(0,PNO,DOWN);break;
            case 65:this->Controller(0,PNO,LEFT);break;
            case 68:this->Controller(0,PNO,RIGHT);break;
            case 32:this->Controller(0,PFIRE,Key[0]);break;
            case 76:
                if(P1[i].GetChoose()==1)
                    P1[i].SetChoose(0);
                else if(P1[i].GetChoose()==0)
                    P1[i].SetChoose(1);
                break;
            case 16777248:this->Controller(0,PCHANGE,Key[0]);
            case 61:
                this->Command(QInputDialog::getText(this,"指令","请输入指令",QLineEdit::Normal,"/help",nullptr,Qt::WindowFlags(1),Qt::ImhNone));
                return;
            case 45:P1[i].Strengthen(10,10,0,0);break;
            case 48:P1[i].Strengthen(0,0,1,0);break;
            }
         }
    }
}

void BattleWindow::keyReleaseEvent(QKeyEvent *event){

   if(!event->isAutoRepeat()){
            qDebug()<<"release"<<event->key();
       switch (event->key()) {
       case 87:if(UP==Key[0])Key[0]=NO;break;
       case 83:if(DOWN==Key[0])Key[0]=NO;break;
       case 65:if(LEFT==Key[0])Key[0]=NO;break;
       case 68:if(RIGHT==Key[0])Key[0]=NO;break;
       }

}
}



void BattleWindow::Play_RedZone(int x){
    int i;
    for(i=0;i<REDZONE_NUMBER;i++){
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
    for(i=0;i<REDZONE_NUMBER;i++){
        if(RedZone_Pre[i].state()==QMediaPlayer::PlayingState) continue;
        RedZone_Pre[i].setVolume(x);
        RedZone_Pre[i].play();
        break;
    }
}
void BattleWindow::CreatePartical(QRect Rect,Type type){
    int i;
    for(i=0;i<PARTICAL_NUMBER;i++){//创建爆炸粒子
        if(partical[i].GetAlive())continue;
                partical[i].~Partical();
               new(&partical[i])Partical(Rect,type);
        break;
    }//创建爆炸粒子
    sql.AddPartical(Partical_Sql(Rect,type));//写入数据库
}


void BattleWindow::CreateEnemy(QRect Rect,int hp,int speed,int bulletspeed,int skin){
    if(!Rect.width()||!Rect.height()) return;
    if(Rect.topRight().x()>X_Max||Rect.bottom()>Y_Max||Rect.x()<0||Rect.y()<0)return;
    int i;
    for(i=0;i<ENEMY_NUMBER;i++){
        if(enemy[i].GetAlive())continue;
        new(&enemy[i])Enemy(Rect,hp,speed,bulletspeed,skin);break;
    }
}

void BattleWindow::CreateObject(QRect Rect,int type,int skin,int hp){
    if(type==0)return;
    int i;
    for(i=0;i<OBJECT_NUMBER;i++){//创建物体
        if(!object[i]->GetAlive()){
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
    for(i=0;i<REDZONE_NUMBER;i++){
        if(redzone[i].GetAlive())continue;
        new(&redzone[i])RedZone(Rect,R,type);
        redzone[i].Flash_Begin();
        CreatePartical(redzone[i].GetRect(),Type::RedZone_Flash);
        break;
    }

    this->Play_RedZone_Pre(redzone[i].GetR()/10);
}

void BattleWindow::ClearMap(QRect Rect){//清理地图
    int i;
    for(i=0;i<ENEMY_NUMBER;i++){
        enemy[i].Dead();
    }
    for(i=0;i<OBJECT_NUMBER;i++)
    if(object[i]->GetAlive())
    object[i]->Dead();

    P1[0].SetPos(Rect);
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


void BattleWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if(P1[0].GetSkill().GetSkill()==SkillName::SubWeapon)
    Mouse_Point=ev->pos();
}


/*
 * typedef struct{A
 * int a;
 * int b;
 * }*ll,k;
 * ll a, b;创建指针
 * k o,i创建结构体
 *
 * A *a, *b;
 *
 *
 *
 * */






void BattleWindow::on_pushButton_clicked()
{
    this->Recive();
}
