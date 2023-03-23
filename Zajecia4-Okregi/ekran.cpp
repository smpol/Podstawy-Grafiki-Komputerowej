#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>

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
    p.drawImage(0, 0, im);
}

// zmienne przechowujace koordynaty 1 punktu
int startX=0;
int startY=0;
bool elipsa=false;

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::RightButton) // czyszczenie całego ekranu gdy wcisniemy prawy przycisk
    {
        //im.fill(0);
        elipsa=true;

    }
    else if(e->button()==Qt::LeftButton)
    {
        elipsa=false;
    }
    startX=e->pos().x();
    startY=e->pos().y();
    im_copy=im;
    update(); // odświeżanie okna
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{

    im=im_copy;

    if (elipsa==true)
        drawElipse(startX, startY, e->pos().x(), e->pos().y());
    else
        drawCircle(startX, startY, e->pos().x(), e->pos().y());

    update();

}

