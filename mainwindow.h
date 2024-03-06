#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <elevator.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const int NUM_ELEVATORS = 3;
    const int NUM_FLOORS = 7;

    Building *building;
    ECS *controlSystem;

    void init();

    void print(QString message);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
