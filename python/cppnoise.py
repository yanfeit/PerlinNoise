# Copyright (c) 2019 by Yanfei Tang (yanfeit89@163.com).
# Open source software license: MIT

import ctypes
import numpy as np
from time import time
import matplotlib.pyplot as plt
from numpy.ctypeslib import ndpointer
from collections import namedtuple

Shape = namedtuple('Shape', 'z y x')
Resolution  = namedtuple('Resolution', 'z y x')

shape      = Shape(0, 8, 16) # [z, y, x]
resolution = Resolution(200, 512, 1024) # resolution in direction [z, y, x]

s1 = time()

# pass the dynamic library
lib = ctypes.CDLL('./libperlinNoise.dylib')

# get the 2d Perlin noise function
perlinNoise2D = lib.perlinNoise2D

# Need specify the types of the argument for function perlinNoise2D
perlinNoise2D.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int)

# This note is extremely useful to understand how to return a 2d array!
# https://stackoverflow.com/questions/43013870/how-to-make-c-return-2d-array-to-python?noredirect=1&lq=1
# We can never pass a 2d array, therefore return 1d array in C function
perlinNoise2D.restype  = ndpointer(dtype=ctypes.c_float, shape=(resolution.y, resolution.x))

result = perlinNoise2D(ctypes.c_int(shape.x), 
					ctypes.c_int(shape.y), 
					ctypes.c_int(resolution.x), 
					ctypes.c_int(resolution.y))

print('cpp time consuming: ', time()-s1)

plt.imshow(result)
plt.show()
