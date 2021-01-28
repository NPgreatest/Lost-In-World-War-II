#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include<QDebug>
#include<QFile>
#include<QFileDialog>
#include<QRandomGenerator>
#include <QIcon>
#include <QInputDialog>
#include<QMediaPlayer>
#include<QSound>
#include"mainwindow.h"
BattleWindow::BattleWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::BattleWindow)
{
    ui->setupUi(this);

    setPalette(QPalette(Qt::yellow));
    setAutoFillBackground(true);
    this->setStyleSheet("#BattleWindow{border-image:url(:/images/BattleGround.jpg);}");

}
void BattleWindow::Load_Map(QString Address){
    int i=0,k=0,read=0;
    XY P;int thp,tmp;
    XY pos[Edit_Max]={0,0};
    XY area[Edit_Max]={0,0};
    int type[Edit_Max]={0};
    int skin[Edit_Max]={0};
    int hp[Edit_Max]={1};
    int e_hp[Edit_Max]={0};
    int e_speed[Edit_Max]={0};
    int e_bullet_speed[Edit_Max]={0};
    XY e_pos[Edit_Max]={0,0},e_area[Edit_Max]={0,0};
    int e_skin[Edit_Max]={0};

    QFile file(Address);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(nullptr,tr("提示"),tr("加载地图失败"), tr("好"));
        this->close();
    }
    QTextStream input(&file);
    while(!input.atEnd()){
        QString line=input.readLine();
        QStringList list=line.split(" ");
        if(line=="CObject:"){
            read=1;i=0;
        continue;
        }
        if(line=="CPlayer:"){
            read=2;i=0;
        continue;
        }
        if(line=="CEnemy:"){
            read=3;i=0;
            continue;
        }
        switch (read) {
        case 1:
            type[i]=list[0].toInt();
            pos[i].x=list[1].toInt();
            pos[i].y=list[2].toInt();
            area[i].x=list[3].toInt();
            area[i].y=list[4].toInt();
            hp[i]=list[5].toInt();
            skin[i]=list[6].toInt();
            i++;break;
        case 2:
            P.x=list[0].toInt();
            P.y=list[1].toInt();
            thp=list[2].toInt();
            tmp=list[3].toInt();
            break;
        case 3:
            e_pos[i].x=list[0].toInt();
            e_pos[i].y=list[1].toInt();
            e_area[i].x=list[2].toInt();
            e_area[i].y=list[3].toInt();
            e_hp[i]=list[4].toInt();
            e_speed[i]=list[5].toInt();
            e_bullet_speed[i]=list[6].toInt();
            e_skin[i]=list[7].toInt();
            i++;break;
        default:break;
        }
    }
    file.close();
    new(&P1)Player(P,thp,tmp);
    for(i=0;i<Edit_Max;i++){
        new(&object[i])Object(pos[i],area[i],type[i],hp[i],skin[i]);
    }

    for(i=0;i<Edit_Max;i++){
        if(e_area[i].x==0||e_area[i].y==0)continue;
            for(k=0;k<Edit_Max;k++){
            if(enemy[k].GetAlive()==false){
            new(&enemy[k])Enemy(e_pos[i],e_area[i],e_hp[i],e_speed[i],e_bullet_speed[i],1);break;
            }
    }
}
}
void BattleWindow::Load_Status(bool intro){
    if(intro==true){this->Load_Introduce();QTimer *timer = new QTimer(this);//介绍模式
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(10);
        return;}


    Red_Zone_Fre=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸频率/ms"),5000,100,20000,100,nullptr,nullptr);
    Red_Zone=QInputDialog::getInt(this,tr("DIY"),tr("输入轰炸几率%"),50,0,100,1,nullptr,nullptr);
    QString Address = QFileDialog::getOpenFileName(this,tr("选择地图"),nullptr, tr("Image Files (*.txt)"));
    Load_Map(Address);
    //QTimer
    QTimer *timer = new QTimer(this);
    QTimer *flash = new QTimer(this);
    QTimer *enemymove = new QTimer(this);
    QTimer *enemyall = new QTimer(this);
    QTimer *generate = new QTimer(this);
    QTimer *boom = new QTimer(this);
    QTimer *redzone=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(bulletfly()));
    connect(flash, SIGNAL(timeout()), this, SLOT(Flash()));
    connect(&move, SIGNAL(timeout()), this, SLOT(Move()));
    connect(enemymove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
    connect(enemyall, SIGNAL(timeout()), this, SLOT(Enemy_All()));
    connect(generate, SIGNAL(timeout()), this, SLOT(Enemy_Generate()));
    connect(boom, SIGNAL(timeout()), this, SLOT(Flash2()));
    connect(redzone, SIGNAL(timeout()), this, SLOT(RedZone_Generate()));


      redzone->start(Red_Zone_Fre);
      timer->start(10);
      flash->start(1000);
      enemymove->start(50);
      enemyall->start(100);
      generate->start(5000);
      boom->start(50);
}

