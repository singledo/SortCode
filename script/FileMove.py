#!/bin/bash
#-*- coding=utf-8 -*-

import os
import sys
import shutil
import getopt

def Traver(path="", suffiexs=""):
    if os.path.isdir(path) == False:
        return None
    filelist = []
    suffiexsLen = len(suffiexs)
    for root, dirs, files in os.walk(path, topdown=False):
        for name in files:
            if (name[len(name) - suffiexsLen : len(name)]) == suffiexs:
                pass
            else:
                continue
            filelist.append(root+'/'+name)
    return filelist

def Copy(src="", dst="" , isOverWrite=True):
    filelist = Traver(path=src, suffiexs=".md")
    if os.path.exists(dst) == False:
        os.makedirs(dst)
        print("destnation direction not exits, we create it.")
    else:
        pass

    print("#### Do copying")
    if dst[-1] == "/":
        dst = dst[0:len(dst)-1]

    for file in filelist:
        _list = file.split("/")
        dstfile = dst+"/"+ _list[-1]
        if os.path.exists(dstfile) == True:
            print("{" + dstfile + "}   is exits")
            if isOverWrite == False:
                print("  #### Skip ####")
                continue
            else:
                os.remove(dstfile)
                print("  ### Remove Write Done.")
        if os.path.exists(file):
            shutil.copyfile(file, dstfile)
            print("{" + dstfile + "}  Copy Done")
        else:
            print("source file is not exit")

def Run(argv=[]):
    _len = len(argv)
    if _len == 0:
        print("Empty Input .....")
        return
    optlist = ""
    remind  = ""
    try:
        optlist, remind = (getopt.getopt(argv, "s:d:o:", [
            '--source=',
            '--destnation=',
            '--OverWrite=',
        ]))
        print(optlist, remind)
    except getopt.GetoptError:
        print("Argument Error ... ")
        print("*.py -s sourcePath -d destnation -o True")

    isOverWrite = True
    destnation  = ""
    source      = ""
    
    for opt, arg in optlist:
        if opt in ("-o", "--OverWrite"):
            if arg == 'False' or arg == 'false':
                isOverWrite = False
        elif opt in ("-d", "--destnation"):
            destnation = arg
        elif opt in ("-s", "--souce"):
            source = arg
    if len(destnation) == 0 or len(source) == 0:
        print("Enpty destnation or source path")
        return 
    Copy(source, destnation, isOverWrite )






if __name__=="__main__":
    print("Move File Script")
    path = "/home/zz/workstation"
    # Traver(path=path, suffiexs=".md")
    # print(sys.argv[0], sys.argv[1], sys.argv[2])
    # Copy(src=path, dst="./", suffiexs=".md")
    str = "FileMove.py -s /home/zz/blog/source/_posts/ -d /home/zz/workstation/sort/markdown/  -o true"

    _argv = []
    Run(sys.argv[1:])
