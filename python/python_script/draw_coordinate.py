# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np
import os

class sctterData():
    def __init__(self):
        self.name=""
        self.px=[]
        self.py=[]
        self.x_name=""
        self.y_name=""
        self.px_max=""
        self.py_max=""
    
def draw_image(px, py, max_x, max_y,image_name):
    axis_arry=[0, max_x, 0, max_y]
    plt.figure('Draw')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.plot(px,py,'ro')
    plt.axis(axis_arry)
    plt.draw()  # 显示绘图    
    plt.pause(10)  #显示5秒
    plt.savefig(image_name)  #保存图象
    plt.close()   #关闭图表

def draw_with_backimage(px, py, max_x, max_y,b_img, image_name):
    img=plt.imread(b_img)
    fig,ax=plt.subplots()
    axis_arry=[0, max_x, 0, max_y]
    ax.imshow(img,extent=axis_arry)
    plt.figure('Draw')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.plot(px,py,'ro')
    plt.axis(axis_arry)
    plt.draw()  # 显示绘图    
    plt.pause(10)  #显示5秒
    plt.savefig(image_name)  #保存图象
    plt.close()   #关闭图表
    
   
def draw_scatterDiagram (pointArry="", bg_img="", outImage="", nsec=100):
    if bg_img!="":
        img=plt.imread(bg_img)
        fig,ax=plt.subplots()
        axis_arry=[0,pointArry.px_max,0,pointArry.py_max]
        ax.imshow(img,extent=axis_arry) 
        plt.axis(axis_arry)
        fig.set_size_inches(18, 9)
    else:
        plt.figure()
    plt.xlabel(pointArry.x_name)
    plt.ylabel(pointArry.y_name)
    plt.scatter(pointArry.px, pointArry.py,linewidths=0.2, c="red")  
    if outImage != "":
        plt.savefig(outImage) 
    plt.show()


if __name__ == '__main__':
    print("draw coordinate image")
    # p1=[0,1.1,1.8,3.1,4.0]
    # p2=[2,2.4,4.3,3.5,2.5]
    # draw_image(p1, p2, 1920, 720, "a.png")
    # draw_with_backimage(p1, p2, 1920, 720, "E:/visteon_workspace/python_script/a.jpg", "b.png")
  
    drawData=sctterData()
    for i in range(0,720,10):
        drawData.px.append(i)
        drawData.py.append(i)
    drawData.name="testp programe"
    drawData.x_name="x-alix"
    drawData.y_name="y-alix"
    drawData.px_max=1280
    drawData.py_max=800
    draw_scatterDiagram(pointArry=drawData,bg_img="E:/visteon_workspace/python_script/1.png", outImage="./out.png", nsec=200)



    