#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "citycoordinates.h"
#include "tspgenomewindow.h"
#include "tspholder.h"
#include "tspwindow.h"

#include <memory>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

struct Generation
{
    int generationNumber;
    int populationSize;
    float bestFitness;
    float totalFitness;
    Genome bestGenome;

    Generation()
        : generationNumber(0)
        , populationSize(0.0)
        , bestFitness(0.0)
        , totalFitness(0.0)
        , bestGenome()
    {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::vector<CityCoordinates> map;

    std::vector<Generation> generations;

    TSPHolder *holder;

    int numberOfGenerations;

    int currentGeneration;

    TSPWindow *window;

    TSPGenomeWindow *genWindow;

    QTimer *timer;

private:
    void generateMap(const int numCities);
    void updateResults();
    void startNewGeneration();

private slots:

    void showGeneration(QTableWidgetItem *item);
    void startButton();
    void exitButton();

    void tick();
};
#endif // MAINWINDOW_H
