#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollBar>
#include <QDebug>

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

Elevator* ECS::addCab(){
    Elevator* e = new Elevator();
    e->setID(this->cabs.size());
    this->cabs.push_back(e);
    return e;
}

void Elevator::setID(int _id){
    id = _id;
}

int ECS::getCabs(){
    return cabs.length();
}

void ECS::sendCabTo(int cab, int floor){
    Elevator* e = cabs.at(cab);

    e->setTargetFloor(floor);

    if (e->getCurrentFloor() > floor){
        e->setDirection("down");
    } else if (e->getCurrentFloor() < floor){
        e->setDirection("up");
    } else {
        e->setDirection("none");
    }

}

Elevator* ECS::getCab(int index){
    return cabs.at(index);
}

int Elevator::getCurrentFloor(){
    return currentFloor;
}

void Elevator::setTargetFloor(int floor){
    targetFloor = floor;
}

int Elevator::getTargetFloor(){
    return targetFloor;
}

void Elevator::setDirection(QString dir){
    direction = dir;

    if (timerId){
        killTimer(timerId);
    }

    if (direction != "none"){
        timerId = startTimer(1000);
    }
}

void Elevator::timerEvent(QTimerEvent *event){
    if (currentFloor == targetFloor){
        killTimer(timerId);
        setDirection("none");
        emit ui_change();
        return;
    }

    if (currentFloor < targetFloor){
        currentFloor += 1;
    } else if (currentFloor > targetFloor){
        currentFloor -= 1;
    }

    emit ui_change();
}

QString Elevator::getDirection(){
    return direction;
}

void Building::addFloor(){
    Floor* f = new Floor();
    this->floors.push_back(f);
}

Floor* Building::getFloor(int index){
    return floors.at(index);
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
    for (int i = 0; i < NUM_ELEVATORS; i++){

        Elevator* e = controlSystem->addCab();

        this->connect(e, SIGNAL(ui_change()), this, SLOT(update_ui()));

        ui->combo_elevator_picker->addItem(QString::number(i));
    }

    MainWindow::print("Added " + QString::number(controlSystem->getCabs()) + " elevators.");

    // Loop: for each floor (7)
    ui->combo_floor_picker->clear();
    for (int i = 0; i < NUM_FLOORS; i++){

        building->addFloor();

        ui->combo_floor_picker->addItem(QString::number(i));
        ui->combo_elevator_dest->addItem(QString::number(i));
    }

    MainWindow::print("Added " + QString::number(NUM_FLOORS) + " floors.");

    setup = false;

    MainWindow::UpdateElevatorPanel(ui->combo_elevator_picker->currentIndex());
    MainWindow::UpdateFloorPanel(ui->combo_floor_picker->currentIndex());
}

void MainWindow::update_ui(){
    MainWindow::RefreshElevatorPanel();
    MainWindow::RefreshFloorPanel();
}

void MainWindow::on_combo_elevator_picker_currentIndexChanged(int index)
{
    if (setup){
        return;
    }

    MainWindow::UpdateElevatorPanel(index);
}

void MainWindow::RefreshElevatorPanel(){
    MainWindow::UpdateElevatorPanel(ui->combo_elevator_picker->currentIndex());
}

void MainWindow::RefreshFloorPanel(){
     MainWindow::UpdateFloorPanel(ui->combo_floor_picker->currentIndex());
}

void MainWindow::UpdateElevatorPanel(int index){
    Elevator* e = controlSystem->getCab(index);


    ui->label_elevator_number->setText(QString::number(e->getCurrentFloor()));
    ui->combo_elevator_dest->setCurrentText(" ");
    ui->label_elevator_info->setText(
                "Elevator " + QString::number(index) + "\n" +
                "Current floor: " + QString::number(e->getCurrentFloor()) + "\n" +
                "Target floor: " + QString::number(e->getTargetFloor()) + "\n" +
                "Direction: " + e->getDirection() + "\n");

}

void MainWindow::UpdateFloorPanel(int index){
    Floor* f = building->getFloor(index);

    ui->label_floor_stats->setText("...");

    for (int i = 0; i < controlSystem->getCabs(); i++){
        if (controlSystem->getCab(i)->getCurrentFloor() == index){
            ui->label_floor_stats->setText(ui->label_floor_stats->text() + "\n" + "Elevator " + QString::number(i) + " is here.");
        }
    }
}

void MainWindow::on_combo_elevator_dest_currentIndexChanged(int index)
{
    if (setup){
        return;
    }

}

void MainWindow::on_button_elevator_dest_clicked()
{
    controlSystem->sendCabTo(ui->combo_elevator_picker->currentIndex(), ui->combo_elevator_dest->currentIndex());
    MainWindow::RefreshElevatorPanel();
    MainWindow::print("Sending elevator " +
                      QString::number(ui->combo_elevator_picker->currentIndex()) +
                      " to floor " +
                      QString::number(ui->combo_elevator_dest->currentIndex()) +
                      + "...");
}

void MainWindow::on_combo_floor_picker_currentIndexChanged(int index)
{
    if (setup){
        return;
    }

    MainWindow::UpdateFloorPanel(index);
}

