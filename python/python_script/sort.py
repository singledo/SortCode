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
from jmctime import interTime
import re
import codecs
from statistics_acc_gyro import lineEntry
import gzip

def partition(arr: list[lineEntry], low: int, high: int):
    pivot, j = arr[low], low
    for i in range(low + 1, high + 1):
        #if arr[i] <= pivot:
        if LETime(arr[i].time, pivot.time):
            j += 1
            arr[j], arr[i] = arr[i], arr[j]
    arr[low], arr[j] = arr[j], arr[low]
    return j 

def quick_sort_between(arr: list[lineEntry], low: int, high: int):
    if high-low <= 1: # 递归结束条件
        return

    m = partition(arr, low, high)  # arr[m] 作为划分标准
    quick_sort_between(arr, low, m - 1)
    quick_sort_between(arr, m + 1, high)

def quick_sort(arr:list[lineEntry]):
    """
    快速排序(in-place)
    :param arr: 待排序的List
    :return: 快速排序是就地排序(in-place)
    """
    quick_sort_between(arr,0, len(arr) - 1)

''' 
def partition(arr: list[int], low: int, high: int):
    pivot, j = arr[low], low
    for i in range(low + 1, high + 1):
        if arr[i] <= pivot:
            j += 1
            arr[j], arr[i] = arr[i], arr[j]
    arr[low], arr[j] = arr[j], arr[low]
    return j 

def quick_sort_between(arr: list[int], low: int, high: int):
    if high-low <= 1: # 递归结束条件
        return

    m = partition(arr, low, high)  # arr[m] 作为划分标准
    quick_sort_between(arr, low, m - 1)
    quick_sort_between(arr, m + 1, high)

def quick_sort(arr:list[int]):
    """
    快速排序(in-place)
    :param arr: 待排序的List
    :return: 快速排序是就地排序(in-place)
    """
    quick_sort_between(arr,0, len(arr) - 1)
    
    
# 测试数据

if __name__ == '__main__':
    import random
    random.seed(54)
    arr = [random.randint(0,100) for _ in range(10)]
    print("原始数据：", arr)
    quick_sort(arr)
    print("快速排序结果：", arr)
'''