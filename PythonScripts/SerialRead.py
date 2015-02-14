import serial

port = 'COM7'

arduino = serial.Serial(port,9600)

while True:
    print(arduino.readline())
