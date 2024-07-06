# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import random
from anim import gen_nRamdomNum
from anim import AnimatedScatter 
import threading
import time
 
# 为线程定义一个函数
def gene_data( threadName, anim):
	count = 1
	while count < 100:
		time.sleep(1)
		count += 1
		_px=gen_nRamdomNum(0, 1920, 50)
		_py=gen_nRamdomNum(0,1080,50)
		anim.set_px_py(_px, _py)
		print("count: {0}".format(count))


if __name__ == '__main__':
	print( "call anim script")
	anim = AnimatedScatter()
	data_thead=threading.Thread(target=gene_data, args=("Thread-1", anim) )
	data_thead.start()
	plt.show()
	data_thead.join()