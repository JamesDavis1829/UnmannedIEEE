import pygame
import serial
import time

port = 'COM7'

arduino = serial.Serial(port,9600,timeout = 0.1);

#user input
while True:
    pygame.display.set_mode((640,480))
    pygame.event.get()
    keyP = pygame.key.get_pressed()
    if keyP[pygame.K_UP]:
        arduino.write("F")
    elif keyP[pygame.K_DOWN]:
        arduino.write("B")
    elif keyP[pygame.K_LEFT]:
        arduino.write("L")
    elif keyP[pygame.K_RIGHT]:
        arduino.write("R")
    elif keyP[pygame.K_ESCAPE]:
        pygame.display.quit
        break
    
    
