#-*-coding: utf-8 -*-
 
"""IMPORTS"""
import os
from tkinter import *
import numpy as np
import matplotlib.pyplot as plt
import threading
import time
from socket import *


"""VARIABLES GLOBALES"""
trains = []
points =[
[691,760], #C1
[400,740], #C2
[136,576], #C3
[153,151], #C4
[417,46], #C5
[710,63], #C6
[1057,93], #C7
[1162,382], #C8
[1060,700], #C9 y=607
]
points = np.array(points)/1.3 
points[::,0]+=80 # ajustement Gauche / Droite
points[::,1]+=20 # ajustement Haut / Bas
rot = +3 *2*np.pi/360
c = np.cos(rot)
s = np.sin(rot)
R = np.matrix([[c, -s], [s, c]])
points = np.array(points*R)
n=len(points) 
cercle = 0
ecart2 = 20


Train_pos = np.array([[10,"TGV111"],[100,"TGV222"],[600,"TGV333"],[1000,"TGV444"]])
ancien_pos = np.array(Train_pos)

 
threads = list()


"""FOCNTIONS"""

def GUI(): 
    """ INTERFACE """
    global cercle
    fenetre = Tk()
    
    Titre = Label(fenetre,text="Positions des trains du RBC", font = "Arial 22")
    Titre.pack()
    
    hauteur, largeur = 700, 1200
    
    cercle = Canvas(fenetre,bg='grey75',height=hauteur,width=largeur)
    cercle.pack()
    
    signe = [-1,-1,+1,  +0.6,+1,+1,  -1,-2,+0.2]
    
    for i, val in enumerate(points):
        p1 = points[i]
        p2 = points[(i+1)%n]
        cercle.create_line(p1[0], p1[1], p2[0], p2[1], width=10, fill="black")
        ecart = 75
        cercle.create_text((p1[0]+p2[0] +ecart*signe[i] )/2, (p1[1]+p2[1]+ecart)/2, anchor=W, font="Purisa 22", fill ='blue',
                    text="C"+str(i+1))
        cercle.create_oval(p1[0]-ecart2/2, p1[1]-ecart2/2, p1[0]+ecart2/2, p1[1]+ecart2/2, outline="green", width=0, fill="green")
    
    fenetre.mainloop()


def MAJ_GUI():
    """Mets à jour la position des trains"""
    global Train_pos, trains, ancien_pos
    
    def parcours(position_train):
        sectionsPos= [0,167, 357, 583, 745, 906, 1119, 1303, 1466, 1745]
        if position_train>=sectionsPos[0] and position_train<sectionsPos[1]:
            i = 0
        elif position_train>=sectionsPos[1] and position_train<sectionsPos[2]:
            i = 1
        elif position_train>=sectionsPos[2] and position_train<sectionsPos[3]:
            i = 2
        elif position_train>=sectionsPos[3] and position_train<sectionsPos[4]:
            i = 3
        elif position_train>=sectionsPos[4] and position_train<sectionsPos[5]:
            i = 4
        elif position_train>=sectionsPos[5] and position_train<sectionsPos[6]:
            i = 5
        elif position_train>=sectionsPos[6] and position_train<sectionsPos[7]:
            i = 6
        elif position_train>=sectionsPos[7] and position_train<sectionsPos[8]:
            i = 7
        else:
            i=8
        p=(position_train-sectionsPos[i])/(sectionsPos[i+1]-sectionsPos[i])
        x = points[(i+1)%n][0]*p + points[(i)%n][0]*(1-p)
        y = points[(i+1)%n][1]*p + points[(i)%n][1]*(1-p)
        return(x,y)
           
    while True:
        # print(len(ancien_pos)!=len(Train_pos) or ((ancien_pos != Train_pos).any()), ancien_pos[0], Train_pos[0])
        if len(ancien_pos)!=len(Train_pos) or ((ancien_pos != Train_pos).any()):
            ancien_pos = np.array(Train_pos)
            for i, j in trains:
                cercle.delete(i)
                cercle.delete(j)
            trains = []
            for l, no in Train_pos:
                # print(l, no)
                p1 = parcours(int(l))
                point = cercle.create_oval(p1[0]-ecart2/2, p1[1]-ecart2/2, p1[0]+ecart2/2, p1[1]+ecart2/2, outline="red", width=0, fill="red")
                decart = 15
                label = cercle.create_text((p1[0]+decart), (p1[1]+decart), anchor=W, font="Purisa 12", fill ='red', 
            text = no)
                trains.append([point, label])
        else:
            # time.sleep(0.1)
            pass
 
 
def comm():
    """Lit le port réseau pour récupérer les données du RBC"""
    global Train_pos, threads
    
    def parse_rep(rep):
        global Train_pos
        # $ entre les trains 
        # : entre les valeurs
        # print(rep)
        nb_trains = rep.count("$")
        data = rep.rstrip().split('$')
        Train_pos = Train_pos[:nb_trains]
        # print(Train_pos)
        for ind, couple in enumerate(data):
            if couple!='':
                # print(ind, len(Train_pos))
                info = couple.split(':')
                nom = info[0]
                long = int(float(info[1]))
                if ind < len(Train_pos):
                    Train_pos[ind] = [long, nom]
                else:
                    Train_pos = np.append(Train_pos, [long, nom]).reshape((ind+1,2))
                    
        
    
    s= socket(AF_INET, SOCK_STREAM)
    hote = "127.0.0.1"
    port = 9000
    s.bind((hote, port))
    k=0
    print("Attente d'une connexion ...")
    s.listen(8)
    client, address = s.accept()
    print("Connecté")

    while True:
            response = client.recv(1024) # 1024
            if response != "":
                parse_rep(response.decode())
                
    
            
    
def main():
    """Fonction principale d'execution"""
    global threads
    
    thread_interface = threading.Thread(target=GUI)
    threads.append(thread_interface)
    thread_interface.start()
    
    time.sleep(1)
    
    thread_comm = threading.Thread(target=comm)
    threads.append(thread_comm)
    thread_comm.start()
    
    maj_position = threading.Thread(target=MAJ_GUI)
    threads.append(maj_position)
    maj_position.start()


    # for index, thread in enumerate(threads):
    #         logging.info("Main    : before joining thread %d.", index)
    #         thread.join()
    #         logging.info("Main    : thread %d done", index)





main()




