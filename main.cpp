#include "Sculptor.h"

int main(){
    
    Sculptor cubo(16, 16, 16); 

    cubo.setColor(0.0, 1.0, 0.0, 1.0);
    cubo.putBox(0, 15, 0, 15, 0, 15);
    cubo.writeOFF("cubo.off");
    
    Sculptor esfera(30, 30, 30);
    
    esfera.setColor(0.0, 0.0, 1.0, 1.0);
    esfera.putSphere(15, 15, 15, 8);
    esfera.writeOFF("esfera.off");
    
    return 0;
}