import numpy as np
from time import time

class PerlinNoise(object):

	def __init__(self, shape = [8, 8], res = [1024, 1024]):

		self.shape = shape
		self.res   = res

		self.gradient = self.gradient()

		self.delta = (shape[0] / res[0], shape[1] / res[1])
		self.d = (res[0] // shape[0], res[1] // shape[1])

		self.noise = np.zeros(res)

		for i in range(res[0]):
			x = i * self.delta[0]
			for j in range(res[1]):
				y = j * self.delta[1]
				self.noise[i, j] = self.perlin(x, y)

	def lerp(self, a0, a1, w):
		return (1 - w) * a0 + w * a1

	def fade(self, t):
		return 6*t**5 - 15*t**4 + 10*t**3

	def gradient(self):

		angles = 2 * np.pi * np.random.rand(self.shape[0] + 1, self.shape[1] + 1)
		gradients = np.dstack( (np.cos(angles), np.sin(angles)) )
		return gradients

	def dotGridGradient(self, ix, iy, x, y):
		
		dx = x - ix
		dy = y - iy

		return dx*self.gradient[ix, iy, 0] + dy*self.gradient[ix, iy, 1]

	def perlin(self, x, y):

		x0 = int(x)
		x1 = x0 + 1
		y0 = int(y)
		y1 = y0 + 1

		sx = self.fade(x - x0)
		sy = self.fade(y - y0)

		n0 = self.dotGridGradient(x0, y0, x, y)
		n1 = self.dotGridGradient(x1, y0, x, y)

		ix0 = self.lerp(n0, n1, sx)

		n0 = self.dotGridGradient(x0, y1, x, y)
		n1 = self.dotGridGradient(x1, y1, x, y)
		ix1 = self.lerp(n0, n1, sx)

		value = self.lerp(ix0, ix1, sy)
		return value

if __name__ == "__main__":

	import matplotlib.pyplot as plt

	s1 = time()	
	model = PerlinNoise(shape = [8, 8], res = [1024, 1024])
	print('cpp time consuming: ', time()-s1)
	#plt.imshow(model.noise)

	#plt.show()
