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
BattleWindow::BattleWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::BattleWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::yellow));
    setAutoFillBackground(true);
    setWindowIcon(QIcon("://images/icon.bmp"));


    //读取文件
    int i=0,k=0,read=0;
    XY P;int thp,tmp;
    XY pos[Edit_Max]={0,0};
    XY area[Edit_Max]={0,0};
    int type[Edit_Max]={0};

    QString filename;
    filename = QFileDialog::getOpenFileName(this,tr("选择地图"),nullptr, tr("Image Files (*.txt)"));
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))//以读的方式打开文件
        qDebug()<<file.errorString();
    QTextStream input(&file);
    while(!input.atEnd()){
        QString line=input.readLine();
        if(line=="CObject:"){
            read=1;i=0;
        continue;
        }
        if(line=="CPlayer:"){
            read=2;i=0;
        continue;
        }
        switch (read) {
        case 1:
            switch (i%5) {
            case 0:type[i/5]=line.toInt(); qDebug()<<line.toInt();i++;break;
            case 1:pos[(i-1)/5].x=line.toInt();qDebug()<<line.toInt();i++;break;
            case 2:pos[(i-2)/5].y=line.toInt();qDebug()<<line.toInt();i++;break;
            case 3:area[(i-3)/5].x=line.toInt();qDebug()<<line.toInt();i++;break;
            case 4:area[(i-4)/5].y=line.toInt();qDebug()<<line.toInt();i++;break;
            }break;
        case 2:switch(i){
            case 0:P.x=line.toInt();i++;break;
            case 1:P.y=line.toInt();i++;break;
            case 2:thp=line.toInt();i++;break;
            case 3:tmp=line.toInt();i++;break;
            }break;
        default:break;
        }
    }
    file.close();
    new(&P1)Player(P,thp,tmp);

    for(i=0;i<Edit_Max;i++){
        if(type[i]==8){
            for(k=0;k<Edit_Max;k++){
            if(enemy[k].GetAlive()==false){
            new(&enemy[k])Enemy(pos[i],area[i],0,100);break;}}
        }if(type[i]==8)continue;
        new(&object[i])Object(pos[i],area[i],type[i]);
    }

  /*  for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==true)qDebug()<<i<<"...";
    }*/

    QTimer *timer = new QTimer(this);
    QTimer *flash = new QTimer(this);
    QTimer *enemymove = new QTimer(this);
    QTimer *enemyall = new QTimer(this);
    QTimer *generate = new QTimer(this);
  //  QTimer *boom = new QTimer(this)
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(bulletfly()));
        connect(flash, SIGNAL(timeout()), this, SLOT(Flash()));
        connect(&move, SIGNAL(timeout()), this, SLOT(Move()));
        connect(enemymove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
        connect(enemyall, SIGNAL(timeout()), this, SLOT(Enemy_All()));
        connect(generate, SIGNAL(timeout()), this, SLOT(Enemy_Generate()));
     //           connect(boom, SIGNAL(timeout()), this, SLOT(Flash2()));
      timer->start(10);
      flash->start(1000);
      enemymove->start(50);
      enemyall->start(100);
      generate->start(5000);
   //   boom->start(500);
}
BattleWindow::~BattleWindow(){}
void BattleWindow::Flash(){
    int i;
    for(i=0;i<Edit_Max;i++){
        if(object[i].GetHP()==-1&&object[i].GetType()==2){object[i].Hit();}
        if(object[i].GetType()==3) object[i].Hit();
    }
}
void BattleWindow::Flash2(){
flash++;
if(flash==5)flash=0;
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
    int i,k,j,m;
    for(i=0;i<Edit_Max;i++){//子弹命中敌人
    if(enemy[i].GetAlive()==false)continue;
    for(k=0;k<P1.GetBulletC();k++){//for
    if(P1.Player_BulletHit(k,enemy[i].GetPos(),enemy[i].GetArea())==true){
        enemy[i].Enemy_UnderAttack(1);
        P1.Player_B1_Hit(k);
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
                P1.Player_UnderAttack(1);qDebug()<<"Hit!!"<<P1.GetHP();
                enemy[i].Enemy_B1_Hit(k);
                if(P1.Player_Dead()==true){
                    QMessageBox::information(nullptr,tr("提示"),tr("您失败了"), tr("好"));
                    this->close();return;

                }
            }
        }
    }
}
void BattleWindow::Player_HitCheck(){
    int i;
    if(P1.GetPos().x<0||P1.GetPos().x>X_Max||P1.GetPos().y<0||P1.GetPos().y>Y_Max){//玩家边界判断
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
        QPainter painter(this);
      //  if(draw==false){
     //   QImage back("://images/BattleGround.jpg");
     //   QRect rect0(0,0,1600,1000);
    //    painter.drawImage(rect0,back);draw=true;}
        QRect rect1(P1.GetPos().x,P1.GetPos().y,50,50);
        QImage image("://images/TankUp.bmp");
        switch (P1.GetHead()) {
        case UP:image.load("://images/TankUp.bmp");break;
        case DOWN:image.load("://images/TankDown.bmp");break;
        case LEFT:image.load("://images/TankLeft.bmp");break;
        case RIGHT:image.load("://images/TankRight.bmp");break;
        }
        painter.drawImage(rect1,image);

        QImage bullet(":/images/Shot.bmp");
        QRect rect[10];


        for(i=0;i<P1.GetBulletC();i++){
            if(P1.GetBulletAlive(i)==true){
            rect[i].adjust(P1.GetBulletPos(i).x,P1.GetBulletPos(i).y,10,10);
            painter.drawImage(rect[i],bullet);}
        }

        QImage Enemy_Image[Edit_Max];
        QRect *Enemy_Rect=new QRect[Edit_Max];
        QRect Enemy_Bullet[Edit_Max][5];

        for(i=0;i<Edit_Max;i++){
            if(enemy[i].GetAlive()==false)continue;
            new(&Enemy_Rect[i])QRect(enemy[i].GetPos().x,enemy[i].GetPos().y,50,50);
            for(k=0;k<5;k++){
                if(enemy[i].GetBulletAlive(k)==false)continue;
                Enemy_Bullet[i][k].setRect(enemy[i].GetBulletPos(k).x,enemy[i].GetBulletPos(k).y,10,10);
                painter.drawImage(Enemy_Bullet[i][k],bullet);
            }
            switch (enemy[i].GetHead()) {
            case UP:Enemy_Image[i].load("://images/EnemyUp.bmp");break;
            case DOWN:Enemy_Image[i].load("://images/EnemyDown.bmp");break;
            case LEFT:Enemy_Image[i].load("://images/EnemyLeft.bmp");break;
            case RIGHT:Enemy_Image[i].load("://images/EnemyRight.bmp");break;
            }
          //  qDebug()<<"enemy:"<<i<<"pos:"<<Enemy_Rect[i].center().x()<<","<<Enemy_Rect[i].center().y();
        painter.drawImage(Enemy_Rect[i],Enemy_Image[i]);
        }

        QImage walls1("://images/Wall1.bmp");
        QImage walls2("://images/Wall2.bmp");

        QImage bedrock1("://images/Bedrock1.bmp");
        QImage bedrock2("://images/Bedrock2.bmp");

        QImage river1("://images/River1.bmp");
        QImage river2("://images/River2.bmp");
        QImage camp("://images/Camp.bmp");
        QImage firstaid("://images/FirstAid.bmp");
        QImage weapon("://images/Weapon.bmp");
        QRect *ObjectRect=new QRect[Edit_Max];
        for(i=0;i<Edit_Max;i++){
            switch (object[i].GetType()) {
            case 1:    new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
                if(object[i].GetHP()==1)
            painter.drawImage(ObjectRect[i],walls1);
                else
            painter.drawImage(ObjectRect[i],walls2);
            break;
            case 2:
                new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
                if(object[i].GetHP()==-1) painter.drawImage(ObjectRect[i],bedrock2);
                else painter.drawImage(ObjectRect[i],bedrock1);
                break;
            case 3:
                new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
                if(object[i].GetHP()==1) painter.drawImage(ObjectRect[i],river1);
                else painter.drawImage(ObjectRect[i],river2);
                break;
            case 5:
                new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
                painter.drawImage(ObjectRect[i],camp);
                break;
            case 6:
                new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
                painter.drawImage(ObjectRect[i],firstaid);
                break;
            case 7:
                new(&ObjectRect[i])QRect(object[i].GetPos().x,object[i].GetPos().y,object[i].GetArea().x,object[i].GetArea().y);
                painter.drawImage(ObjectRect[i],weapon);
                break;
            }
    }
    }

    void BattleWindow::Enemy_Move(){
    int i,k;
    for(i=0;i<Edit_Max;i++){
        if(enemy[i].GetAlive()==false){continue;}
        enemy[i].Enemy_Move(enemy[i].GetMoveSpeed());
                if(enemy[i].GetPos().x<0||enemy[i].GetPos().x>X_Max||enemy[i].GetPos().y<0||enemy[i].GetPos().y>Y_Max){
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
                new(&enemy[k])Enemy(t1,t2,5,100);break;}
                }

        }
    }
    void BattleWindow::Player_Move(){
          move.start(10);
    }
    void BattleWindow::Move(){
        P1.Player_Move(2);Player_HitCheck();
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
