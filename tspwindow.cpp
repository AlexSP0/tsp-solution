#include "tspwindow.h"
#include "mapconstants.h"
#include "ui_tspwindow.h"

#include <QPainter>
#include <QPointF>

TSPWindow::TSPWindow(std::vector<CityCoordinates> *m, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TSPWindow)
    , map(m)
{
    ui->setupUi(this);

    repaint();
}

TSPWindow::~TSPWindow()
{
    delete ui;
}

void TSPWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter qp(this);

    renderMap(&qp);
}

void TSPWindow::renderMap(QPainter *qp)
{
    resize(MAP_HEIGHT_IN_PIXELS, MAP_WIDTH_IN_PIXELS);
    for (size_t i = 0; i < map->size(); i++)
    {
        int x = translateX(map->at(i).xCoord);
        int y = translateY(map->at(i).yCoord);
        qp->drawEllipse(x, y, 5, 5);
        printCityNum(qp, x + 5, y + 15, QString::number(i));
    }
}

void TSPWindow::printCityNum(QPainter *qp, int x, int y, QString text)
{
    qp->drawText(x, y, text);
}

int TSPWindow::translateX(float xCoord)
{
    float one  = (float) MAP_WIDTH_IN_PIXELS / MAX_X_CITY_COORDINATE;
    int result = one * xCoord;
    return result;
}

int TSPWindow::translateY(float yCoord)
{
    float one  = (float) MAP_HEIGHT_IN_PIXELS / MAX_Y_CITY_COORDINATE;
    int result = one * yCoord;
    return result;
}
