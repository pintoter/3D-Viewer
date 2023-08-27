#include "mainwindow.h"
#include "myopenglwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
    timer = new QTimer;
    gifImage = new QImage[50]{};
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
}

MainWindow::~MainWindow()
{
    saveSettings();
    s21_remove_object(&ui->visualWidget->inputObject);
    s21_remove_object(&ui->visualWidget->startObject);
    delete timer;
    delete[] gifImage;
    delete ui;
}

void MainWindow::on_selectPointColor_clicked()
{
    ui->visualWidget->pointColor = QColorDialog::getColor(Qt::white, this, tr("Выберите цвет точек"));
    ui->visualWidget->update();
}


void MainWindow::on_selectLineColor_clicked()
{
    ui->visualWidget->lineColor = QColorDialog::getColor(Qt::white, this, tr("Выберите цвет линий"));
    ui->visualWidget->update();
}


void MainWindow::on_selectBackgroundColor_clicked()
{
    ui->visualWidget->backgroundColor = QColorDialog::getColor(Qt::white, this, tr("Выберите цвет фона"));
    ui->visualWidget->update();
}



void MainWindow::on_radioButtonParallel_clicked()
{
    ui->visualWidget->projectionMode = 0;
    ui->visualWidget->update();
}


void MainWindow::on_radioButtonCentral_clicked()
{
    ui->visualWidget->projectionMode = 1;
    ui->visualWidget->update();
}


void MainWindow::on_comboBoxPointType_currentIndexChanged(int index)
{
    ui->visualWidget->pointMode = index;
    ui->visualWidget->update();
}


void MainWindow::on_comboBoxLineType_currentIndexChanged(int index)
{
    ui->visualWidget->lineMode = index;
    ui->visualWidget->update();
}

void MainWindow::on_pushButton_x_move_clicked()
{
    s21_move_x(&ui->visualWidget->inputObject, ui->x_move_in->value()/100);
    ui->visualWidget->update();
}


void MainWindow::on_pushButton_y_move_clicked()
{
    s21_move_y(&ui->visualWidget->inputObject, ui->y_move_in->value()/100);
    ui->visualWidget->update();
}



void MainWindow::on_pushButton_z_move_clicked()
{
    s21_move_z(&ui->visualWidget->inputObject, ui->z_move_in->value()/100);
    ui->visualWidget->update();
}

void MainWindow::on_pushButton_x_rotate_clicked()
{
    s21_rotate_x(&ui->visualWidget->inputObject, ui->x_rotate_in->value());
    ui->visualWidget->update();
}


void MainWindow::on_pushButton_y_rotate_clicked()
{
    s21_rotate_y(&ui->visualWidget->inputObject, ui->y_rotate_in->value());
    ui->visualWidget->update();
}


void MainWindow::on_pushButton_z_rotate_clicked()
{
    s21_rotate_z(&ui->visualWidget->inputObject, ui->z_rotate_in->value());
    ui->visualWidget->update();
}


void MainWindow::on_button_return_obj_clicked()
{
    ui->scale_in->setValue(5);
    s21_copy_matrix(&ui->visualWidget->startObject.matrix, &ui->visualWidget->inputObject.matrix);
    ui->visualWidget->update();
}


void MainWindow::on_scale_in_valueChanged(int value)
{

    s21_scale(&ui->visualWidget->inputObject, value, ui->visualWidget->prev_scale);
    ui->visualWidget->prev_scale = value;
    ui->visualWidget->update();
}


void MainWindow::on_open_file_clicked()
{
    object_t startObject, inputObject;
    QString path = QFileDialog::getOpenFileName(this, tr("Select object file"), "/Users", "Objects File (*.obj)");

    QByteArray ba = path.toLocal8Bit();
    char* path_file = ba.data();

    int err = 0;

    if (!path.isEmpty())
    {
        err = s21_loader(path_file, &startObject);
        err = s21_loader(path_file, &inputObject);
    if (err != 0) {
        QString errorMessage = "Произошла ошибка!";
        QMessageBox::critical(nullptr, "Ошибка", errorMessage);
        s21_remove_object(&startObject);
        s21_remove_object(&inputObject);
    }
    else {
        setDefSettings();
        ui->visualWidget->startObject = startObject;
        ui->visualWidget->inputObject = inputObject;
        s21_geometric_rotations(&startObject);
        s21_geometric_rotations(&inputObject);
        ui->labelName->setText(ui->visualWidget->inputObject.name);
        ui->labelVertexes->setText(QString::number(ui->visualWidget->inputObject.count_vertexes));
        ui->labelFacets->setText(QString::number(ui->visualWidget->inputObject.count_facets));
    }
    }
}

void MainWindow::setDefSettings()
{
    ui->x_move_in->setValue(0);
    ui->y_move_in->setValue(0);
    ui->z_move_in->setValue(0);
    ui->x_rotate_in->setValue(0);
    ui->y_rotate_in->setValue(0);
    ui->z_rotate_in->setValue(0);
    ui->scale_in->setValue(5);
}


