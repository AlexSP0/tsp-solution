#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "citycoordinates.h"
#include "tspholder.h"
#include "tspwindow.h"

#include <memory>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::vector<CityCoordinates> map;

    std::vector<Genome> population;

    TSPWindow *window;

    void generateMap(const int numCities);

    void createPopulation(int, int);

private slots:

    void startButton();
    void exitButton();
};
#endif // MAINWINDOW_H
