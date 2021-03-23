#ifndef SETTING_H
#define SETTING_H
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QIcon>
#include <QVector>
#include <QPainter>
#include <QIcon>
#include <QMainWindow>
#include <QMouseEvent>
#include <QDir>
#include <QMediaPlayer>
#include <QRect>
#include <QTimer>
#include <QFileDialog>
#include "Button.h"
#include "All.h"
#include "AllMusic.h"
namespace Ui
{
    class Setting;
}
class MainWindow;
class Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_mode_currentIndexChanged(int index);

    void on_difficult_currentIndexChanged(int index);

    void on_MainSlide_sliderMoved(int position);

    void on_SoundSlide_sliderMoved(int position);

    void Label_Tick();

    void on_SChange_clicked();

    void on_WChange_clicked();

    void on_AChange_clicked();

    void on_DChange_clicked();

    void on_ShiftChange_clicked();

    void on_SpaceChange_clicked();

    void on_LChange_clicked();

    void on_pushButton_3_clicked();

    void Me_Close();

    void on_MainSlide_valueChanged(int value);

    void on_SoundSlide_valueChanged(int value);

private:
    Ui::Setting *ui;
    MainWindow *mainwindow;
    QGraphicsOpacityEffect *trans[100];
    QPropertyAnimation *audio[100];

    QTimer tick;

    AllMusic allmusic;

    QVector<QString> key;
    Settings settings;

    int chose = 0;
    void Me_Vanish();

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
};

#endif // SETTING_H
