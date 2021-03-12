#include "Client.h"
#include "ui_Client.h"
//BattleWindow::BattleWindow(QWidget  *parent,int Mission) : QMainWindow(parent),ui(new Ui::BattleWindow),Mission(Mission){
Client::Client(QWidget *parent)
 : QMainWindow(parent),ui(new Ui::Client)
{
    int i;
    ui->setupUi(this);
    head=NO;
    QRect Rect;
    for(i=0;i<200;i++){
    object[i]=new Temp();
    }
    setWindowIcon(QIcon(":/Images/Images/icon.png"));

    object[1]=new Wall(Rect,1,1);
    object[2]=new Wall(Rect,1,1);
    object[3]=new Wall(Rect,1,1);
    object[2]->SetStatue(1);
    object[3]->SetStatue(2);//Wall

    object[11]=new BedRock(Rect,1);
    object[12]=new BedRock(Rect,1);
    object[12]->SetStatue(1);//BedRock

    object[21]=new River(Rect,1);
    object[22]=new River(Rect,1);
    object[22]->SetStatue(1);//River

    object[31]=new Portal(Rect);
    object[32]=new Portal(Rect);
    object[32]->SetStatue(1);

    object[41]=new Camp(Rect,1,1);
    object[42]=new Camp(Rect,1,1);
    object[43]=new Camp(Rect,1,1);
    object[42]->SetStatue(1);
    object[43]->SetStatue(2);


    object[51]=new FirstAid(Rect,2);
    object[52]=new FirstAid(Rect,2);
    object[53]=new FirstAid(Rect,2);
    object[52]->SetStatue(1);
    object[53]->SetStatue(2);

    object[61]=new Weapon(Rect,2);
    object[62]=new Weapon(Rect,2);
    object[63]=new Weapon(Rect,2);
    object[62]->SetStatue(1);
    object[63]->SetStatue(2);

    object[71]=new Ruins(Rect,1);

    object[81]=new Grass(Rect,1);

    object[91]=new Nail(Rect);
    object[92]=new Nail(Rect);
    object[92]->SetStatue(1);

    object[101]=new Ice(Rect);//引用方块图片
    object[102]=new Ice(Rect);
    object[102]->SetStatue(1);



    new(&enemy[1])Enemy(Rect,1,1,1,1);
    enemy[1].Enemy_ChangeHead(0);
    new(&enemy[2])Enemy(Rect,1,1,1,1);
    enemy[2].Enemy_ChangeHead(1);
    new(&enemy[3])Enemy(Rect,1,1,1,1);
    enemy[3].Enemy_ChangeHead(2);
    new(&enemy[4])Enemy(Rect,1,1,1,1);
    enemy[4].Enemy_ChangeHead(3);

    new(&enemy[11])Enemy(Rect,1,1,1,2);
    enemy[11].Enemy_ChangeHead(0);
    new(&enemy[12])Enemy(Rect,1,1,1,2);
    enemy[12].Enemy_ChangeHead(1);
    new(&enemy[13])Enemy(Rect,1,1,1,2);
    enemy[13].Enemy_ChangeHead(2);
    new(&enemy[14])Enemy(Rect,1,1,1,2);
    enemy[14].Enemy_ChangeHead(3);

    new(&enemy[21])Enemy(Rect,1,1,1,3);
    enemy[21].Enemy_ChangeHead(0);
    new(&enemy[22])Enemy(Rect,1,1,1,3);
    enemy[22].Enemy_ChangeHead(1);
    new(&enemy[23])Enemy(Rect,1,1,1,3);
    enemy[23].Enemy_ChangeHead(2);
    new(&enemy[24])Enemy(Rect,1,1,1,3);
    enemy[24].Enemy_ChangeHead(3);

    new(&enemy[31])Enemy(Rect,1,1,1,4);
    enemy[31].Enemy_ChangeHead(0);
    new(&enemy[32])Enemy(Rect,1,1,1,4);
    enemy[32].Enemy_ChangeHead(1);
    new(&enemy[33])Enemy(Rect,1,1,1,4);
    enemy[33].Enemy_ChangeHead(2);
    new(&enemy[34])Enemy(Rect,1,1,1,4);
    enemy[34].Enemy_ChangeHead(3);

    new(&enemy[41])Enemy(Rect,1,1,1,5);
    enemy[41].Enemy_ChangeHead(0);
    new(&enemy[42])Enemy(Rect,1,1,1,5);
    enemy[42].Enemy_ChangeHead(1);
    new(&enemy[43])Enemy(Rect,1,1,1,5);
    enemy[43].Enemy_ChangeHead(2);
    new(&enemy[44])Enemy(Rect,1,1,1,5);
    enemy[44].Enemy_ChangeHead(3);





    new(&P1[0])Player(Rect,1,1);//玩家初始化
    P1[0].Player_ChangeHead(0);
    new(&P1[1])Player(Rect,1,1);//玩家初始化
    P1[1].Player_ChangeHead(1);
    new(&P1[2])Player(Rect,1,1);//玩家初始化
    P1[2].Player_ChangeHead(2);
    new(&P1[3])Player(Rect,1,1);//玩家初始化
    P1[3].Player_ChangeHead(3);
    new(&P1[4])Player(Rect,1,1);//玩家初始化
    P1[4].Player_ChangeHead(0);
    P1[4].Player_Slow();
    new(&P1[5])Player(Rect,1,1);//玩家初始化
    P1[5].Player_ChangeHead(1);
    P1[5].Player_Slow();
    new(&P1[6])Player(Rect,1,1);//玩家初始化
    P1[6].Player_ChangeHead(2);
    P1[6].Player_Slow();
    new(&P1[7])Player(Rect,1,1);//玩家初始化
    P1[7].Player_ChangeHead(3);
    P1[7].Player_Slow();


    //  实例化槽类
        bar[0] = new Bar(350,1000,100,2);
        bar[1] = new Bar(900,1000,100,1);
        bar[2] = new Bar(1420,1000,100,3);
    //  实例化槽类


        exit.load(":/Images/Images/cancel.png");

    GLWidGet_2 *openGL = new GLWidGet_2(this, this);

    openGL->setGeometry(0, 0, 2000, 1000);
    openGL->lower();

    connect(&Timer, &QTimer::timeout, openGL, &GLWidGet_2::animate);
    connect(&Checker, SIGNAL(timeout()), this, SLOT(Bullet_Fly()));
    Checker.start(100);
    Timer.start(10);

    udp_socket = new QUdpSocket(this);
    port = 10080;
    last_recv = 0;

    udp_socket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);//设置udp 端口
    connect(udp_socket, &QUdpSocket::readyRead,
            this, &Client::Recive);

    connect(&ParticalTick, SIGNAL(timeout()), this, SLOT(Flash2()));
    ParticalTick.start(50);

  //  QTimer reciver;
   // connect(&reciver, SIGNAL(timeout()), this, SLOT(Recive()));
   // reciver.start(50);
