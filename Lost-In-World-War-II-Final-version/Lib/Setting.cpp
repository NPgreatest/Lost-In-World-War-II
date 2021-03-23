#include "Setting.h"
#include "ui_Setting.h"
#include "mainwindow.h"
Setting::Setting(QWidget *parent) : QMainWindow(parent),
                                    ui(new Ui::Setting)
{
    setWindowIcon(QIcon(":/Images/Images/icon.png"));
    int i;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //取消标题栏
    for (i = 0; i < 50; i++)
    {
        trans[i] = new QGraphicsOpacityEffect();
        trans[i]->setOpacity(0);
    }
    ui->Audio1->setGraphicsEffect(trans[0]);
    ui->Audio2->setGraphicsEffect(trans[1]);
    ui->Audio3->setGraphicsEffect(trans[2]);
    ui->MainSlide->setGraphicsEffect(trans[3]);
    ui->SoundSlide->setGraphicsEffect(trans[4]);
    ui->Hard->setGraphicsEffect(trans[5]);
    ui->difficult->setGraphicsEffect(trans[6]);
    ui->gamemode->setGraphicsEffect(trans[7]);
    ui->mode->setGraphicsEffect(trans[8]);
    ui->AChange->setGraphicsEffect(trans[9]);
    ui->DChange->setGraphicsEffect(trans[10]);
    ui->LChange->setGraphicsEffect(trans[11]);
    ui->SChange->setGraphicsEffect(trans[12]);
    ui->ShiftChange->setGraphicsEffect(trans[13]);
    ui->SpaceChange->setGraphicsEffect(trans[14]);
    ui->WChange->setGraphicsEffect(trans[15]);
    ui->label_3->setGraphicsEffect(trans[16]);
    ui->label_4->setGraphicsEffect(trans[17]);
    ui->label_5->setGraphicsEffect(trans[18]);
    ui->label_6->setGraphicsEffect(trans[19]);
    ui->label_7->setGraphicsEffect(trans[20]);
    ui->label_8->setGraphicsEffect(trans[21]);
    ui->label_9->setGraphicsEffect(trans[22]);
    ui->label_10->setGraphicsEffect(trans[23]);
    ui->label_11->setGraphicsEffect(trans[24]);
    ui->l1->setGraphicsEffect(trans[25]);
    ui->l2->setGraphicsEffect(trans[26]);
    ui->l3->setGraphicsEffect(trans[27]);
    ui->l4->setGraphicsEffect(trans[28]);
    ui->l5->setGraphicsEffect(trans[29]);
    ui->l6->setGraphicsEffect(trans[30]);
    ui->l7->setGraphicsEffect(trans[31]);
    ui->pushButton->setGraphicsEffect(trans[32]);
    ui->pushButton_2->setGraphicsEffect(trans[33]);
    ui->pushButton_3->setGraphicsEffect(trans[34]);
    ui->pushButton_4->setGraphicsEffect(trans[35]);
    show();
    this->setStyleSheet("#Setting{border-image:url(:/Images/Images/BackGround_Dark.png);}");
    showFullScreen();

    allmusic.AddRedZoneMusic();
    allmusic.AddHit2Music();
    allmusic.AddHitMusic();

    for (i = 0; i < 36; i++)
    {
        audio[i] = new QPropertyAnimation(trans[i], "opacity", this);
        audio[i]->setDuration(2000);
        audio[i]->setStartValue(0);
        audio[i]->setEndValue(1.0);
        audio[i]->start();
    }

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
                settings.gamemode = 1;
                continue;
            }
            settings.gamemode = list[1].toInt();
        }
        if (list[0] == "backsound")
        {
            if (list[1].toInt() < 0 || list[1].toInt() > 100)
            {
                settings.backsound = 50;
                continue;
            }
            settings.backsound = list[1].toInt();
        }
        if (list[0] == "sound")
        {
            if (list[1].toInt() < 0 || list[1].toInt() > 100)
            {
                settings.sound = 100;
                continue;
            }
            settings.sound = list[1].toInt();
        }
        if (list[0] == "internetmode")
        {
            if (list[1].toInt() < 0 || list[1].toInt() > 2)
            {
                settings.internetmode = 0;
                continue;
            }
            settings.internetmode = list[1].toInt();
        }
        if (list[0] == "W")
        {
            settings.W = list[1].toInt();
            key.append(list[2]);
        }
        if (list[0] == "S")
        {
            settings.S = list[1].toInt();
            key.append(list[2]);
        }
        if (list[0] == "A")
        {
            settings.A = list[1].toInt();
            key.append(list[2]);
        }
        if (list[0] == "D")
        {
            settings.D = list[1].toInt();
            key.append(list[2]);
        }
        if (list[0] == "Shift")
        {
            settings.Shift = list[1].toInt();
            key.append(list[2]);
        }
        if (list[0] == "Space")
        {
            settings.Space = list[1].toInt();
            key.append(list[2]);
        }
        if (list[0] == "L")
        {
            settings.L = list[1].toInt();
            key.append(list[2]);
        }
    }
    file.close();
    ui->MainSlide->setValue(settings.backsound);
    ui->SoundSlide->setValue(settings.sound);
    ui->difficult->setCurrentIndex(settings.gamemode);
    ui->mode->setCurrentIndex(settings.internetmode);

    if (key.count() != 7)
    {
        key.clear();
        key << "W"
            << "S"
            << "A"
            << "D"
            << "Shift"
            << "Space"
            << "L";
    }
    connect(&tick, SIGNAL(timeout()), this, SLOT(Label_Tick()));
    tick.start(250);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_pushButton_clicked()
{
    QString line;
    QString aFile = QDir::currentPath() + "/settings.txt";
    QFile file(aFile);

    //默认构造settings.txt
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "gamemode:" << settings.gamemode << "\n";
    out << "backsound:" << settings.backsound << "\n";
    out << "sound:" << settings.sound << "\n";
    out << "internetmode:" << settings.internetmode << "\n";
    out << "W:" << settings.W << ":" << key.at(0) << "\n";
    out << "S:" << settings.S << ":" << key.at(1) << "\n";
    out << "A:" << settings.A << ":" << key.at(2) << "\n";
    out << "D:" << settings.D << ":" << key.at(3) << "\n";
    out << "Shift:" << settings.Shift << ":" << key.at(4) << "\n";
    out << "Space:" << settings.Space << ":" << key.at(5) << "\n";
    out << "L:" << settings.L << ":" << key.at(6) << "\n";
    file.close();
}
void Setting::Label_Tick()
{
    switch (chose)
    {
    case 0:
        ui->l1->setText(key.at(0));
        ui->l2->setText(key.at(1));
        ui->l3->setText(key.at(2));
        ui->l4->setText(key.at(3));
        ui->l5->setText(key.at(4));
        ui->l6->setText(key.at(5));
        ui->l7->setText(key.at(6));
        break;
    case 1:
        if (ui->l1->text() == " ")
            ui->l1->setText(key.at(chose - 1));
        else
            ui->l1->setText(" ");
        break;
    case 2:
        if (ui->l2->text() == " ")
            ui->l2->setText(key.at(chose - 1));
        else
            ui->l2->setText(" ");
        break;
    case 3:
        if (ui->l3->text() == " ")
            ui->l3->setText(key.at(chose - 1));
        else
            ui->l3->setText(" ");
        break;
    case 4:
        if (ui->l4->text() == " ")
            ui->l4->setText(key.at(chose - 1));
        else
            ui->l4->setText(" ");
        break;
    case 5:
        if (ui->l5->text() == " ")
            ui->l5->setText(key.at(chose - 1));
        else
            ui->l5->setText(" ");
        break;
    case 6:
        if (ui->l6->text() == " ")
            ui->l6->setText(key.at(chose - 1));
        else
            ui->l6->setText(" ");
        break;
    case 7:
        if (ui->l7->text() == " ")
            ui->l7->setText(key.at(chose - 1));
        else
            ui->l7->setText(" ");
        break;
    }
}
void Setting::on_pushButton_2_clicked()
{
    Me_Vanish();
    QTimer::singleShot(2000, this, SLOT(Me_Close()));
}

