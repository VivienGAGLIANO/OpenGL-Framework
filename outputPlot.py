# -*- coding: utf-8 -*-
"""
Created on Tue Apr 12 00:30:43 2022

@author: Lilian
"""
import matplotlib.pyplot as plt 
res = []

with open('C:/Users/Lilian/Documents/Projet GIT/IMN504-TP3 + projet/OUTPUT.txt') as f:
    for line in f:
        data = line.split("\n")
        res.append(float(data[0]))

plt.plot(res)
plt.show()