//
        showFullScreen();
}

Client::~Client()
{
    delete ui;
}
void Client::Flash2(){
    int i;
    for(i=0;i<PARTICAL_NUMBER;i++){
        if(!partical[i].GetAlive())continue;
        partical[i].FLash();
    }

}
void Client::paint(QPainter *painter, QPaintEvent *event) {
    int i;

    QImage temp(":/Images/Images/BattleGround.png");

    painter->drawImage(QRect(0,0,1920,1080),temp);


    for(i=0;i<Object_S.count();i++){//创建物体
        painter->drawImage(Object_S.at(i).MeRect,object[GetObjectImage(Object_S.at(i).type,Object_S.at(i).Status)]->GetImage());
    }

    painter->drawImage(QRect(1840,1000,80,80),exit);

    for(i=0;i<Enemy_S.count();i++){//创建物体
        painter->drawImage(Enemy_S.at(i).MeRect,enemy[this->GetEnemyImage(Enemy_S.at(i).type,Enemy_S.at(i).head)].GetImage());
    }

    for(i=0;i<PLAYER_B1_NUMBER;i++){
        if(!bullet1[i].GetAlive()) continue;
        painter->drawImage(bullet1[i].GetRect().adjusted(-10,-10,20,20),bullet1[i].GetImage());
    }

    for(i=0;i<PLAYER_B2_NUMBER;i++){
        if(!bullet2[i].GetAlive()) continue;
        painter->drawImage(bullet2[i].GetRect().adjusted(-10,-10,20,20),bullet2[i].GetImage());
    }

    for(i=0;i<Player_S.count();i++){
        painter->drawImage(Player_S.at(i).MeRect,
                           P1[this->GetPlayerImage(
                    Player_S.at(i).number,Player_S.at(i).head,Player_S.at(i).slow)].GetImage());
    }

    for(i=0;i<PARTICAL_NUMBER;i++){//创建物体
        if(!partical[i].GetAlive())continue;
        painter->drawImage(partical[i].GetRect(),partical[i].GetImage());
    }

    for(i=0;i<3;i++){
       painter->drawImage(bar[i]->GetRect1(),bar[i]->GetImage1());
       painter->drawImage(bar[i]->GetRect2(),bar[i]->GetImage2());
    }


}//OpenGl实现
QString Client::get_ip(){
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();//返回了IP地址
    }
    return 0;
}


