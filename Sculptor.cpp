#include <Sculptor.h>
#include <fstream>
#include <iostream>

Sculptor::Sculptor(int nx_, int ny_, int nz_){

    nx = nx_; 
    ny = ny_; 
    nz = nz_;
    v = new Voxel **[nx];

    for(int i = 0; i < nx; i++){
        v[i] = new Voxel *[ny];
        for(int j = 0; j < ny; j++){
            v[i][j] = new Voxel [nz];
            for(int k = 0; k < nz; k++){
                v[i][j][k].show = true;
            }
        }
    }
}

Sculptor::~Sculptor(){

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            delete[] v[i][j]; 
        }
        delete[] v[i];
    }
    delete[] v;

}

void Sculptor::setColor(float r, float g, float b, float a){
   
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z){
    
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) 
        v[x][y][z].show = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;

}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                putVoxel(i, j, k);
            }
        }
    }
}




