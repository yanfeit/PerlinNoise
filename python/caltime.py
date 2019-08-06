# I use this to compare the speed numpy and c language
# There is a difference of definition in shape and res between pvigier's and mine
import numpy as np
from perlin2d import generate_perlin_noise_2d
from perlin3d import generate_perlin_noise_3d
from cppnoise import octavePerlin2d, octavePerlin3d
from time import time

lattice2d = (8, 8)
lattice3d = (1, 8, 8)
res2d = (512, 512)
res3d = (20, 512, 512)

t1 = time()
for _ in range(10):
	generate_perlin_noise_2d(res2d, lattice2d)
print('2D noise, numpy time consuming: ', (time()-t1)/10.0)

t1 = time()
for _ in range(10):
	generate_perlin_noise_3d(res3d, lattice3d)
print('3D noise, numpy time consuming: ', (time()-t1)/10.0)

t1 = time()
for _ in range(10):
	octavePerlin2d(lattice2d, res2d)
print('2D noise, cpp time consuming: ', (time()-t1)/10.0)

t1 = time()
for _ in range(10):
	octavePerlin3d(lattice3d, res3d)
print('3D noise, cpp time consuming: ', (time()-t1)/10.0)

