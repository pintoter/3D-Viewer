#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget { parent }
{
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST); // устанавливает режим проверки глубины пикселей
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0, (GLint)w, (GLint)h);
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
                 backgroundColor.blueF(), backgroundColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    setupProjection();

    glMatrixMode(GL_MODELVIEW);  // Инициализация матрицы модели
    glLoadIdentity();  // Сброс матрицы вида модели

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    drawAxis();
    if (pointMode != 0)
        pointDrawing();
    lineDrawing();
}

void MyOpenGLWidget::setupProjection() {
    if (inputObject.max_value_coordinate < 1) {
        inputObject.max_value_coordinate = 2;
    }
    GLdouble zNear = 0.001;  // Ближнее расстояние отсечения
    GLdouble zFar = inputObject.max_value_coordinate * 5;  // Дальнее расстояние отсечения

    if (projectionMode) {  // Central/Perspective projection

        GLdouble fovY = 60;  // Поле зрения в градусах по оси y
        GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
        GLdouble fW = fH;

        glFrustum(-fW, fW, -fH, fH, zNear,
                  zFar); // Устанавливает усеченный конус в режим перспективы
        glTranslatef(0, 0, -2);
    } else { // Parallel/Orthographic projection
        glOrtho(-1, 1, -1, 1, -3, zFar);
    }
}

void MyOpenGLWidget::drawAxis()
{
    glLineWidth(1.0f); // устанавливаю ширину линии приближённо в пикселях
    // Рисуем оси координат
    glBegin(GL_LINES);
    // Ось X - красный цвет
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    // Ось Y - зеленый цвет
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    // Ось Z - синий цвет
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -0.5f);
    glVertex3f(0.0f, 0.0f, 0.5f);
    glEnd();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *mo)
{
    mPos = mo->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *mo)
{
    xRot = 5 / M_PI * (mo->pos().y() - mPos.y());
    yRot = 5 / M_PI * (mo->pos().x() - mPos.x());
    update();
}

void MyOpenGLWidget::pointDrawing() {
        glColor3d(pointColor.redF(), pointColor.greenF(), pointColor.blueF());
        glPointSize(pointSize);
        if (pointMode == 1) {
            glEnable(GL_POINT_SMOOTH);
        }
        glBegin(GL_POINTS);
        for (int i = 0; i < inputObject.count_facets; i++) {
            int j = 0;
            int row = 0;
                for (j = 0; j < inputObject.polygon[i].count_vertex_of_facets; j++) {
                    row = inputObject.polygon[i].vertexes_list[j];
                    glVertex3f(inputObject.matrix.matrix[row - 1][Ox],
                               inputObject.matrix.matrix[row - 1][Oy],
                               inputObject.matrix.matrix[row - 1][Oz]);
                }
        }
        glEnd();
        if (pointMode == 1) {
            glDisable(GL_POINT_SMOOTH);
        }
}

void MyOpenGLWidget::lineDrawing() {
    glEnable(GL_LINE_SMOOTH);
    glColor3d(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
    glLineWidth(lineSize);
    if (lineMode == 1) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
    }
    for (int i = 0; i < inputObject.count_facets; i++) {
        int j = 0;
        int row = 0;
        glBegin(GL_LINE_LOOP);
        for (j = 0; j < inputObject.polygon[i].count_vertex_of_facets; j++) {
            row = inputObject.polygon[i].vertexes_list[j];
            glVertex3f(inputObject.matrix.matrix[row-1][Ox],
                               inputObject.matrix.matrix[row-1][Oy],
                               inputObject.matrix.matrix[row-1][Oz]);
        }
        glEnd();
    }
    if (lineMode == 1) {
        glDisable(GL_LINE_STIPPLE);
    }
    glDisable(GL_LINE_SMOOTH);
}