BattleWindow::~BattleWindow(){}

void BattleWindow::RedZone_Generate(){
    int i,x,r,type;
    XY pos;
    x = QRandomGenerator::global()->generate();
    if(x%(100/Red_Zone)!=0)return;
    for(i=0;i<Edit_Min;i++){
    if(redzone[i].GetAlive()==true)continue;
    pos.x=QRandomGenerator::global()->bounded(0,X_Max);
    pos.y=QRandomGenerator::global()->bounded(0,Y_Max);
    r=QRandomGenerator::global()->bounded(50,200);
    type=QRandomGenerator::global()->bounded(1,4);
    new(&redzone[i])RedZone(pos,r,type);
    redzone[i].Flash_Begin();
    return;
}
}

void BattleWindow::Flash(){
    int i;
    for(i=0;i<Edit_Max;i++){
        if(object[i].GetAlive()==false)continue;
        if(object[i].GetHP()==-1&&object[i].GetType()==2){object[i].Hit();}
        if(object[i].GetType()==3) object[i].Hit();
    }
    for(i=0;i<Edit_Min;i++){
        if(redzone[i].GetAlive()==false)continue;
        if(redzone[i].GetFlash()==-1)continue;
        if(redzone[i].GetFlash()==4)RedZoneBoom(i);
        redzone[i].Flash();
    }
}
void BattleWindow::Flash2(){
    int i;

    for (i=0;i<Edit_Max;i++) {
        if(enemy[i].GetFlash()==-1)continue;
        enemy[i].Flash();
    }
}
void BattleWindow::RedZoneBoom(int x){
    int i;
    for(i=0;i<Edit_Max;i++){
    if(object[i].GetAlive()==false)continue;
    if(redzone[x].Object_Hit(object[i].GetPos(),object[i].GetArea())==true){
        object[i].Dead();
    }
}
    for(i=0;i<Edit_Max;i++){
    if(enemy[i].GetAlive()==false)continue;
    if(redzone[x].Object_Hit(enemy[i].GetPos(),enemy[i].GetArea())==true){
        enemy[i].Dead();
    }
}



}
void BattleWindow::bulletfly(){
int i;
P1.Player_B1_Move();
for(i=0;i<Edit_Max;i++){
    enemy[i].Enemy_B1_Move();
}
Bullet_HitCheck();
}
void BattleWindow::Bullet_HitCheck(){
    int i,k,j;
    for(i=0;i<Edit_Max;i++){//子弹命中敌人
    if(enemy[i].GetAlive()==false)continue;
    for(k=0;k<P1.GetBulletC();k++){//for
    if(P1.Player_BulletHit(k,enemy[i].GetPos(),enemy[i].GetArea())==true){
        enemy[i].Enemy_UnderAttack(1);
        P1.Player_B1_Hit(k);
        enemy[i].Flash_Begin();
        }
    }//end for
    }

    for(i=0;i<Edit_Max;i++){
    if(object[i].GetAlive()==false||object[i].GetType()==6||object[i].GetType()==7)continue;
    for(k=0;k<P1.GetBulletC();k++){//for
    if(P1.Player_BulletHit(k,object[i].GetPos(),object[i].GetArea())==true){
        if(object[i].GetType()!=3){
        object[i].Hit();
        P1.Player_B1_Hit(k);

            }
        }
    }//end for
    for(j=0;j<Edit_Max;j++){
        if(enemy[j].GetAlive()==false||object[i].GetType()==5||object[i].GetType()==6||object[i].GetType()==7)continue;
        for(k=0;k<5;k++){
            if(enemy[j].Enemy_BulletHit(k,object[i].GetPos(),object[i].GetArea())==true){
                if(object[i].GetType()!=3){
                object[i].Hit();
                enemy[j].Enemy_B1_Hit(k);
                    }
            }
        }
    }
    }
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==false)continue;
        for(k=0;k<5;k++){
            if(enemy[i].Enemy_BulletHit(k,P1.GetPos(),P1.GetArea())==true){
                P1.Player_UnderAttack(1);
                enemy[i].Enemy_B1_Hit(k);
                if(P1.Player_Dead()==true){
                    QMessageBox::information(nullptr,tr("提示"),tr("您失败了"), tr("好"));
                    this->~BattleWindow();
                    backto=new MainWindow;
                    backto->show();
                    return;

                }
            }
        }
    }
}
void BattleWindow::Player_HitCheck(){
    int i;
    if(P1.GetPos().x<0||P1.GetPos().x+50>X_Max||P1.GetPos().y<0||P1.GetPos().y+50>Y_Max){//玩家边界判断
        P1.Player_Move(-1);
        Player_HitCheck();//递归处理
    }
    for(i=0;i<Edit_Max;i++){//墙判断
        if(object[i].GetAlive()==false)continue;
        if(P1.Player_Hit(object[i].GetPos(),object[i].GetArea())==true){
            if(object[i].GetType()==6){//急救包
                P1.Strengthen(1,0,0,0,0);
                object[i].Hit();
            }
            if(object[i].GetType()==7){//武器箱
                P1.Strengthen(0,0,0,0,1);
                object[i].Hit();
            }
            P1.Player_Move(-1);
            Player_HitCheck();//递归处理
        }
    }//墙end
    }


