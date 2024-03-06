#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QVector>
#include <QString>

class Elevator{
public:
    Elevator(){
        currentFloor = 0;
        targetFloor = 0;
        direction = "none";
        state = "open";
    }

    void setDoorState(QString state);
    int getCurrentFloor();
    void setTargetFloor(int floor);
    int getTargetFloor();
    void setDirection(QString direction);
    QString getDirection();
private:
    int currentFloor;
    int targetFloor;
    QString direction;
    QString state;
};

class ECS{
public:
    void addCab();
    int getCabs();
    Elevator* getCab(int index);
    void callCabTo(int floor);
    void sendCabTo(int cab, int floor);
private:
    QVector<Elevator*> cabs;
    QVector<int> floorRequests;
};

class Interface{
public:
    void sendSignal();
    void printMessage();
private:
    QString message;
};

class Sensor{
public:
    int getState();
private:
    int state;
};

class Floor{
public:
    int getFloor();
private:
    int number;
};

class Building{
public:
    int getFloors();
    Floor* getFloor(int index);
    void addFloor();
private:
    QVector<Floor*> floors;
};

#endif // ELEVATOR_H
