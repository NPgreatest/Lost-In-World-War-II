#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class BattleWindow;

class GLWidGet : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidGet(BattleWindow *battlewindow, QWidget *parent);
    ~GLWidGet() {}
public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    BattleWindow *battlewindow;
};

#endif // GLWIDGET_H
