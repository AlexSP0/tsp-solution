#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mapconstants.h"
#include "tspwindow.h"

#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , numberOfGenerations(0)
    , currentGeneration(0)
{
    ui->setupUi(this);

    holder = new TSPHolder();

    timer = new QTimer();
    timer->setInterval(1000);

    connect(ui->StartButton, &QPushButton::clicked, this, &MainWindow::startButton);
    connect(ui->ExitButton, &QPushButton::clicked, this, &MainWindow::exitButton);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete window;
    delete timer;
    delete holder;
}

void MainWindow::generateMap(const int numCities)
{
    int r    = MAX_X_CITY_COORDINATE / 2.5;
    int step = 360 / numCities;

    for (int i = 0; i < 360; i = i + step)
    {
        double rad = (double) i / 180 * 3.14;
        double x   = r * cos(rad);
        double y   = r * sin(rad);
        CityCoordinates newCity((int) x + MAX_X_CITY_COORDINATE / 2,
                                (int) y + MAX_X_CITY_COORDINATE / 2);
        map.push_back(newCity);
    }

    //    do
    //    {
    //        float x = QRandomGenerator::global()->bounded(MAX_X_CITY_COORDINATE);
    //        float y = QRandomGenerator::global()->bounded(MAX_X_CITY_COORDINATE);

    //        CityCoordinates newCity(x, y);

    //        if (std::find(map.begin(), map.end(), newCity) == map.end())
    //        {
    //            map.push_back(newCity);
    //        }

    //    } while (map.size() < numCities);
}

void MainWindow::startButton()
{
    QString numCitiesString     = ui->NumberOfCitiesLineEdit->text();
    QString numPopulationString = ui->PopulationSizeLineEdit->text();
    QString numOfGenerations    = ui->numGenerationsLineEdit->text();

    generateMap(numCitiesString.toInt());
    holder->createPopulation(numPopulationString.toInt(), numCitiesString.toInt());
    numberOfGenerations = numOfGenerations.toInt();

    window = new TSPWindow(&map, holder->population, 0, numPopulationString.toInt());
    window->show();
    timer->start();
}

void MainWindow::exitButton()
{
    this->close();
}

void MainWindow::startNewGeneration()
{
    holder->genNextGeneration();

    delete window;

    window = new TSPWindow(&map, holder->population, 0, holder->population.size());
    window->show();
    timer->start();
}

void MainWindow::tick()
{
    if (window->isBusy == false)
    {
        window->close();

        timer->stop();

        std::swap(holder->population, window->getPopulation());
        holder->calculateTotalAndBestFitness();

        if (currentGeneration < numberOfGenerations)
        {
            startNewGeneration();
            currentGeneration++;
        }
    }
}
