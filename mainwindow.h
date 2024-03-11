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
    bool setup = true;

    Building *building;
    ECS *controlSystem;

    void init();
    void print(QString message);

    void UpdateElevatorPanel(int index);
    void RefreshElevatorPanel();
    void UpdateFloorPanel(int index);
    void RefreshFloorPanel();

public slots:
    void update_ui();

private slots:
    void on_combo_elevator_picker_currentIndexChanged(int index);

    void on_combo_elevator_dest_currentIndexChanged(int index);

    void on_button_elevator_dest_clicked();

    void on_combo_floor_picker_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