void Setting::on_mode_currentIndexChanged(int index)
{
    settings.internetmode = index;
}

void Setting::on_difficult_currentIndexChanged(int index)
{
    settings.gamemode = index;
}

void Setting::on_MainSlide_sliderMoved(int position)
{
    settings.backsound = position;
}

void Setting::on_SoundSlide_sliderMoved(int position)
{
    settings.sound = position;
}

void Setting::keyPressEvent(QKeyEvent *event)
{
    QString t;
    t.setNum(event->key());
    if (chose < 1 || chose > 7)
        return;
    if (event->text() != "" && event->text() != " ")
        key.replace(chose - 1, event->text());
    else
        key.replace(chose - 1, "Key:" + t);
    switch (chose)
    {
    case 1:
        settings.W = event->key();
        break;
    case 2:
        settings.S = event->key();
        break;
    case 3:
        settings.A = event->key();
        break;
    case 4:
        settings.D = event->key();
        break;
    case 5:
        settings.Shift = event->key();
        break;
    case 6:
        settings.Space = event->key();
        break;
    case 7:
        settings.L = event->key();
        break;
    default:
        break;
    }
}

void Setting::on_SChange_clicked()
{
    if (chose == 2)
        chose = 0;
    else
        chose = 2;
}

void Setting::on_WChange_clicked()
{
    if (chose == 1)
        chose = 0;
    else
        chose = 1;
}

