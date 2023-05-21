#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    connect(ui->alpha_poziom, SIGNAL(valueChanged(int)), ui->ekran, SLOT(alpha_set(int)));
    connect(ui->dylatacja_b, SIGNAL(clicked(bool)), ui->ekran, SLOT(dylatacja_przycisk()));
    connect(ui->erozja_b, SIGNAL(clicked(bool)), ui->ekran, SLOT(erozja_przycisk()));
    connect(ui->operacja3_b, SIGNAL(clicked(bool)), ui->ekran, SLOT(operacja3_przycisk()));
    connect(ui->operacja4_b, SIGNAL(clicked(bool)), ui->ekran, SLOT(operacja4_przycisk()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


