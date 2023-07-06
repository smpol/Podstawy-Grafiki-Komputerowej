#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    //connect(ui->b_czysc, SIGNAL(clicked(bool)), ui->ekran, SLOT(czysc()));
    //connect(ui->b_wypelnij, SIGNAL(clicked(bool)), ui->ekran, SLOT(scan_line()));
    //connect(ui->x_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(moxe_x(int)));
    connect(ui->x_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(moveX(int)));
    connect(ui->y_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(moveY(int)));
    connect(ui->sx_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_sX(int)));
    connect(ui->sy_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_sY(int)));
    connect(ui->obrot_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_obrot(int)));
    connect(ui->inter_check, SIGNAL(toggled(bool)), ui->ekran, SLOT(interpelacja_set(bool)));
    connect(ui->shx_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_shX(int)));
    connect(ui->shy_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_shY(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


