#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>

#define WYSOKOSC 600
#define SZEROKOSC 900

int wybrany_obraz = 1;
int stopien = 0;

Ekran::Ekran(QWidget *parent) : QWidget{parent}
{

    im = QImage(WYSOKOSC, SZEROKOSC, QImage::Format_RGB32);
    obraz = QImage(WYSOKOSC, SZEROKOSC, QImage::Format_RGB32);
    obraz1 = QImage(WYSOKOSC, SZEROKOSC, QImage::Format_RGB32);
    obraz2 = QImage(WYSOKOSC, SZEROKOSC, QImage::Format_RGB32);

    im.fill(0);
    obraz.load("/Users/michal/Documents/Qt/grafika komp/Zajecia13-Morphing/img/pan.jpeg");
    obraz1.load("/Users/michal/Documents/Qt/grafika komp/Zajecia13-Morphing/img/pan.jpeg");
    obraz2.load("/Users/michal/Documents/Qt/grafika komp/Zajecia13-Morphing/img/mars.jpg");

    update();
}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, obraz);
    p.drawImage((SZEROKOSC / 2), 0, im);
}

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (e->pos().x() < SZEROKOSC / 2)
        {
            if (wybrany_obraz == 1)
            {
                if (obraz_1.size() < 3)
                {
                    obraz_1.push_back(e->pos());
                }
            }
            else
            {
                if (obraz_2.size() < 3)
                {
                    obraz_2.push_back(e->pos());
                }
            }
        }
    }
    updateObrazka();
}

void Ekran::updateObrazka()
{
    if (wybrany_obraz == 1)
    {
        obraz = obraz1;
        for (int i = 0; i < obraz_1.size(); i++)
        {
            drawPixel(obraz_1[i].x(), obraz_1[i].y(), 255, 0, 0, OBRAZ_PODLGLAD);
        }
    }
    else
    {
        obraz = obraz2;
        for (int i = 0; i < obraz_2.size(); i++)
        {
            drawPixel(obraz_2[i].x(), obraz_2[i].y(), 255, 0, 0, OBRAZ_PODLGLAD);
        }
    }
    if (obraz_1.size() == 3 && wybrany_obraz == 1)
    {
        for (int i = 0; i < 3; i++)
        {
            drawLine(obraz_1[i].x(), obraz_1[i].y(), obraz_1[(i + 1) % 3].x(), obraz_1[(i + 1) % 3].y());
        }
    }
    if (obraz_2.size() == 3 && wybrany_obraz == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            drawLine(obraz_2[i].x(), obraz_2[i].y(), obraz_2[(i + 1) % 3].x(), obraz_2[(i + 1) % 3].y());
        }
    }
    if (obraz_1.size()==3 && obraz_2.size()==3)
    {
        punkty(stopien);
        morphing(stopien);
    }
    update();
}

void Ekran::zmianaObrazka1()
{
     qDebug("Obrazek1");
    obraz=obraz1;
    wybrany_obraz = 1;
    updateObrazka();
}

void Ekran::zmianaObrazka2()
{
    qDebug("Obrazek2");
    wybrany_obraz = 2;
    obraz=obraz2;
    updateObrazka();
}

void Ekran::mouseMoveEvent(QMouseEvent *)
{

}

void Ekran::zmiana_suwak(int i)
{
    stopien = i;
    qDebug("%d", stopien);
    updateObrazka();
}
