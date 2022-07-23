#include "tspgenomewindow.h"
#include "ui_tspgenomewindow.h"

#include <math.h>
#include <QPainter>

TSPGenomeWindow::TSPGenomeWindow(std::vector<CityCoordinates> *m, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TSPGenomeWindow)
    , map(m)
{
    ui->setupUi(this);

    repaint();
}

TSPGenomeWindow::~TSPGenomeWindow()
{
    delete ui;
}

void TSPGenomeWindow::setGenome(Genome gen)
{
    routes.clear();

    genome.bits.clear();
    genome.fitness = 0.0;

    genome = gen;

    for (size_t i = 0; i < genome.bits.size(); i++)
    {
        if (i == 0)
        {
            continue;
        }
        Route newRoute(genome.bits.at(i - 1), genome.bits.at(i));
        routes.push_back(newRoute);
    }
}

void TSPGenomeWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter qp(this);

    render(&qp);
}

void TSPGenomeWindow::render(QPainter *qp)
{
    resize(MAP_WIDTH_IN_PIXELS, MAP_HEIGHT_IN_PIXELS);
    for (size_t i = 0; i < map->size(); i++)
    {
        int x = translateX(map->at(i).xCoord);
        int y = translateY(map->at(i).yCoord);
        qp->drawEllipse(x, y, 5, 5);
        printCityNum(qp, x + 5, y + 15, QString::number(i));
    }

    for (auto route : routes)
    {
        drawRoute(route, qp);
    }

    for (size_t i = 0; i < genome.bits.size(); i++)
    {
        qp->drawText(0, 11 * i, QString::number(genome.bits.at(i)));
    }
}

void TSPGenomeWindow::drawRoute(Route &route, QPainter *qp)
{
    float x1abs = map->at(route.fromCity).xCoord;
    float y1abs = map->at(route.fromCity).yCoord;

    float x2abs = map->at(route.toCity).xCoord;
    float y2abs = map->at(route.toCity).yCoord;

    float x1 = translateX(x1abs);
    float y1 = translateY(y1abs);

    float x2 = translateX(x2abs);
    float y2 = translateY(y2abs);

    qp->drawLine(x1, y1, x2, y2);

    float x = x2 - x1;
    float y = y2 - y1;

    float ostr = 0.1;

    float length = sqrt(x * x + y * y) / 7;
    float ugol   = atan2(y, x);

    float f1x2 = x2 - length * cos(ugol - ostr);
    float f1y2 = y2 - length * sin(ugol - ostr);

    qp->drawLine(x2, y2, f1x2, f1y2);

    f1x2 = x2 - length * cos(ugol + ostr);
    f1y2 = y2 - length * sin(ugol + ostr);

    qp->drawLine(x2, y2, f1x2, f1y2);
}

void TSPGenomeWindow::printCityNum(QPainter *qp, int x, int y, QString text)
{
    qp->drawText(x, y, text);
}

int TSPGenomeWindow::translateX(float xCoord)
{
    float one  = (float) MAP_WIDTH_IN_PIXELS / MAX_X_CITY_COORDINATE;
    int result = one * xCoord;
    return result;
}

int TSPGenomeWindow::translateY(float yCoord)
{
    float one  = (float) MAP_HEIGHT_IN_PIXELS / MAX_Y_CITY_COORDINATE;
    int result = one * yCoord;
    return result;
}
