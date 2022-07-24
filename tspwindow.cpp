#include "tspwindow.h"
#include "mapconstants.h"
#include "ui_tspwindow.h"

#include <math.h>
#include <QPainter>
#include <QPointF>
#include <QTimer>

TSPWindow::TSPWindow(std::vector<CityCoordinates> *m,
                     std::vector<Genome> &population,
                     int begin,
                     int end,
                     QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TSPWindow)
    , isBusy(true)
    , map(m)
    , currentGenome(5)
{
    ui->setupUi(this);

    calc = new TSPCalculator(population, begin, end, m);

    timer = new QTimer;
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(personalTick()));

    repaint();

    timer->start();
}

TSPWindow::~TSPWindow()
{
    delete ui;
    delete calc;
    delete timer;
}

std::vector<Genome> &TSPWindow::getPopulation()
{
    return calc->populationPart;
}

void TSPWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter qp(this);

    renderMap(&qp);
}

void TSPWindow::renderMap(QPainter *qp)
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
}

void TSPWindow::drawRoute(Route &route, QPainter *qp)
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

//для пошаговых вычислений для каждого индивида
void TSPWindow::tick()
{
    int fromCity = 0;
    int toCity   = 0;
    int curGenome;

    calc->showRoutes(fromCity, toCity, curGenome);

    if (currentGenome != curGenome)
    {
        if (curGenome == -1)
        {
            timer->stop();
            isBusy = false;
            return;
        }
        routes.clear();
    }

    Route route(fromCity, toCity);
    routes.push_back(route);
    currentGenome = curGenome;

    repaint();
}

//Для вычислений всего индивида за один шаг
void TSPWindow::personalTick()
{
    int curGenome = 0;
    Genome gen;
    calc->calculateGenomeFitness(curGenome, gen);

    if (curGenome == -1)
    {
        timer->stop();
        isBusy = false;
        routes.clear();
        return;
    }

    for (size_t i = 0; i < gen.bits.size(); i++)
    {
        if (i == 0)
        {
            continue;
        }
        Route route;
        route.fromCity = gen.bits[i - 1];
        route.toCity   = gen.bits[i];
        routes.push_back(route);
    }

    repaint();

    routes.clear();

    currentGenome = curGenome;
}
