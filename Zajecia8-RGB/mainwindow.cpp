#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
//    connect(ui->b_czysc, SIGNAL(clicked(bool)), ui->ekran, SLOT(czysc()));
//    connect(ui->b_wypelnij, SIGNAL(clicked(bool)), ui->ekran, SLOT(scan_line()));
   connect(ui->red_rgb, SIGNAL(valueChanged(int)), ui->ekran, SLOT(red_rgb(int)));
   connect(ui->green_rgb, SIGNAL(valueChanged(int)), ui->ekran, SLOT(green_rgb(int)));
   connect(ui->blue_rgb, SIGNAL(valueChanged(int)), ui->ekran, SLOT(blue_rgb(int)));
   connect(ui->hue_hsv, SIGNAL(valueChanged(int)), ui->ekran, SLOT(hue_hsv(int)));
   connect(ui->saturation_hsv, SIGNAL(valueChanged(int)), ui->ekran, SLOT(saturation_hsv(int)));
   connect(ui->value_hsv, SIGNAL(valueChanged(int)), ui->ekran, SLOT(value_hsv(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


