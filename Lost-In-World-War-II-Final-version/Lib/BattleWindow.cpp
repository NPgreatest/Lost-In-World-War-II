#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

BattleWindow::BattleWindow(QWidget *parent, int Mission, Settings settings)
    : QMainWindow(parent),
      Mission(Mission),
      ui(new Ui::BattleWindow),
      settings(settings)
{

    ui->setupUi(this);

    //setPalette(QPalette(Qt::yellow));

    setAutoFillBackground(true);

    this->setStyleSheet("#BattleWindow{border-image:url(:/Images/Images/BattleGround.png);}");

    setWindowIcon(QIcon(":/Images/Images/icon.png"));
    exit.load(":/Images/Images/cancel.png");
    temp.load(":/Images/Images/BattleGround.png");

    //实例化物体
    int i;
    for (i = 0; i < OBJECT_NUMBER; i++)
    {
        object[i] = new Temp();
    }
    //  实例化槽类

    if (settings.gamemode == 1 || settings.gamemode == 0)
    {
        bar[0] = new Bar(350, 1000, 40, 2);
    }
    else if (settings.gamemode == 2)
    {
        bar[0] = new Bar(350, 1000, 30, 2);
    }
    else if (settings.gamemode == 3)
    {
        bar[0] = new Bar(350, 1000, 20, 2);
    }

    bar[1] = new Bar(900, 1000, 100, 1);
    bar[2] = new Bar(1420, 1000, 100, 3);
    //  实例化槽类

    allmusic.AddHitMusic();
    allmusic.AddHit2Music();
    allmusic.AddRedZoneMusic();

    openGL->setGeometry(0, 0, 1920, 1080);
    openGL->lower();

    MeIp = get_ip();

    connect(&Timer, &QTimer::timeout, openGL, &GLWidGet::animate); //OpenGL Connect

    connect(&Timer, SIGNAL(timeout()), this, SLOT(Bullet_Fly()));
    connect(&One_Sec, SIGNAL(timeout()), this, SLOT(Flash()));
    connect(&move, SIGNAL(timeout()), this, SLOT(Move()));
    connect(&FinalWeapon, SIGNAL(timeout()), this, SLOT(P1_Weapon()));
    connect(&EnemyMove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
    connect(&EnemyMove, SIGNAL(timeout()), this, SLOT(Boss_Move()));
    connect(&EnemyAll, SIGNAL(timeout()), this, SLOT(Enemy_All()));
    connect(&ParticalTick, SIGNAL(timeout()), this, SLOT(Flash2()));

    if (settings.internetmode == 1)
        connect(&UploadData, SIGNAL(timeout()), this, SLOT(Write_Sql()));

    Timer.start(10);

    showFullScreen();

    if (Mission == 0)
    { //介绍模式
        this->Load_Introduce();
        return;
    } //介绍模式

    ParticalTick.start(50);

    One_Sec.start(1000);
    EnemyMove.start(50);
    EnemyAll.start(100);
    move.start(10);
    UploadData.start(20);

    udp_socket = new QUdpSocket(this);
    port = 10080;
    last_recv = 0;

    udp_socket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint); //设置udp 端口
    connect(udp_socket, &QUdpSocket::readyRead, this, &BattleWindow::Recive);

    switch (Mission)
    {
    case 1:
        MissionTeach();
        return;
    case 2:
        MissionRougueLike();
        return;
    default:
        QString Address = QFileDialog::getOpenFileName(this, tr("Choose Map"), nullptr, tr("Image Files (*.txt)"));
        QFile file(Address);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(nullptr, tr("Warning"), tr("Failed to load map"), tr("OK"));
            return;
        } //加载地图失败
        file.close();
        Load_Map(Address);
    }
}

