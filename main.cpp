#include "Sculptor.h"
#include <cstdlib> 

int main() {
    
    Sculptor diamante(16, 16, 16); 

    diamante.setColor(0.5, 0.5, 0.5, 1.0);
    diamante.putBox(0, 15, 0, 15, 0, 15); 

    
    diamante.setColor(0.25, 0.65, 1.0, 1.0); 
    for (int i = 0; i < 10; i++) { 
        int x = rand() % 14 + 1; 
        int y = rand() % 14 + 1;
        int z = rand() % 14 + 1;
        
        diamante.putVoxel(x, y, z);
        diamante.putVoxel(x+1, y, z);
        diamante.putVoxel(x, y+1, z);
        diamante.putVoxel(x, y, z+1);
    }

    diamante.writeOFF("diamante.off");
    return 0;
}