# -*- coding: utf-8 -*-
"""
Created on Tue Apr 12 00:30:43 2022

@author: Lilian
"""
import matplotlib.pyplot as plt 
orbit1 = []
orbit2 = []
orbit3 = []
orbit4 = []
orbit5 = []

with open('C:/Users/Lilian/Documents/Projet GIT/IMN504-TP3 + projet/log/orbit1.txt') as f:
    for line in f:
        data = line.split("\n")
        orbit1.append(float(data[0]))

with open('C:/Users/Lilian/Documents/Projet GIT/IMN504-TP3 + projet/log/orbit2.txt') as f:
    for line in f:
        data = line.split("\n")
        orbit2.append(float(data[0]))
        
with open('C:/Users/Lilian/Documents/Projet GIT/IMN504-TP3 + projet/log/orbit3.txt') as f:
    for line in f:
        data = line.split("\n")
        orbit3.append(float(data[0])) 
        
with open('C:/Users/Lilian/Documents/Projet GIT/IMN504-TP3 + projet/log/orbit4.txt') as f:
    for line in f:
        data = line.split("\n")
        orbit4.append(float(data[0]))
        
with open('C:/Users/Lilian/Documents/Projet GIT/IMN504-TP3 + projet/log/orbit5.txt') as f:
    for line in f:
        data = line.split("\n")
        orbit5.append(float(data[0]))
        
figure, axis = plt.subplots(3, 2)
plt.figure(figsize=(20, 20))
axis[0, 0].plot(orbit1)
axis[0, 0].set_title("planet 1 : 71")
axis[0, 1].plot(orbit2)
axis[0, 1].set_title("planet 2 : -58")
axis[1, 0].plot(orbit3)
axis[1, 0].set_title("planet 3 : -44.8")
axis[1, 1].plot(orbit4)
axis[1, 1].set_title("planet 4: 31.61")
axis[2, 0].plot(orbit5)
axis[2, 0].set_title("planet 5 par rapport à 4: 33.992265")
plt.show()