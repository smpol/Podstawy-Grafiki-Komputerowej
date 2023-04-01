#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    connect(ui->b_czysc, SIGNAL(clicked(bool)), ui->ekran, SLOT(czysc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