void BattleWindow::Load_Map(QString Address)
{
    QFile file(Address);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(nullptr, tr("Warning"), tr("Failed to load map"), tr("OK"));
        backto = new MainWindow;
        backto->show();
        this->~BattleWindow();
        return;
    } //加载地图失败

    int read = 0, tlv;
    QRect Player_Rect;
    int thp, tmp;

    QRect Object_Rect;
    int type;
    int skin;
    int hp;

    int e_hp;
    int e_speed;
    int e_bullet_speed;
    QRect Enemy_Rect;
    int e_skin;

    Player_Rect.setRect(0, 0, 0, 0);

    //加载地图
    QTextStream input(&file);
    while (!input.atEnd())
    {
        QString line = input.readLine();
        QStringList list = line.split(" ");
        if (line == "CObject:")
        {
            read = 1;
            continue;
        }
        else if (line == "CPlayer:")
        {
            read = 2;
            continue;
        }
        else if (line == "CEnemy:")
        {
            read = 3;
            continue;
        }
        switch (read)
        {
        case 1:
            type = list[0].toInt();
            Object_Rect.setRect(list[1].toInt(), list[2].toInt(), list[3].toInt(), list[4].toInt());
            hp = list[5].toInt();
            skin = list[6].toInt();
            CreateObject(Object_Rect, type, skin, hp);
            break;
        case 2:
            Player_Rect.setRect(list[0].toInt(), list[1].toInt(), 40, 40);
            thp = list[2].toInt();
            tmp = list[3].toInt();
            tlv = list[4].toInt();
            CreatePlayer(Player_Rect, thp, tlv);
            break;
        case 3:
            Enemy_Rect.setRect(list[0].toInt(), list[1].toInt(), list[2].toInt(), list[3].toInt());
            e_hp = list[4].toInt();
            e_speed = list[5].toInt();
            e_bullet_speed = list[6].toInt();
            e_skin = list[7].toInt();
            CreatePartical(Enemy_Rect, Type::Object_Hit);
            CreateEnemy(Enemy_Rect, e_hp, e_speed, e_bullet_speed, e_skin);
            break;
        default:
            QMessageBox::information(nullptr, tr("提示"), tr("加载地图失败"), tr("好"));
            this->~BattleWindow();
            backto = new MainWindow;
            backto->setMouseTracking(true);
            backto->show();
            break;
        }
    }
    file.close();
}

void BattleWindow::paint(QPainter *painter, QPaintEvent *event)
{
    int i, k;

    switch (LevelB)
    {
    case 2:
    case 3:
    case 4:
        temp.load(":/Images/Images/BattleGround.png");
        break;
    case 5:
    case 6:
        temp.load(":/Images/Images/BattleGround_2.png");
        break;
    case 7:
    case 8:
        temp.load(":/Images/Images/BattleGround_3.png");
        break;
    case 9:
        temp.load(":/Images/Images/BattleGround_4.png");
        break;
    }

    painter->drawImage(QRect(0, 0, 1920, 1080), temp);

    //画boss
    if (boss1->GetAlive())
        painter->drawImage(boss1->GetRect(), boss1->GetImage());

    //画boss

    for (i = 0; i < OBJECT_NUMBER; i++)
    { //创建物体
        if (!object[i]->GetAlive())
            continue;
        painter->drawImage(object[i]->GetRect(), object[i]->GetImage());
    }

    for (i = 0; i < ENEMY_NUMBER; i++)
    { //画敌人
        if (enemy[i].GetAlive() == false)
            continue;
        painter->drawImage(enemy[i].GetRect(), enemy[i].GetImage());
    } //画敌人

    for (i = 0; i < PLAYER_NUMBER_MAX; i++)
    {
        if (!P1[i].GetActivate())
            continue;
        if (!move.isActive())
            painter->drawImage(P1[i].GetRect(), P1[i].GetImage()); //画玩家
        else
        {
            if (P1[i].GetHead() == UP || P1[i].GetHead() == DOWN)
                painter->drawImage(QRect(P1[i].GetRect().x() + QRandomGenerator::global()->bounded(-2, 2),
                                         P1[i].GetRect().y(), 40, 40),
                                   P1[i].GetImage()); //画玩家
            else
                painter->drawImage(QRect(P1[i].GetRect().x(),
                                         P1[i].GetRect().y() + QRandomGenerator::global()->bounded(-2, 2), 40, 40),
                                   P1[i].GetImage()); //画玩家
        }
    }

    painter->drawImage(QRect(1840, 1000, 80, 80), exit);

    for (k = 0; k < PLAYER_NUMBER_MAX; k++)
    {
        if (!P1[k].GetActivate())
            continue;

        for (i = 0; i < PLAYER_B1_NUMBER; i++)
        {
            if (!bullet1[i].GetAlive())
                continue;
            painter->drawImage(bullet1[i].GetRect().adjusted(-10, -10, 20, 20), bullet1[i].GetImage());
        }
        for (i = 0; i < PLAYER_B2_NUMBER; i++)
        {
            if (bullet2[i].GetAlive())
            {
                painter->drawImage(bullet2[i].GetRect().adjusted(-10, -10, 20, 20), bullet2[i].GetImage());
            }
        }
    }

    bar[0]->SetValue(P1[0].GetHP());
    bar[1]->SetValue(P1[0].GetMP());
    bar[2]->SetValue(P1[0].GetProcess());
    for (i = 0; i < 3; i++)
    {
        painter->drawImage(bar[i]->GetRect1(), bar[i]->GetImage1());
        painter->drawImage(bar[i]->GetRect2(), bar[i]->GetImage2());
    }

    for (i = 0; i < PARTICAL_NUMBER; i++)
    { //创建粒子
        if (!partical[i].GetAlive())
            continue;
        painter->drawImage(partical[i].GetRect(), partical[i].GetImage());
    }

    painter->drawImage(P1[0].GetSkill().GetRect(), P1[0].GetSkill().GetImage()); //画技能槽

    if (!Mission)
        drawIntroduce(*painter); //   draw  介绍模式
}

