#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QPainter>
#include <QIcon>
#include <QMainWindow>
#include <QMouseEvent>
#include<QMediaPlayer>
#include<QTimer>
#include"BattleWindow.h"
#include"EditMap.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void mousePressEvent(QMouseEvent *)Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
    void PlayTap();
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private slots:
void flash();
void Tick();
private:
        QMediaPlayer *p=new QMediaPlayer;
        QMediaPlayer *s=new QMediaPlayer;
    Ui::MainWindow *ui;
    BattleWindow *Battle;
    EditMap *Map;
    QImage Begin,DIY,Options,About,Quit,Move,Name,Close;
    QImage Partical1[10];
    QImage Partical2[10];
    QImage Partical3[10];
    QImage Mission_I[Edit_Min];

    QRect QuitR,OptionsR,AboutR,BeginR,DIYR,CloseR;
    QRect Mission_R[Edit_Min];
  //  QRect SelectR[20];
  //  QRect CloseR;
    QTimer Flash;
    int Main_Select=0;
    int Main_Mod=0;
    int x=1;
    int Seed();
};




#endif // MAINWINDOW_H
