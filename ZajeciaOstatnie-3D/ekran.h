#ifndef EKRAN_H
#define EKRAN_H

#include <QStack>
#include <QtAlgorithms>
#include <QColorDialog>
#include <QWidget>
#include <algorithm>
#include <cmath>
#include <QPushButton>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    enum SCIANA
    {
        PRZEDNIA,
        TYLNA,
        LEWA,
        PRAWA,
        GORA,
        DOL
    };
    struct punkt3D
    {
        int x;
        int y;
        int z;
    };
    QVector<punkt3D> punkty_pocz;
    QVector<punkt3D> punkty3D;
    QVector<QPoint> punkty2D;
    bool ukrycie_scian = false;
    bool teskturowanie_scian = false;
    int rotacja_x = 0;
    int rotacja_y = 0;
    int rotacja_z = 0;
    double sX = 80.0 / 100.0;
    double sY = 80.0 / 100.0;
    double sZ = 80.0 / 100.0;
    double tX = 75;
    double tY = 75;
    double tZ = 195;
    void drawPixel(int x, int y, int red, int green, int blue)
    {
        int width = im.width();
        int height = im.height();

        if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
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
            drawPixel(x1, y1, 0, 255, 255);
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
                    drawPixel(x, (int)floor(y + 0.5), 0, 255, 255);
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
                    drawPixel((int)floor(x + 0.5), y, 0, 255, 255);
                }
            }
        }
    }

    void przeksztalcenia()
    {
        punkty3D.clear();

        double srodekX = (width() / 2.0) + tX;
        double srodekY = (height() / 2.0) + tY;
        double srodekZ = tZ + 150;

        double Transalcja[4][4] = {{1, 0, 0, tX},
                                   {0, 1, 0, tY},
                                   {0, 0, 1, tZ},
                                   {0, 0, 0, 1}};

        double Skalowanie[4][4] = {{sX, 0, 0, 0},
                                   {0, sY, 0, 0},
                                   {0, 0, sZ, 0},
                                   {0, 0, 0, 1}};

        double ObrotX[4][4] = {{1, 0, 0, 0},
                               {0, cos(rotacja_x * M_PI / 180.0), -sin(rotacja_x * M_PI / 180.0), 0},
                               {0, sin(rotacja_x * M_PI / 180.0), cos(rotacja_x * M_PI / 180.0), 0},
                               {0, 0, 0, 1}};

        double ObrotY[4][4] = {{cos(rotacja_y * M_PI / 180.0), 0, sin(rotacja_y * M_PI / 180.0), 0},
                               {0, 1, 0, 0},
                               {-sin(rotacja_y * M_PI / 180.0), 0, cos(rotacja_y * M_PI / 180.0), 0},
                               {0, 0, 0, 1}};

        double ObrotZ[4][4] = {{cos(rotacja_z * M_PI / 180.0), -sin(rotacja_z * M_PI / 180.0), 0, 0},
                               {sin(rotacja_z * M_PI / 180.0), cos(rotacja_z * M_PI / 180.0), 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1}};

        double temp = 0;
        double szescian[4] = {0.0, 0.0, 0.0, 1.0};
        int transformedPoint[4];
        int scaledPoint[4];

        for (int i = 0; i < punkty_pocz.size(); i++)
        {
            szescian[0] = punkty_pocz[i].x - srodekX;
            szescian[1] = punkty_pocz[i].y - srodekY;
            szescian[2] = punkty_pocz[i].z - srodekZ;

            for (int x = 0; x < 4; x++)
            {
                temp = 0;
                for (int y = 0; y < 4; ++y)
                {
                    temp += szescian[y] * Transalcja[x][y];
                }
                transformedPoint[x] = temp;
            }
            for (int x = 0; x < 4; x++)
            {
                temp = 0;
                for (int y = 0; y < 4; ++y)
                {
                    temp += transformedPoint[y] * Skalowanie[x][y];
                }
                scaledPoint[x] = temp;
            }

            for (int x = 0; x < 4; x++)
            {
                temp = 0;
                for (int y = 0; y < 4; ++y)
                {
                    temp += scaledPoint[y] * ObrotZ[x][y];
                }
                transformedPoint[x] = temp;
            }
            for (int x = 0; x < 4; x++)
            {
                temp = 0;
                for (int y = 0; y < 4; ++y)
                {
                    temp += transformedPoint[y] * ObrotY[x][y];
                }
                scaledPoint[x] = temp;
            }
            for (int x = 0; x < 4; x++)
            {
                temp = 0;
                for (int y = 0; y < 4; ++y)
                {
                    temp += scaledPoint[y] * ObrotX[x][y];
                }
                transformedPoint[x] = temp;
            }

            punkty3D.append({transformedPoint[0] + (int)srodekX,
                             transformedPoint[1] + (int)srodekY,
                             transformedPoint[2] + (int)srodekZ});
        }
        punkty3D_to_2D(punkty3D);
    }
    void punkty3D_to_2D(QVector<punkt3D> pkt)
    {
        punkty2D.clear();

        for (int i = 0; i < pkt.size(); i++)
        {
            double x = pkt[i].x - width() / 2.0;
            double y = pkt[i].y - height() / 2.0;
            double z = pkt[i].z;

            // Obliczanie perspektywy
            double perspektywX, perspektywY;
            // ogniskowa ustawiona na stale 150
            if (z + 150 >= 1) // sprawdzanie czy jest przed ekranem
            {
                // wzor z filmu
                perspektywX = (150 * x) / (z + 150);
                perspektywY = (150 * y) / (z + 150);
            }
            else // jesli nie to punkt poza ekranem
            {
                perspektywX = x;
                perspektywY = y;
            }
            // Przesunięcie do środka ekranu
            double cX = width() / 2.0;
            double cY = height() / 2.0;

            double tempX = perspektywX + cX;
            double tempY = perspektywY + cY;

            punkty2D.append(QPoint(tempX, tempY));
        }
        rysuj_szescian(punkty2D);
    }

    bool Czy_widoczna_sciana(QPoint punkt1, QPoint punkt2, QPoint punkt3)
    {
        // Wektory
        QPoint wektor1 = punkt2 - punkt1;
        QPoint wektor2 = punkt3 - punkt1;
        // Iloczyn wektorow
        int iloczyn_wektorow = (wektor1.x() * wektor2.y()) - (wektor1.y() * wektor2.x());

        // Jesli iloczyn wektorowy jest wiekszy/rowny od 0 to znaczy ze zwrocony przodem do uzytkownika 
        return iloczyn_wektorow >= 0;
    }

    void rysuj_szescian(QVector<QPoint> szescian2d)
    {
        // Rysuj sciany w trybie ukrywania scian niewidocznych
        if (ukrycie_scian)
        {
            bool gorna_sciana =    Czy_widoczna_sciana(szescian2d[2], szescian2d[3], szescian2d[1]);
            bool dolna_sciana =    Czy_widoczna_sciana(szescian2d[5], szescian2d[4], szescian2d[6]);

            bool lewa_sciana =     Czy_widoczna_sciana(szescian2d[1], szescian2d[5], szescian2d[0]);
            bool prawa_sciana =    Czy_widoczna_sciana(szescian2d[3], szescian2d[7], szescian2d[6]);

            bool przednia_sciana = Czy_widoczna_sciana(szescian2d[0], szescian2d[2], szescian2d[4]);
            bool tylnia_sciana =   Czy_widoczna_sciana(szescian2d[1], szescian2d[5], szescian2d[7]);
            

            if (przednia_sciana)
            {
                drawWall(PRZEDNIA, szescian2d);
                if (teskturowanie_scian)
                {
                    wypelnij_trojkat(szescian2d[0], szescian2d[2], szescian2d[6], 1);
                    wypelnij_trojkat(szescian2d[0], szescian2d[6], szescian2d[4], 2);
                }
            }

            if (tylnia_sciana)
            {
                drawWall(TYLNA, szescian2d);
                if (teskturowanie_scian)
                {
                    wypelnij_trojkat(szescian2d[1], szescian2d[3], szescian2d[7], 1);
                    wypelnij_trojkat(szescian2d[1], szescian2d[7], szescian2d[5], 2);
                }
            }


            if (!gorna_sciana)
            {
                drawWall(GORA, szescian2d);
                if (teskturowanie_scian)
                {
                    wypelnij_trojkat(szescian2d[2], szescian2d[0], szescian2d[3], 1);
                    wypelnij_trojkat(szescian2d[3], szescian2d[1], szescian2d[0], 2);
                }
            }

            if (dolna_sciana)
            {
                drawWall(DOL, szescian2d);
                if (teskturowanie_scian)
                {
                    wypelnij_trojkat(szescian2d[4], szescian2d[6], szescian2d[5], 1);
                    wypelnij_trojkat(szescian2d[5], szescian2d[7], szescian2d[6], 2);
                }
            }

            if (!lewa_sciana)
            {
                drawWall(LEWA, szescian2d);
                if (teskturowanie_scian)
                {
                    wypelnij_trojkat(szescian2d[5], szescian2d[4], szescian2d[0], 1);
                    wypelnij_trojkat(szescian2d[5], szescian2d[0], szescian2d[1], 2);
                }
            }

            if (prawa_sciana)
            {
                drawWall(PRAWA, szescian2d);
                if (teskturowanie_scian)
                {
                    wypelnij_trojkat(szescian2d[7], szescian2d[6], szescian2d[2], 1);
                    wypelnij_trojkat(szescian2d[7], szescian2d[2], szescian2d[3], 2);
                }
            }
        }
        else
        {
            // rysowanie całego szescianu
            drawWall(GORA, szescian2d);
            drawWall(DOL, szescian2d);
            drawWall(LEWA, szescian2d);
            drawWall(PRAWA, szescian2d);
            drawWall(PRZEDNIA, szescian2d);
            drawWall(TYLNA, szescian2d);
        }
    }

    void wypelnij_trojkat(QPoint p1, QPoint p2, QPoint p3, int czesc)
    {
        QColor color;
        QVector<QPoint> punkty_szescianu;
        // punkty trójkąta tekstury
        QPoint org_p1;
        QPoint org_p2;
        QPoint org_p3;

        if (czesc == 1)
        {
            org_p1 = {0, 0};
            org_p2 = {0, obraz.height() - 1};
            org_p3 =  {obraz.width() - 1, 0};
        }
        else
        {
            org_p2 = {obraz.width() - 1, obraz.height() - 1};
            org_p1 = {obraz.width() - 1, 0};
            org_p3 = {0, obraz.height() - 1};
        }

        punkty_szescianu.append(p1);
        punkty_szescianu.append(p2);
        punkty_szescianu.append(p3);
        int najnizszy = punkty_szescianu[0].y();
        int najwyzej = punkty_szescianu[0].y();
        int najbardziejNaLewo = punkty_szescianu[0].x();
        int najbardziejNaPrawo = punkty_szescianu[0].x();

        for (int i = 1; i < (int)punkty_szescianu.size(); i++)
        {
            if (punkty_szescianu[i].y() < najnizszy)
                najnizszy = punkty_szescianu[i].y();
            if (punkty_szescianu[i].y() > najwyzej)
                najwyzej = punkty_szescianu[i].y();
            if (punkty_szescianu[i].x() < najbardziejNaLewo)
                najbardziejNaLewo = punkty_szescianu[i].x();
            if (punkty_szescianu[i].x() > najbardziejNaPrawo)
                najbardziejNaPrawo = punkty_szescianu[i].x();
        }

        double wyznaczik = (punkty_szescianu[0].y() - punkty_szescianu[1].y()) * (punkty_szescianu[2].x() - punkty_szescianu[1].x()) + (punkty_szescianu[1].x() - punkty_szescianu[0].x()) * (punkty_szescianu[2].y() - punkty_szescianu[1].y());
        for (int y = najnizszy; y < najwyzej; y++)
        {
            for (int x = najbardziejNaLewo; x < najbardziejNaPrawo; x++)
            {
                // wspolrzednych barycentrycznych
                double w = ((punkty_szescianu[1].y() - punkty_szescianu[2].y()) * (x - punkty_szescianu[2].x()) + (punkty_szescianu[2].x() - punkty_szescianu[1].x()) * (y - punkty_szescianu[2].y())) / wyznaczik;
                double v = ((punkty_szescianu[2].y() - punkty_szescianu[0].y()) * (x - punkty_szescianu[2].x()) + (punkty_szescianu[0].x() - punkty_szescianu[2].x()) * (y - punkty_szescianu[2].y())) / wyznaczik;
                double u = 1.0 - w - v;

                // sprawdzenie czy punkt lezy w trojkacie
                if (u >= 0 && u < 1 && v >= 0 && v < 1 && w >= 0 && w < 1)
                {
                    double Punkt_x = u * org_p1.x() + v * org_p2.x() + w * org_p3.x();
                    double Punkt_y = u * org_p1.y() + v * org_p2.y() + w * org_p3.y();

                    color = obraz.pixelColor(Punkt_x, Punkt_y);
                    if (x >= 0 && x < width() && y >= 0 && y < height())
                        im.setPixelColor(x, y, color);
                }
            }
        }
    }

    void drawWall(int wybor, QVector<QPoint> szescian)
    {
        switch (wybor)
        {
        case PRZEDNIA:
            drawLine(szescian[0].x(), szescian[0].y(), szescian[2].x(), szescian[2].y());
            drawLine(szescian[2].x(), szescian[2].y(), szescian[6].x(), szescian[6].y());
            drawLine(szescian[4].x(), szescian[4].y(), szescian[6].x(), szescian[6].y());
            drawLine(szescian[4].x(), szescian[4].y(), szescian[0].x(), szescian[0].y());
            break;
        case TYLNA:
            drawLine(szescian[1].x(), szescian[1].y(), szescian[3].x(), szescian[3].y());
            drawLine(szescian[7].x(), szescian[7].y(), szescian[3].x(), szescian[3].y());
            drawLine(szescian[7].x(), szescian[7].y(), szescian[5].x(), szescian[5].y());
            drawLine(szescian[1].x(), szescian[1].y(), szescian[5].x(), szescian[5].y());
            break;
        case LEWA:
            drawLine(szescian[5].x(), szescian[5].y(), szescian[4].x(), szescian[4].y());
            drawLine(szescian[1].x(), szescian[1].y(), szescian[0].x(), szescian[0].y());
            drawLine(szescian[1].x(), szescian[1].y(), szescian[5].x(), szescian[5].y());
            drawLine(szescian[4].x(), szescian[4].y(), szescian[0].x(), szescian[0].y());
            break;
        case PRAWA:
            drawLine(szescian[7].x(), szescian[7].y(), szescian[6].x(), szescian[6].y());
            drawLine(szescian[3].x(), szescian[3].y(), szescian[7].x(), szescian[7].y());
            drawLine(szescian[2].x(), szescian[2].y(), szescian[6].x(), szescian[6].y());
            drawLine(szescian[2].x(), szescian[2].y(), szescian[3].x(), szescian[3].y());
            break;
        case GORA:
            drawLine(szescian[2].x(), szescian[2].y(), szescian[0].x(), szescian[0].y());
            drawLine(szescian[2].x(), szescian[2].y(), szescian[3].x(), szescian[3].y());
            drawLine(szescian[3].x(), szescian[3].y(), szescian[1].x(), szescian[1].y());
            drawLine(szescian[1].x(), szescian[1].y(), szescian[0].x(), szescian[0].y());
            break;
        case DOL:
            drawLine(szescian[4].x(), szescian[4].y(), szescian[6].x(), szescian[6].y());
            drawLine(szescian[4].x(), szescian[4].y(), szescian[5].x(), szescian[5].y());
            drawLine(szescian[7].x(), szescian[7].y(), szescian[5].x(), szescian[5].y());
            drawLine(szescian[7].x(), szescian[7].y(), szescian[6].x(), szescian[6].y());
            break;
        default:
            break;
        }
    }

public slots:
    void moveX(int);
    void moveY(int);
    void moveZ(int);
    void set_sX(int);
    void set_sY(int);
    void set_sZ(int);
    void set_obrotX(int);
    void set_obrotY(int);
    void set_obrotZ(int);
    void ukrywanie_scian(bool);
    void teksturowanie(bool);
    void aktualizuj();

protected:
    void paintEvent(QPaintEvent *event);
signals:
private:
    QImage im;
    // QImage im_copy;
    QImage obraz;
};

#endif // EKRAN_H
