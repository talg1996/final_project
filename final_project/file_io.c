/* file_io.c */
#define _CRT_SECURE_NO_WARNINGS  /* ������ ������ MSVC �� �������� "�� ������" */
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Manager for Stations BST */
typedef struct {
    Station* head;       /* root �� ��� */
} StationManager;

/* Insert station into BST by ID */
Station* insertStation(Station* root, Station* newSt) {
    if (!root) return newSt;
    if (newSt->id < root->id)
        root->left = insertStation(root->left, newSt);
    else if (newSt->id > root->id)
        root->right = insertStation(root->right, newSt);
    return root;
}

/* Load stations from a CSV file into a BST and return as manager */
StationManager* loadStationManager(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    char line[256];
    Station* root = NULL;
    int lineNum = 0;

    while (fgets(line, sizeof(line), fp)) {
        lineNum++;
        if (lineNum == 1) continue;  /* ����� �� ����� */

        /* ���� �� \n ���� ����� */
        line[strcspn(line, "\r\n")] = '\0';

        /* ����� ����� ����� ������� strtok_s */
        char* context = NULL;
        char* token = strtok_s(line, ",", &context);
        if (!token) continue;

        /* ����� ���� ���� */
        Station* st = malloc(sizeof(Station));
        memset(st, 0, sizeof(Station));

        /* ����� ���� ���� */
        st->id = atoi(token);
        token = strtok_s(NULL, ",", &context);
        st->name = token ? _strdup(token) : _strdup("");
        token = strtok_s(NULL, ",", &context);
        st->nPorts = token ? atoi(token) : 0;
        token = strtok_s(NULL, ",", &context);
        st->coord.x = token ? atof(token) : 0.0;
        token = strtok_s(NULL, ",", &context);
        st->coord.y = token ? atof(token) : 0.0;

        /* ����� ���� ������ */
        st->portsList = NULL;
        st->nCars = 0;
        st->carQueue.front = st->carQueue.rear = NULL;
        st->left = st->right = NULL;

        /* ����� ��� */
        root = insertStation(root, st);
    }

    fclose(fp);

    /* ����� ���� ����� */
    StationManager* mgr = malloc(sizeof(StationManager));
    mgr->head = root;
    return mgr;
}
