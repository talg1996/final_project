#include <stdio.h>
#include "structs.h"

// הצהרות לפונקציות שהן בקבצים אחרים
Station* loadStationManager(const char* filename);

int main() {
    Station* root = loadStationManager("C:\\Users\\talg1\\source\\repos\\final_project\\final_project\\Stations.txt");

    if (!root) {
        printf("Failed to load stations.\n");
        return 1;
    }

    printf("\nLoaded stations (in-order):\n");

    return 0;
}
