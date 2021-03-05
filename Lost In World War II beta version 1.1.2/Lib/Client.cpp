#include "Client.h"
#include "ui_Client.h"
//BattleWindow::BattleWindow(QWidget  *parent,int Mission) : QMainWindow(parent),ui(new Ui::BattleWindow),Mission(Mission){
Client::Client(QWidget *parent)
 : QMainWindow(parent),ui(new Ui::Client)
{
    ui->setupUi(this);

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
    object[11]=new Ice(Rect);




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
    int i,k;

    QImage temp(":/Images/Images/BattleGround.png");

    painter->drawImage(QRect(0,0,2000,1000),temp);


    for(i=0;i<sql.GetObject_Num();i++){//创建物体
        painter->drawImage(sql.GetObjectW(i).MeRect,object[sql.GetObjectW(i).type]->GetImage());
    }

    for(i=0;i<PARTICAL_NUMBER;i++){//创建物体
        if(!partical[i].GetAlive())continue;
        painter->drawImage(partical[i].GetRect(),partical[i].GetImage());
    }





    /*for(i=0;i<sql.GetEnemy_Num();i++){
        painter->drawImage(sql.GetEnemey(i).MeRect,sql.GetEnemey(i).MeImage);
        for(k=0;k<ENEMY_BULLET_NEMBER;k++){
             painter->drawImage(sql.GetEnemey(i).B1Rect[k],sql.GetEnemey(i).B1Image[k]);
        }
    }*/


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
                bool clear=false;
    qint32 x,y,x1,y1,type;
    Type ptype;
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

            if(message==Message::Load_Object){
                if(!clear){sql.ObjectClear();clear=true;qDebug()<<"clear!";}
                //for(i=0;i<OBJECT_NUMBER;i++){
                    //if(object[i]->GetAlive())continue;
                for(j=0;j<count;j++){
                    in >> count;
                    in >>x>>y>>x1>>y1>>type;
                     //   qDebug()<<x<<y<<x1<<y1<<type;
                   // CreateObject(QRect(x,y,x1,y1),type);
                    sql.AddObject(Object_Sql(QRect(x,y,x1,y1),type));
                    goto a;
                }
                //break;
               // }

            }
            else if(message==Message::Load_Partical){
                //for(i=0;i<PARTICAL_NUMBER;i++){
                  //  if(partical[i].GetAlive())continue;
                in>>x>>y>>x1>>y1>>ptype;
              //  qDebug()<<"Partical"<<x<<y<<x1<<y1<<ptype;
                CreatePartical(QRect(x,y,x1,y1),ptype);
                //break;
                //}

            }

}


    }
}


void Client::on_pushButton_clicked()
{
    this->Recive();
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
/*void Client::CreateObject(QRect Rect,int type){
    int i;
    for(i=0;i<OBJECT_NUMBER;i++){//创建方块
        if(object[i]->GetAlive())continue;
        switch (type) {
        case 1:object[i]->~Object();object[i]=new Wall(Rect,1,1);break;
        case 2:object[i]->~Object();object[i]=new BedRock(Rect,1);break;
        case 3:object[i]->~Object();object[i]=new River(Rect,1);break;
        case 4:object[i]->~Object();object[i]=new Portal(Rect);break;
        case 5:object[i]->~Object();object[i]=new Camp(Rect,1,1);break;
        case 6:object[i]->~Object();object[i]=new FirstAid(Rect,2);break;
        case 7:object[i]->~Object();object[i]=new Weapon(Rect,2);break;
        case 8:object[i]->~Object();object[i]=new Ruins(Rect,1);break;
        case 9:object[i]->~Object();object[i]=new Grass(Rect,1);break;
        case 10:object[i]->~Object();object[i]=new Nail(Rect);break;
        case 11:object[i]->~Object();object[i]=new Ice(Rect);break;
        }
        break;
    }//创建方块
}*/
