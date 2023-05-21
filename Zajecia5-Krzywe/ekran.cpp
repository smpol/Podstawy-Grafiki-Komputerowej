#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>

#define wysokosc 1000
#define szerokosc 1000
int temp = 100;
int liczba_k=5000;
bool bspline = false;

QVector<QPointF> points;

void Ekran::setBezier()
{
    bspline=false;
    im.fill(0);
    for (int i = 0; i < points.size(); i++)
    {
        drawPixel(points[i].x(), points[i].y());
    }
    if (points.size() >= 4)
    {
        if (bspline)
            drawBSpline(points, liczba_k);
        else
            drawBezier(points, liczba_k);
    }
    update();
}

void Ekran::setBSpline()
{
    bspline = true;
    im.fill(0);
    for (int i = 0; i < points.size(); i++)
    {
        drawPixel(points[i].x(), points[i].y());
    }
    if (points.size() >= 4)
    {
        if (bspline)
            drawBSpline(points, liczba_k);
        else
            drawBezier(points, liczba_k);
    }
    update();
}

Ekran::Ekran(QWidget *parent) : QWidget{parent}
{
    im = QImage(szerokosc, wysokosc, QImage::Format_RGB32);
    im.fill(0);

    //    im_copy = QImage(szerokosc, wysokosc, QImage::Format_RGB32);
    //    im_copy.fill(0);
}

void Ekran::set_k_string(QString n)
{
    bool ok; // nie wiem po co to jest ale musi być
    liczba_k=n.toInt(&ok, 10);
    qDebug("Ustawiona wartosc nowa: %d", liczba_k);
    if (points.size()>0)
    {
        im.fill(0);
        for (int i = 0; i < points.size(); i++)
        {
            drawPixel(points[i].x(), points[i].y());
        }
        if (points.size() >= 4)
        {
            if (bspline)
                drawBSpline(points, liczba_k);
            else
                drawBezier(points, liczba_k);
        }
    }
    update();

}

void Ekran::czysc()
{
    im.fill(0);
    //    im_copy.fill(0);
    points.clear();
    update();
}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
}

// zmienne przechowujace koordynaty 1 punktu
int startX = 0;
int startY = 0;
// bool elipsa=false;

void Ekran::mousePressEvent(QMouseEvent *e)
{
    int startX = e->position().x();
    int startY = e->position().y();
    if (e->button() == Qt::LeftButton)
    {
        drawPixel(startX, startY);
        points << QPointF(startX, startY);
    }
    else if (e->button() == Qt::RightButton)
    {
        int index = findNearestPoint(points, startX, startY);
        if (index != -1)
        {
            points.remove(index);
            im.fill(0);
            for (int i = 0; i < points.size(); i++)
            {
                drawPixel(points[i].x(), points[i].y());
            }
        }
    }
    if (points.size() >= 4)
    {
        if (bspline)
            drawBSpline(points, liczba_k);
        else
            drawBezier(points, liczba_k);
    }

    update(); // odświeżanie okna
}

int temp_index = -1;

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::MiddleButton)
    {
        int tempX = e->position().x();
        int tempY = e->position().y();
        if (temp_index == -1)
        {
            temp_index = findNearestPoint(points, tempX, tempY);
        }
        if (temp_index != -1)
        {
            im.fill(0);
            points[temp_index].setX(tempX);
            points[temp_index].setY(tempY);
            for (int i = 0; i < points.size(); i++)
            {
                drawPixel(points[i].x(), points[i].y());
            }
            if (points.size() >= 4)
            {
                //drawBezier(points, liczba_k);
                if (bspline)
                    drawBSpline(points, liczba_k);
                else
                    drawBezier(points, liczba_k);
            }
        }
    }

    update();
}

void Ekran::mouseReleaseEvent(QMouseEvent *)
{
    temp_index = -1;
}
