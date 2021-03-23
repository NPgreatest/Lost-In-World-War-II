#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPainter>
#include <QIcon>
#include <QMainWindow>
#include <QMouseEvent>

#include <QMediaPlayer>
#include <QRect>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "BattleWindow.h"
#include "EditMap.h"
#include "Button.h"
#include "Partical.h"
#include "Client.h"
#include "Email.h"
#include "Setting.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Me_Appear();
    void PlayTap();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private slots:
    void flash();
    void Tick();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_Back_clicked()
    {
        Main_Mod = 0;
        this->Me_Appear();
    }

    void on_Story_clicked();

    void on_Battle_clicked();

    void Tap_Fun() { PlayTap(); }

    void on_pushButton_8_clicked();

    void Me_Vanish();

    void Setting_Appear();

    void on_pushButton_7_clicked();

private:
    QMediaPlayer *p = new QMediaPlayer;
    QMediaPlayer s[Edit_Min];
    Ui::MainWindow *ui;
    BattleWindow *Battle;
    Client *client;
    Email *email;
    EditMap *Map;
    Setting *setting;

    QImage Partical1[10];
    QImage Partical2[10];
    QImage Partical3[10];

    Settings settings;

    QGraphicsOpacityEffect *trans[100];
    QPropertyAnimation *audio[100];

    Partical partical[Edit_Max];

    QTimer Flash;

    int Main_Select = 0;
    int Main_Mod = 0;
    int x = 1;
    int Times = 0;
    int Seed();
    void CreatePartical(QRect Rect, Type type);
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
};

#endif // MAINWINDOW_H
