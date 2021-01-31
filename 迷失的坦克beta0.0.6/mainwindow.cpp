#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Player.h"
#include<QMessageBox>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    p->setMedia(QUrl("qrc:/sounds/sounds/MainMusic.mp3"));
    p->setVolume(100);
    s->setMedia(QUrl("qrc:/sounds/sounds/Tap.mp3"));
    s->setVolume(100);
    p->play();
    int i;
    ui->setupUi(this);
    ui->centralwidget->setMouseTracking(true);
    Main_Mod=0;Main_Select=0;
    setWindowIcon(QIcon("://images/icon.png"));
    this->setStyleSheet("#MainWindow{border-image:url(:/images/BackGround.png);}");
    Mission1.load("://images/Mission1.png");
    Mission2.load("://images/Mission2.png");
    Mini1.load("://images/Mini1.png");
    Mini2.load("://images/Mini2.png");
    Survival1.load("://images/Survival1.png");
    Survival2.load("://images/Survival2.png");
    Select.load("://images/Challenge_Window.png");
    Close1.load("://images/Close1.png");
    Close2.load("://images/Close2.png");
    About1.load("://images/About1.png");
    About2.load("://images/About2.png");
    Options1.load("://images/Options1.png");
    Options2.load("://images/Options2.png");
    Quit1.load("://images/Quit1.png");
    Quit2.load("://images/Quit2.png");

    MissionR.setRect(700,50,1300,800);
    MiniR.setRect(750,300,600,300);
    SurvivalR.setRect(740,450,600,300);
    CloseR.setRect(1252,932,300,50);
    OptionsR.setRect(1100,800,120,70);
    AboutR.setRect(1262,835,100,50);
    QuitR.setRect(1406,820,100,50);
    for(i=0;i<20;i++){
        SelectR[i].setRect(50+(i*300)-((i/5)*1500),125+((i/5)*200),300,200);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    int i;
    QPainter painter(this);

    switch (Main_Mod) {
    case 0:
        this->setStyleSheet("#MainWindow{border-image:url(:/images/BackGround.png);}");
        painter.drawImage(MissionR,Mission1);
        painter.drawImage(MiniR,Mini1);
        painter.drawImage(SurvivalR,Survival1);
        painter.drawImage(OptionsR,Options1);
        painter.drawImage(AboutR,About1);
        painter.drawImage(QuitR,Quit1);
        switch (Main_Select) {
        case 1:painter.drawImage(MissionR,Mission2);break;
        case 2:painter.drawImage(MiniR,Mini2);break;
        case 3:painter.drawImage(SurvivalR,Survival2);break;
        case 4:painter.drawImage(OptionsR,Options2);break;
        case 5:painter.drawImage(AboutR,About2);break;
        case 6:painter.drawImage(QuitR,Quit2);break;
        default:break;
        }break;
    case 1:
        this->setStyleSheet("#MainWindow{border-image:url(://images/Mission_BackGround.jpg);}");
        for(i=0;i<20;i++){
            painter.drawImage(SelectR[i],Select);
        }
        painter.drawImage(CloseR,Close1);
        switch (Main_Select) {
        case 100:painter.drawImage(CloseR,Close2);break;

        }

        break;
    }


}
void MainWindow::mouseMoveEvent(QMouseEvent *ev){
    int t=Main_Select;
    if(Main_Mod==0){
    if(AboutR.contains(ev->pos())==true){
        Main_Select=5;
        this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(MiniR.contains(ev->pos())==true){
        Main_Select=2;this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(SurvivalR.contains(ev->pos())==true){
        Main_Select=3;this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(OptionsR.contains(ev->pos())==true){
        Main_Select=4;this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(MissionR.contains(ev->pos())==true){
        Main_Select=1;this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else if(QuitR.contains(ev->pos())==true){
        Main_Select=6;
    }else {Main_Select=0;this->setCursor(QCursor(Qt::ArrowCursor));}
    }else if(Main_Mod==1){
        if(CloseR.contains(ev->pos())==true){
            Main_Select=100;
        }
    }

    if(t!=Main_Select&&Main_Select!=0)PlayTap();
    update();
}
void MainWindow::mousePressEvent(QMouseEvent *ev){
qDebug()<<ev->x()<<","<<ev->y();
if(Main_Mod==0){
if(MiniR.contains(ev->pos())==true){
    QMessageBox::information(nullptr,tr("提示"),tr("敬请期待"), tr("好"));
    return;
}
if(SurvivalR.contains(ev->pos())==true){
    Battle=new BattleWindow;
    Battle->show();
    Battle->Load_Status(false,0);
    this->~MainWindow();p->~QMediaPlayer();
    return;
}
if(OptionsR.contains(ev->pos())==true){
    Map=new EditMap;
    Map->show();
    this->~MainWindow();p->~QMediaPlayer();
    return;
}
if(AboutR.contains(ev->pos())==true){
    Battle=new BattleWindow;
    Battle->show();
    Battle->Load_Status(true,0);p->~QMediaPlayer();
    this->~MainWindow();return;
}
if(QuitR.contains(ev->pos())==true){
    p->~QMediaPlayer();this->~MainWindow();
    return;
}
if(MissionR.contains(ev->pos())==true){
    Main_Mod=1;return;
}
}else if(Main_Mod==1){
    if(CloseR.contains(ev->pos())==true){
        Main_Mod=0;return;
    }
    if(SelectR[0].contains(ev->pos())==true){
        Battle=new BattleWindow;
        Battle->show();
        Battle->Load_Status(false,1);
        this->~MainWindow();p->~QMediaPlayer();
        return;
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