void BattleWindow::paintEvent(QPaintEvent *event){
        ui->Bar->setValue(P1.GetHP());
        int i,k;
        QPainter painter(this);//Qpainter
        //QImage
        QImage P1_Image("://images/TankUp.bmp");
        QImage Wall_Image1("://images/Wall1.bmp");
        QImage Wall_Image2("://images/Wall2.bmp");
        QImage Bedrock_Image1("://images/Bedrock1.bmp");
        QImage Bedrock_Image2("://images/Bedrock2.bmp");
        QImage River_Image1("://images/River1.bmp");
        QImage River_Image2("://images/River2.bmp");
        QImage Camp_Image1("://images/Camp.bmp");
        QImage FirstAid_Image1("://images/FirstAid.bmp");
        QImage Weapon_Image1("://images/Weapon.bmp");
        QImage RedZone_Image[6];
        RedZone_Image[0].load("://images/RedZone1.bmp");RedZone_Image[0]=Image_Transparent(RedZone_Image[0],50);
        RedZone_Image[1].load("://images/RedZone1.bmp");RedZone_Image[1]=Image_Transparent(RedZone_Image[1],100);
        RedZone_Image[2].load("://images/RedZone1.bmp");RedZone_Image[2]=Image_Transparent(RedZone_Image[2],150);
        RedZone_Image[3].load("://images/RedZone1.bmp");RedZone_Image[3]=Image_Transparent(RedZone_Image[3],200);
        RedZone_Image[4].load("://images/RedZone1.bmp");RedZone_Image[4]=Image_Transparent(RedZone_Image[4],255);
        RedZone_Image[5].load("://images/RedZone2.bmp");RedZone_Image[5]=Image_Transparent(RedZone_Image[5],255);
        QImage Boom_Image1("://images/Boom1.bmp");Boom_Image1=Image_Cut(Boom_Image1);
        QImage Boom_Image2("://images/Boom2.bmp");Boom_Image2=Image_Cut(Boom_Image2);
        QImage Boom_Image3("://images/Boom3.bmp");Boom_Image3=Image_Cut(Boom_Image3);
        QImage Boom_Image4("://images/Boom4.bmp");Boom_Image4=Image_Cut(Boom_Image4);
        QImage Boom_Image5("://images/Boom5.bmp");Boom_Image5=Image_Cut(Boom_Image5);
        QImage Boom_Image6("://images/Boom6.bmp");Boom_Image6=Image_Cut(Boom_Image6);
        QImage Enemy_Image[4];        QImage Enemy_Image2[4];
        Enemy_Image[0].load("://images/EnemyUp.bmp");       Enemy_Image[0]=Image_Cut(Enemy_Image[0]);
        Enemy_Image[1].load("://images/EnemyDown.bmp");     Enemy_Image[1]=Image_Cut(Enemy_Image[1]);
        Enemy_Image[2].load("://images/EnemyLeft.bmp");     Enemy_Image[2]=Image_Cut(Enemy_Image[2]);
        Enemy_Image[3].load("://images/EnemyRight.bmp");    Enemy_Image[3]=Image_Cut(Enemy_Image[3]);
        Enemy_Image2[0].load("://images/EnemyUp2.bmp");       Enemy_Image2[0]=Image_Cut(Enemy_Image2[0]);
        Enemy_Image2[1].load("://images/EnemyDown2.bmp");     Enemy_Image2[1]=Image_Cut(Enemy_Image2[1]);
        Enemy_Image2[2].load("://images/EnemyLeft2.bmp");     Enemy_Image2[2]=Image_Cut(Enemy_Image2[2]);
        Enemy_Image2[3].load("://images/EnemyRight2.bmp");    Enemy_Image2[3]=Image_Cut(Enemy_Image2[3]);
        QImage Skill1("://images/skill1.bmp"); Skill1=Image_Transparent(Skill1,100);
        switch (P1.GetHead()) {
        case UP:P1_Image.load("://images/TankUp.bmp");break;
        case DOWN:P1_Image.load("://images/TankDown.bmp");break;
        case LEFT:P1_Image.load("://images/TankLeft.bmp");break;
        case RIGHT:P1_Image.load("://images/TankRight.bmp");break;
        }
        P1_Image=Image_Cut(P1_Image);
        QImage P1_Bullet_Image(":/images/Shot.bmp");
        QImage Enemy_Bullet_Image(":/images/Shot.bmp");

        //QRect
        QRect P1_Rect(P1.GetPos().x,P1.GetPos().y,50,50);
        QRect P1_Bullet_Rect[10];
        QRect *Enemy_Rect=new QRect[Edit_Max];
        QRect Enemy_Bullet_Rect[Edit_Max][5];
        QRect *ObjectRect=new QRect[Edit_Max];
        QPoint Line1(1500,0);//边界线
        QPoint Line2(1500,1000);
        painter.drawLine(Line1,Line2);
        for(i=0;i<Edit_Max;i++){
            if(object[i].GetAlive()==false)continue;
            new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
            switch (object[i].GetType()) {
            case 1:
                if(object[i].GetHP()==0)
            painter.drawImage(ObjectRect[i],Wall_Image2);
                else
            painter.drawImage(ObjectRect[i],Wall_Image1);
            break;
            case 2:
                if(object[i].GetHP()==-1) painter.drawImage(ObjectRect[i],Bedrock_Image2);
                else painter.drawImage(ObjectRect[i],Bedrock_Image1);
                break;
            case 3:
                if(object[i].GetHP()==1) painter.drawImage(ObjectRect[i],River_Image1);
                else painter.drawImage(ObjectRect[i],River_Image2);
                break;
            case 5:
                painter.drawImage(ObjectRect[i],Camp_Image1);
                break;
            case 6:
                painter.drawImage(ObjectRect[i],FirstAid_Image1);
                break;
            case 7:
                painter.drawImage(ObjectRect[i],Weapon_Image1);
                break;
            }
    }

        for(i=0;i<P1.GetBulletC();i++){
            if(P1.GetBulletAlive(i)==true){
            P1_Bullet_Rect[i].adjust(P1.GetBulletPos(i).x,P1.GetBulletPos(i).y,10,10);
            painter.drawImage(P1_Bullet_Rect[i],P1_Bullet_Image);}
        }
        painter.drawImage(P1_Rect,P1_Image);




        for(i=0;i<Edit_Max;i++){


            if(enemy[i].GetAlive()==false&&enemy[i].GetFlash()==-1)continue;
            new(&Enemy_Rect[i])QRect(enemy[i].GetPos().x,enemy[i].GetPos().y,enemy[i].GetArea().x,enemy[i].GetArea().y);

            for(k=0;k<5;k++){
                if(enemy[i].GetBulletAlive(k)==false)continue;
                if(enemy[i].GetAlive()==false)continue;
                Enemy_Bullet_Rect[i][k].setRect(enemy[i].GetBulletPos(k).x,enemy[i].GetBulletPos(k).y,10,10);
                painter.drawImage(Enemy_Bullet_Rect[i][k],Enemy_Bullet_Image);
            }
            switch (enemy[i].GetSkin()) {
            case 1:
            switch (enemy[i].GetHead()) {
            case UP:painter.drawImage(Enemy_Rect[i],Enemy_Image[0]);break;
            case DOWN:painter.drawImage(Enemy_Rect[i],Enemy_Image[1]);break;
            case LEFT:painter.drawImage(Enemy_Rect[i],Enemy_Image[2]);break;
            case RIGHT:painter.drawImage(Enemy_Rect[i],Enemy_Image[3]);break;
            }break;
            case 2:
            switch (enemy[i].GetHead()) {
            case UP:painter.drawImage(Enemy_Rect[i],Enemy_Image2[0]);break;
            case DOWN:painter.drawImage(Enemy_Rect[i],Enemy_Image2[1]);break;
            case LEFT:painter.drawImage(Enemy_Rect[i],Enemy_Image2[2]);break;
            case RIGHT:painter.drawImage(Enemy_Rect[i],Enemy_Image2[3]);break;
            }
            }
            if(enemy[i].GetAlive()==true)continue;
            switch (enemy[i].GetFlash()) {
            case 0:painter.drawImage(Enemy_Rect[i],Boom_Image1);break;
            case 1:painter.drawImage(Enemy_Rect[i],Boom_Image2);break;
            case 2:painter.drawImage(Enemy_Rect[i],Boom_Image3);break;
            case 3:painter.drawImage(Enemy_Rect[i],Boom_Image4);break;
            case 4:painter.drawImage(Enemy_Rect[i],Boom_Image5);break;
            case 5:painter.drawImage(Enemy_Rect[i],Boom_Image6);break;
            default:break;
            }
        }
        //paint RedZone
        for(i=0;i<Edit_Min;i++){
            if(redzone[i].GetAlive()==false)continue;
            QRect temp(redzone[i].GetPos().x-redzone[i].GetR(),redzone[i].GetPos().y-redzone[i].GetR(),redzone[i].GetR()*2,redzone[i].GetR()*2);
            painter.drawImage(temp,RedZone_Image[redzone[i].GetFlash()]);
        }





//paint Introduce
        if(IntroduceP!=0)drawIntroduce(painter);
}

