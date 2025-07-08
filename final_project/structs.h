/* structures.h */
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdlib.h>

/* Charging speed enumeration */
typedef enum {
    FAST,
    MID,
    SLOW
} PortType;

/* Charging port status enumeration */
typedef enum {
    OCCUPIED = 1,
    FREE = 2,
    OUT_OF_ORDER = 3
} PortStatus;

/* Date structure */
typedef struct {
    int Year;   /* >=1900 and <= current year */
    int Month;  /* 1-12 */
    int Day;    /* 1-31 */
    int Hour;   /* 0-23 */
    int Min;    /* 0-59 */
} Date;

/* Forward declarations */
struct Port;
struct Car;

/* Car structure */
typedef struct Car {
    char nLicense[10];  /* 9-character license string + '\0' */
    PortType portType;  /* Preferred charging speed */
    double totalPayed;  /* Total payment to date */
    struct Port *pPort; /* Pointer to charging Port, NULL if none */
    int inQueue;        /* 0: not in queue/charging, 1: in queue */
} Car;

/* Binary tree node for cars database */
typedef struct tCar {
    Car *car;           /* Pointer to Car */
    struct tCar *right; /* Right subtree */
    struct tCar *left;  /* Left subtree */
} tCar;

/* Node in car queue linked list */
typedef struct carNode {
    Car *car;               /* Pointer to Car */
    struct carNode *next;   /* Next in queue */
} carNode;

/* Car queue manager */
typedef struct {
    carNode *front; /* Front of queue */
    carNode *rear;  /* Rear of queue */
} qCar;

/* Charging port structure */
typedef struct Port {
    int num;               /* Port number */
    PortType portType;     /* Charging speed */
    PortStatus status;     /* OCCUPIED, FREE, or OUT_OF_ORDER */
    Car *p2car;            /* Pointer to connected Car, NULL if none */
    Date tin;              /* Start time of charging */
    struct Port *next;     /* Next port in linked list */
} Port;

/* Station structure */
typedef struct Station {
    int id;                /* Unique station ID */
    char *name;            /* Dynamically allocated station name */
    int nPorts;            /* Number of ports in station */
    struct {
        double x;
        double y;
    } coord;               /* Location coordinates */
    Port *portsList;       /* Head of linked list of ports */
    int nCars;             /* Number of cars in queue */
    qCar carQueue;         /* Queue of cars waiting */
    struct Station *right; /* Right subtree */
    struct Station *left;  /* Left subtree */
} Station;

typedef struct {
    Station* head;       /* root של העץ */
} StationManager;

#endif /* STRUCTURES_H */
