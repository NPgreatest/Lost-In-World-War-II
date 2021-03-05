#ifndef GLWIDGET_2_H
#define GLWIDGET_2_H

#include <QOpenGLWidget>
#include<QOpenGLFunctions>

class Client;

class GLWidGet_2: public QOpenGLWidget
{
    Q_OBJECT

public:

    GLWidGet_2(Client *client, QWidget *parent);

public slots:

    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Client *client;

};

#endif // GLWIDGET_2_H
