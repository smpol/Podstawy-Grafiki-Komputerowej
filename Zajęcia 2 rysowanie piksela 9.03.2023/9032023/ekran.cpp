#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>



Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (200, 100, QImage::Format_RGB32);
    im.fill(0);

//    im.width();
//    im.height();

    drawPixel(50, 20, 255, 180, 0);
    drawPixel(-50, 2000, 255, 180, 0);

//    int x = 50;
//    int y = 20;
//    uchar *pix = im.scanLine(y); // dostęp do piksela?
//    pix[4*x]=255; // blue
//    pix[4*x+1]=0; //green
//    pix[4*x+2]=255; //red
}

void Ekran::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::yellow);
    p.drawImage(0, 0, im);
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    qDebug("x %d y %d", e->pos().x(), e->pos().y()); //kordy maciek tepaj
    drawPixel(e->pos().x(), e->pos().y(), 255, 255, 255); // rysowanie
    update(); // odświeżanie okna
}
