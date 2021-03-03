#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Player.h"
#include<QMessageBox>
#include<QDebug>
#include<QRandomGenerator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    int i;
    QTimer *tick=new QTimer(this);
    connect(tick,  SIGNAL(timeout()), this, SLOT(update()));
    connect(tick,  SIGNAL(timeout()), this, SLOT(Tick()));
    connect(&Flash,  SIGNAL(timeout()), this, SLOT(flash()));
    Flash.start(800);
    tick->start(10);



    p->setMedia(QUrl("qrc:/sounds/sounds/MainMusic.mp3"));
    p->setVolume(100);
    for(i=0;i<Edit_Min;i++)
    s[i].setMedia(QUrl("qrc:/sounds/sounds/Tap.mp3"));

    p->play();
    ui->setupUi(this);
    ui->centralwidget->setMouseTracking(true);
    Main_Mod=0;Main_Select=0;
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


    connect(ui->pushButton,SIGNAL(Mouse_Click()),this,SLOT(Tap_Fun()));
    connect(ui->pushButton_2,SIGNAL(Mouse_Click()),this,SLOT(Tap_Fun()));
    connect(ui->pushButton_3,SIGNAL(Mouse_Click()),this,SLOT(Tap_Fun()));
    connect(ui->pushButton_4,SIGNAL(Mouse_Click()),this,SLOT(Tap_Fun()));
    connect(ui->pushButton_5,SIGNAL(Mouse_Click()),this,SLOT(Tap_Fun()));
    connect(ui->Back,SIGNAL(Mouse_Click()),this,SLOT(Tap_Fun()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    int i;
    QPainter painter(this);
    painter.drawImage(QRect(120,0,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(10,160,200,200),Partical2[Seed()]);
    painter.drawImage(QRect(70,220,200,200),Partical3[Seed()]);
    painter.drawImage(QRect(180,240,200,200),Partical2[Seed()]);
    painter.drawImage(QRect(50,330,200,200),Partical3[Seed()]);
    painter.drawImage(QRect(0,300,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(0,0,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(100,0,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(0,100,200,200),Partical3[Seed()]);
    painter.drawImage(QRect(170,100,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(250,0,200,200),Partical2[Seed()]);
    painter.drawImage(QRect(300,100,200,200),Partical3[Seed()]);
    painter.drawImage(QRect(10,500,200,200),Partical3[Seed()]);
    painter.drawImage(QRect(300,100,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(189,408,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(442,9,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(442,600,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(630,550,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(830,350,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(7,694,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(87,694,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(3,765,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(66,745,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(2,840,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(6,914,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(78,815,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(72,1000,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(233,913,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(368,920,200,200),Partical1[Seed()]);
    painter.drawImage(QRect(541,934,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 280 , 795 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 202 , 627 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 527 , 165 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 626 , 2 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 742 , 9 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 870 , 6 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 989 , 6 ,200,200),Partical3[Seed()]);
    painter.drawImage(QRect( 1102 , 2 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1201 , 6 ,200,200),Partical3[Seed()]);
    painter.drawImage(QRect( 1313 , 6 ,200,200),Partical3[Seed()]);
    painter.drawImage(QRect( 1395 , 3 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1512 , 3 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1638 , 4 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1774 , 4 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 703 , 44 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 836 , 43 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 964 , 46 ,200,200),Partical3[Seed()]);
    painter.drawImage(QRect( 1067 , 46 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1222 , 43 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1352 , 44 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1503 , 46 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1679 , 44 ,200,200),Partical3[Seed()]);
    painter.drawImage(QRect( 1833 , 43 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 632 , 117 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 840 , 123 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 988 , 122 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 721 , 894 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 837 , 837 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 827 , 915 ,200,200),Partical3[Seed()]);
    painter.drawImage(QRect( 950 , 821 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 962 , 900 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1082 , 788 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1077 , 909 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1188 , 767 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1193 , 885 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1255 , 777 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1315 , 872 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1365 , 668 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1385 , 767 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1394 , 891 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1480 , 628 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1485 , 752 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1490 , 870 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1615 , 594 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1584 , 745 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1590 , 871 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1722 , 591 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1706 , 709 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1696 , 831 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1850 , 582 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1782 , 796 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1812 , 686 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1760 , 884 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1397 , 612 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1583 , 536 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 1704 , 483 ,200,200),Partical2[Seed()]);
    painter.drawImage(QRect( 1833 , 419 ,200,200),Partical1[Seed()]);
    painter.drawImage(QRect( 211 , 626 ,200,200),Partical1[Seed()]);

    for(i=0;i<Edit_Max;i++){//创建粒子
        if(partical[i].GetAlive()==false)continue;
        painter.drawImage(partical[i].GetRect(),partical[i].GetImage());
    }


}


void MainWindow::PlayTap(){
    int i;
    for(i=0;i<Edit_Min;i++){
        if(s[i].state()==QMediaPlayer::PlayingState) continue;
        s[i].setVolume(50);
        s[i].play();
        break;
    }
}

void MainWindow::flash(){
x = QRandomGenerator::global()->bounded(1,1000);
}

int MainWindow::Seed(){//x每秒随机
    static unsigned int a=0;
    a++;if(a==89)a=1;
    return ((((a*x+a*a-6)*a)%4)+1);
}
void MainWindow::Tick(){
    int i;
    for(i=0;i<Edit_Max;i++){
        partical[i].FLash();
    }
    for(i=0;i<5;i++)
    CreatePartical(QRect(500+QRandomGenerator::global()->bounded(-50,50),180+QRandomGenerator::global()->bounded(-100,100),50,50),Type::Mist);

    if(Main_Mod==1){
        if(ui->pushButton->x()<=2000){
        ui->pushButton->setGeometry(ui->pushButton->x()+10,ui->pushButton->y(),ui->pushButton->width(),ui->pushButton->height());
        ui->pushButton_2->setGeometry(ui->pushButton_2->x()+10,ui->pushButton_2->y(),ui->pushButton_2->width(),ui->pushButton_2->height());
        ui->pushButton_3->setGeometry(ui->pushButton_3->x()+10,ui->pushButton_3->y(),ui->pushButton_3->width(),ui->pushButton_3->height());
        ui->pushButton_4->setGeometry(ui->pushButton_4->x()+10,ui->pushButton_4->y(),ui->pushButton_4->width(),ui->pushButton_4->height());
        ui->pushButton_5->setGeometry(ui->pushButton_5->x()+10,ui->pushButton_5->y(),ui->pushButton_5->width(),ui->pushButton_5->height());
        return;
        }

        if(ui->Story->x()<=300){
            ui->Story->setGeometry(ui->Story->x()+10,ui->Story->y(),ui->Story->width(),ui->Story->height());
            ui->Battle->setGeometry(ui->Battle->x()-13,ui->Battle->y(),ui->Battle->width(),ui->Battle->height());
            ui->Back->setGeometry(ui->Back->x()-10,ui->Back->y(),ui->Back->width(),ui->Back->height());

        }
    }

    if(Main_Mod==0){
        if(ui->Story->x()>=-500){
            ui->Story->setGeometry(ui->Story->x()-10,ui->Story->y(),ui->Story->width(),ui->Story->height());
            ui->Battle->setGeometry(ui->Battle->x()+13,ui->Battle->y(),ui->Battle->width(),ui->Battle->height());
            ui->Back->setGeometry(ui->Back->x()+10,ui->Back->y(),ui->Back->width(),ui->Back->height());
            return;
        }
        if(ui->pushButton->x()>1300){
            ui->pushButton->setGeometry(ui->pushButton->x()-10,ui->pushButton->y(),ui->pushButton->width(),ui->pushButton->height());
            ui->pushButton_2->setGeometry(ui->pushButton_2->x()-10,ui->pushButton_2->y(),ui->pushButton_2->width(),ui->pushButton_2->height());
            ui->pushButton_3->setGeometry(ui->pushButton_3->x()-10,ui->pushButton_3->y(),ui->pushButton_3->width(),ui->pushButton_3->height());
            ui->pushButton_4->setGeometry(ui->pushButton_4->x()-10,ui->pushButton_4->y(),ui->pushButton_4->width(),ui->pushButton_4->height());
            ui->pushButton_5->setGeometry(ui->pushButton_5->x()-10,ui->pushButton_5->y(),ui->pushButton_5->width(),ui->pushButton_5->height());
        }
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    Map=new EditMap;
    Map->show();
    this->~MainWindow();
    p->~QMediaPlayer();
    return;
}

void MainWindow::on_pushButton_3_clicked()
{
    Battle=new BattleWindow(nullptr,0);
    Battle->show();
    p->~QMediaPlayer();
    this->~MainWindow();return;
}

void MainWindow::on_pushButton_4_clicked()
{
    Battle=new BattleWindow(nullptr,100);
    Battle->show();
    this->~MainWindow();
    p->~QMediaPlayer();
    return;
}

void MainWindow::on_pushButton_5_clicked()
{
    p->~QMediaPlayer();
    this->~MainWindow();
    return;
}

void MainWindow::on_Story_clicked(){
    Battle=new BattleWindow(nullptr,1);
    Battle->show();
    this->~MainWindow();p->~QMediaPlayer();
    return;
}

void MainWindow::on_Battle_clicked()
{
    Battle=new BattleWindow(nullptr,2);
    Battle->show();
    this->~MainWindow();p->~QMediaPlayer();
    return;
}
void MainWindow::CreatePartical(QRect Rect,Type type){
    int i;
    for(i=0;i<Edit_Max;i++){//创建爆炸粒子
        if(partical[i].GetAlive()==true)continue;
                partical[i].~Partical();
               new(&partical[i])Partical(Rect,type);
        break;
    }//创建爆炸粒子
}
void MainWindow::mouseMoveEvent(QMouseEvent *ev){
    switch (QRandomGenerator::global()->bounded(1,5)) {
    case 1:CreatePartical(QRect(ev->x()-10,ev->y()-10,20,20),Type::Player_B3_UP);break;
    case 2:CreatePartical(QRect(ev->x()-10,ev->y()-10,20,20),Type::Player_B3_DOWN);break;
    case 3:CreatePartical(QRect(ev->x()-10,ev->y()-10,20,20),Type::Player_B3_LEFT);break;
    case 4:CreatePartical(QRect(ev->x()-10,ev->y()-10,20,20),Type::Player_B3_RIGHT);break;
    case 5:CreatePartical(QRect(ev->x()-10,ev->y()-10,20,20),Type::Object_Hit);break;

    }

}
