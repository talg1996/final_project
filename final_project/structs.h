#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>

typedef enum {
    FAST, MID, SLOW
} PortType;

typedef enum {
    OCCUPIED = 1, FREE = 2, OUT_OF_ORDER = 3
} PortStatus;

typedef struct {
    int Year, Month, Day, Hour, Min;
} Date;

struct Port;
struct Car;

typedef struct Car {
    char nLicense[10];
    PortType portType;
    double totalPayed;
    struct Port* pPort;
    int inQueue;
} Car;

typedef struct tCar {
    Car* car;
    struct tCar* right, * left;
} tCar;

typedef struct carNode {
    Car* car;
    struct carNode* next;
} carNode;

typedef struct {
    carNode* front, * rear;
} qCar;

typedef struct Port {
    int num;
    PortType portType;
    PortStatus status;
    Car* p2car;
    Date tin;
    struct Port* next;
} Port;

typedef struct Station {
    int id;
    char* name;
    int nPorts;
    struct {
        double x, y;
    } coord;
    Port* portsList;
    int nCars;
    qCar carQueue;
    struct Station* left, * right;
} Station;

#endif
