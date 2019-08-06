/*
The code essentially is from the WIKI page and Adian's webpage.
https://en.wikipedia.org/wiki/Perlin_noise
https://flafla2.github.io/2014/08/09/perlinnoise.html

Copyright (c) 2019 by Yanfei Tang (yanfeit89@163.com).
Open source software license: MIT
*/
#include "PerlinNoise.h"

//Create a 2D array of gradients whose directions are random.
// A variation is to use Perlin's method.
Vector2D** gradient2D(int ixmax, int iymax){
	srand (time(NULL));
	int i, j;
	Float angle;

	// Create a 2d array of points in 2d...
	Vector2D **gradients = (Vector2D **)malloc(iymax * sizeof(Vector2D *)); 
    for (i = 0; i < iymax; i++){
         gradients[i] = (Vector2D *)malloc(ixmax * sizeof(Vector2D)); 
    }

    for (j = 0; j < iymax; j++){
    	for (i = 0; i < ixmax; i++){
    		angle = 2 * PI * rand()/RAND_MAX;
    		gradients[j][i].x = cos(angle);
    		gradients[j][i].y = sin(angle);
    	}
    }
    return gradients;
}

// Computes the dot product of the distance and gradient vectors.
Float dotGridGradient2D(int ix, int iy, Float x, Float y, Vector2D** gradients) {

    // Compute the distance vector
    Float dx = x - (Float)ix;
    Float dy = y - (Float)iy;

    // Compute the dot-product
    return (dx*gradients[iy][ix].x + dy*gradients[iy][ix].y);
}

Float perlin2D(Float x, Float y, Vector2D** gradients) {

    // Determine grid cell coordinates
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    Float sx = fade(x - (Float)x0);
    Float sy = fade(y - (Float)y0);

    // Interpolate between grid point gradients
    Float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient2D(x0, y0, x, y, gradients);
    n1 = dotGridGradient2D(x1, y0, x, y, gradients);
    ix0 = lerp(n0, n1, sx);

    n0 = dotGridGradient2D(x0, y1, x, y, gradients);
    n1 = dotGridGradient2D(x1, y1, x, y, gradients);
    ix1 = lerp(n0, n1, sx);

    value = lerp(ix0, ix1, sy);
    return value;
}


extern "C" {
    // My definitions of shape and res are inversed from pvigier's 
    // see his imprssive numpy code https://github.com/pvigier/perlin-numpy
	Float* perlinNoise2D(int lattice_x, int lattice_y, int res_x, int res_y){

		int i, j;
		Float x, y, delta_x, delta_y;

		Vector2D** gradients;

		gradients = gradient2D(lattice_x+1, lattice_y+1);

		Float *noise = (Float *)malloc(res_y*res_x* sizeof(Float)); 
		
		delta_x = Float(lattice_x) / Float(res_x);
		delta_y = Float(lattice_y) / Float(res_y);

		for (j = 0; j < res_y; j++){
			y = Float(j) * delta_y;
			for (i = 0; i < res_x; i++){
				x = Float(i) * delta_x;
				noise[j*res_x + i] = perlin2D(x, y, gradients);
			}
		}


		return noise;
	} 
}

// Create a 3D array of gradients.
Vector3D*** gradient3D(int ixmax, int iymax, int izmax){
    srand (time(NULL));
    int i, j, k;
    Float polar, azimutal;

    // Create a 2d array of points in 2d...
    Vector3D ***gradients = (Vector3D ***)malloc(izmax * sizeof(Vector3D **)); 
    for (k = 0; k < izmax; k++){
        gradients[k] = (Vector3D **)malloc(iymax * sizeof(Vector3D *)); 
        for (j = 0; j < iymax; j++){
            gradients[k][j] = (Vector3D *)malloc(ixmax * sizeof(Vector3D)); 
        }       
    }

    // give value to the arrays
    for (k = 0; k < izmax; k++){
        for (j = 0; j < iymax; j++){
            for (i = 0; i < ixmax; i++){
                polar    = PI * rand()/RAND_MAX;
                azimutal = 2 * PI * rand()/RAND_MAX;
                gradients[k][j][i].x = cos(azimutal) * sin(polar);
                gradients[k][j][i].y = sin(azimutal) * sin(polar);
                gradients[k][j][i].z = cos(polar);
            }
        }
    }
    return gradients;
}

// Compute the dot product of the distance and gradient vectors.
Float dotGridGradient3D(int ix, int iy, int iz, Float x, Float y, Float z, Vector3D*** gradients){
    // Compute the distance vector
    Float dx = x - (Float)ix;
    Float dy = y - (Float)iy;
    Float dz = z - (Float)iz;

    // Compute the dot-product
    return (dx*gradients[iz][iy][ix].x + dy*gradients[iz][iy][ix].y + dz*gradients[iz][iy][ix].z);
}

// return perlin noise on a 3D map
Float perlin3D(Float x, Float y, Float z, Vector3D*** gradients){
    // Determine grid cell coordinates
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;
    int z0 = (int)z;
    int z1 = z0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    Float sx = fade(x - (Float)x0);
    Float sy = fade(y - (Float)y0);
    Float sz = fade(z - (Float)z0);

    // Interpolate between grid point gradients
    Float n0, n1, ix0, ix1, iy0, iy1, value;

    n0 = dotGridGradient3D(x0, y0, z0, x, y, z, gradients);
    n1 = dotGridGradient3D(x1, y0, z0, x, y, z, gradients);
    ix0 = lerp(n0, n1, sx);

    n0 = dotGridGradient3D(x0, y1, z0, x, y, z, gradients);
    n1 = dotGridGradient3D(x1, y1, z0, x, y, z, gradients);
    ix1 = lerp(n0, n1, sx);

    iy0 = lerp(ix0, ix1, sy);

    n0 = dotGridGradient3D(x0, y0, z1, x, y, z, gradients);
    n1 = dotGridGradient3D(x1, y0, z1, x, y, z, gradients);
    ix0 = lerp(n0, n1, sx);

    n0 = dotGridGradient3D(x0, y1, z1, x, y, z, gradients);
    n1 = dotGridGradient3D(x1, y1, z1, x, y, z, gradients);
    ix1 = lerp(n0, n1, sx);

    iy1 = lerp(ix0, ix1, sy);

    value = lerp(iy0, iy1, sz);

    return value;
}

// for python usage
extern "C" {
    Float* perlinNoise3D(int lattice_x, int lattice_y, int lattice_z, int res_x, int res_y, int res_z){
        int i, j, k;
        Float x, y, z, delta_x, delta_y, delta_z;

        Vector3D*** gradients;

        gradients = gradient3D(lattice_x+1, lattice_y+1, lattice_z+1);

        Float *noise = (Float *)malloc(res_y*res_x*res_z * sizeof(Float)); 
        
        delta_x = Float(lattice_x) / Float(res_x);
        delta_y = Float(lattice_y) / Float(res_y);
        delta_z = Float(lattice_z) / Float(res_z);

        for (k = 0; k < res_z; k++){
            z = Float(k) * delta_z;
            for (j = 0; j < res_y; j++){
                y = Float(j) * delta_y;
                for (i = 0; i < res_x; i++){
                    x = Float(i) * delta_x;
                    noise[k*res_y*res_x + j*res_x + i] = perlin3D(x, y, z, gradients);
                }
            }
        }

        return noise;
    }
}