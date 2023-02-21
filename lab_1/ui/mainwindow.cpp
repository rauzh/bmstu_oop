#include <cstdio>
#include <unistd.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tasks.h"
#include "figure.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, 1, 1);
}

MainWindow::~MainWindow()
{
    task_t cur_task;
    cur_task.action = FREE;
    DoTask(cur_task);

    delete ui;
}

result_t MainWindow::DrawScene(void)
{
    scene_t scene;
    scene.canvas = ui->graphicsView->scene();
    scene.width = ui->graphicsView->width();
    scene.height = ui->graphicsView->height();

    task_t cur_task;
    cur_task.action = DRAW;
    cur_task.scene = scene;

    result_t res_code = DoTask(cur_task);

    return res_code;
}

void MainWindow::on_LoadFigureButton_clicked()
{
    task_t cur_task;
    cur_task.action = LOAD;
    cur_task.filename = INPUT_FILE;

    result_t res_code = DoTask(cur_task);

    if (res_code != SUCCESS)
    {
        HandleError(res_code);
        return;
    }

    res_code = DrawScene();

    if (res_code != SUCCESS)
        HandleError(res_code);
}

void MainWindow::on_MoveButton_clicked()
{
    move_t coefs = InitMove(ui->DxField->value(), ui->DyField->value(), ui->DzField->value());

    task_t cur_task;
    cur_task.action = MOVE;
    cur_task.move_coefs = coefs;

    result_t res_code = DoTask(cur_task);

    if (res_code != SUCCESS)
    {
        HandleError(res_code);
        return;
    }

    res_code = DrawScene();

    if (res_code != SUCCESS)
        HandleError(res_code);
}

void MainWindow::on_ScaleButton_clicked()
{
    point_t center;
    center.x = ui->CSxField->value();
    center.y = ui->CSyField->value();
    center.z = ui->CSzField->value();

    scale_t coefs;
    coefs.kx = ui->KxField->value();
    coefs.ky = ui->KyField->value();
    coefs.kz = ui->KzField->value();

    task_t cur_task;
    cur_task.action = SCALE;
    cur_task.center = center;
    cur_task.scale_coefs = coefs;

    result_t res_code = DoTask(cur_task);

    if (res_code != SUCCESS)
    {
        HandleError(res_code);
        return;
    }

    res_code = DrawScene();

    if (res_code != SUCCESS)
        HandleError(res_code);
}

void MainWindow::on_RotateButton_clicked()
{
    point_t center;
    center.x = ui->CRxField->value();
    center.y = ui->CRyField->value();
    center.z = ui->CRzField->value();

    rotate_t coefs;
    coefs.ax = ui->AxField->value();
    coefs.ay = ui->AyField->value();
    coefs.az = ui->AzField->value();

    task_t cur_task;
    cur_task.action = ROTATE;
    cur_task.center = center;
    cur_task.rotate_coefs = coefs;

    result_t res_code = DoTask(cur_task);

    if (res_code != SUCCESS)
    {
        HandleError(res_code);
        return;
    }

    res_code = DrawScene();

    if (res_code != SUCCESS)
        HandleError(res_code);
}