void BattleWindow::Move()
{ //玩家移动
    int i;
    for (i = 0; i < PLAYER_NUMBER_MAX; i++)
    {
        if (!P1[i].GetActivate())
            continue;
        if (Key[i] == UP || Key[i] == DOWN || Key[i] == LEFT || Key[i] == RIGHT)
            P1[i].Player_Move(P1[i].GetSpeed());
        Player_HitCheck(i);
    }
}

void BattleWindow::Controller(int number, KEYBOARD_CONTROLL key, HEAD head, double angle)
{
    int i, k;
    for (i = 0; i < PLAYER_NUMBER_MAX; i++)
    {
        if (!P1[i].GetActivate())
            continue;
        if (number == i)
            break;
        if (i == PLAYER_NUMBER_MAX)
            return;
    }

    Key[number] = head;

    switch (head)
    {
    case UP:
        P1[number].Player_ChangeHead(0);
        break;
    case DOWN:
        P1[number].Player_ChangeHead(1);
        break;
    case LEFT:
        P1[number].Player_ChangeHead(2);
        break;
    case RIGHT:
        P1[number].Player_ChangeHead(3);
        break;
    case NO:
        break;
    }
    switch (key)
    {
    case PCHANGE:
    {
        P1[number].GetSkill().SkillChange();
        if (P1[number].GetSkill().GetSkill() != SkillName::SubWeapon)
            return;
        QCursor t(QPixmap::fromImage(QImage(":/Images/Images/cursor.png")));
        t.setPos(P1[0].GetRect().center());
        this->setCursor(t);
    }
    break;
    case PFIRE:
        switch (P1[number].GetSkill().GetSkill())
        {
        case SkillName::MainWeapon:
            if (!P1[number].Player_B1Fire(settings.gamemode == 0 ? true : false))
            {
                //播放MPOUT
            }
            else
            {
                this->CreateBullet(P1[number].GetRect().adjusted(15, 15, -15, -15),
                                   P1[number].GetHead(),
                                   1, P1[number].Damage(SkillName::MainWeapon),
                                   Target::ALL, number, 10);
            }
            break;
        case SkillName::SubWeapon:
            if (!P1[number].Player_B2Fire(settings.gamemode == 0 ? true : false))
                return;
            for (k = -2; k < 3; k++)
                CreateBullet2(P1[i].GetRect().adjusted(15, 15, -15, -15),
                              angle + (k * 0.3), 3,
                              P1[i].Damage(SkillName::SubWeapon),
                              Target::ALL, number, 5, 15);
            break;
        case SkillName::Fire:
            if (P1[number].Player_B3Fire(settings.gamemode == 0 ? true : false))
            {
                allmusic.PlayFireMusic(settings.sound);
                switch (P1[number].GetHead())
                {
                case UP:
                    CreatePartical(P1[number].GetRect().adjusted(-50, -100, 60, -40), Type::Player_B3_UP);
                    break;
                case DOWN:
                    CreatePartical(P1[number].GetRect().adjusted(-50, 40, 60, 100), Type::Player_B3_DOWN);
                    break;
                case LEFT:
                    CreatePartical(P1[number].GetRect().adjusted(-100, -50, -40, 60), Type::Player_B3_LEFT);
                    break;
                case RIGHT:
                    CreatePartical(P1[number].GetRect().adjusted(40, -50, 110, 60), Type::Player_B3_RIGHT);
                    break;
                default:
                    break;
                }
            }
            break;
        }
        break;
    default:
        break;
    }
}

