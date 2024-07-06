# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import random


def gen_nRamdomNum(min, max, n):
	_ret_arry=[]
	for i in range(n):
		_ret_arry.append(random.randint(min, max))
	return _ret_arry
		
class AnimatedScatter(object):
	def __init__(self, numpoints=50):
		self.px = []
		self.py = []
		self.max_x = 1920
		self.max_y = 1280
		self.numpoints = numpoints
		# Setup the figure and axes...
		self.fig, self.ax = plt.subplots()
		# Then setup FuncAnimation.
		self.ani = animation.FuncAnimation(self.fig, self.update, frames=600, interval=1000, init_func=self.setup_plot, blit=True)


	def set_px_py(self, _px, _py):
		self.py.clear()
		self.px.clear()
		self.px = _px
		self.py = _py
			
				
	def setup_plot(self):
		#self.px.clear()
		#self.py.clear()

		#self.px = gen_nRamdomNum(0,1920, 50)
		#self.py = gen_nRamdomNum(0,1280, 50)

		self.scat = self.ax.scatter(self.px, self.py,linewidths=0.2, c="red")
		self.ax.axis([0, self.max_x, 0, self.max_y])
		# For FuncAnimation's sake, we need to return the artist we'll be using
		# Note that it expects a sequence of artists, thus the trailing comma.
		return self.scat,

	def update(self, i):
		#self.px.clear()
		#self.py.clear()

		#self.px = gen_nRamdomNum(0,1920, 50)
		#self.py = gen_nRamdomNum(0,1280, 50)
		self.scat = self.ax.scatter(self.px, self.py,linewidths=0.2, c="red")
		# We need to return the updated artist for FuncAnimation to draw..
		# Note that it expects a sequence of artists, thus the trailing comma.
		return self.scat,

if __name__ == '__main__':
    a = AnimatedScatter()
    plt.show()
