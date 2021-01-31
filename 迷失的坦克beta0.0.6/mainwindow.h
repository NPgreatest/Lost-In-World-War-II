#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QPainter>
#include <QIcon>
#include <QMainWindow>
#include <QMouseEvent>
#include<QMediaPlayer>
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


private:
        QMediaPlayer *p=new QMediaPlayer;
        QMediaPlayer *s=new QMediaPlayer;
    Ui::MainWindow *ui;
    BattleWindow *Battle;
    EditMap *Map;
    QImage Mission1;
    QImage Mini1;
    QImage Survival1;
    QImage Mission2;
    QImage Mini2;
    QImage Survival2;
    QImage Select;
    QImage Close1;
    QImage Close2;
    QImage Quit1,Quit2,Options1,Options2,About1,About2;
    QRect QuitR,OptionsR,AboutR;
    QRect MissionR;
    QRect MiniR;
    QRect SurvivalR;
    QRect SelectR[20];
    QRect CloseR;
    int Main_Select=0;
    int Main_Mod=0;
};




#endif // MAINWINDOW_H