void BattleWindow::keyPressEvent(QKeyEvent *event)
{
    int i;
    for (i = 0; i < PLAYER_NUMBER_MAX; i++)
    {
        if (!P1[i].GetActivate())
            continue;
        if (!event->isAutoRepeat())
        {
            if (event->key() == settings.W)
                this->Controller(0, PNO, UP);
            if (event->key() == settings.S)
                this->Controller(0, PNO, DOWN);
            if (event->key() == settings.A)
                this->Controller(0, PNO, LEFT);
            if (event->key() == settings.D)
                this->Controller(0, PNO, RIGHT);
            if (event->key() == settings.Space)
            {
                int x, y;
                x = Mouse_Point.x() - P1[0].GetRect().center().x();
                y = Mouse_Point.y() - P1[0].GetRect().center().y();
                this->Controller(0, PFIRE, Key[0], GetAngle(x, y));
            }
            if (event->key() == settings.L)
            {
                if (P1[i].GetChoose() == 1)
                {
                    P1[i].SetChoose(0);
                    P1[i].Player_UnSlow();
                }
                else if (P1[i].GetChoose() == 0)
                {
                    P1[i].SetChoose(1);
                    P1[i].Player_Slow();
                }
            }
            if (event->key() == settings.Shift)
                this->Controller(0, PCHANGE, Key[0]);
            if (event->key() == 61)
                this->Command(QInputDialog::getText(this, "Command", "Please Input Command", QLineEdit::Normal, "/help", nullptr, Qt::WindowFlags(1), Qt::ImhNone));
        }
    }
}

void BattleWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())
    {
        if (event->key() == settings.W)
            if (UP == Key[0])
                Key[0] = NO;
        if (event->key() == settings.S)
            if (DOWN == Key[0])
                Key[0] = NO;
        if (event->key() == settings.A)
            if (LEFT == Key[0])
                Key[0] = NO;
        if (event->key() == settings.D)
            if (RIGHT == Key[0])
                Key[0] = NO;
    }
}

void BattleWindow::CreatePartical(QRect Rect, Type type)
{
    int i;
    for (i = 0; i < PARTICAL_NUMBER; i++)
    { //创建爆炸粒子
        if (partical[i].GetAlive())
            continue;
        partical[i].~Partical();
        new (&partical[i]) Partical(Rect, type);
        break;
    } //创建爆炸粒子
    Partical_S.push(Partical_Sql(Rect, type));
}

void BattleWindow::CreateEnemy(QRect Rect, int hp, int speed, int bulletspeed, int skin)
{
    if (!Rect.width() || !Rect.height())
        return;
    if (Rect.topRight().x() > X_Max || Rect.bottom() > Y_Max || Rect.x() < 0 || Rect.y() < 0)
        return;
    int i;
    for (i = 0; i < ENEMY_NUMBER; i++)
    {
        if (enemy[i].GetAlive())
            continue;
        enemy[i].~Enemy();
        new (&enemy[i]) Enemy(Rect, hp, speed, bulletspeed, skin);
        break;
    }
}

