#include "Client.h"
#include "ui_Client.h"
//BattleWindow::BattleWindow(QWidget  *parent,int Mission) : QMainWindow(parent),ui(new Ui::BattleWindow),Mission(Mission){
Client::Client(QWidget *parent)
 : QMainWindow(parent),ui(new Ui::Client)
{
    ui->setupUi(this);
    head=NO;
    QRect Rect;
    object[1]=new Wall(Rect,1,1);
    object[2]=new BedRock(Rect,1);
    object[3]=new River(Rect,1);
    object[4]=new Portal(Rect);
    object[5]=new Camp(Rect,1,1);
    object[6]=new FirstAid(Rect,2);
    object[7]=new Weapon(Rect,2);
    object[8]=new Ruins(Rect,1);
    object[9]=new Grass(Rect,1);
    object[10]=new Nail(Rect);
    object[11]=new Ice(Rect);//引用方块图片


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



    bullet[0].Init(Rect,HEAD::UP,1);
    bullet[1].Init(Rect,HEAD::UP,1);
    bullet[2].Init(Rect,HEAD::UP,2);
    bullet[3].Init(Rect,HEAD::UP,3);
    bullet[4].Init(Rect,HEAD::UP,4);//引用子弹图片

    new(&P1[0])Player(Rect,1,1,1);//玩家初始化
    P1[0].Player_ChangeHead(0);
    new(&P1[1])Player(Rect,1,1,1);//玩家初始化
    P1[1].Player_ChangeHead(1);
    new(&P1[2])Player(Rect,1,1,1);//玩家初始化
    P1[2].Player_ChangeHead(2);
    new(&P1[3])Player(Rect,1,1,1);//玩家初始化
    P1[3].Player_ChangeHead(3);
    new(&P1[4])Player(Rect,1,1,1);//玩家初始化
    P1[4].Player_ChangeHead(0);
    P1[4].Player_Slow();
    new(&P1[5])Player(Rect,1,1,1);//玩家初始化
    P1[5].Player_ChangeHead(1);
    P1[5].Player_Slow();
    new(&P1[6])Player(Rect,1,1,1);//玩家初始化
    P1[6].Player_ChangeHead(2);
    P1[6].Player_Slow();
    new(&P1[7])Player(Rect,1,1,1);//玩家初始化
    P1[7].Player_ChangeHead(3);
    P1[7].Player_Slow();


    GLWidGet_2 *openGL = new GLWidGet_2(this, this);

    openGL->setGeometry(0, 0, 2000, 1000);
    openGL->lower();

    connect(&Timer, &QTimer::timeout, openGL, &GLWidGet_2::animate);
    Timer.start(10);

    udp_socket = new QUdpSocket(this);
    port = 10080;
    last_recv = 0;

    udp_socket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);//设置udp 端口
    connect(udp_socket, &QUdpSocket::readyRead,
            this, &Client::Recive);

    connect(&ParticalTick, SIGNAL(timeout()), this, SLOT(Flash2()));
    ParticalTick.start(50);
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

    painter->drawImage(QRect(0,0,2000,1000),temp);


    for(i=0;i<sql.GetObject_Num();i++){//创建物体
        //qDebug()<<sql.GetObject_Num()<<"+objecttype:"<<sql.GetObjectW(i).type;
        painter->drawImage(sql.GetObjectW(i).MeRect,object[sql.GetObjectW(i).type]->GetImage());
    }



    for(i=0;i<sql.GetEnemy_Num();i++){//创建物体
        painter->drawImage(sql.GetEnemy(i).MeRect,enemy[this->GetEnemyImage(sql.GetEnemy(i).type,sql.GetEnemy(i).head)].GetImage());
    }

    for(i=0;i<sql.GetBullet_Num();i++){
        //qDebug()<<sql.GetBullet_Num()<<"+type:"<<sql.GetBullet(i).type;
        painter->drawImage(sql.GetBullet(i).MeRect,bullet[sql.GetBullet(i).type].GetImage());
    }

    for(i=0;i<sql.GetPlayer_Num();i++){
        painter->drawImage(sql.GetPlayer(i).MeRect,
                           P1[this->GetPlayerImage(
                    sql.GetPlayer(i).number,sql.GetPlayer(i).head,sql.GetPlayer(i).slow)].GetImage());
    }

    for(i=0;i<PARTICAL_NUMBER;i++){//创建物体
        if(!partical[i].GetAlive())continue;
        painter->drawImage(partical[i].GetRect(),partical[i].GetImage());
    }

}//OpenGl实现
QString Client::get_ip()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();//返回了IP地址
    }
    return 0;
}


