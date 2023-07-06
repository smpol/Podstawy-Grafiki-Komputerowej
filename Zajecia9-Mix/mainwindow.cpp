#include "mainwindow.h"
#include "ui_mainwindow.h"
//enum WARSTWA
//{
//    WARSTWA1,
//    WARSTWA2,
//    WARSTWA3
//};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    connect(ui->alpha_poziom, SIGNAL(valueChanged(int)), ui->ekran, SLOT(alpha_set(int)));

    connect (ui->normal_mix, SIGNAL(clicked(bool)), ui->ekran, SLOT(normal_set()));
    connect (ui->multiply_mix, SIGNAL(clicked(bool)), ui->ekran, SLOT(multiply_set()));
    connect (ui->screen_mix, SIGNAL(clicked(bool)), ui->ekran, SLOT(screen_set()));
    connect (ui->overlay_mix, SIGNAL(clicked(bool)), ui->ekran, SLOT(overlay_set()));
    connect (ui->darken_mix, SIGNAL(clicked(bool)), ui->ekran, SLOT(darken_set()));

    connect (ui->warstwa1_radio, SIGNAL(clicked(bool)), ui->ekran, SLOT(wybrana_warstwa1()));
    connect (ui->warstwa2_radio, SIGNAL(clicked(bool)), ui->ekran, SLOT(wybrana_warstwa2()));
    connect (ui->warstwa3_radio, SIGNAL(clicked(bool)), ui->ekran, SLOT(wybrana_warstwa3()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


