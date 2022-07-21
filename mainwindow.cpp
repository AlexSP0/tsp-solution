#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mapconstants.h"
#include "tspwindow.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->StartButton, &QPushButton::clicked, this, &MainWindow::startButton);
    connect(ui->ExitButton, &QPushButton::clicked, this, &MainWindow::exitButton);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete window;
}

void MainWindow::generateMap(const int numCities)
{
    do
    {
        float x = QRandomGenerator::global()->bounded(MAX_X_CITY_COORDINATE);
        float y = QRandomGenerator::global()->bounded(MAX_X_CITY_COORDINATE);

        CityCoordinates newCity(x, y);

        if (std::find(map.begin(), map.end(), newCity) == map.end())
        {
            map.push_back(newCity);
        }

    } while (map.size() < numCities);
}

void MainWindow::startButton()
{
    QString numCitiesString     = ui->NumberOfCitiesLineEdit->text();
    QString numPopulationString = ui->PopulationSizeLineEdit->text();

    generateMap(numCitiesString.toInt());
    createPopulation(numPopulationString.toInt(), numCitiesString.toInt());

    window = new TSPWindow(&map, population, 0, numPopulationString.toInt());
    window->show();
}

void MainWindow::exitButton()
{
    this->close();
}

void MainWindow::createPopulation(int populationSize, int genomeSize)
{
    for (size_t i = 0; i < populationSize; i++)
    {
        population.emplace_back(Genome(genomeSize));
    }
}
