#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myopenglwidget.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void on_check_points_stateChanged(int arg1);
    void on_selectPointColor_clicked();
    void on_selectBackgroundColor_clicked();
    void on_selectLineColor_clicked();
    void on_radioButtonParallel_clicked();
    void on_radioButtonCentral_clicked();
    void on_comboBoxPointType_currentIndexChanged(int index);
    void on_comboBoxLineType_currentIndexChanged(int index);
    void on_pushButton_x_move_clicked();
    void on_pushButton_y_move_clicked();
    void on_pushButton_z_move_clicked();
    void on_pushButton_x_rotate_clicked();
    void on_pushButton_y_rotate_clicked();
    void on_pushButton_z_rotate_clicked();
    void on_button_return_obj_clicked();
    void on_scale_in_valueChanged(int value);
    void on_open_file_clicked();
    void on_pointSize_input_valueChanged(double arg1);
    void on_lineSize_input_valueChanged(double arg1);

    void on_pushButton_screen_clicked();

    void on_pushButton_gif_clicked();
    void slotTimer();

    void on_pushButton_all_move_clicked();

    void on_pushButton_all_rotate_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QGifImage *gif;
    QImage *gifImage;
    int gifTime = 0;
    void saveSettings();
    void loadSettings();
    void setDefSettings();
};

#endif // MAINWINDOW_H
