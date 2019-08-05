/*
The code essentially is from the WIKI page.
https://en.wikipedia.org/wiki/Perlin_noise

Copyright (c) 2019 by Yanfei Tang (yanfeit89@163.com).
Open source software license: MIT
*/
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>

#define PI 3.1415926535

#ifndef PRECISION
#define PRECISION 1
#endif
#if PRECISION==1
typedef float Float;
#else
typedef double Float;
#endif

using namespace std;

struct Vector2D
{
	Float x, y;
};

struct Vector3D
{
	Float x, y, z;
};

//high order polynomial function/s-curve.
//fade(0) = 0.0
//fade(0.5) = 0.5
//fade(1.0) = 1.0
inline Float fade(Float t){
	return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

//weighted function blance a0 and a1
//linearly interpolate a0 and a1 with weight w ranging in [0.0, 1.0]
inline Float lerp(Float a0, Float a1, Float w){
	return (1.0 - w)*a0 + w*a1;
}

//Create a 2D array of gradients whose directions are random.
Vector2D** gradient2D(int iymax, int ixmax);

// Computes the dot product of the distance and gradient vectors.
Float dotGridGradient2D(int ix, int iy, Float x, Float y, Vector2D** gradients);

// return perlin noise on a single 2D point
Float perlin2D(Float x, Float y, Vector2D** gradients);

// create dll for ctype python usage
extern "C" {
	Float* perlinNoise2D(int shape_x, int shape_y, int res_x, int res_y);
} 



