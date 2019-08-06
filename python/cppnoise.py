# Copyright (c) 2019 by Yanfei Tang (yanfeit89@163.com).
# Open source software license: MIT

import ctypes
import numpy as np
from time import time
import matplotlib.pyplot as plt
from numpy.ctypeslib import ndpointer
from collections import namedtuple
import matplotlib.animation as animation

def octavePerlin2d(lattice, res, octaves = 1, persistence=0.5):

	# pass the dynamic library
	lib = ctypes.CDLL('./libperlinNoise.dylib')
	# get the 2d Perlin noise function
	perlinNoise2D = lib.perlinNoise2D
	# Need specify the types of the argument for function perlinNoise2D
	perlinNoise2D.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int)

	# This note is extremely useful to understand how to return a 2d array!
	# https://stackoverflow.com/questions/43013870/how-to-make-c-return-2d-array-to-python?noredirect=1&lq=1
	# We can never pass a 2d array, therefore return 1d array in a C function
	perlinNoise2D.restype = ndpointer(dtype=ctypes.c_float, shape = (res[0], res[1]))
	
	noise = np.zeros(res)
	frequency = 1
	amplitude = 1
	for _ in range(octaves):
		temp = perlinNoise2D(ctypes.c_int(frequency*lattice[1]), 
			ctypes.c_int(frequency*lattice[0]), 
			ctypes.c_int(res[1]), 
			ctypes.c_int(res[0]) )
		noise += amplitude * temp
		frequency *= 2
		amplitude *= persistence
	return noise

def octavePerlin3d(lattice, res, octaves = 1, persistence=0.5):

	lib = ctypes.CDLL('./libperlinNoise.dylib')
	perlinNoise3D = lib.perlinNoise3D
	perlinNoise3D.argtypes = (ctypes.c_int, ctypes.c_int, 
							ctypes.c_int, ctypes.c_int,
							ctypes.c_int, ctypes.c_int)
	perlinNoise3D.restype = ndpointer(dtype=ctypes.c_float, shape = (res[0], res[1], res[2]))

	noise = np.zeros(res)
	frequency = 1
	amplitude = 1
	for _ in range(octaves):
		temp = perlinNoise3D(ctypes.c_int(frequency*lattice[2]), 
			ctypes.c_int(frequency*lattice[1]), 
			ctypes.c_int(frequency*lattice[0]),
			ctypes.c_int(res[2]), 
			ctypes.c_int(res[1]),
			ctypes.c_int(res[0]) )
		noise += amplitude * temp
		frequency *= 2
		amplitude *= persistence
	return noise

if __name__ == '__main__':
	Lattice       = namedtuple('Lattice', 'z y x')
	Resolution    = namedtuple('Resolution', 'z y x')

	lattice      = Lattice(1, 8, 16) # [z, y, x]
	resolution   = Resolution(200, 512, 1024) # resolution in direction [z, y, x]

	# pass the dynamic library
	lib = ctypes.CDLL('./libperlinNoise.dylib')

	# get the 2d Perlin noise function
	perlinNoise2D = lib.perlinNoise2D

	# Need specify the types of the argument for function perlinNoise2D
	perlinNoise2D.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int)

	# This note is extremely useful to understand how to return a 2d array!
	# https://stackoverflow.com/questions/43013870/how-to-make-c-return-2d-array-to-python?noredirect=1&lq=1
	# We can never pass a 2d array, therefore return 1d array in a C function
	perlinNoise2D.restype  = ndpointer(dtype=ctypes.c_float, shape=(resolution.y, resolution.x))

	result = perlinNoise2D(ctypes.c_int(lattice.x), 
					ctypes.c_int(lattice.y), 
					ctypes.c_int(resolution.x), 
					ctypes.c_int(resolution.y))


	plt.imshow(result, cmap = 'gray')
	plt.tight_layout()
	plt.savefig("noise2d.png")
	plt.show()

	result = octavePerlin2d((8, 16), (512, 1024), 4)
	plt.imshow(result, cmap = 'gray')
	plt.tight_layout()
	plt.savefig("octavenoise2d.png")
	plt.show()

	noise = octavePerlin3d((1, 4, 4), (40, 256, 256), 4)
	fig = plt.figure()
	images = [[plt.imshow(layer, cmap='hot', interpolation='lanczos', animated=True)] for layer in noise]
	animation = animation.ArtistAnimation(fig, images, interval=50, blit=False)
	plt.tight_layout()
	animation.save('cppnoise.gif', writer="imagemagick", fps = 20, dpi = 100)
	plt.show()




