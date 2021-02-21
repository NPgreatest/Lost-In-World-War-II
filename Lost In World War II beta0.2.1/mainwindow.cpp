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
    QTimer *tick=new QTimer(this);
    connect(tick,  SIGNAL(timeout()), this, SLOT(Tick()));
    connect(&Flash,  SIGNAL(timeout()), this, SLOT(flash()));
    Flash.start(800);
    tick->start(10);
    p->setMedia(QUrl("qrc:/sounds/sounds/MainMusic.mp3"));
    p->setVolume(100);
    s->setMedia(QUrl("qrc:/sounds/sounds/Tap.mp3"));
    s->setVolume(100);
    p->play();
    ui->setupUi(this);
    ui->centralwidget->setMouseTracking(true);
    Main_Mod=0;Main_Select=0;
    setWindowIcon(QIcon(":/Images/Images/icon.png"));
    this->setStyleSheet("#MainWindow{border-image:url(:/Images/Images/BackGround.jpg);}");

    Quit.load(":/Images/Images/Quit.png");
    About.load(":/Images/Images/About.png");
    Options.load(":/Images/Images/Options.png");
    Begin.load(":/Images/Images/Begin.png");
    DIY.load(":/Images/Images/DIY.png");
    Move.load(":/Images/Images/Move.png");
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
    Name.load(":/Images/Images/title.png");
    Mission_I[0].load(":/Images/Images/Challenge_Window.png");
    Mission_I[1].load(":/Images/Images/Challenge_Window2.png");
    Close.load(":/Images/Images/Close1.png");

    Mission_R[0].setRect(-500,300,500,500);
    Mission_R[1].setRect(2000,300,500,500);

    BeginR.setRect(1300,300,200,50);
    DIYR.setRect(1310,400,180,50);
    AboutR.setRect(1250,500,300,50);
    OptionsR.setRect(1350,600,100,50);
    QuitR.setRect(1350,700,100,50);
    CloseR.setRect(2000,800,300,100);
    /*for(i=0;i<20;i++){
        SelectR[i].setRect(50+(i*300)-((i/5)*1500),125+((i/5)*200),300,200);
    }*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    int i;
    QPainter painter(this);


 //  x = QRandomGenerator::global()->bounded(1,8);

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

    painter.drawImage(QRect( 300,50,1000,100), Name);

        this->setStyleSheet("#MainWindow{border-image:url(:/Images/Images/BackGround.jpg);}");
        switch (Main_Select) {
        case 1:painter.drawImage(BeginR.adjusted(-80,-80,80,80),Move);break;
        case 2:painter.drawImage(DIYR.adjusted(-100,-80,100,80),Move);break;
        case 3:painter.drawImage(AboutR.adjusted(-150,-80,150,80),Move);break;
        case 4:painter.drawImage(OptionsR.adjusted(-80,-50,80,50),Move);break;
        case 5:painter.drawImage(QuitR.adjusted(-80,-50,80,50),Move);break;
        default:break;
        }
        painter.drawImage(BeginR,Begin);
        painter.drawImage(DIYR,DIY);
        painter.drawImage(AboutR,About);
        painter.drawImage(OptionsR,Options);
        painter.drawImage(QuitR,Quit);

        painter.drawImage(Mission_R[0],Mission_I[0]);
        painter.drawImage(Mission_R[1],Mission_I[1]);
        painter.drawImage(CloseR,Close);

    /*    this->setStyleSheet("#MainWindow{border-image:url(:/Images/Images/Mission_BackGround.jpg);}");
        for(i=0;i<20;i++){
            painter.drawImage(SelectR[i],Select);
        }
        painter.drawImage(CloseR,Close1);
        switch (Main_Select) {
        case 100:painter.drawImage(CloseR,Close2);break;

        }

        break;*/


}
void MainWindow::mouseMoveEvent(QMouseEvent *ev){
    int t=Main_Select;
    if(Main_Mod==0){
    if(BeginR.contains(ev->pos())==true){
        Main_Select=1;
        this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(DIYR.contains(ev->pos())==true){
        Main_Select=2;this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(AboutR.contains(ev->pos())==true){
        Main_Select=3;this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(OptionsR.contains(ev->pos())==true){
        Main_Select=4;this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(QuitR.contains(ev->pos())==true){
        Main_Select=5;
    }else {Main_Select=0;this->setCursor(QCursor(Qt::ArrowCursor));}
    }else if(Main_Mod==1){
        if(Mission_R[0].contains(ev->pos())==true){
            Main_Select=1;
            this->setCursor(QCursor(Qt::PointingHandCursor));
        }
        else if(Mission_R[1].contains(ev->pos())==true){
            Main_Select=2;
            this->setCursor(QCursor(Qt::PointingHandCursor));
        }
        else if(CloseR.contains(ev->pos())==true){
            Main_Select=3;
            this->setCursor(QCursor(Qt::PointingHandCursor));
        }
        else {
            Main_Select=0;
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
        }

    if(t!=Main_Select&&Main_Select!=0)PlayTap();
    update();
}
void MainWindow::mousePressEvent(QMouseEvent *ev){
qDebug()<<"painter.drawImage(QRect("<<ev->x()<<","<<ev->y()<<",200,200),Partical1[Seed()]);";
if(Main_Mod==0){
if(BeginR.contains(ev->pos())==true){
    Main_Mod=1;

}
if(DIYR.contains(ev->pos())==true){
    Map=new EditMap;
    Map->show();
    this->~MainWindow();p->~QMediaPlayer();
    return;
}
if(AboutR.contains(ev->pos())==true){
    Battle=new BattleWindow;
    Battle->show();
    Battle->Load_Status(0);p->~QMediaPlayer();
    this->~MainWindow();return;
}
if(OptionsR.contains(ev->pos())==true){
    Battle=new BattleWindow;
    Battle->show();
    Battle->Load_Status(100);
    this->~MainWindow();p->~QMediaPlayer();
    return;
}
if(QuitR.contains(ev->pos())==true){
    p->~QMediaPlayer();this->~MainWindow();
    return;
}
}else if(Main_Mod==1){
    if(Mission_R[0].contains(ev->pos())==true){
        QMessageBox::information(nullptr,tr("提示"),tr("坦克移动:WSAD\n更换武器:LShift\n作弊：按 - 增加HP、MP\n      按 = 跳关\n"), tr("好"));
          Battle=new BattleWindow;
          Battle->show();
          Battle->Load_Status(2);
          this->~MainWindow();p->~QMediaPlayer();
          return;
    }
    else if(Mission_R[1].contains(ev->pos())==true){
        Battle=new BattleWindow;
        Battle->show();
        Battle->Load_Status(1);
        this->~MainWindow();p->~QMediaPlayer();
        return;
    }
    else if(CloseR.contains(ev->pos())==true){
        Main_Mod=0;
    }
}
}
void MainWindow::PlayTap(){
    if(s->state()==QMediaPlayer::PlayingState){
        s->stop();
        s->setVolume(50);
        s->play();
    }
    s->setVolume(100);
    s->play();
}
 //   QMessageBox::information(nullptr,tr("提示"),tr("若无地图文件\n请先编辑地图\n再选择已创建的地图"), tr("好"));
 //   QMessageBox::information(nullptr,tr("提示"),tr("上下左右空格控制坦克"), tr("好"));
void MainWindow::flash(){
x = QRandomGenerator::global()->bounded(1,1000);
}

int MainWindow::Seed(){//x每秒随机
    static unsigned int a=0;
    a++;if(a==89)a=1;
    return ((((a*x+a*a-6)*a)%4)+1);
}
void MainWindow::Tick(){
    if(Main_Mod==1){
        if(BeginR.x()>=-500){
        BeginR.adjust(-10,0,-10,0);
        DIYR.adjust(10,0,10,0);
        OptionsR.adjust(0,10,0,10);
        QuitR.adjust(0,-10,0,-10);
        AboutR.adjust(10,10,10,10);return;}
        if(Mission_R[0].x()<=300){
            Mission_R[0].adjust(10,0,10,0);
            Mission_R[1].adjust(-13,0,-13,0);
            CloseR.adjust(-5,0,-5,0);
        }

    }
    if(Main_Mod==0){
        if(Mission_R[0].x()>=-500){
            Mission_R[0].adjust(-10,0,-10,0);
            Mission_R[1].adjust(13,0,13,0);
            CloseR.adjust(5,0,5,0);return;
        }
        if(BeginR.x()<=1300){
        BeginR.adjust(10,0,10,0);
        DIYR.adjust(-10,0,-10,0);
        OptionsR.adjust(0,-10,0,-10);
        QuitR.adjust(0,10,0,10);
        AboutR.adjust(-10,-10,-10,-10);
        }
    }

}