void BattleWindow::Enemy_Move(){
    int i,k;
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==false)continue;
        enemy[i].Enemy_Move(enemy[i].GetMoveSpeed());
                if(enemy[i].GetPos().x<0||enemy[i].GetPos().x+enemy[i].GetArea().x>X_Max||
                        enemy[i].GetPos().y<0||enemy[i].GetPos().y+enemy[i].GetArea().y>Y_Max){
                    enemy[i].Enemy_Move(-(enemy[i].GetMoveSpeed()));
                    enemy[i].Enemy_RndChangeHead();
                }
        for(k=0;k<Edit_Max;k++){
            if(object[k].GetAlive()==false)continue;
            if(enemy[i].Enemy_Hit(object[k].GetPos(),object[k].GetArea())==true){
                enemy[i].Enemy_Move(-(enemy[i].GetMoveSpeed()));
                enemy[i].Enemy_RndChangeHead();
        }
        }

    }
}

    void BattleWindow::Enemy_Generate(){
        int i,k,x,y;
        XY t1,t2={50,50};
        for(i=0;i<Edit_Max;i++){
            if(object[i].GetType()!=5)continue;
            x = QRandomGenerator::global()->generate();
            y = QRandomGenerator::global()->generate();
                for(k=0;k<Edit_Max;k++){
                if(enemy[k].GetAlive()==false){
                    t1=object[i].GetPos();
                   if(x%2==1)t1.x-=50;
                   else t1.x+=50;
                   if(y%2==1)t1.y-=50;
                   else t1.y+=50;
                new(&enemy[k])Enemy(t1,t2,2,10,20,2);break;}
                }
        }
    }
    void BattleWindow::Player_Move(){
          move.start(10);
    }
    void BattleWindow::Move(){
        P1.Player_Move(P1.GetSpeed());Player_HitCheck();
    }
    void BattleWindow::Enemy_All(){
        int i;
        for (i=0;i<Edit_Max ;i++ ) {if(enemy[i].GetAlive()==false)continue;
        int x = QRandomGenerator::global()->generate();
        if(x%6==0){
           enemy[i].Enemy_RndChangeHead();
        }
        if(x%5==0)
            enemy[i].Enemy_B1Fire();
        }
    }
    void BattleWindow::keyPressEvent(QKeyEvent *event){
        if(!event->isAutoRepeat()){
            switch (event->key()) {
                case Qt::Key_Left:
                Player_Move();
                P1.Player_ChangeHead(2);
                    break;
                case Qt::Key_Right:
                Player_Move();
                P1.Player_ChangeHead(3);
                    break;
                case Qt::Key_Up:
                Player_Move();
                P1.Player_ChangeHead(0);
                    break;
                case Qt::Key_Down:
                Player_Move();
                P1.Player_ChangeHead(1);
                    break;
                case Qt::Key_Space:
                P1.Player_B1Fire();
                    break;
            }
         }
    }
    void BattleWindow::keyReleaseEvent(QKeyEvent *event){
        if(!event->isAutoRepeat()){
        switch (event->key()) {
            case Qt::Key_Left:
                move.stop();
                break;
            case Qt::Key_Right:
                move.stop();
                break;
            case Qt::Key_Up:
                move.stop();
                break;
            case Qt::Key_Down:
                move.stop();
                break;
        }
        }
    }

    QImage BattleWindow::Image_Cut(QImage image)
    {
            image = image.convertToFormat(QImage::Format_ARGB32);
            union myrgb
            {
                uint rgba;
                uchar rgba_bits[4];
            };
            myrgb* mybits =(myrgb*) image.bits();
            int len = image.width()*image.height();
            while(len --> 0)
            {
                mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:255;
                mybits++;
            }
            return image;
}
    QImage BattleWindow::Image_Transparent(QImage image,int x)
    {
            image = image.convertToFormat(QImage::Format_ARGB32);
            union myrgb
            {
                uint rgba;
                uchar rgba_bits[4];
            };
            myrgb* mybits =(myrgb*) image.bits();
            int len = image.width()*image.height();
            while(len --> 0)
            {
                mybits->rgba_bits[3] = (mybits->rgba== 0xFFFFFFFF)?0:x;
                mybits++;
            }
            return image;
}
   void BattleWindow::mousePressEvent(QMouseEvent *event){


    }

   void BattleWindow::mouseMoveEvent(QMouseEvent *event){
        qDebug()<<event->x();
                qDebug()<<event->y();

    }
