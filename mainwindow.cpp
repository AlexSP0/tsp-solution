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

    generateMap(50);

    connect(ui->StartButton, &QPushButton::clicked, this, &MainWindow::startButton);
    connect(ui->ExitButton, &QPushButton::clicked, this, &MainWindow::exitButton);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete population;
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

    population = new TSPHolder(numPopulationString.toInt(), numCitiesString.toInt(), &map);

    TSPWindow *win = new TSPWindow(&map);
    win->show();
}

void MainWindow::exitButton()
{
    this->close();
}
