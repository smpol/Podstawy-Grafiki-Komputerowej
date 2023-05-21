#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>

#define wysokosc 550
#define szerokosc 550

Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    im.fill(0);
}

void Ekran::red_rgb(int i)
{
    red=i;
    qDebug("red %d", red);
    barwy_skrocone(RGB_R);
    update();
}
void Ekran::green_rgb(int i)
{
    green = i;
    qDebug("green %d", green);
    barwy_skrocone(RGB_G);
    update();
}
void Ekran::blue_rgb(int i)
{
    blue=i;
    qDebug("blue %d", blue);
    barwy_skrocone(RGB_B);
    update();
}
void Ekran::hue_hsv(int i)
{
    hue=i;
    qDebug("hue %d", hue);
    barwy_skrocone(HSV_H);
    update();

}
void Ekran::saturation_hsv(int i)
{
    saturation=i;
    qDebug("saturation %d", saturation);
    barwy_skrocone(HSV_S);
    update();
}
void Ekran::value_hsv(int i)
{
    value=i;
    qDebug("value %d", value);
    barwy_skrocone(HSV_V);
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

