#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>

#define wysokosc 1000
#define szerokosc 1000
int temp=100;
int tryb = 0;
QVector<QPointF> punkty;


Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    im.fill(0);
    // dodawanie punktow
    punkty.push_back(QPointF(218,112));
    punkty.push_back(QPointF(106,112));
    punkty.push_back(QPointF(115,321));
    punkty.push_back(QPointF(241,466));
    punkty.push_back(QPointF(416,471));
    punkty.push_back(QPointF(478,354));
    punkty.push_back(QPointF(446,37));
    punkty.push_back(QPointF(335,199));
    punkty.push_back(QPointF(339,350));
    punkty.push_back(QPointF(218,350));
    for (int i=0; i<punkty.size(); i++)
    {
        drawPixel(punkty[i].x(), punkty[i].y(), 255, 255, 255);
    }
    scanline(punkty);

}

void Ekran::czysc()
{
    im.fill(0);
    update();
    punkty.clear();
}

void Ekran::scan_line()
{
    scanline(punkty);
    update();
}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
}

// zmienne przechowujace koordynaty 1 punktu
int startX=-1;
int startY=-1;

void Ekran::mousePressEvent(QMouseEvent *e)
{
    //dodawanie punktu do wektora punktow
    punkty.push_back(e->pos());
    //rysowanie punktu
    //drawPixel(e->x(), e->y(), 255, 255, 255);
    //qDebug() << e->pos();
    drawPixel(e->pos().x(), e->pos().y(), 255, 255, 255);
    update(); // odświeżanie okna
}

void Ekran::mouseMoveEvent(QMouseEvent *)
{
//    im=im_copy;
//    update();
}