void Client::Recive(){
    int count=1;
    Message message;
    bool clear=false,clear2=false,clear3=false,slow;
    qint32 x,y,x1,y1,type;
    qint32 m1;
    qint32 ip;
    Type ptype;
    HEAD head,head2;
    while (udp_socket->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(data.data(), data.size());
        QDataStream in(&data, QIODevice::ReadOnly);

        while(1){
        if(in.atEnd())break;//读到底
         in >> message; // 第一个消息
            switch (message) {
            case Message::Load_Object:
                if(!clear){Object_S.clear();clear=true;}//清楚现有数据库
                    in >> ip;  if(ip!=6) break;
                    in >>x>>y>>x1>>y1>>type>>m1;
                    if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>X_Max||y1>Y_Max||type<1||type>11||m1<0||m1>2)break;
                    Object_S.append(Object_Sql(QRect(x,y,x1,y1),type,m1));
                break;
            case Message::Load_Partical:
                in >> ip; if(ip!=6) break;
                in>>x>>y>>x1>>y1>>ptype;
                if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>X_Max||y1>Y_Max)break;
                CreatePartical(QRect(x,y,x1,y1),ptype);
                break;
            case Message::Load_Enemy:
                if(!clear2){Enemy_S.clear();;clear2=true;}//清楚现有数据库
                    in>>ip; if(ip!=6) break;
                    in >>x>>y>>x1>>y1>>head>>type;
                    if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>X_Max||y1>Y_Max||type<1||type>4||head<0||head>3)break;
                    Enemy_S.append(Enemy_Sql(QRect(x,y,x1,y1),head,type));
                break;
            case Message::Load_Bullet:
                    in>>count; if(count>PLAYER_B1_NUMBER||count<0)break;
                    in >>x>>y>>x1>>y1>>type;
                    if(x<-100||x>X_Max||y<-100||y>Y_Max||x1<1||y1<1||x1>200||y1>200||type<0||type>4)break;
                    if(bullet1[count].GetAlive()){
                        bullet1[count].SetRect(QRect(x,y,x1,y1));
                    }else{
                        CreateBullet(QRect(x,y,x1,y1),NO,type,1,Target::ALL,1,1);
                    }
                break;
            case Message::Dead_Bullet:
                in>>ip;
                if(bullet1[count].GetAlive()) bullet1[count].PlayerBullet1_Dead();
                break;
            case Message::Load_Bullet2:
                in>>count;
                if(count>PLAYER_B2_NUMBER||count<0)break;
                in >>x>>y>>x1>>y1>>type;
                if(x<-100||x>X_Max||y<-100||y>Y_Max||x1<1||y1<1||x1>200||y1>200||type<0||type>4)break;
                if(bullet2[count].GetAlive()){
                    bullet2[count].SetRect(QRect(x,y,x1,y1));
                }else{
                    CreateBullet2(QRect(x,y,x1,y1),0,type,1,Target::ALL,1,1,1);
                }
            break;
            case Message::Load_Player:
                if(!clear3){Player_S.clear();clear3=true;}
                    in>>ip; if(ip!=6) break;
                    in >>x>>y>>x1>>y1>>head2>>slow>>type;
                    if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>50||y1>50||type<0||type>10||head<0||head>3)break;
                    Player_S.append(Player_Sql(QRect(x,y,x1,y1),head2,type,slow));
                break;
            case Message::Player_Join_Is_Success:
                in>>m1;
                if(m1==-1)
                    QMessageBox::information(nullptr,tr("Sorry"),tr("Failed to Join the game..."), tr("OK"));
                if(m1>0&&m1<10){
                    QString t;
                    t.setNum(m1);
                    QMessageBox::information(nullptr,tr("Success"),"Success to join the game\nyour number is:"+t, tr("OK"));
                    this->MeNumber=m1;
                   // ui->pushButton->hide();工程模式
                }
                break;
            case Message::Load_Bar:
                in>>m1;
                if(m1==this->MeNumber){
                    in>>x>>y>>x1;
                    bar[0]->SetValue(x);
                    bar[1]->SetValue(y);
                    bar[2]->SetValue(x1);
                }
            default:break;
            }
        }
    }
}

void Client::CreatePartical(QRect Rect,Type type){
    int i;
    for(i=0;i<PARTICAL_NUMBER;i++){//创建爆炸粒子
        if(partical[i].GetAlive())continue;
                partical[i].~Partical();
               new(&partical[i])Partical(Rect,type);
        break;
    }//创建爆炸粒子
}

int Client::GetEnemyImage(int type,HEAD head){
    switch (head) {
    case UP:return 1+((type-1)*10);
    case DOWN:return 2+((type-1)*10);
    case LEFT:return 3+((type-1)*10);
    case RIGHT:return 4+((type-1)*10);
    }
    return 1;
}

