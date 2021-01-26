#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H
#include <QPainter>
#include <QMainWindow>
#include <QTimer>
#include<QTime>
#include"Player.h"
#include"Object.h"
#include"Enemy.h"
QT_BEGIN_NAMESPACE
namespace Ui { class BattleWindow; }
QT_END_NAMESPACE
class QKeyEvent;
class MainWindow;
class BattleWindow : public QMainWindow
{
    Q_OBJECT
public:
    BattleWindow(QWidget *parent = nullptr);
    ~BattleWindow();
void  Player_Move();
private slots:
void Move();
void bulletfly();//让子弹飞
void Player_HitCheck();//玩家碰撞检测
//void Enemy_HitCheck();//敌人碰撞检测
void Bullet_HitCheck();//所有子弹碰撞检测
void Flash();//实现动画
void Flash2();//实现动画
void Enemy_Move();//敌人移动
void Enemy_All();//敌人随机转向及发射子弹
void Enemy_Generate();
protected:
       void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
       int flash=0;
    Ui::BattleWindow *ui;
    Player P1;
    Enemy *enemy=new Enemy[Edit_Max];
    Object *object=new Object[Edit_Max];
    XY boom[Edit_Max];
    QTimer move;
    bool press=false;
  //  bool draw=false;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // BATTLEWINDOW_H
