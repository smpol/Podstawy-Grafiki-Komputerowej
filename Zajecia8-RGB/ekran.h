#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <algorithm>
#include <cmath>
#include <QPushButton>
#include <QStack>
#include <QtAlgorithms>
#include <QColorDialog>
enum tryb_color
{
    RGB_R,
    RGB_G,
    RGB_B,
    HSV_H,
    HSV_S,
    HSV_V
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    QColor color;

    int red = 0;
    int green = 0;
    int blue = 0;
    int hue = 0;
    int saturation = 0;
    int value = 0;

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
            for (int i = 0; i < przekazane_punkty.size() - 1; i++)
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

    void barwy_skrocone(int tryb)
    {

        for (int y = 0; y < im.height(); y++)
        {
            for (int x = 0; x < im.width(); x++)
            {
                if (tryb == RGB_R)
                    drawPixel(x, y, red, (y * 255) / im.height(), (x * 255) / im.width());
                else if (tryb == RGB_G)
                    drawPixel(x, y, (y * 255) / im.height(), green, (x * 255) / im.width());
                else if (tryb == RGB_B)
                    drawPixel(x, y, (y * 255) / im.height(), (x * 255) / im.width(), blue);
                else if (tryb == HSV_H || tryb == HSV_S || tryb == HSV_V)
                {
                    float S, V, C, X, H_prim;
                    float r, g, b, m;

                    if (tryb == HSV_H)
                    {
                        S = (float)x / (im.width() - 1); // Przeliczenie nasycenia na podstawie pozycji piksela wzdłuż osi x
                        V = (float)y / (im.height() - 1); // Przeliczenie wartości na podstawie pozycji piksela wzdłuż osi y
                        C = V * S;  // Obliczenie chrominancji ze wzoru z PDFa
                        H_prim = ((float)hue / 255) * 6; // Przeliczenie wartości H na przedział [0,6]
                        X = C * (1 - fabs(fmod(H_prim, 2) - 1)); // Obliczenie wartości X ze wzoru z PDFa
                    }
                    if (tryb == HSV_S)
                    {
                        S = (float)saturation / 255;
                        V = (float)y / (im.height() - 1);
                        C = V * S;
                        H_prim = ((float)x / (im.width() - 1)) * 6;
                        X = C * (1 - fabs(fmod(H_prim, 2) - 1));
                    }
                    if (tryb == HSV_V)
                    {
                        S = (float)y / (im.height() - 1);
                        V = (float)value / 255;
                        C = V * S;
                        H_prim = ((float)x / (im.width() - 1)) * 6;
                        X = C * (1 - fabs(fmod(H_prim, 2) - 1));
                    }

                    m = V-C; // obliczamy ze wzoru z PDFa
                    // Piksel znajduje się w pierwszej części barwnego koła, która odpowiada kolorom czerwonym.
                    if (H_prim >= 0 && H_prim <= 1)
                    {
                        r = V;
                        g = X + m;
                        b = m;
                    }
                    //Piksel znajduje się w drugiej części barwnego koła, która odpowiada kombinacjom kolorów czerwonego i zielonego.
                    else if (H_prim > 1 && H_prim <= 2)
                    {
                        r = X + m;
                        g = V;
                        b = m;
                    }
                    //Piksel znajduje się w trzeciej części barwnego koła, która odpowiada kombinacjom kolorów zielonego i niebieskiego.
                    else if (H_prim > 2 && H_prim <= 3)
                    {
                        r = m;
                        g = V;
                        b = X + m;
                    }
                    //Piksel znajduje się w czwartej części barwnego koła, która odpowiada kombinacjom kolorów niebieskiego i czerwonego.
                    else if (H_prim > 3 && H_prim <= 4)
                    {
                        r = m;
                        g = X + m;
                        b = V;
                    }
                    //Piksel znajduje się w piątej części barwnego koła, która odpowiada kombinacjom kolorów czerwonego i zielonego.
                    else if (H_prim > 4 && H_prim <= 5)
                    {
                        r = X + m;
                        g = m;
                        b = V;
                    }
                    //Piksel znajduje się w szóstej części barwnego koła,
                    else
                    {
                        r = V;
                        g = m;
                        b = X + m;
                    }
                    drawPixel(x, y, r * 255, g * 255, b * 255); //wartosci rgb sa w przedziale [0,1] dlatego mnozymy przez 255
                }
            }
        }
    }

public slots:
    void red_rgb(int);
    void green_rgb(int);
    void blue_rgb(int);
    void hue_hsv(int);
    void saturation_hsv(int);
    void value_hsv(int);

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
