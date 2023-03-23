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
    tablica_zapisanych_lini();
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
bool clear=false; // zmienna pomocnicza ktora przechowuje informacje czy kliknalem prawy przycisk myszy aby usunac całą plansze czy nie

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::RightButton)
    {
        for (int i=0; i<wysokosc; i++)
        {
            for (int j=0; j<szerokosc; j++)
            {
                drawPixel(i, j, 2);
            }
        }
        clear=true;
    }
    startX=e->pos().x();
    startY=e->pos().y();

    update(); // odświeżanie okna
}

int tempx=0;
int tempy=0;

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    // sprawdzamy tutaj czy została przesunieta linia podczas przesuwania myszką

    // jeżeli tak to usuwamy poprzednią linie i rysujemy nową
    if ((tempx!=e->pos().x()) || tempy!=e->pos().y())
    {
        drawLine(startX, startY, tempx, tempy, 1);
        tempx=e->pos().x();
        tempy=e->pos().y();
        drawLine(startX, startY, e->pos().x(), e->pos().y(), 0);
    }
    // jeżeli nie to linia ciągle będzie narysowana
    else
    {
        drawLine(startX, startY, e->pos().x(), e->pos().y(), 0);
    }
    update();

}

void Ekran::mouseReleaseEvent(QMouseEvent *e)
{
    // sprawdzamy czy uzyliśmy prawego klawisza myszy do czyszczenia ekranu czy nie
    // dzieki temu niweluje blad, ze podczas klikania prawego przycisku myszy zawsze rysowal sie 1 piksel
    if (clear==true)
        clear=false;
    else
        drawLine(startX, startY, e->pos().x(), e->pos().y(), 2);

    update();
}
