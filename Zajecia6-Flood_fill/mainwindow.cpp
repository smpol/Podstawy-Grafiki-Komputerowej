#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(co chcemy podlaczyc(np. przycisk), obsuga sygnalu, osbluga widgetu, SLOT(funkcja));
    connect(ui->suwak, SIGNAL(valueChanged(int)), ui->ekran, SLOT(wartosc(int)));
    connect(ui->b_czysc, SIGNAL(clicked(bool)), ui->ekran, SLOT(czysc()));
    connect(ui->radioElipsa, SIGNAL(toggled(bool)), ui->ekran, SLOT(tryb_elipsa()));
    connect(ui->radioKolo, SIGNAL(toggled(bool)), ui->ekran, SLOT(tryb_kolo()));
    connect(ui->suwak, SIGNAL(valueChanged(int)), this, SLOT(setWartosc(int)));
    connect(ui->radioLinia, SIGNAL(toggled(bool)), ui->ekran, SLOT(tryb_linia()));
    connect(ui->radioWiadro, SIGNAL(toggled(bool)), ui->ekran, SLOT(tryb_wiadro()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWartosc(int n)
{
    ui->wartosc->setText(QString("%0").arg(n));
}

