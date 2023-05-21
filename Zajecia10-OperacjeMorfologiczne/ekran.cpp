#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>

#define wysokosc 550
#define szerokosc 550

int wybrana_wartstwa=1;
int alpha=100;

bool started=false;

Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{


    im=QImage(550, 550, QImage::Format_RGB32);
    im_kolor=QImage(550,550, QImage::Format_RGB32);
    im_blackwhite_oryginal=QImage(550,550, QImage::Format_RGB32);

    im.fill(0);
    im_kolor.load("/Users/michal/Documents/Qt/grafika komp/Zajecia10-OperacjeMorfologiczne/Resources/wydzial.jpeg");
    //update();

    color_to_blackwhite();
    

    //normal_mode();

    update();
}


void Ekran::alpha_set(int i)
{
    promien=i;
    qDebug("%d", i);
}

void Ekran::dylatacja_przycisk()
{
    dylatacja(promien);
    copy_warstwa();
    update();
}

void Ekran::erozja_przycisk()
{
    erozja(promien);
    copy_warstwa();
    update();
}

void Ekran::operacja3_przycisk()
{
    dylatacja(promien);
    copy_warstwa();
    erozja(promien);
    copy_warstwa();
    update();
}

void Ekran::operacja4_przycisk()
{
    erozja(promien);
    copy_warstwa();
    dylatacja(promien);
    copy_warstwa();
    update();
}


void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
}


void Ekran::mousePressEvent(QMouseEvent *)
{

}

void Ekran::mouseMoveEvent(QMouseEvent *)
{

}

