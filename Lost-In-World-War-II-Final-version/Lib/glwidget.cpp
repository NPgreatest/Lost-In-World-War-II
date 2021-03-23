#include "glwidget.h"
#include "BattleWindow.h"
GLWidGet::GLWidGet(BattleWindow *battlewindow, QWidget *parent)
    : QOpenGLWidget(parent), battlewindow(battlewindow)
{
    setFixedSize(1920, 1080);
    setAutoFillBackground(false);
}

void GLWidGet::animate()
{
    update();
}

void GLWidGet::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    battlewindow->paint(&painter, event);

    painter.end();

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_STENCIL_BUFFER_BIT);
}
