#ifndef EDITMAP_H
#define EDITMAP_H
#include"All.h"
#include <QPainter>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class EditMap;}
class MainWindow;
class EditMap : public QMainWindow
{
    Q_OBJECT
protected:
       void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
public:
    explicit EditMap(QWidget *parent = nullptr);
    ~EditMap();
    virtual void mousePressEvent(QMouseEvent *)Q_DECL_OVERRIDE;
    XY GetPos(int x,int y);
    QImage Image_Cut(QImage image);
private slots:
       void on_Finish_clicked();

       void on_Back_clicked();

       void on_checkBox_stateChanged(int arg1);

       void on_checkBox_2_stateChanged(int arg1);

private:

    QImage number[200];

    MainWindow *a;
    Ui::EditMap *ui;
    int Ctype=1;
    bool me=false;
    bool acc=true;
    int type[Edit_Max]={0};
    int skin[Edit_Max]={0};
    int hp[Edit_Max]={-1};
    XY pos[Edit_Max]={0,0},area[Edit_Max]={0,0};

    XY ppos;


    int e_hp[Edit_Max]={0};
    int e_speed[Edit_Max]={0};
    int e_bullet_speed[Edit_Max]={0};
    int e_skin[Edit_Max]={0};
    XY e_pos[Edit_Max]={0,0},e_area[Edit_Max]={0,0};
};

#endif // EDITMAP_H
