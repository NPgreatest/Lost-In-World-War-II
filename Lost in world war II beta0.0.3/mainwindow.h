#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private slots:


    void on_test_clicked();

    void on_Map_clicked();

    void on_AboutAuthor_clicked();

    void on_Exit_clicked();

    void on_button2_clicked();

    void on_button1_clicked();

private:
    Ui::MainWindow *ui;
    BattleWindow *Battle;
    EditMap *Map;
};




#endif // MAINWINDOW_H
