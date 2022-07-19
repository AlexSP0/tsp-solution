#ifndef TSPWINDOW_H
#define TSPWINDOW_H

#include "citycoordinates.h"

#include <QWidget>

namespace Ui
{
class TSPWindow;
}

class TSPWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TSPWindow(std::vector<CityCoordinates> *m, QWidget *parent = nullptr);
    ~TSPWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::TSPWindow *ui;

    const std::vector<CityCoordinates> *map;

    void renderMap(QPainter *);

    void printCityNum(QPainter *, int, int, QString);

    int translateX(float);
    int translateY(float);
};

#endif // TSPWINDOW_H