void BattleWindow::CreateObject(QRect Rect, int type, int skin, int hp)
{
    if (type == 0)
        return;
    int i;
    for (i = 0; i < OBJECT_NUMBER; i++)
    { //创建物体
        if (!object[i]->GetAlive())
        {
            delete object[i];
            break;
        }

    } //创建物体
    switch (type)
    {
    case 1:
        object[i] = new Wall(Rect, skin, hp);
        break;
    case 2:
        object[i] = new BedRock(Rect, skin);
        break;
    case 3:
        object[i] = new River(Rect, skin);
        break;
    case 4:
        object[i] = new Portal(Rect);
        break;
    case 5:
        object[i] = new Camp(Rect, 1, hp);
        break;
    case 6:
        object[i] = new FirstAid(Rect, 1);
        break;
    case 7:
        object[i] = new Weapon(Rect, 1);
        break;
    case 8:
        object[i] = new Camp(Rect, 2, hp);
        break;
    case 9:
        object[i] = new FirstAid(Rect, 2);
        break;
    case 10:
        object[i] = new Weapon(Rect, 2);
        break;
    case 11:
        object[i] = new Camp(Rect, 3, hp);
        break;
    case 12:
        object[i] = new FirstAid(Rect, 3);
        break;
    case 13:
        object[i] = new Weapon(Rect, 3);
        break;
    case 14:
        object[i] = new Ruins(Rect, QRandomGenerator::global()->bounded(1, 3));
        break;
    case 15:
        object[i] = new Grass(Rect, QRandomGenerator::global()->bounded(1, 3));
        break;
    case 16:
        object[i] = new Nail(Rect);
        break;
    case 17:
        object[i] = new Ice(Rect);
        break;
    default:
        break;
    }
}
void BattleWindow::CreateRedZone(QRect Rect, int R, int type)
{
    int i;
    for (i = 0; i < REDZONE_NUMBER; i++)
    {
        if (redzone[i].GetAlive())
            continue;
        redzone[i].~RedZone();
        new (&redzone[i]) RedZone(Rect, R, type);
        redzone[i].Flash_Begin();
        CreatePartical(redzone[i].GetRect(), Type::RedZone_Flash);
        allmusic.PlayRedZoneMusic(redzone[i].GetR() / 10);
        break;
    }
}
void BattleWindow::CreateBullet(QRect const MeRect, HEAD const h, int const type, int const Damage, Target target, int master, int Speed)
{
    int i;
    for (i = 0; i < PLAYER_B1_NUMBER; i++)
    {
        if (bullet1[i].GetAlive())
            continue;
        bullet1[i].Init(MeRect, h, type, Damage, target, master, Speed);
        break;
    }
}
void BattleWindow::CreateBullet2(QRect const MeRect, double const Drection, int const type, int const Damage, Target const target, int const master, int const speed, int const HP)
{
    int i;
    for (i = 0; i < PLAYER_B2_NUMBER; i++)
    {
        if (bullet2[i].GetAlive())
            continue;
        bullet2[i].Init(MeRect, Drection, type, Damage, target, master, speed, HP);
        break;
    }
}
int BattleWindow::CreatePlayer(QRect MeRect, int HP, int WeaponLv)
{
    int i;
    for (i = 0; i < PLAYER_NUMBER_MAX; i++)
    {
        if (P1[i].GetActivate())
            continue;
        P1[i].~Player();
        new (&P1[i]) Player(MeRect, HP, WeaponLv);
        return i;
    }
    return -1;
}

void BattleWindow::ClearMap(QRect Rect)
{ //清理地图
    int i;
    for (i = 0; i < ENEMY_NUMBER; i++)
    {
        enemy[i].Dead();
    }
    for (i = 0; i < OBJECT_NUMBER; i++)
        if (object[i]->GetAlive())
            object[i]->Dead();

    P1[0].SetPos(Rect);
}

BattleWindow::~BattleWindow()
{ //释放内存
    int i;
    delete[] redzone;
    delete[] partical;
    for (i = 0; i < OBJECT_NUMBER; i++)
    {
        delete object[i];
    }
    delete ui;
    delete[] enemy;
    delete[] bullet1;
    delete[] bullet2;
    delete bar[0];
    delete bar[1];
    delete bar[2];
    delete boss1;
    delete openGL;
    delete udp_socket;
    qDebug() << "release success";
}

void BattleWindow::RainFire()
{
    int r;
    QRect Rect(QRandomGenerator::global()->bounded(0, X_Max),
               QRandomGenerator::global()->bounded(0, X_Max),
               QRandomGenerator::global()->bounded(50, 500),
               QRandomGenerator::global()->bounded(50, 500));
    r = QRandomGenerator::global()->bounded(50, 200);
    CreateRedZone(Rect, r, 1);
}

void BattleWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (P1[0].GetSkill().GetSkill() == SkillName::SubWeapon)
        Mouse_Point = ev->pos();
}
