#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QTimer>
#include <QTimerEvent>

class Elevator : public QObject{
    Q_OBJECT
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
    void setID(int id);
private:
    int id;
    int currentFloor;
    int targetFloor;
    QString direction;
    QString state;
    int timerId;
protected:
    void timerEvent(QTimerEvent *event);
signals:
    void ui_change();
};

class ECS{
public:
    Elevator* addCab();
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
