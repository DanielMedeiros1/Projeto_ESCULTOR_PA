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
    
    Sculptor elipse(30,30,30);

    elipse.setColor(1.0, 0.0, 0.0, 1.0);
    elipse.putEllipsoid(18, 18, 18, 10, 8, 6);
    elipse.writeOFF("elipse.off");

    return 0;
}