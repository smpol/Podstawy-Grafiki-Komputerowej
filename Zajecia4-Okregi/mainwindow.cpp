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

    //connect QSlider "suwak" to QTextEdit "ilosc"
    connect(ui->suwak, SIGNAL(valueChanged(int)), ui->ilosc, SLOT(setNum(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

