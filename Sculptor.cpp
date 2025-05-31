#include "Sculptor.h"
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

void Sculptor::writeOFF(const char *filename){

    std::ofstream fout(filename);
        if (!fout.is_open()){
            std::cerr << "Erro \n";
            return;
        }

   
    int totalVoxels = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    totalVoxels++;
                }
            }
        }
    }

   
    fout << "OFF\n";

    fout << totalVoxels * 8 << " " << totalVoxels * 6 << " 0\n";

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                   
                    float x = i - 0.5, y = j - 0.5, z = k - 0.5; // Centralizado
                    fout << x << " " << y << " " << z << "\n"; // Vértice 0
                    fout << x << " " << y + 1 << " " << z << "\n"; // Vértice 1
                    fout << x + 1 << " " << y + 1 << " " << z << "\n"; // Vértice 2
                    fout << x + 1 << " " << y << " " << z << "\n"; // Vértice 3
                    fout << x << " " << y << " " << z + 1 << "\n"; // Vértice 4
                    fout << x << " " << y + 1 << " " << z + 1 << "\n"; // Vértice 5
                    fout << x + 1 << " " << y + 1 << " " << z + 1 << "\n"; // Vértice 6
                    fout << x + 1 << " " << y << " " << z + 1 << "\n"; // Vértice 7
                }
            }
        }
    }

    
    int vertexOffset = 0; 
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    
                    float r = v[i][j][k].r;
                    float g = v[i][j][k].g;
                    float b = v[i][j][k].b;
                    float a = v[i][j][k].a;

                    
                    // Face frontal (Z+)
                    fout << "4 " << vertexOffset + 4 << " " << vertexOffset + 5 << " "
                         << vertexOffset + 6 << " " << vertexOffset + 7 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    // Face traseira (Z-)
                    fout << "4 " << vertexOffset + 0 << " " << vertexOffset + 1 << " "
                         << vertexOffset + 2 << " " << vertexOffset + 3 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    // Face inferior (Y-)
                    fout << "4 " << vertexOffset + 0 << " " << vertexOffset + 3 << " "
                         << vertexOffset + 7 << " " << vertexOffset + 4 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    // Face superior (Y+)
                    fout << "4 " << vertexOffset + 1 << " " << vertexOffset + 2 << " "
                         << vertexOffset + 6 << " " << vertexOffset + 5 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    // Face esquerda (X-)
                    fout << "4 " << vertexOffset + 0 << " " << vertexOffset + 1 << " "
                         << vertexOffset + 5 << " " << vertexOffset + 4 << " "
                         << r << " " << g << " " << b << " " << a << "\n";
                    // Face direita (X+)
                    fout << "4 " << vertexOffset + 3 << " " << vertexOffset + 2 << " "
                         << vertexOffset + 6 << " " << vertexOffset + 7 << " "
                         << r << " " << g << " " << b << " " << a << "\n";

                    vertexOffset += 8; 
                }
            }
        }
    }

    fout.close();
    std::cout << "Arquivo " << filename << " criado!\n";
}


