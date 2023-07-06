#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    connect(ui->reset_button, SIGNAL(clicked(bool)), ui->ekran, SLOT(reset()));
    connect(ui->interpolacja_button, SIGNAL(clicked(bool)), ui->ekran, SLOT(interpolacja_change()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


