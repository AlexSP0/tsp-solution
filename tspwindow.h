#ifndef TSPWINDOW_H
#define TSPWINDOW_H

#include "citycoordinates.h"
#include "genome.h"
#include "mapconstants.h"
#include "tspcalculator.h"

#include <QWidget>

namespace Ui
{
class TSPWindow;
}

class TSPWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TSPWindow(
        std::vector<CityCoordinates> *, std::vector<Genome> &, int, int, QWidget *parent = nullptr);
    ~TSPWindow();

    bool isBusy;

public:
    std::vector<Genome> &getPopulation();

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
    void personalTick();
};

#endif // TSPWINDOW_H
