/*
The code essentially is from the WIKI page.
https://en.wikipedia.org/wiki/Perlin_noise

Copyright (c) 2019 by Yanfei Tang (yanfeit89@163.com).
Open source software license: MIT
*/
#include "PerlinNoise.h"

//Create a 2D array of gradients whose directions are random.
Vector2D** gradient2D(int iymax, int ixmax){
	srand (time(NULL));
	int i, j;
	Float angle;

	// Create a 2d array of points in 2d...
	Vector2D **gradients = (Vector2D **)malloc(iymax * sizeof(Vector2D *)); 
    for (i = 0; i < iymax; i++){
         gradients[i] = (Vector2D *)malloc(ixmax * sizeof(Vector2D)); 
    }

    for (i = 0; i < iymax; i++){
    	for (j = 0; j < ixmax; j++){
    		angle = 2 * PI * rand()/RAND_MAX;
    		gradients[i][j].x = cos(angle);
    		gradients[i][j].y = sin(angle);
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
	Float* perlinNoise2D(int shape_x, int shape_y, int res_x, int res_y){

		int i, j;
		Float x, y, delta_x, delta_y;

		Vector2D** gradients;

		gradients = gradient2D(shape_x+1, shape_y+1);

		Float *noise = (Float *)malloc(res_y*res_x* sizeof(Float)); 
		
		delta_x = Float(shape_x) / Float(res_x);
		delta_y = Float(shape_y) / Float(res_y);

		for (i = 0; i < res_y; i++){
			y = Float(i) * delta_y;
			for (j = 0; j < res_x; j++){
				x = Float(j) * delta_x;
				noise[i*res_x + j] = perlin2D(x, y, gradients);
			}
		}


		return noise;
	} 
}