#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::init(){
    // Init function which uses the variables above to set up the system
    // For example, NUM_ELEVATORS and NUM_FLOORS will be used to edit the groupboxes

    ui->combo_elevator_picker->clear();
    for (int i = 1; i <= NUM_ELEVATORS; i++){
        ui->combo_elevator_picker->addItem(QString::number(i));
    }

    ui->combo_floor_picker->clear();
    for (int i = 1; i <= NUM_FLOORS; i++){
        ui->combo_floor_picker->addItem(QString::number(i));
    }
}
