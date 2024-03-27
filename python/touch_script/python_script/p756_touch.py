# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np
import os
import zipfile as zfile
from draw_coordinate import sctterData
from draw_coordinate import draw_scatterDiagram
import shutil
from jmctime import jmcTTime
from jmctime import GETime
from jmctime import EQTime
from jmctime import LETime
import re
import codecs
import sys

# pip install zipfile37

touchLogFileDir=r"C:\Users\Jzhang91\Documents\WeChat Files\zhangjun1010031041\FileStorage\File\2024-03\vstgloballogcontrol_2024_3_24_15_25_22\vstgloballogcontrol\qnx\DLT"
       
def extractFile(src,dst=""):
    _zf=zfile.ZipFile(src,'r')
    _zf.extractall(path=dst)
    _zf.close()
  
def Dir2DIMList(dir):
    # print(dir)
    DIMList=[]
    _list=os.listdir(dir)
    for node in _list:
        if node.startswith("DIM_") == True:
            fullPath=dir+"/"+node
            DIMList.append(fullPath)
            #print("1"+fullPath)
        else:
            pass
            #print(node)
    return DIMList

def toDIMList(src):
    DIMList=[]
    _pre_dir=os.getcwd()
    os.chdir(src)
    _list=os.listdir()
    for node in _list:
        if node.endswith('.zip') == True:
            _len=len(node)
            _dir=node[0:_len-4:]
            fullDir=src+"/"+_dir
            fullZipfile=src+"/"+node
            # print("%s==>\r\n%s"%(fullZipfile, fullDir))
            if os.path.exists(fullDir) == True:
                shutil.rmtree(fullDir)
            extractFile(fullZipfile, fullDir)
            dirDimList=Dir2DIMList(fullDir)
            if len(dirDimList)!=0:
                DIMList.extend(dirDimList)
        else:
            fullPath=src+"/"+node
            if os.path.isfile(fullPath)==True and node.startswith("DIM_") == True:
                DIMList.append(fullPath)
    return DIMList
    
class lineEntry:
    def __init__(self, strLine="",logfile=""):
        self.line=strLine
        self.lineArry=self.line.split(' ')
        self.time=jmcTTime(self.lineArry[0], self.lineArry[1])
        self.logfile=logfile
 

def filterTime(fileList="", startTime="",endTime="",TAG=""):
    outList=[]
    for node in fileList:
        try:
            f=codecs.open(node, 'r', encoding='utf-8',errors='ignore')
            for line in f.readlines():
                if re.search(TAG,line):
                    #print(line)
                    lineE=lineEntry(line,node)
                    #print(line)
                    if GETime(lineE.time,startTime) == True and \
                        LETime(lineE.time, endTime) == True:
                        outList.append(lineE)
            f.close()
        except UnicodeError as UE:
            print("file:[%s]"%(node))
            print('except:', UE)
    return outList
    
    
if __name__ == '__main__':
    print("analyze P756 touch point and draw the point on screen image")
    dimList=toDIMList(touchLogFileDir)
    #for node in dimList:
    #    print(node)
    # 2023-11-19 16:28:00.00 ~ 2023-11-19 16:30:00.00
    startTime=jmcTTime("2024-03-24","15:21:00.00")
    endTime  =jmcTTime("2024-03-24","15:22:00.00")
    TAG      ="qvm vinput: Event type "
    outList=filterTime(dimList,startTime,endTime,TAG)
    x_index=0
    y_index=0
    px=[]
    py=[]
    for node in outList:
        sub_xtag=r"0x35"
        sub_ytag=r"0x36"
        if re.search(sub_xtag, node.line):
            _xArry=node.line.split(' ')
            #print("%d"%(len(_xArry)))
            px.append(int(_xArry[13]))
            x_index+=1
        elif re.search(sub_ytag, node.line):
            _yArry=node.line.split(' ')        
            #print("%d"%(len(_yArry)))
            py.append(-int(_yArry[13])+720)
            y_index+=1
    for i in range(0,x_index):
        print("[x:%d,y:%d]"%(px[i],720-py[i]))
        #print("%s"%(node.line))

    drawData=sctterData()
    drawData.px = px
    drawData.py = py
    drawData.name="JMC-P789 point"
    drawData.x_name="x-alix"
    drawData.y_name="y-alix"
    drawData.px_max=1920
    drawData.py_max=720
    draw_scatterDiagram(pointArry=drawData,bg_img=r"C:\Users\Jzhang91\Desktop\Doc\P756\script\wechar.png", outImage="./out.png", nsec=200)


    print("out len:%d"%(len(outList)))

    
    
    
    