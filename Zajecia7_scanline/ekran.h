#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <algorithm>
#include <cmath>
#include <QPushButton>
#include <QStack>
#include <QtAlgorithms>
#include <QColorDialog>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    void drawPixel(int x, int y, int red, int green, int blue)
    {
        int width = im.width();
        int height = im.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela
            pix[4 * x] = blue;
            pix[4 * x + 1] = green;
            pix[4 * x + 2] = red;
        }
    }
    void drawLine(int x0, int y0, int x1, int y1)
    {
        double m = 0;
        if (x1 == x0 && y1 == y0) // rysowanie piskela tylko dla punktu
        {
            drawPixel(x1, y1, 255, 255, 255);
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
                    drawPixel(x, (int)floor(y + 0.5), 255, 255, 255);
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
                    drawPixel((int)floor(x + 0.5), y, 255, 255, 255);
                }
            }
        }
    }
    void scanline(QVector<QPointF> &przekazane_punkty)
    {
        int y_max = -1;
        int y_min = -1;
        int y1, y2, x1, x2;
        double temp;
        QVector<int> punktyX;
        // sprawdzanie czy jest więcej niż 2 punkty
        if (przekazane_punkty.size() < 2)
            return;

        // szukanie największej i najmniejszej współrzędnej y
        for (int i = 0; i < przekazane_punkty.size(); i++)
        {
            if (przekazane_punkty[i].y() > y_max)
            {
                y_max = przekazane_punkty[i].y();
            }
            else if (przekazane_punkty[i].y() < y_min)
            {
                y_min = przekazane_punkty[i].y();
            }
        }
        // rysowanie wypełnienia
        for (int y = y_min; y <= y_max; y++)
        {
            for (int i = 0; i < przekazane_punkty.size() -1; i++)
            {
                
                
                y1 = przekazane_punkty[i].y();
                y2 = przekazane_punkty[i + 1].y();
                x1 = przekazane_punkty[i].x();
                x2 = przekazane_punkty[i + 1].x();
                // sprawdzanie ktory punkt jest nizej
                if (y1 > y2)
                {
                    qSwap(y1, y2);
                    qSwap(x1, x2);
                }
                // sprawdzanie czy punkt leży na odcinku
                if (y >= y1 && y < y2 && y1 != y2)
                {
                    temp = x1 + (double)(y - y1) * (x2 - x1) / (y2 - y1);
                    punktyX.push_back((int)floor(temp));
                }
            }
            // sprawdzanie ostatniego punktu z pierwszym
            y1 = przekazane_punkty[0].y();
            y2 = przekazane_punkty[przekazane_punkty.size() - 1].y();
            x1 = przekazane_punkty[0].x();
            x2 = przekazane_punkty[przekazane_punkty.size() - 1].x();
            // sprawdzanie ktory punkt jest nizej
            if (y1 > y2)
            {
                qSwap(y1, y2);
                qSwap(x1, x2);
            }
            // sprawdzanie czy punkt leży na odcinku
            if (y >= y1 && y < y2 && y1 != y2)
            {
                temp = x1 + (double)(y - y1) * (x2 - x1) / (y2 - y1);
                punktyX.push_back((int)floor(temp));
            }
            // sortowanie punktów i rysowanie linii
            std::sort(punktyX.begin(), punktyX.end());
            for (int i = 0; i < punktyX.size() - 1; i += 2)
            {
                drawLine(punktyX[i], y, punktyX[i + 1], y);
            }
            punktyX.clear();
        }
    }

public slots:
    void czysc();
    void scan_line();

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
