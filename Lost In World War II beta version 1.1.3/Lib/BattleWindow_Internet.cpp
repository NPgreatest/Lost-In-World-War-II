#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"

void BattleWindow::Write_Sql(){
  //  qDebug()<<"begin writeDatagram:......";
    int i,k;
    sql.ObjectClear();
    sql.EnemyClear();
    sql.BulletClear();
    sql.PlayerClear();
    for(i=0;i<OBJECT_NUMBER;i++){
        if(!object[i]->GetAlive()) continue;
        sql.AddObject(Object_Sql(object[i]->GetRect(),object[i]->GetType()));
    }

    for(i=0;i<ENEMY_NUMBER;i++){
        if(!enemy[i].GetAlive()) continue;
        sql.AddEnemy(Enemy_Sql(enemy[i].GetRect(),enemy[i].GetHead(),enemy[i].GetSkin()));
        for(k=0;k<ENEMY_BULLET_NEMBER;k++){
            if(!enemy[i].GetB1(k).GetAlive())continue;
            sql.AddBullet(Bullet_Sql(enemy[i].GetB1(k).GetRect(),enemy[i].GetB1(k).GetType()));
        }
    }

    for(i=0;i<PLAYER_NUMBER_MAX;i++){
        if((P1+i)==nullptr||!P1[i].GetActivate()) continue;
        sql.AddPlayer(Player_Sql(P1[i].GetRect(),P1[i].GetHead(),i,P1[i].GetSlow()));
        for(k=0;k<PLAYER_B1_NUMBER;k++){
            if(!P1[i].GetB1(k).GetAlive()) continue;
            sql.AddBullet(Bullet_Sql(P1[i].GetB1(k).GetRect(),P1[i].GetB1(k).GetType()));
        }
        for(k=0;k<PLAYER_B2_NUMBER;k++){
            if(!P1[i].GetB2(k).GetAlive()) continue;
            sql.AddBullet(Bullet_Sql(P1[i].GetB2(k).GetRect(),P1[i].GetB2(k).GetType()));
        }
    }

    QByteArray data;
    QDataStream output(&data, QIODevice::WriteOnly);



    for(i=0;i<sql.GetObject_Num();i++){
        output<<Message::Load_Object<<sql.GetObject_Num()-i;
        output<<sql.GetObjectW(i).MeRect.x();
        output<<sql.GetObjectW(i).MeRect.y();
        output<<sql.GetObjectW(i).MeRect.width();
        output<<sql.GetObjectW(i).MeRect.height();
        output<<sql.GetObjectW(i).type;
    }



    for(i=0;i<sql.GetPartical_Num();i++){
        output<<Message::Load_Partical<<sql.GetPartical_Num()-i;
        output<<sql.GetPartical(i).MeRect.x();
        output<<sql.GetPartical(i).MeRect.y();
        output<<sql.GetPartical(i).MeRect.width();
        output<<sql.GetPartical(i).MeRect.height();
        output<<sql.GetPartical(i).type;

    }

    sql.PartivalClear();


    for(i=0;i<sql.GetEnemy_Num();i++){
        output<<Message::Load_Enemy<<sql.GetEnemy_Num()-i;
        output<<sql.GetEnemy(i).MeRect.x();
        output<<sql.GetEnemy(i).MeRect.y();
        output<<sql.GetEnemy(i).MeRect.width();
        output<<sql.GetEnemy(i).MeRect.height();
        output<<sql.GetEnemy(i).head;
        output<<sql.GetEnemy(i).type;
     }



    for(i=0;i<sql.GetBullet_Num();i++){
        output<<Message::Load_Bullet<<sql.GetBullet_Num()-i;
        output<<sql.GetBullet(i).MeRect.x();
        output<<sql.GetBullet(i).MeRect.y();
        output<<sql.GetBullet(i).MeRect.width();
        output<<sql.GetBullet(i).MeRect.height();
        output<<sql.GetBullet(i).type;
    }


    for(i=0;i<sql.GetPlayer_Num();i++){
        output<<Message::Load_Player<<sql.GetPlayer_Num()-i;
        output<<sql.GetPlayer(i).MeRect.x();
        output<<sql.GetPlayer(i).MeRect.y();
        output<<sql.GetPlayer(i).MeRect.width();
        output<<sql.GetPlayer(i).MeRect.height();
        output<<sql.GetPlayer(i).head;
        output<<sql.GetPlayer(i).slow;
        output<<sql.GetPlayer(i).number;
    }

    udp_socket->writeDatagram(data, data.length(),QHostAddress::Broadcast, this->port);
    data.clear();

   // qDebug()<<"writeDatagram Done!";

}






QString BattleWindow::get_ip()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();//返回了IP地址
    }
    return 0;
}

void BattleWindow::Recive(){
    qint32 m1,m2,m3;
    QString ip;
    int i;
    Message message;
    HEAD head;
    while (udp_socket->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(data.data(), data.size());
        QDataStream in(&data, QIODevice::ReadOnly);
        in >>message;
        switch (message) {
        case Message::Player_Join:
        {
            in>>ip;
            if(!AllIP.contains(ip)){
                for(i=0;i<PLAYER_NUMBER_MAX;i++){
                    if(P1[i].GetActivate())continue;
                    new(&P1[i])Player(P1[0].GetRect().adjusted(-50,0,-50,0),99999,100,3);
                    QByteArray data;
                    data.resize(udp_socket->pendingDatagramSize());
                    udp_socket->readDatagram(data.data(), data.size());
                    QDataStream in(&data, QIODevice::WriteOnly);
                    in<<Message::Player_Join_Is_Success<<i;
                    udp_socket->writeDatagram(data, data.length(),QHostAddress::Broadcast, this->port);
                    AllIP.append(ip);
                    return;
                }
            }
                QByteArray data;
                data.resize(udp_socket->pendingDatagramSize());
                udp_socket->readDatagram(data.data(), data.size());
                QDataStream in(&data, QIODevice::WriteOnly);
                in<<Message::Player_Join_Is_Success<<-1;
                udp_socket->writeDatagram(data, data.length(),QHostAddress::Broadcast, this->port);
                break;
        }
        case Message::KEYBOARD_PUSHD:
            in>>m1;
            for(i=0;i<PLAYER_NUMBER_MAX;i++){
                if(!P1[i].GetActivate()||m1!=i)continue;
                in>>head;
                Controller(m1,KEYBOARD_CONTROLL::PNO,head);
                break;
            }
            break;
        case Message::KEYBOARD_OTHER:
            in>>m1;
            for(i=0;i<PLAYER_NUMBER_MAX;i++){
                if(!P1[i].GetActivate()||m1!=i)continue;
                Controller(m1,KEYBOARD_CONTROLL::PFIRE,P1[i].GetHead());
                break;
            }
            break;
        case Message::KEYBOARD_RELEASED:
            in>>m1;
            for(i=0;i<PLAYER_NUMBER_MAX;i++){
                if(!P1[i].GetActivate()||m1!=i)continue;
                Controller(m1,KEYBOARD_CONTROLL::PNO,NO);
                break;
            }
            break;
        default:break;
        }


    }
}
