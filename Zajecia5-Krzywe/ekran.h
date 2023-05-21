#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <algorithm>
#include <cmath>
#include <QPushButton>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    void drawPixel(int x, int y)
    {
        int width = im.width();
        int height = im.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela
            pix[4 * x] = 255;            // blue
            pix[4 * x + 1] = 255;        // green
            pix[4 * x + 2] = 255;
        }
    }
    void clearPixel(int x, int y)
    {
        int width = im.width();
        int height = im.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela
            pix[4 * x] = 0;            // blue
            pix[4 * x + 1] = 0;        // green
            pix[4 * x + 2] = 0;
        }
    }
    void drawLine(int x0, int y0, int x1, int y1)
    {
        double m = 0;
        if (x1 == x0 && y1 == y0) // rysowanie piskela tylko dla punktu
        {
            drawPixel(x1, y1);
        }
        else
        {
            if (abs(x1 - x0) >= abs(y1 - y0))
            {
                if (x0 > x1) // Jeżeli punkt początkowy jest po prawej stronie
                {
                    std::swap(x0, x1);
                    std::swap(y0, y1);
                }
                m = (double)(y1 - y0) / (x1 - x0);
                for (int x = x0; x <= x1; x++)
                {
                    int y = m * (x - x0) + y0;
                    drawPixel(x, (int)floor(y + 0.5));
                }
            }
            else // zamiana osi OX z OY
            {
                if (y0 > y1)
                {
                    std::swap(x0, x1);
                    std::swap(y0, y1);
                }
                m = (double)(x1 - x0) / (y1 - y0);
                for (int y = y0; y <= y1; y++)
                {
                    int x = m * (y - y0) + x0;
                    drawPixel((int)floor(x + 0.5), y);
                }
            }
        }
    }

    void drawCircle(int x0, int y0, int x1, int y1)
    {
        int R = sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
        for (int i = 0; i <= (R / sqrt(2)); i++)
        {
            int xy = sqrt(R * R - i * i);

            drawPixel(i + x0, (int)floor(xy + 0.5) + y0);
            drawPixel(i + x0, -(int)floor(xy + 0.5) + y0);
            drawPixel(-i + x0, (int)floor(xy + 0.5) + y0);
            drawPixel(-i + x0, -(int)floor(xy + 0.5) + y0);

            drawPixel((int)floor(xy + 0.5) + x0, i + y0);
            drawPixel(-(int)floor(xy + 0.5) + x0, i + y0);
            drawPixel((int)floor(xy + 0.5) + x0, -i + y0);
            drawPixel(-(int)floor(xy + 0.5) + x0, -i + y0);
        }
    }
    void drawElipse(int x0, int y0, int x1, int y1, int suwaczek)
    {
        int a = abs(x1 - x0);
        int b = abs(y1 - y0);
        int pxTemp, pyTemp, py, px;
        pxTemp = a;
        pyTemp = 0;
        double kat;
        // Rysowanie linii między kolejnymi wierzchołkami
        for (int i = 1; i <= suwaczek; ++i)
        {
            // obliczenie kąta miedzy punktami
            kat = i * 2 * M_PI / suwaczek;
            px = a * cos(kat); // ruszanie pierwszej przekatnej wzgledem x
            py = b * sin(kat); // ruszanie drugiej przekatnej wzgledem y
            drawLine(px + x0, py + y0, pxTemp + x0, pyTemp + y0);
            pxTemp = px;
            pyTemp = py;
        }
    }

    int findNearestPoint(QVector<QPointF> &points, int x, int y)
    {
        int odlegosc = 20;//index of nearest point
        int index=-1;
        for (int i=0; i<points.size(); i++)
        {
            if (sqrt((points[i].x()-x)*(points[i].x()-x) + (points[i].y()-y)*(points[i].y()-y)) < odlegosc)
            {
                odlegosc = sqrt((points[i].x()-x)*(points[i].x()-x) + (points[i].y()-y)*(points[i].y()-y));
                index = i;
            }
        }
        return index;
    }

    void drawBezier(QVector<QPointF> &points, int k)
    {
//     uzywajac drawLine
       QPointF poczatek_lini, koniec_lini;
       qDebug("Wywolanie funkcji z k %d", k);
       for (int i=0; i<points.size()-3; i+=3)
       {
           for (int j=0; j<=k; j++)
           {
               float t = (float)j/(float)k;
               poczatek_lini = (1-t)*(1-t)*(1-t)*points[0+i] + 3*(1-t)*(1-t)*t*points[1+i] + 3*(1-t)*t*t*points[2+i] + t*t*t*points[3+i];
               if (j==0)
               {
                   koniec_lini = poczatek_lini;
               }
               else
               {
                   drawLine(poczatek_lini.x(), poczatek_lini.y(), koniec_lini.x(), koniec_lini.y());
                   koniec_lini = poczatek_lini;
               }
           }
       }
    }
    void drawBSpline(QVector<QPointF> &points, int k)
    {
        QPointF poczatek_lini, koniec_lini;
        for (int i=0; i<points.size()-3; i++)
        {
            for (int j=0; j<=k; j++)
            {
                float t = (float)j/(float)k;

                //bspline
                poczatek_lini = ((float)1/6)*(-pow(t,3) + 3*pow(t,2) - 3*t + 1)*points[0+i] + ((float)1/6)*(3*pow(t,3) - 6*pow(t,2) + 4)*points[1+i] + ((float)1/6)*(-3*pow(t,3) + 3*pow(t,2) + 3*t + 1)*points[2+i] + ((float)1/6)*pow(t,3)*points[3+i];
                if (j==0)
                {
                    koniec_lini = poczatek_lini;
                }
                else
                {
                    drawLine(poczatek_lini.x(), poczatek_lini.y(), koniec_lini.x(), koniec_lini.y());
                    koniec_lini = poczatek_lini;
                }
            }
        }
    }

public slots:
    void czysc();
    void set_k_string(QString);
    void setBezier();
    void setBSpline();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *e);
signals:
private:
    QImage im;
    QImage im_copy;
};

#endif // EKRAN_H
