#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print(QString message){
    ui->label_console->setText(ui->label_console->text() + "\n" + message);
    // Can't figure out how to make the area autoscroll to the bottom :(
}

void MainWindow::init(){

    MainWindow::print("Matthew Czarnowski");
    MainWindow::print("101151676");
    MainWindow::print("---");

    // Init function which uses the variables above to set up the system
    // For example, NUM_ELEVATORS and NUM_FLOORS will be used to edit the groupboxes

    building = new Building();
    controlSystem = new ECS();

    // Loop: for each elevator (3)
    ui->combo_elevator_picker->clear();
    for (int i = 1; i <= NUM_ELEVATORS; i++){

        // controlSystem->addCab();

        ui->combo_elevator_picker->addItem(QString::number(i));
    }

    MainWindow::print("Added " + QString::number(NUM_ELEVATORS) + " elevators.");

    // Loop: for each floor (7)
    ui->combo_floor_picker->clear();
    for (int i = 1; i <= NUM_FLOORS; i++){

        // building->addFloor();

        ui->combo_floor_picker->addItem(QString::number(i));
    }

    MainWindow::print("Added " + QString::number(NUM_FLOORS) + " floors.");
}
