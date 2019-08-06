/*
The code essentially is from the WIKI page and Adian's webpage.
https://en.wikipedia.org/wiki/Perlin_noise
https://flafla2.github.io/2014/08/09/perlinnoise.html

Copyright (c) 2019 by Yanfei Tang (yanfeit89@163.com).
Open source software license: MIT
*/
#include "PerlinNoise.h"

// This main is used to check if the function
// works or not
int main(int argc, char **argv){

	Float* noise;

   int shape_x, shape_y, shape_z;
   int res_x, res_y, res_z;

   shape_x = 16;
   shape_y = 8;
   shape_z = 2;

   res_x   = 1024;
   res_y   = 512;
   res_z   = 100;

	noise = perlinNoise2D(shape_x, shape_y, res_x, res_y);

	FILE *fp;

	int i, j;
   	// open the file for writing
   	fp = fopen ("./file.txt","w");
 
   	for(i = 0; i < res_y; i++){
   		for (j = 0; j < res_x; j++){
   			fprintf (fp, "%f\t", noise[i*res_x + j]);
   		}
       	fprintf(fp, "\n");
   	}
 
   	// close the file
   	fclose (fp);

   noise = perlinNoise3D(shape_x, shape_y, shape_z, res_x, res_y, res_z);

	return 0;
}