void MainWindow::saveSettings()
{
    QSettings settings("MyApplication", "3DViewer");

    settings.beginGroup("projection");
    settings.setValue("type", ui->visualWidget->projectionMode);
    settings.endGroup();

    settings.beginGroup("lineSet");
    settings.setValue("mode", ui->comboBoxLineType->currentIndex());
    settings.setValue("color", ui->visualWidget->lineColor);
    settings.setValue("size", ui->lineSize_input->value());
    settings.endGroup();

    settings.beginGroup("verticies");
    settings.setValue("mode", ui->comboBoxPointType->currentIndex());
    settings.setValue("color", ui->visualWidget->pointColor);
    settings.setValue("size", ui->pointSize_input->value());
    settings.endGroup();

    settings.beginGroup("background");
    settings.setValue("color", ui->visualWidget->backgroundColor);
    settings.endGroup();
}

void MainWindow::loadSettings()
{
    QSettings settings("MyApplication", "3DViewer");

    settings.beginGroup("projection");
    if ((ui->visualWidget->projectionMode = settings.value("type").toInt()) == 0) {
    ui->radioButtonParallel->setChecked(true);
    }
    else
    ui->radioButtonCentral->setChecked(true);
    settings.endGroup();

    settings.beginGroup("lineSet");
    ui->visualWidget->lineMode = settings.value("mode").toInt();
    ui->comboBoxLineType->setCurrentIndex(settings.value("mode").toInt());
        if (settings.value("color").toString().length() > 0) {
            ui->visualWidget->lineColor = settings.value("color").toString();
        }
        ui->lineSize_input->setValue(settings.value("size").toInt());
        settings.endGroup();

        settings.beginGroup("verticies");
        ui->visualWidget->pointMode = settings.value("mode").toInt();
        ui->comboBoxPointType->setCurrentIndex(settings.value("mode").toInt());
        ui->visualWidget->pointColor = settings.value("color").toString();
        ui->pointSize_input->setValue(settings.value("size").toInt());
        settings.endGroup();

        settings.beginGroup("background");
        if (settings.value("color").toString().length() > 0) {
            ui->visualWidget->backgroundColor = settings.value("color").toString();
        }
        settings.endGroup();
}


void MainWindow::on_pointSize_input_valueChanged(double arg1)
{
    ui->visualWidget->pointSize = arg1;
    ui->visualWidget->update();
}

void MainWindow::on_lineSize_input_valueChanged(double arg1)
{
    ui->visualWidget->lineSize = arg1;
    ui->visualWidget->update();
}


void MainWindow::on_pushButton_screen_clicked()
{
    QFileDialog dialogPhoto(this);
    QString name = ui->labelName->text();
    QDateTime dateTime = dateTime.currentDateTime();
    QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss_");
    if (ui->labelName->text().isEmpty())
        name = "None";
    else
        name.chop(4);
    QString name_photo = dialogPhoto.getSaveFileName(
        this, "Save as...", "Screenshot_" + currentDateTime + name,
        "BMP (*.bmp);; JPEG (*.jpeg)");
    ui->visualWidget->grabFramebuffer().save(name_photo);
}

void MainWindow::on_pushButton_gif_clicked()
{
    ui->pushButton_gif->setEnabled(false);
    timer->start(100);
}

void MainWindow::slotTimer() {
    if (gifTime < 50) {
        gifImage[gifTime] = ui->visualWidget->grabFramebuffer();
        ++gifTime;
    } else {
        gif = new QGifImage();
        for (int i = 0; i < gifTime; ++i) {
        gif->addFrame(gifImage[i].scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), 0);
        }
        QString name = ui->labelName->text();
        QDateTime dateTime = dateTime.currentDateTime();
        QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss_");
        if (ui->labelName->text().isEmpty())
            name = "None";
        else
            name.chop(4);
        QString fileName = QFileDialog::getSaveFileName(
            this, "Save GIF", "GIF_" + currentDateTime + name, "GIF (*.gif)");
        gif->save(fileName);
        ui->pushButton_gif->setEnabled(true);
        timer->stop();
        delete gif;
        gifTime = 0;
    }
}


void MainWindow::on_pushButton_all_move_clicked()
{
    s21_move_x(&ui->visualWidget->inputObject, ui->x_move_in->value()/100);
    s21_move_y(&ui->visualWidget->inputObject, ui->y_move_in->value()/100);
    s21_move_z(&ui->visualWidget->inputObject, ui->z_move_in->value()/100);
    ui->visualWidget->update();
}


void MainWindow::on_pushButton_all_rotate_clicked()
{
    s21_rotate_x(&ui->visualWidget->inputObject, ui->x_rotate_in->value());
    s21_rotate_y(&ui->visualWidget->inputObject, ui->y_rotate_in->value());
    s21_rotate_z(&ui->visualWidget->inputObject, ui->z_rotate_in->value());
    ui->visualWidget->update();
}
