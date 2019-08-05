import ctypes
import numpy as np
from time import time
import matplotlib.pyplot as plt
from numpy.ctypeslib import ndpointer

s1 = time()


model = ctypes.CDLL('./libPerlinNoise.dylib')

PerlinNoise2D = model.perlinNoise2D


PerlinNoise2D.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int)

PerlinNoise2D.restype  = ndpointer(dtype=ctypes.c_float, shape=(1024, 1024))

result = PerlinNoise2D(ctypes.c_int(8), 
					ctypes.c_int(8), 
					ctypes.c_int(1024), 
					ctypes.c_int(1024))

print('cpp time consuming: ', time()-s1)

np.savetxt("file2.txt", result )

plt.imshow(result)
plt.show()
