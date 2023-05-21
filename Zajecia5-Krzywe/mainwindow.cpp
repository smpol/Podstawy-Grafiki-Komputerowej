#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    connect(ui->b_czysc, SIGNAL(clicked(bool)), ui->ekran, SLOT(czysc()));
    connect(ui->ilosc_k, SIGNAL(textChanged(QString)), ui->ekran, SLOT(set_k_string(QString)));
    connect(ui->radioBezier, SIGNAL(toggled(bool)), ui->ekran, SLOT(setBezier()));
    connect(ui->radioBSpline, SIGNAL(toggled(bool)), ui->ekran, SLOT(setBSpline()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

