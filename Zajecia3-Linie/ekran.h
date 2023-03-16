#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <algorithm>
#include <cmath>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    void drawPixel(int x, int y)
    {
        int width=im.width();
        int height=im.height();
        if ((x>=0) && (x<=width) && (y>=0) && (y<=height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela?
            pix[4*x]=255; // blue
            pix[4*x+1]=255; //green
            pix[4*x+2]=255; //red
        }

    }
    void drawLine(int x0, int y0, int x1, int y1)
    {
        bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
        if (steep) { // jeśli linia jest "stroma", zamień współrzędne x i y
                    std::swap(x0, y0);
                    std::swap(x1, y1);
                }

                if (x0 > x1) { // jeśli punkt startowy jest po prawej stronie punktu końcowego, zamień je miejscami
                    std::swap(x0, x1);
                    std::swap(y0, y1);
                }

                int dx = x1 - x0;
                int dy = std:abs(y1 - y0);
                int error = dx / 2; // zmienna pomocnicza używana do obliczenia błędu przy wyznaczaniu kolejnych punktów na linii
                int ystep = (y0 < y1) ? 1 : -1; // ustal kierunek rysowania linii
                int y = y0;
                for (int x = x0; x <= x1; x++) {
                            if (steep) { // jeśli linia jest "stroma", narysuj punkt o współrzędnych zamienionych miejscami
                                drawPixel(y,x);
                            } else {
                                drawPixel(x, y);
                            }
                            error -= dy;
                            if (error < 0) {
                                y += ystep; // jeśli błąd jest mniejszy niż 0, przesuń się do kolejnego punktu na linii
                                error += dx;
                            }
                        }
    }


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
signals:
private:
    QImage im;
};

#endif // EKRAN_H
