#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>



Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (1000, 1000, QImage::Format_RGB32);
    im.fill(0);
}

void Ekran::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::yellow);
    p.drawImage(0, 0, im);
}

int startX=0;
int startY=0;
bool czy_postawiono=false;

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (czy_postawiono==false)
    {
        startX=e->pos().x();
        startY=e->pos().y();
        drawPixel(startX, startY);
        czy_postawiono=true;
    }
    else if (czy_postawiono==true)
    {
        drawLine(startX, startY, e->pos().x(), e->pos().y());
        //update();
        czy_postawiono=false;
        //czy_postawiono=false;
    }
    //qDebug("x %d y %d", e->pos().x(), e->pos().y()); //kordynaty
    qDebug("x1 %d y1 %d\n x2 %d y2 %d\n", startX, startY, e->pos().x(), e->pos().y());
    //drawPixel(e->pos().x(), e->pos().y(), 255, 255, 255); // rysowanie


    update(); // odświeżanie okna
}
