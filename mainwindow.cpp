#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mapconstants.h"
#include "tspwindow.h"

#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    holder->createPopulation(numPopulationString.toInt(), numCitiesString.toInt());

    window = new TSPWindow(&map, holder->population, 0, numPopulationString.toInt());
    window->show();
    timer->start();
}

void MainWindow::exitButton()
{
    this->close();
}

void MainWindow::tick()
{
    if (window->isBusy == false)
    {
        timer->stop();
        QMessageBox msgBox;
        msgBox.setText("WINDOW STOPS!");
        msgBox.exec();
    }
}