void Client::Recive(){
    int i=0,j=0,count=1;
                Message message;
                bool clear=false,clear2=false,clear3=false,clear4=false,slow;
    qint32 x,y,x1,y1,type;
    qint32 m1,m2;
    Type ptype;
    HEAD head,head2;
    while (udp_socket->hasPendingDatagrams())
    {
        QByteArray data;

        data.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(data.data(), data.size());

            QDataStream in(&data, QIODevice::ReadOnly);


            while(1){
            //for(i=0;i<1000;i++){
            if(in.atEnd())break;


           a: in >> message;
            switch (message) {
            case Message::Load_Object:
                if(!clear){sql.ObjectClear();clear=true;}
                    in >> count;
                    if(count<=0||count>1000)break;
                    in >>x>>y>>x1>>y1>>type;
                    if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>X_Max||y1>Y_Max||type<1||type>11)break;
                    //qDebug()<<"Loadobject:"<<count<<x<<y<<x1<<y1<<type;
                    sql.AddObject(Object_Sql(QRect(x,y,x1,y1),type));
                    goto a;
                break;
            case Message::Load_Partical:
                in >> count;if(count<=0||count>1000)break;
                in>>x>>y>>x1>>y1>>ptype;
                if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>X_Max||y1>Y_Max)break;
                //qDebug()<<"LoadPartical:"<<count<<x<<y<<x1<<y1<<ptype;
                CreatePartical(QRect(x,y,x1,y1),ptype);
                goto a;
                break;
            case Message::Load_Enemy:
                if(!clear2){sql.EnemyClear();clear2=true;}
                    in>>count;if(count<=0||count>1000)break;
                    in >>x>>y>>x1>>y1>>head>>type;
                    if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>X_Max||y1>Y_Max||type<1||type>4||head<0||head>3)break;
                    //qDebug()<<"LoadEnemy:"<<count<<x<<y<<x1<<y1<<type;
                    sql.AddEnemy(Enemy_Sql(QRect(x,y,x1,y1),head,type));
                    goto a;
                break;
            case Message::Load_Bullet:
                if(!clear3){sql.BulletClear();clear3=true;}
                    in>>count;if(count<=0||count>1000)break;
                    in >>x>>y>>x1>>y1>>type;
                    if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>50||y1>50||type<1||type>4)break;
                    //qDebug()<<"Loadbullet:"<<count<<x<<y<<x1<<y1<<type;
                    sql.AddBullet(Bullet_Sql(QRect(x,y,x1,y1),type));
                    goto a;
                break;
            case Message::Load_Player:
                if(!clear4){sql.PlayerClear();clear4=true;}
                    in>>count;if(count<=0||count>1000)break;
                    in >>x>>y>>x1>>y1>>head2>>slow>>type;
                    if(x<0||x>X_Max||y<0||y>Y_Max||x1<1||y1<0||x1>50||y1>50||type<0||type>10||head<0||head>3)break;
                    qDebug()<<"LoadPlayer:"<<count<<x<<y<<x1<<y1<<type;
                    sql.AddPlayer(Player_Sql(QRect(x,y,x1,y1),head2,type,slow));
                    goto a;
                break;
            case Message::Player_Join_Is_Success:
                in>>m1;
                if(m1==-1)
                    QMessageBox::information(nullptr,tr("Sorry"),tr("Failed to Join the game..."), tr("OK"));
                if(m1>0&&m1<10){
                    QMessageBox::information(nullptr,tr("Success"),tr("Success to join the game"), tr("OK"));
                    this->MeNumber=m1;
                }
                break;
                goto a;
            //default:break;
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
    case 32:output<<Message::KEYBOARD_OTHER<<this->MeNumber;break;//2代表发炮
    }
    udp_socket->writeDatagram(data, data.length(),QHostAddress::Broadcast, this->port);
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
