#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>

#define wysokosc 1000
#define szerokosc 1000
int temp=100;
//bool tryb=false;
int tryb = 0;

Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    im.fill(0);

    im_copy=QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    im_copy.fill(0);

}

void Ekran::wartosc(int n)
{
    qDebug("%d", n);
    temp=n;
}

void Ekran::czysc()
{
    im.fill(0);
    update();
}
void Ekran::tryb_kolo()
{
    tryb=0;
}
void Ekran::tryb_elipsa()
{
    tryb=1;
}
void Ekran::tryb_linia()
{
    tryb=2;
}
void Ekran::tryb_wiadro()
{
    tryb=3;
}


void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
}

// zmienne przechowujace koordynaty 1 punktu
int startX=0;
int startY=0;

void Ekran::mousePressEvent(QMouseEvent *e)
{
    startX=e->pos().x();
    startY=e->pos().y();
    if (tryb==3)
    {
        QRgb rgb = im.pixel(e->pos().x(), e->pos().y());
        flood_fill(e->pos().x(), e->pos().y(), wysokosc, szerokosc, rgb);
    }
    im_copy=im;
    update(); // odświeżanie okna
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{

    im=im_copy;

    if (tryb==1)
        drawElipse(startX, startY, e->pos().x(), e->pos().y(), temp);
    else if(tryb==0)
        drawCircle(startX, startY, e->pos().x(), e->pos().y());
    else if (tryb==2)
        drawLine(startX, startY, e->pos().x(), e->pos().y());


    update();

}

