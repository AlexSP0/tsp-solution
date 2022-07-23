#ifndef TSPGENOMEWINDOW_H
#define TSPGENOMEWINDOW_H

#include "citycoordinates.h"
#include "genome.h"
#include "mapconstants.h"

#include <QWidget>

namespace Ui
{
class TSPGenomeWindow;
}

class TSPGenomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TSPGenomeWindow(std::vector<CityCoordinates> *m, QWidget *parent = nullptr);
    ~TSPGenomeWindow();

    void setGenome(Genome gen);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::TSPGenomeWindow *ui;

    Genome genome;
    std::vector<Route> routes;
    const std::vector<CityCoordinates> *map;

private:
    void render(QPainter *);
    void printCityNum(QPainter *, int, int, QString);
    void drawRoute(Route &, QPainter *);

    int translateX(float);
    int translateY(float);
};

#endif // TSPGENOMEWINDOW_H
