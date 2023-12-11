# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np
import os
import sys
import zipfile as zfile
from draw_coordinate import sctterData
from draw_coordinate import draw_scatterDiagram
import shutil
from jmctime import jmcTTime
from jmctime import GETime
from jmctime import EQTime
from jmctime import LETime
from jmctime import interTime
import re
import codecs

import gzip

class lineEntry:
    def __init__(self, strLine=""):
        self.line=strLine
        self.lineArry=self.line.split(' ')
        self.time=jmcTTime(self.lineArry[0], self.lineArry[1])

def timeMin (arr:list[lineEntry]):
    min_node=arr[0]
    for node in arr:
        if GETime(min_node.time, node.time) == True:
            min_node = node
    return min_node  
    
def sort(arr:list[lineEntry]):
    outList=[]
    while len(arr) > 0:
        min_n = timeMin(arr)
        outList.append(min_n)
        arr.remove(min_n)
    return outList


def gzExtra(src, tar):
    with gzip.open(src, 'rb') as f_in, open(tar, 'wb') as f_out:
        f_out.write(f_in.read())

def toMainList(src):
    _src=src.replace('\\', '/')
    MainList=[]
    _pre_dir=os.getcwd()
    os.chdir(_src)
    _list=os.listdir()
    for node in _list:
        if node.endswith('.gz') == True and node.startswith('main_'):
            _full_path=_src+"/"+node
            MainList.append(_full_path)
    return MainList
    
def filterTime_MainLog(fileList="", startTime="",endTime="",TAG=""):
    outList=[]
    _pre_line=''
    ntime=0
    for node in fileList:
        try:
            f=codecs.open(node, 'r', encoding='utf-8',errors='ignore')
            for line in f.readlines():
                if re.search(TAG,line):
                    #print(line)
                    #print(line)
                    lineE=lineEntry(line)
                    #print(line)
                    if GETime(lineE.time,startTime) == True and \
                        LETime(lineE.time, endTime) == True:
                        outList.append(lineE)
                        if _pre_line != '':
                            if interTime(_pre_line.time, lineE.time) > 200:
                                # print("nime:%d \n[_pre_line-%s] \n[curr line-%s]"%(ntime, _pre_line.line, lineE.line))
                                ntime += 1
                        _pre_line=lineE
            f.close()
        except UnicodeError as UE:
            print("file:[%s]"%(node))
            print('except:', UE)
    return outList
    
def MainListDecompress(MainList):
    outList=[]
    for node in MainList:
        _len=len(node)
        _out_node=node[0:_len-3:]
        if os.path.exists(_out_node) == True:
            #print(_out_node)
            os.remove(_out_node)
        gzExtra (node, _out_node)
        outList.append (_out_node)
    return  outList  
    
if __name__ == '__main__':
    print("statistics_acc_gyro.py  statistics acc gyro info")
    startTime=jmcTTime("2023-12-09","13:57:49.00")
    endTime  =jmcTTime("2023-12-09","18:23:42.00")
    mainSrc=r"D:\BaiduNetdiskDownload\腾讯导航测试-1209\2023-12-09-18-25-46\vstgloballogcontrol"
    MainList=toMainList(mainSrc)
    decompressList=MainListDecompress(MainList)
    outContent=filterTime_MainLog (decompressList,startTime,endTime, "NAVI_DEBUG")

    sortLine=sort(outContent)

    #intervalTime=interTime(startTime,endTime)
    #for node in outContent:
    #    print(node.line)
    # print("receive time:%d time:%ds %f" %(len(outContent),intervalTime, float(len(outContent))/(float(intervalTime)/10)))
