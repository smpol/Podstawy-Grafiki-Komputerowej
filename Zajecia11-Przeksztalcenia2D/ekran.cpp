#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>

#define wysokosc 1000
#define szerokosc 1000
QVector<QPointF> punkty;
double mX=0.0;
double mY=0.0;
double sX=1.0;
double sY=1.0;
double shX=0.0;
double shY=0.0;
double obrot_value=0;
bool interpel=false;


Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    obraz_zrodlo = QImage(QString::fromStdString("/Users/michal/Documents/Qt/grafika komp/Zajecia11-Przeksztalcenia2D/img/mars.jpg"));
    im.fill(0);
}
void Ekran::update_draw()
{
    im.fill(0);
    przeksztalcenia2d(mX, mY, sX, sY, obrot_value, shX, shY, interpel);
    update();
}
void Ekran::moveX(int i)
{
    qDebug("wartość X %d", i);
    mX=i;
    update_draw();
}
void Ekran::moveY(int i)
{
    qDebug("wartość Y %d", i);
    mY=i;
    update_draw();
}
void Ekran::set_sX(int i)
{
    qDebug ("Wartosc sX %d", i);
    sX=(float)i/100;
    update_draw();
}
void Ekran::set_sY(int i)
{
    qDebug ("Wartosc sY %d", i);
    sY=(float)i/100;
    update_draw();
}
void Ekran::set_obrot(int i)
{
    qDebug ("Wartosc obrotu %d", i);
    obrot_value=i;
    update_draw();
}
void Ekran::set_shX(int i)
{
    qDebug ("Wartosc shX %d", i);
    shX=(float)i/100;
    update_draw();
}
void Ekran::set_shY(int i)
{
    qDebug ("Wartosc shY %d", i);
    shY=(float)i/100;
    update_draw();
}
void Ekran::interpelacja_set(bool i)
{
    if (i==true)
        interpel=true;
    else
        interpel=false;
    update_draw();
}
void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
    update_draw();
}

