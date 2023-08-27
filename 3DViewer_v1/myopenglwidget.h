#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QColor>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <QOpenGLFunctions>

#ifdef __cplusplus
extern "C"
{
#endif
#include "../include/s21_3DViewer_v1.h"
#ifdef __cplusplus
}
#endif

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);

    object_t inputObject;
    object_t startObject;

    int projectionMode = 0;

    QColor backgroundColor = Qt::black;
    QColor lineColor = Qt::white;
    QColor pointColor = Qt::white;

    int pointMode = 0;
    int lineMode = 0;

    int pointSize = 1;
    int lineSize = 1;

    int prev_scale = 5;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    double xRot, yRot, zRot;
    QPoint mPos;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    char* path;
    void setupProjection();
    void drawAxis();
    void pointDrawing();
    void lineDrawing();

};

#endif // MYOPENGLWIDGET_H
