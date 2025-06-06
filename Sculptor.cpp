#include "Sculptor.h"
#include <fstream>
#include <iostream>
#include <iomanip>



Sculptor::Sculptor(int _nx, int _ny, int _nz){

    nx = _nx; 
    ny = _ny; 
    nz = _nz;
    v = new Voxel **[nx];

    for(int i = 0; i < nx; i++){
        v[i] = new Voxel *[ny];
        for(int j = 0; j < ny; j++){
            v[i][j] = new Voxel [nz];
            for(int k = 0; k < nz; k++){
                v[i][j][k].show = false;
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
    
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz){ 
        v[x][y][z].show = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor ::cutVoxel(int x, int y, int z){ 
    
    v[x][y][z].show = false; 

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

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      for (int k = z0; k <= z1; k++) {
        cutVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
  
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){        
                    
                float dx = i - xcenter;
                float dy = j - ycenter;
                float dz = k - zcenter;                
                if ((dx * dx + dy * dy + dz * dz) <= radius * radius){
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if ((i - xcenter) * (i - xcenter) + (j - ycenter) * (j - ycenter) + (k - zcenter) * (k - zcenter) <= radius * radius){
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                
                float dx = (float)(i - xcenter) / rx;
                float dy = (float)(j - ycenter) / ry;
                float dz = (float)(k - zcenter) / rz;
                
                if(dx * dx + dy * dy + dz * dz <= 1.0)
                    putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                
                float dx = (float)(i - xcenter) / rx;
                float dy = (float)(j - ycenter) / ry;
                float dz = (float)(k - zcenter) / rz;
                
                if(dx * dx + dy * dy + dz * dz <= 1.0){
                    cutVoxel(i,j,k);
                }
            }    
        }
    }
}


void Sculptor::writeOFF(const char *filename){

    std::ofstream outfile(filename);
        if (!outfile.is_open()){
            std::cerr << "Erro \n";
            return;
        }

   
    int totalVoxels = 0;
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if (v[i][j][k].show){
                    totalVoxels++;
                }
            }
        }
    }

   
    outfile << "OFF\n";

    outfile << totalVoxels * 8 << " " << totalVoxels * 6 << " 0\n";

    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if (v[i][j][k].show){
                   
                    float x = i - 0.5, y = j - 0.5, z = k - 0.5; // Centralizado
                    outfile << x << " " << y << " " << z << "\n"; // Vértice 0
                    outfile << x << " " << y + 1 << " " << z << "\n"; // Vértice 1
                    outfile << x + 1 << " " << y + 1 << " " << z << "\n"; // Vértice 2
                    outfile << x + 1 << " " << y << " " << z << "\n"; // Vértice 3
                    outfile << x << " " << y << " " << z + 1 << "\n"; // Vértice 4
                    outfile << x << " " << y + 1 << " " << z + 1 << "\n"; // Vértice 5
                    outfile << x + 1 << " " << y + 1 << " " << z + 1 << "\n"; // Vértice 6
                    outfile << x + 1 << " " << y << " " << z + 1 << "\n"; // Vértice 7
                }
            }
        }
    }

    int offset = 0;
    for (int i = 0; i < nx; i++){
      for (int j = 0; j < ny; j++){
        for (int k = 0; k < nz; k++){
          if (v[i][j][k].show){
          
            outfile << std::fixed
                    << std::setprecision(2);

            outfile << "4 " << 4 + offset << " " << 5 + offset << " "
                    << 6 + offset << " " << 7 + offset << " " << v[i][j][k].r
                    << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                    << v[i][j][k].a << std::endl;

            outfile << "4 " << 0 + offset << " " << 1 + offset << " "
                    << 2 + offset << " " << 3 + offset << " " << v[i][j][k].r
                    << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                    << v[i][j][k].a << std::endl;

            outfile << "4 " << 0 + offset << " " << 3 + offset << " "
                    << 7 + offset << " " << 4 + offset << " " << v[i][j][k].r
                    << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                    << v[i][j][k].a << std::endl;
                  
            outfile << "4 " << 1 + offset << " " << 2 + offset << " "
                    << 6 + offset << " " << 5 + offset << " " << v[i][j][k].r
                    << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                    << v[i][j][k].a << std::endl;

            outfile << "4 " << 0 + offset << " " << 1 + offset << " "
                    << 5 + offset << " " << 4 + offset << " " << v[i][j][k].r
                    << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                    << v[i][j][k].a << std::endl;

            outfile << "4 " << 3 + offset << " " << 2 + offset << " "
                    << 6 + offset << " " << 7 + offset << " " << v[i][j][k].r
                    << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                    << v[i][j][k].a << std::endl;
          
            offset += 8;

        }
      }
    }
  }

  
  outfile.close();

  std ::cout << "Arquivo " << filename << " criado" << std::endl;
}



