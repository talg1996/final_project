#define _CRT_SECURE_NO_WARNINGS
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Station* insertStation(Station* root, Station* newSt) {
    if (!root) return newSt;
    if (newSt->id < root->id)
        root->left = insertStation(root->left, newSt);
    else if (newSt->id > root->id)
        root->right = insertStation(root->right, newSt);
    return root;
}

Station* createStationFromLine(const char* line) {
    char buffer[256];
    strncpy(buffer, line, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* context = NULL;
    char* token = strtok_s(buffer, ",", &context);
    if (!token) return NULL;

    Station* st = malloc(sizeof(Station));
    if (!st) return NULL;
    memset(st, 0, sizeof(Station));

    st->id = atoi(token);

    token = strtok_s(NULL, ",", &context); // name
    if (token) {
        st->name = malloc(strlen(token) + 1);
        if (st->name) strcpy(st->name, token);
    }
    else {
        st->name = malloc(1);
        st->name[0] = '\0';
    }

    token = strtok_s(NULL, ",", &context); // nPorts
    st->nPorts = token ? atoi(token) : 0;

    token = strtok_s(NULL, ",", &context); // coord.x
    st->coord.x = token ? atof(token) : 0.0;

    token = strtok_s(NULL, ",", &context); // coord.y
    st->coord.y = token ? atof(token) : 0.0;

    st->portsList = NULL;
    st->nCars = 0;
    st->carQueue.front = st->carQueue.rear = NULL;
    st->left = st->right = NULL;

    return st;
}

Station* loadStationManager(const char* filename) {
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
        if (lineNum == 1) continue;  // skip header

        // Remove trailing newline characters
        line[strcspn(line, "\r\n")] = '\0';

        Station* st = createStationFromLine(line);
        if (st) {
            root = insertStation(root, st);
        }
    }

    fclose(fp);
    return root;
}
