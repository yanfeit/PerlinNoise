#include "PerlinNoise.h"

int main(int argc, char **argv){

	Float* noise;
	noise = perlinNoise2D(8, 8, 1024, 1024);
	FILE *fp;

	int i, j;
   	// open the file for writing
   	fp = fopen ("./file.txt","w");
 
   	for(i = 0; i < 1024; i++){
   		for (j = 0; j < 1024; j++){
   			fprintf (fp, "%f\t", noise[i*1024 + j]);
   		}
       	fprintf(fp, "\n");
   	}
 
   	// close the file
   	fclose (fp);

	return 0;
}


