#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Player.h"
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    int i;
    QTimer *tick = new QTimer(this);
    connect(tick, SIGNAL(timeout()), this, SLOT(update()));
    connect(tick, SIGNAL(timeout()), this, SLOT(Tick()));
    connect(&Flash, SIGNAL(timeout()), this, SLOT(flash()));
    Flash.start(800);
    tick->start(10);

    p->setMedia(QUrl("qrc:/sounds/sounds/MainMusic.mp3"));
    p->setVolume(100);
    for (i = 0; i < Edit_Min; i++)
        s[i].setMedia(QUrl("qrc:/sounds/sounds/Tap.mp3"));

    p->play();
    ui->setupUi(this);
    ui->centralwidget->setMouseTracking(true);
    Main_Mod = 0;
    Main_Select = 0;
    setWindowIcon(QIcon(":/Images/Images/icon.png"));
    this->setStyleSheet("#MainWindow{border-image:url(:/Images/Images/BackGround.jpg);}");

    Partical1[1].load(":/Images/Images/1_1.png");
    Partical1[2].load(":/Images/Images/1_2.png");
    Partical1[3].load(":/Images/Images/1_3.png");
    Partical1[4].load(":/Images/Images/1_4.png");
    Partical2[1].load(":/Images/Images/2_1.png");
    Partical2[2].load(":/Images/Images/2_2.png");
    Partical2[3].load(":/Images/Images/2_3.png");
    Partical2[4].load(":/Images/Images/2_4.png");
    Partical3[1].load(":/Images/Images/3_1.png");
    Partical3[2].load(":/Images/Images/3_2.png");
    Partical3[3].load(":/Images/Images/3_3.png");
    Partical3[4].load(":/Images/Images/3_4.png");

    QCursor t(QPixmap::fromImage(QImage(":/Images/Images/cursor.png")));
    this->setCursor(t);

    for (i = 0; i < 50; i++)
    {
        trans[i] = new QGraphicsOpacityEffect();
        trans[i]->setOpacity(0);
    }

    ui->Title->setGraphicsEffect(trans[0]);
    ui->pushButton->setGraphicsEffect(trans[1]);
    ui->pushButton_2->setGraphicsEffect(trans[2]);
    ui->pushButton_3->setGraphicsEffect(trans[3]);
    ui->pushButton_4->setGraphicsEffect(trans[4]);
    ui->pushButton_5->setGraphicsEffect(trans[5]);
    ui->pushButton_7->setGraphicsEffect(trans[6]);
    ui->pushButton_8->setGraphicsEffect(trans[7]);

    this->Me_Appear();

    connect(ui->pushButton, SIGNAL(Mouse_Click()), this, SLOT(Tap_Fun()));
    connect(ui->pushButton_2, SIGNAL(Mouse_Click()), this, SLOT(Tap_Fun()));
    connect(ui->pushButton_3, SIGNAL(Mouse_Click()), this, SLOT(Tap_Fun()));
    connect(ui->pushButton_4, SIGNAL(Mouse_Click()), this, SLOT(Tap_Fun()));
    connect(ui->pushButton_5, SIGNAL(Mouse_Click()), this, SLOT(Tap_Fun()));
    connect(ui->Back, SIGNAL(Mouse_Click()), this, SLOT(Tap_Fun()));

    showFullScreen();

    QString line;
    QString aFile = QDir::currentPath() + "/settings.txt";
    QFile file(aFile);

    if (!file.open(QIODevice::ReadOnly))
    { //默认构造settings.txt
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << "gamemode:1\n";
        out << "backsound:50\n";
        out << "sound:100\n";
        out << "internetmode:0\n";
        out << "W:87:W\n";
        out << "S:83:S\n";
        out << "A:65:A\n";
        out << "D:68:D\n";
        out << "Shift:16777248:Shift\n";
        out << "Space:32:Space\n";
        out << "L:76:L\n";
        file.close();
        return;
    } //默认构造settings.txt

    QTextStream read(&file);

    while (!read.atEnd())
    {
        line = read.readLine();
        QStringList list = line.split(":");
        if (list[0] == "gamemode")
        {
            if (list[1].toInt() < 0 || list[1].toInt() > 3)
            {
                QMessageBox::information(nullptr, tr("Warning"), tr("gamemode setting failed...\nPlease go to the Setting Page"), tr("OK"));
                settings.gamemode = 1;
                continue;
            }
            settings.gamemode = list[1].toInt();
        }
        if (list[0] == "backsound")
        {
            if (list[1].toInt() < 0 || list[1].toInt() > 100)
            {
                QMessageBox::information(nullptr, tr("Warning"), tr("backsound setting failed...\nPlease go to the Setting Page"), tr("OK"));
                settings.backsound = 50;
                continue;
            }
            settings.backsound = list[1].toInt();
        }
        if (list[0] == "sound")
        {
            if (list[1].toInt() < 0 || list[1].toInt() > 100)
            {
                QMessageBox::information(nullptr, tr("Warning"), tr("sound setting failed...\nPlease go to the Setting Page"), tr("OK"));
                settings.sound = 100;
                continue;
            }
            settings.sound = list[1].toInt();
        }
        if (list[0] == "internetmode")
        {
            if (list[1].toInt() < 0 || list[1].toInt() > 2)
            {
                QMessageBox::information(nullptr, tr("Warning"), tr("internetmode setting failed...\nPlease go to the Setting Page"), tr("OK"));
                settings.internetmode = 0;
                continue;
            }
            settings.internetmode = list[1].toInt();
        }
        if (list[0] == "W")
        {
            settings.W = list[1].toInt();
        }
        if (list[0] == "S")
        {
            settings.S = list[1].toInt();
        }
        if (list[0] == "A")
        {
            settings.A = list[1].toInt();
        }
        if (list[0] == "D")
        {
            settings.D = list[1].toInt();
        }
        if (list[0] == "Shift")
        {
            settings.Shift = list[1].toInt();
        }
        if (list[0] == "Space")
        {
            settings.Space = list[1].toInt();
        }
        if (list[0] == "L")
        {
            settings.L = list[1].toInt();
        }
    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete p;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int i;
    QPainter painter(this);
    painter.drawImage(QRect(120, 0, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(10, 160, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(70, 220, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(180, 240, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(50, 330, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(0, 300, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(0, 0, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(100, 0, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(0, 100, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(170, 100, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(250, 0, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(300, 100, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(10, 500, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(300, 100, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(189, 408, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(442, 9, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(442, 600, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(630, 550, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(830, 350, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(7, 694, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(87, 694, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(3, 765, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(66, 745, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(2, 840, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(6, 914, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(78, 815, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(72, 1000, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(233, 913, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(368, 920, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(541, 934, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(280, 795, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(202, 627, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(527, 165, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(626, 2, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(742, 9, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(870, 6, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(989, 6, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(1102, 2, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1201, 6, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(1313, 6, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(1395, 3, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1512, 3, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1638, 4, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1774, 4, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(703, 44, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(836, 43, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(964, 46, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(1067, 46, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1222, 43, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1352, 44, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1503, 46, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1679, 44, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(1833, 43, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(632, 117, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(840, 123, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(988, 122, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(721, 894, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(837, 837, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(827, 915, 200, 200), Partical3[Seed()]);
    painter.drawImage(QRect(950, 821, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(962, 900, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1082, 788, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1077, 909, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1188, 767, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1193, 885, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1255, 777, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1315, 872, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1365, 668, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1385, 767, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1394, 891, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1480, 628, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1485, 752, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1490, 870, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1615, 594, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1584, 745, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1590, 871, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1722, 591, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1706, 709, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1696, 831, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1850, 582, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1782, 796, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1812, 686, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1760, 884, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1397, 612, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1583, 536, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(1704, 483, 200, 200), Partical2[Seed()]);
    painter.drawImage(QRect(1833, 419, 200, 200), Partical1[Seed()]);
    painter.drawImage(QRect(211, 626, 200, 200), Partical1[Seed()]);
    for (i = 0; i < Edit_Max; i++)
    { //创建粒子
        if (partical[i].GetAlive() == false)
            continue;
        painter.drawImage(partical[i].GetRect(), partical[i].GetImage());
    }
}

void MainWindow::PlayTap()
{
    int i;
    for (i = 0; i < Edit_Min; i++)
    {
        if (s[i].state() == QMediaPlayer::PlayingState)
            continue;
        s[i].setVolume(50);
        s[i].play();
        break;
    }
}

void MainWindow::flash()
{
    x = QRandomGenerator::global()->bounded(1, 1000);
}

int MainWindow::Seed()
{ //x每秒随机
    static unsigned int a = 0;
    a++;
    if (a == 89)
        a = 1;
    return ((((a * x + a * a - 6) * a) % 4) + 1);
}
void MainWindow::Tick()
{
    int i;
    for (i = 0; i < Edit_Max; i++)
    {
        partical[i].FLash();
    }
    for (i = 0; i < 5; i++)
        CreatePartical(QRect(500 + QRandomGenerator::global()->bounded(-50, 50), 180 + QRandomGenerator::global()->bounded(-100, 100), 50, 50), Type::Mist);

    if (Main_Mod == 1)
        if (ui->Story->x() <= 300)
        {
            ui->Story->setGeometry(ui->Story->x() + 10, ui->Story->y(), ui->Story->width(), ui->Story->height());
            ui->Battle->setGeometry(ui->Battle->x() - 13, ui->Battle->y(), ui->Battle->width(), ui->Battle->height());
            ui->Back->setGeometry(ui->Back->x() - 10, ui->Back->y(), ui->Back->width(), ui->Back->height());
        }

    if (Main_Mod == 0)
    {
        if (ui->Story->x() >= -500)
        {
            ui->Story->setGeometry(ui->Story->x() - 10, ui->Story->y(), ui->Story->width(), ui->Story->height());
            ui->Battle->setGeometry(ui->Battle->x() + 13, ui->Battle->y(), ui->Battle->width(), ui->Battle->height());
            ui->Back->setGeometry(ui->Back->x() + 10, ui->Back->y(), ui->Back->width(), ui->Back->height());
            return;
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (Main_Mod == 1)
        return;
    Map = new EditMap;
    Map->show();
    this->~MainWindow();

    return;
}

void MainWindow::on_pushButton_3_clicked()
{
    if (Main_Mod == 1)
        return;
    Battle = new BattleWindow(nullptr, 0, settings);
    Battle->show();
    this->~MainWindow();
    return;
}

void MainWindow::on_pushButton_4_clicked()
{
    if (Main_Mod == 1)
        return;
    if (settings.internetmode == 2)
    {
        client = new Client;
        client->show();
        this->~MainWindow();

        return;
    }
    Battle = new BattleWindow(nullptr, 100, settings);
    Battle->show();
    this->~MainWindow();

    return;
}

void MainWindow::on_pushButton_5_clicked()
{
    if (Main_Mod == 1)
        return;
    this->Me_Vanish();
    QTimer::singleShot(1000, this, SLOT(Setting_Appear()));
}

void MainWindow::on_Story_clicked()
{
    if (settings.internetmode == 2)
    {
        client = new Client;
        client->show();
        this->~MainWindow();

        return;
    }
    Battle = new BattleWindow(nullptr, 1, settings);
    Battle->show();
    this->~MainWindow();

    return;
}

void MainWindow::on_Battle_clicked()
{
    if (settings.internetmode == 2)
    {
        client = new Client;
        client->show();
        this->~MainWindow();

        return;
    }
    Battle = new BattleWindow(nullptr, 2, settings);
    Battle->show();
    this->~MainWindow();

    return;
}
void MainWindow::CreatePartical(QRect Rect, Type type)
{
    int i;
    for (i = 0; i < Edit_Max; i++)
    { //创建爆炸粒子
        if (partical[i].GetAlive() == true)
            continue;
        partical[i].~Partical();
        new (&partical[i]) Partical(Rect, type);
        break;
    } //创建爆炸粒子
}
void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    switch (QRandomGenerator::global()->bounded(1, 5))
    {
    case 1:
        CreatePartical(QRect(ev->x() - 10, ev->y() - 10, 20, 20), Type::Player_B3_UP);
        break;
    case 2:
        CreatePartical(QRect(ev->x() - 10, ev->y() - 10, 20, 20), Type::Player_B3_DOWN);
        break;
    case 3:
        CreatePartical(QRect(ev->x() - 10, ev->y() - 10, 20, 20), Type::Player_B3_LEFT);
        break;
    case 4:
        CreatePartical(QRect(ev->x() - 10, ev->y() - 10, 20, 20), Type::Player_B3_RIGHT);
        break;
    case 5:
        CreatePartical(QRect(ev->x() - 10, ev->y() - 10, 20, 20), Type::Object_Hit);
        break;
    }
}
void MainWindow::on_pushButton_8_clicked()
{
    this->~MainWindow();

    return;
}

void MainWindow::Me_Vanish()
{
    int i;
    for (i = 0; i < 8; i++)
    {
        audio[i] = new QPropertyAnimation(trans[i], "opacity", this);
        audio[i]->setDuration(1000);
        audio[i]->setStartValue(1.0);
        audio[i]->setEndValue(0);
        audio[i]->start();
    }
    ui->Battle->raise();
    ui->Back->raise();
    ui->Story->raise();
}

void MainWindow::Me_Appear()
{
    int i;
    for (i = 0; i < 8; i++)
    {
        audio[i] = new QPropertyAnimation(trans[i], "opacity", this);
        audio[i]->setDuration(1000);
        audio[i]->setStartValue(0);
        audio[i]->setEndValue(1.00);
        audio[i]->start();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (Main_Mod == 1)
        return;
    Main_Mod = 1;
    this->Me_Vanish();
}
void MainWindow::Setting_Appear()
{
    setting = new Setting();
    setting->show();
    this->~MainWindow();
}

void MainWindow::on_pushButton_7_clicked()
{
    email = new Email;
    email->show();
}
