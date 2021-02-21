#ifndef PAINT_H
#define PAINT_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget{
Q_OBJECT
protected:
       void paintEvent(QPaintEvent *event)    Q_DECL_OVERRIDE;
public:
       explicit Widget(QWidget *parent=0);
       ~Widget();
private:
       Ui::Widget *ui;



};


#endif // PAINT_H
