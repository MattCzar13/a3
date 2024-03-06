#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QVector>
#include <QString>

class Elevator{
public:
    void setDoorState(QString state);
private:
    int currentFloor;
    int targetFloor;
    QString direction;
    QString state;
};

class ECS{
public:
    void addCab();
    void sendCabTo(int floor);
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
    Floor getFloor(int index);
    void addFloor();
private:
    QVector<Floor*> floors;
};

#endif // ELEVATOR_H
