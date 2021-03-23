#ifndef EDITMAP_H
#define EDITMAP_H
#include "All.h"
#include <QPainter>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include "Button.h"
namespace Ui
{
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
    virtual void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    QPoint GetPos(int x, int y);
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
    int Ctype = 1;
    bool me = false;
    bool acc = true;
    int type[Edit_Max] = {0};
    int skin[Edit_Max] = {0};
    int hp[Edit_Max] = {-1};
    QRect Rect[Edit_Max];

    QPoint ppos;
    int Me_HP, Me_MP, Me_WeaponLv, Me_B1C;

    int e_hp[Edit_Max] = {0};
    int e_speed[Edit_Max] = {0};
    int e_bullet_speed[Edit_Max] = {0};
    int e_skin[Edit_Max] = {0};
    QRect E_Rect[Edit_Max];
};

#endif // EDITMAP_H