int Client::GetPlayerImage(int type,HEAD head,bool slow){
    return (slow*4+head);
}
void Client::Request(int mode){
    QByteArray data;
    QDataStream output(&data, QIODevice::WriteOnly);
    switch (mode) {
    case 0:
        output<<Message::Player_Join<<this->get_ip();
        break;

    default:return;

    }
    udp_socket->writeDatagram(data, data.length(),QHostAddress::Broadcast, this->port);
    data.clear();
}
void Client::on_pushButton_clicked()
{
    this->Request(0);
}
void Client::keyPressEvent(QKeyEvent *event){
if(!event->isAutoRepeat()){
    QByteArray data;
    QDataStream output(&data, QIODevice::WriteOnly);
    switch (event->key()) {//wsad space
    case 87:output<<Message::KEYBOARD_PUSHD<<this->MeNumber<<HEAD::UP;head=UP;break;
    case 83:output<<Message::KEYBOARD_PUSHD<<this->MeNumber<<HEAD::DOWN;head=DOWN;break;
    case 65:output<<Message::KEYBOARD_PUSHD<<this->MeNumber<<HEAD::LEFT;head=LEFT;break;
    case 68:output<<Message::KEYBOARD_PUSHD<<this->MeNumber<<HEAD::RIGHT;head=RIGHT;break;//1代表按下 0123代表
    case 32:output<<Message::KEYBOARD_OTHER<<this->MeNumber<<KEYBOARD_CONTROLL::PFIRE<<Mouse_Point.x()<<Mouse_Point.y();break;//2代表发炮
    case 16777248:output<<Message::KEYBOARD_OTHER<<this->MeNumber<<KEYBOARD_CONTROLL::PCHANGE;break;//换武器技能
    }
    //qDebug()<<"sending data..."<<data<<this->MeNumber;
    udp_socket->writeDatagram(data, data.length(),QHostAddress::Broadcast, this->port);
    data.clear();
}
}

void Client::keyReleaseEvent(QKeyEvent *event){
if(!event->isAutoRepeat()){
    switch (event->key()) {
    case 87:if(UP!=head)return;break;
    case 83:if(DOWN!=head)return;break;
    case 65:if(LEFT!=head)return;break;
    case 68:if(RIGHT!=head)return;break;
    }//返回
    QByteArray data;
    QDataStream output(&data, QIODevice::WriteOnly);
    switch (event->key()) {//wsad space
    case 87:output<<Message::KEYBOARD_RELEASED<<this->MeNumber;break;
    case 83:output<<Message::KEYBOARD_RELEASED<<this->MeNumber;break;
    case 65:output<<Message::KEYBOARD_RELEASED<<this->MeNumber;break;
    case 68:output<<Message::KEYBOARD_RELEASED<<this->MeNumber;break;
    default:return;
    }
    udp_socket->writeDatagram(data, data.length(),QHostAddress::Broadcast, this->port);
}
}

void Client::mouseMoveEvent(QMouseEvent *ev)
{
    Mouse_Point=ev->pos();
}

void Client::CreateBullet(QRect const MeRect,HEAD const h,int const type,int const Damage,Target target,int master,int Speed){
    int i;
    for(i=0;i<PLAYER_B1_NUMBER;i++){
        if(bullet1[i].GetAlive()) continue;
            bullet1[i].Init(MeRect,h,type,Damage,target,master,Speed);
            break;
    }
}
void Client::CreateBullet2(QRect const MeRect,double const Drection,int const type,int const Damage,Target const target,int const master,int const speed,int const HP){
     int i;
     for(i=0;i<PLAYER_B2_NUMBER;i++){
        if(bullet2[i].GetAlive()) continue;
            bullet2[i].Init(MeRect,Drection,type,Damage,target,master,speed,HP);
            break;
     }
}

void Client::CorrectBullet(int number,QRect Rect,bool Alive){
    if(Alive==false){
        bullet1[number].PlayerBullet1_Dead();
        return;
    }
    bullet1[number].SetRect(Rect);
    return;
}
void Client::Bullet_Fly(){
    int i;
    for(i=0;i<PLAYER_B1_NUMBER;i++){
        if(!bullet1[i].GetAlive()) continue;
        if(bulletr[i].contains(bullet1[i].GetRect())){
            bullet1[i].PlayerBullet1_Dead();
        }else{
        bulletr[i]=bullet1[i].GetRect();
        }
    }
    for(i=0;i<PLAYER_B2_NUMBER;i++){
        if(!bullet2[i].GetAlive()) continue;
        if(bulletr2[i].contains(bullet2[i].GetRect())){
            bullet2[i].PlayerBullet2_Dead();
        }else{
        bulletr2[i]=bullet2[i].GetRect();
        }
    }
}

void Client::on_pushButton_2_clicked()
{
    this->~Client();
}

void Client::mousePressEvent(QMouseEvent *a){
    if(QRect(1840,1000,80,80).contains(a->pos())){
        this->~Client();
        mainwindow=new MainWindow();
        mainwindow->show();
    }
}
