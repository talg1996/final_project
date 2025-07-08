#include <stdio.h>
#include "structs.h"




int main() {
    
    Station* root = NULL;
    loadStationManager("C:\\Users\\talg1\\source\\repos\\final_project\\final_project\\Stations.txt",&root);
    if (!root) {
        printf("Failed to load stations\n");
        return 1;
    }



    return 0;
}