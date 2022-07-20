#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "citycoordinates.h"
#include "tspholder.h"

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

    TSPHolder *population;

private:
    Ui::MainWindow *ui;

    std::vector<CityCoordinates> map;

    void generateMap(const int numCities);

private slots:

    void startButton();
    void exitButton();
};
#endif // MAINWINDOW_H
