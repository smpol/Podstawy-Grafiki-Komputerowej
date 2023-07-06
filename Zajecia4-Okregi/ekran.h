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
    void drawLine(int x0, int y0, int x1, int y1)
    {
        double m = 0;
        if(x1 == x0 && y1 == y0) // rysowanie piskela tylko dla punktu
        {
            drawPixel(x1, y1);
        }
        else
        {
            if(abs(x1 - x0) >= abs(y1 - y0))
            {
                if(x0 > x1) // Jeżeli punkt początkowy jest po prawej stronie
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
            else //zamiana osi OX z OY
            {
                if(y0 > y1)
                {
                    std::swap(x0, x1);
                    std::swap(y0, y1);
                }
                m = (double)(x1 - x0) / (y1 - y0);
                for (int y = y0; y <= y1; y++)
                {
                    int x = m * (y - y0) + x0;
                    drawPixel( (int)floor(x + 0.5), y);
                }
            }
        }
    }

    void drawCircle(int x0, int y0, int x1, int y1)
    {
        int R = sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
        for(int i = 0; i <= (R/sqrt(2)); i++)
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
    void drawElipse(int x0, int y0, int x1, int y1, int suwak)
    {
        int a = abs(x1 - x0);
        int b = abs(y1 - y0);
        int pxTemp,pyTemp,py,px;
        pxTemp = a ;
        pyTemp = 0;
        double kat;
        // Rysowanie linii między kolejnymi wierzchołkami
        for (int i = 1; i <= suwak; ++i)
        {
            kat = i * 2 * M_PI / suwak; //kąta miedzy punktami
            px = a * cos(kat); //przekatna wzgledem x
            py = b * sin(kat); //przekatna wzgledem y
            drawLine(px + x0, py + y0, pxTemp + x0, pyTemp + y0);
            pxTemp = px;
            pyTemp = py;
        }
    }

public slots:
    void wartosc(int);
    void czysc();
    void tryb_elipsa();
    void tryb_kolo();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:
private:
    QImage im;
    QImage im_copy;
};


#endif // EKRAN_H
