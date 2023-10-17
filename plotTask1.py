import matplotlib.pyplot as pl
import pandas as pd

def plot1():
    data = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task1.txt", sep=" ", names=[1, 2])
    pl.plot(data[1], data[2])
    pl.axhline(y=0.0002, color='red', linestyle='--')
    pl.xlabel("Количесто узлов, n")
    pl.ylabel("Tочность")
    pl.title("Зависимость Δn")
    pl.grid(True)
    pl.show()

def plot2():
    data2 = pd.read_csv("D:/5sem/numerical/Lab1/cmake-build-debug/task1_2.txt", sep=" ", names=[1, 2])
    pl.figure(figsize=(10, 5))
    pl.plot(data2[1], data2[2])
    pl.xlabel("x")
    pl.ylabel("Tочность")
    pl.title("Ошибка приближения")
    pl.grid(True)
    pl.show()

plot1()

