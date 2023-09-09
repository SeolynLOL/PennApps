import cv2
import serial
from twilio.rest import Client

import numpy as np
from time import sleep


face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0)
arduino = serial.Serial('/dev/cu.usbserial-1430', 9600)
#arduino = serial.Serial('/dev/cu.usbmodem14301', 9600)
sleep(2)



client = Client(account_sid, auth_token)
timer = 0
stage = 0


while True:

    data = arduino.readline().decode('utf-8')
    print("Sensor Data:", data)
    print("timer: ", timer)
    values = data.split(",")
    values[0] = int(values[0])
    if values[0] > 85 and timer > 2:
        if stage == 0:
            print("wake up")
            
        if stage == 1:
            call = client.calls.create(
                        twiml='<Response><Say>This is your final warning. Get back on the grind!</Say></Response>',
                        to='+16472896168',
                        from_='+14788181450'
                    )
            
        if stage == 3:
            arduino.write("a".encode())
            stage =-1
        stage+=1
        timer = 0
    else:
        timer+=1


    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=5, minSize=(30, 30))

    for (x, y, w, h) in faces:
        arduino.write(f"{x},{y},{w},{h}\n".encode())

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    cv2.imshow('Face Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close() 