#include "Sculptor.h"

int main(){
    
    //Estou usando o cutVoxel para cortar os voxels extremos da esfera e da elipse, para que elas fiquem "lisas".

    Sculptor cubo(16, 16, 16); 

    cubo.setColor(0.0, 1.0, 0.0, 1.0);
    cubo.putBox(0, 15, 0, 15, 0, 15);
    cubo.writeOFF("cubo.off");
    
    Sculptor esfera(30, 30, 30);
    
    esfera.setColor(0.0, 0.0, 1.0, 1.0);
    esfera.putSphere(15, 15, 15, 8);
    esfera.cutVoxel(23, 15, 15);
    esfera.cutVoxel(7, 15, 15);
    esfera.cutVoxel(15, 23, 15);
    esfera.cutVoxel(15, 7, 15);
    esfera.cutVoxel(15, 15, 23);
    esfera.cutVoxel(15, 15, 7);
    esfera.writeOFF("esfera.off");
    
    Sculptor elipse(30,30,30);

    elipse.setColor(1.0, 0.0, 0.0, 1.0);
    elipse.putEllipsoid(18, 18, 18, 10, 8, 6);
    elipse.cutVoxel(28, 18, 18);
    elipse.cutVoxel(8, 18, 18);
    elipse.cutVoxel(18, 26, 18);
    elipse.cutVoxel(18, 10, 18);
    elipse.cutVoxel(18, 18, 24);
    elipse.cutVoxel(18, 18, 12);
    elipse.writeOFF("elipse.off");

    return 0;
}