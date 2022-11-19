#Controlador del auto

#Módulos
import os
import serial
from tkinter import *

#Objeto Serial - Arduino
pyserial = serial.Serial()
pyserial.baudrate = 38400
pyserial.port = 'COM3'

#Clase Principal
class Panel():
    def __init__(self):
        #Configuración de la ventana
        self.ventana = Tk()
        self.ventana.geometry('640x426')
        self.ventana.title('Control')
        self.ventana.resizable(0,0)
        self.ventana.config(cursor='fleur')
        
        #Ícono
        self.Ruta_Trabajo = os.getcwd()
        self.ventana.iconbitmap('{}\\iconos\\auto.ico'.format(self.Ruta_Trabajo))
        
        #Fondo
        self.fondo = PhotoImage(file='{}\\imagenes\\auto.png'.format(self.Ruta_Trabajo))
        self.lblfondo = Label(self.ventana, image=self.fondo)
        self.lblfondo.pack()
        
        #Accesorios - Widgets
        self.Widgets()
        
    def Widgets(self):
        #Botones AWSD -  Lo enviamos en código ASCII

        #Izquierda - a
        self.Boton4 = Button(self.ventana, text="←")
        self.Boton4.config(bg="white", 
                           fg="black",
                           relief="raised", 
                           justify="center",
                           font="Helvetica 18 bold",
                           command= lambda: self.ClickBoton(97))
        self.Boton4.place(x=20, y=366, width=50, height=50)

        #Atras - s
        self.Boton4 = Button(self.ventana, text="↓")
        self.Boton4.config(bg="white", 
                           fg="black",
                           relief="raised", 
                           justify="center",
                           font="Helvetica 18 bold",
                           command= lambda: self.ClickBoton(115))
        self.Boton4.place(x=90, y=366, width=50, height=50)

        #Derecha - d
        self.Boton4 = Button(self.ventana, text="→")
        self.Boton4.config(bg="white", 
                           fg="black",
                           relief="raised", 
                           justify="center",
                           font="Helvetica 18 bold",
                           command= lambda: self.ClickBoton(100))
        self.Boton4.place(x=160, y=366, width=50, height=50)

        #Adelante - w
        self.Boton4 = Button(self.ventana, text="↑")
        self.Boton4.config(bg="white", 
                           fg="black",
                           relief="raised", 
                           justify="center",
                           font="Helvetica 18 bold",
                           command= lambda: self.ClickBoton(119))
        self.Boton4.place(x=90, y=296, width=50, height=50)
    
    def RunApp(self):
        self.ventana.mainloop()

    def ClickBoton(self, valor):
        comando = valor
        pyserial.open()
        pyserial.write(b'comando')
        pyserial.close()
        
if __name__ == '__main__':
    Sofware = Panel()
    Sofware.RunApp()
