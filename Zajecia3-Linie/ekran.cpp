#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>

#define wysokosc 1000
#define szerokosc 1000

Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    im.fill(0);

    im_copy=QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    im_copy.fill(0);
}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //p.fillRect(0, 0, width(), height(), Qt::yellow);
    p.drawImage(0, 0, im);
}

// zmienne przechowujace koordynaty 1 punktu
int startX=0;
int startY=0;
//bool clear=false; // zmienna pomocnicza ktora przechowuje informacje czy kliknalem prawy przycisk myszy aby usunac całą plansze czy nie

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::RightButton) // czyszczenie całego ekranu gdy wcisniemy prawy przycisk
    {
        im.fill(0);
    }
    startX=e->pos().x();
    startY=e->pos().y();
    im_copy=im;
    update(); // odświeżanie okna
}

int tempx=-1;
int tempy=-1;

void Ekran::mouseMoveEvent(QMouseEvent *e)
{

    im=im_copy;
    // sprawdzamy tutaj czy została przesunieta linia podczas przesuwania myszką

    // jeżeli tak to usuwamy poprzednią linie i rysujemy nową
    if ((tempx!=e->pos().x()) || tempy!=e->pos().y())
    {
        //drawLine(startX, startY, tempx, tempy, 1);
        tempx=e->pos().x();
        tempy=e->pos().y();
        drawLine(startX, startY, e->pos().x(), e->pos().y());
    }
    // jeżeli nie to linia ciągle będzie narysowana
    else
    {
        drawLine(startX, startY, e->pos().x(), e->pos().y());
    }
    update();

}

