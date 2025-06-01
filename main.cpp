#include "Sculptor.h"

int main(){
    
    Sculptor cubo(16, 16, 16); 

    cubo.setColor(1.0, 0.0, 0.0, 1.0);
    cubo.putBox(0, 15, 0, 15, 0, 15); 

    cubo.writeOFF("cubo.off");
    
    return 0;
}