void Setting::on_AChange_clicked()
{
    if (chose == 3)
        chose = 0;
    else
        chose = 3;
}

void Setting::on_DChange_clicked()
{
    if (chose == 4)
        chose = 0;
    else
        chose = 4;
}

void Setting::on_ShiftChange_clicked()
{
    if (chose == 5)
        chose = 0;
    else
        chose = 5;
}

void Setting::on_SpaceChange_clicked()
{
    if (chose == 6)
        chose = 0;
    else
        chose = 6;
}

void Setting::on_LChange_clicked()
{
    if (chose == 7)
        chose = 0;
    else
        chose = 7;
}

void Setting::on_pushButton_3_clicked()
{

    QString aFile;

    aFile = QFileDialog::getSaveFileName(this, "选择地图目录", QCoreApplication::applicationDirPath(), ".txt", nullptr, nullptr);
    aFile.append(".txt");
    QFile file(aFile);

    //默认构造settings.txt
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "gamemode:" << settings.gamemode << "\n";
    out << "backsound:" << settings.backsound << "\n";
    out << "sound:" << settings.sound << "\n";
    out << "internetmode:" << settings.internetmode << "\n";
    out << "W:" << settings.W << ":" << key.at(0) << "\n";
    out << "S:" << settings.S << ":" << key.at(1) << "\n";
    out << "A:" << settings.A << ":" << key.at(2) << "\n";
    out << "D:" << settings.D << ":" << key.at(3) << "\n";
    out << "Shift:" << settings.Shift << ":" << key.at(4) << "\n";
    out << "Space:" << settings.Space << ":" << key.at(5) << "\n";
    out << "L:" << settings.L << ":" << key.at(6) << "\n";
    file.close();
}
void Setting::Me_Close()
{
    this->~Setting();
    mainwindow = new MainWindow;
    mainwindow->show();
}
void Setting::Me_Vanish()
{
    int i;
    for (i = 0; i < 36; i++)
    {
        audio[i] = new QPropertyAnimation(trans[i], "opacity", this);
        audio[i]->setDuration(2000);
        audio[i]->setStartValue(1.0);
        audio[i]->setEndValue(0);
        audio[i]->start();
    }
}

void Setting::on_MainSlide_valueChanged(int value)
{
    allmusic.PlayRedZoneMusic(value / 2);
}

void Setting::on_SoundSlide_valueChanged(int value)
{
    allmusic.PlayHit2Music(value);
}
