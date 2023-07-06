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
    connect(ui->z_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(moveZ(int)));
    connect(ui->sx_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_sX(int)));
    connect(ui->sy_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_sY(int)));
    connect(ui->sz_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_sZ(int)));
    connect(ui->obrot_sliderX, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_obrotX(int)));
    connect(ui->obrot_sliderY, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_obrotY(int)));
    connect(ui->obrot_sliderZ, SIGNAL(valueChanged(int)), ui->ekran, SLOT(set_obrotZ(int)));
    connect(ui->ukryj_check, SIGNAL(toggled(bool)), ui->ekran, SLOT(ukrywanie_scian(bool)));
    connect(ui->texture_check, SIGNAL(toggled(bool)), ui->ekran, SLOT(teksturowanie(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


