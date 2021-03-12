#ifndef EMAIL_H
#define EMAIL_H
#include <QIcon>
#include <QMainWindow>
#include"Button.h"

namespace Ui {
class Email;
}

class Email : public QMainWindow
{
    Q_OBJECT

public:
    explicit Email(QWidget *parent = nullptr);
    ~Email();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Email *ui;
};

#endif // EMAIL_H
