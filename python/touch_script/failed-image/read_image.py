# -*- coding: utf-8 -*-

import os 
import codecs
import re
import stat
import subprocess



QFILE_DIR=r'C:/Program Files (x86)/Qualcomm/QPST/bin/'
IMAGEINFO_FILE=r"C:/Users/Jzhang91/AppData/Roaming/Qualcomm/QFIL/COM13_PartitionsList.xml"

class image_node:
	def  __init__(self):
		self._label =""
		self._physical_partition_number=""
		self._start_sector=""
		self._num_partition_sectors=""
		self._type=""
		self._guid=""
		
	def set_label(self, label):
		self._label =label
		
	def set_physical_partition_number(self, number):
		self._physical_partition_number = number
		
	def set_start_sector(self, value):
		self._start_sector = value
		
	def set_num_partition_sectors(self, value):
		self._num_partition_sectors = value
		
	def set_type(self, value):
		self._type = value
		
	def set_guid(self, value):
		self._guid = value
		
	def showInfo (self):
		print ("lable                      == %s"%(self._label))
		print ("physical_partition_number  == %s"%(self._physical_partition_number))
		print ("start_sector               == %s"%(self._start_sector))
		print ("num_partition_sectors      == %s"%(self._num_partition_sectors))
		print ("type                       == %s"%(self._type))
		print ("guid                       == %s"%(self._guid))
			

def IMAGEFILE_LIST (imagefile, imagelist):
	
	f=codecs.open(imagefile, 'r', encoding='utf-8',errors='ignore')
	for line in f.readlines():
		if line.startswith (r"  <partition label"):
			_nodearry=re.split(' |=', line)
			_index=0
			_subImage=image_node()
			#  <partition label="ssd" physical_partition_number="0" start_sector="6" num_partition_sectors="2" type="2C86E742-745E-4FDD-BFD8-B6A7AC638772" guid="40784C1F-0E55-875C-8B92-20528301AE3F" />

			for subnode in _nodearry:
				#print ("%d == %s"%(_index,subnode))
				if _index == 4:
					_subImage.set_label (subnode)
				elif _index == 6:
					_subImage.set_physical_partition_number (subnode)
				elif _index == 8:
					_subImage.set_start_sector (subnode)
				elif _index == 10:
					_subImage.set_num_partition_sectors (subnode)
				elif _index == 12:
					_subImage.set_type (subnode)					
				elif _index == 14: 
					_subImage.set_guid (subnode)																									
				_index+=1
			# end for subnode in _nodearry:
			imagelist.append (_subImage)
	f.close()	


QCOM="COM13"
searchdir=os.getcwd()

if __name__ == '__main__':
	print("QFILE Read image")
	#os.chdir(QFILE_DIR)
	# print (os.getcwd())
	image_list=[]
	IMAGEFILE_LIST (IMAGEINFO_FILE, image_list)

	# cmd_res = subprocess.Popen(_cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,universal_newlines=True)
	#print(cmd_res.stdout.read())

	for imageNode in image_list:
	#imageNode=image_list[0]
	#imageNode.showInfo()
		_cmd=r"C:\Users\Jzhang91\Desktop\failed_start\failed-image\readEmmc.bat" + \
		" " + QCOM + \
		" " + searchdir +\
		" " + imageNode._label +\
		" " + imageNode._physical_partition_number + \
		" " + imageNode._start_sector + \
		" " + imageNode._num_partition_sectors + \
		" " + imageNode._type + \
		" " + imageNode._guid
		# print(_cmd)
		cmd_res = subprocess.Popen(_cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,universal_newlines=True)
		print(cmd_res.stdout.read())
			

