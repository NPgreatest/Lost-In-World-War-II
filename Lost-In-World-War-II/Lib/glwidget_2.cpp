#include "glwidget_2.h"

#include"Client.h"

GLWidGet_2::GLWidGet_2(Client *client, QWidget *parent)
    : QOpenGLWidget(parent), client(client)
{
    setFixedSize(1920, 1080);
    setAutoFillBackground(false);


}

void GLWidGet_2::animate()
{
    update();
}


void GLWidGet_2::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    client->paint(&painter, event);

    painter.end();

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_STENCIL_BUFFER_BIT);
}
