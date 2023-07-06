#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    connect(ui->obraz1_radio, SIGNAL(clicked(bool)), ui->ekran, SLOT(zmianaObrazka1()));
    connect(ui->obraz2_radio, SIGNAL(clicked(bool)), ui->ekran, SLOT(zmianaObrazka2()));
    connect(ui->postep_slider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(zmiana_suwak(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


