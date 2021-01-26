#ifndef EDITMAP_H
#define EDITMAP_H
#include"All.h"
#include <QPainter>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class EditMap;
}
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
private slots:
       void on_Finish_clicked();

       void on_Back_clicked();

       void on_checkBox_stateChanged(int arg1);

private:
    MainWindow *a;
    Ui::EditMap *ui;
    int Ctype=1;
    bool me=false;
    bool acc=true;
    int type[200]={0};
    XY pos[200]={0,0},area[200]={0,0};
    XY ppos;

};

#endif // EDITMAP_H
