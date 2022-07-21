#ifndef TSPWINDOW_H
#define TSPWINDOW_H

#include "citycoordinates.h"
#include "genome.h"
#include "tspcalculator.h"

#include <QWidget>

namespace Ui
{
class TSPWindow;
}

struct Route
{
    double fromCity;
    double toCity;
    Route()
        : fromCity(0.0)
        , toCity(0.0)
    {}
    Route(int from, int to)
        : fromCity(from)
        , toCity(to)
    {}
};

class TSPWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TSPWindow(
        std::vector<CityCoordinates> *, std::vector<Genome> &, int, int, QWidget *parent = nullptr);
    ~TSPWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::TSPWindow *ui;

    TSPCalculator *calc;

    QTimer *timer;

    const std::vector<CityCoordinates> *map;

    std::vector<Route> routes;

    int currentGenome;

    void renderMap(QPainter *);

    void drawRoute(Route &, QPainter *);

    void printCityNum(QPainter *, int, int, QString);

    int translateX(float);
    int translateY(float);

private slots:
    void tick();
};

#endif // TSPWINDOW_H
