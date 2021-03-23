#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include "mainwindow.h"

void BattleWindow::Write_Sql()
{
    int i;

    for (i = 0; i < OBJECT_NUMBER; i++)
    {
        if (!object[i]->GetAlive())
            continue;
        Object_S.push(Object_Sql(object[i]->GetRect(), object[i]->GetType(), object[i]->GetStatus()));
    }

    for (i = 0; i < ENEMY_NUMBER; i++)
    {
        if (!enemy[i].GetAlive())
            continue;
        Enemy_S.push(Enemy_Sql(enemy[i].GetRect(), enemy[i].GetHead(), enemy[i].GetSkin()));
    }

    for (i = 0; i < PLAYER_NUMBER_MAX; i++)
    {
        if ((P1 + i) == nullptr || !P1[i].GetActivate())
            continue;
        Player_S.push(Player_Sql(P1[i].GetRect(), P1[i].GetHead(), i, P1[i].GetSlow()));
    }

    QByteArray data;
    QDataStream output(&data, QIODevice::WriteOnly);

    while (!Object_S.isEmpty())
    {
        output << Message::Load_Object << 6;
        t1 = Object_S.pop();
        output << t1.MeRect.x();
        output << t1.MeRect.y();
        output << t1.MeRect.width();
        output << t1.MeRect.height();
        output << t1.type;
        output << t1.Status;
    }

    while (!Partical_S.isEmpty())
    {
        t2 = Partical_S.pop();
        output << Message::Load_Partical << 6;
        output << t2.MeRect.x();
        output << t2.MeRect.y();
        output << t2.MeRect.width();
        output << t2.MeRect.height();
        output << t2.type;
    }

    while (!Enemy_S.isEmpty())
    {
        t3 = Enemy_S.pop();
        output << Message::Load_Enemy << 6;
        output << t3.MeRect.x();
        output << t3.MeRect.y();
        output << t3.MeRect.width();
        output << t3.MeRect.height();
        output << t3.head;
        output << t3.type;
    }

    for (i = 0; i < PLAYER_B1_NUMBER; i++)
    { //直接传递数组内容
        if (!bullet1[i].GetAlive())
            continue;
        output << Message::Load_Bullet << i;
        output << bullet1[i].GetRect().x();
        output << bullet1[i].GetRect().y();
        output << bullet1[i].GetRect().width();
        output << bullet1[i].GetRect().height();
        output << bullet1[i].GetType();
    }

    for (i = 0; i < PLAYER_B2_NUMBER; i++)
    {
        if (!bullet2[i].GetAlive())
            continue;
        output << Message::Load_Bullet2 << i;
        output << bullet2[i].GetRect().x();
        output << bullet2[i].GetRect().y();
        output << bullet2[i].GetRect().width();
        output << bullet2[i].GetRect().height();
        output << bullet2[i].GetType();
    }

    while (!Player_S.isEmpty())
    {
        t4 = Player_S.pop();
        output << Message::Load_Player << 6;
        output << t4.MeRect.x();
        output << t4.MeRect.y();
        output << t4.MeRect.width();
        output << t4.MeRect.height();
        output << t4.head;
        output << t4.slow;
        output << t4.number;
    }

    for (i = 1; i < PLAYER_NUMBER_MAX; i++)
    {
        if (!P1[i].GetActivate())
            continue;
        output << Message::Load_Bar << i;
        output << P1[i].GetHP() << P1[i].GetMP() << P1[i].GetProcess();
    }

    udp_socket->writeDatagram(data, data.length(), QHostAddress::Broadcast, this->port);

    data.clear();
}

QString BattleWindow::get_ip()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString(); //返回了IP地址
    }
    return 0;
}

void BattleWindow::Recive()
{
    qint32 m1, m2, m3;
    QString ip;
    int i;
    Message message;
    HEAD head;
    KEYBOARD_CONTROLL key;
    while (udp_socket->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(data.data(), data.size());
        QDataStream in(&data, QIODevice::ReadOnly);
        in >> message;
        switch (message)
        {
        case Message::Player_Join:
        {
            in >> ip;
            if (!AllIP.contains(ip))
            {
                i = CreatePlayer(P1[0].GetRect().adjusted(-50, 0, -50, 0), 5, 100);
                QByteArray data;
                data.resize(udp_socket->pendingDatagramSize());
                udp_socket->readDatagram(data.data(), data.size());
                QDataStream in(&data, QIODevice::WriteOnly);
                in << Message::Player_Join_Is_Success << i;
                udp_socket->writeDatagram(data, data.length(), QHostAddress::Broadcast, this->port);
                AllIP.append(ip);
            }
        }
        case Message::KEYBOARD_PUSHD:
            in >> m1;
            for (i = 1; i < PLAYER_NUMBER_MAX; i++)
            {
                if (!P1[i].GetActivate() || m1 != i)
                    continue;
                in >> head;
                Controller(m1, KEYBOARD_CONTROLL::PNO, head, 0);
                break;
            }
            break;
        case Message::KEYBOARD_OTHER:
            in >> m1;
            for (i = 1; i < PLAYER_NUMBER_MAX; i++)
            {
                if (!P1[i].GetActivate() || m1 != i)
                    continue;
                in >> key;
                switch (key)
                {
                case KEYBOARD_CONTROLL::PFIRE:
                    if (P1[i].GetSkill().GetSkill() == SkillName::SubWeapon)
                    {
                        in >> m2 >> m3;
                        Controller(m1, KEYBOARD_CONTROLL::PFIRE, Key[i],
                                   GetAngle(m2 - P1[i].GetRect().center().x(),
                                            m3 - P1[i].GetRect().center().y()));
                        break;
                    }
                    Controller(m1, KEYBOARD_CONTROLL::PFIRE, Key[i]);
                    break;
                case KEYBOARD_CONTROLL::PCHANGE:
                    Controller(m1, KEYBOARD_CONTROLL::PCHANGE, P1[i].GetHead());
                    break;
                default:
                    break;
                }
                break;
            }
            break;
        case Message::KEYBOARD_RELEASED:
            in >> m1;
            for (i = 0; i < PLAYER_NUMBER_MAX; i++)
            {
                if (!P1[i].GetActivate() || m1 != i)
                    continue;
                Controller(m1, KEYBOARD_CONTROLL::PNO, NO);
                break;
            }
            break;
        default:
            break;
        }
    }
}
