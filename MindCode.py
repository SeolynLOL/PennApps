import serial
from twilio.rest import Client
from playsound import playsound
from time import sleep


arduino = serial.Serial('COM5', 9600)
#arduino = serial.Serial('/dev/cu.usbmodem14301', 9600)


account_sid = 'AC25bd8b77a07f84c7443be0806ad1d857'
auth_token = '86516d18b446f077968b428ca2a136cb'

client = Client(account_sid, auth_token)
timer = 0
stage = 0

while True:
    data = arduino.readline().decode('utf-8').strip()
    values = data.split(",")
    print(values)
    if values[0] == '1':
        playsound('kobe.mp3')
        message = client.messages.create(
                     body="Job finished? I dont think so. Get back on the grind...",
                     to='+16472896168',
                     from_='+14788181450'
                 )

    elif values[0] == '2':
        playsound('kobe.mp3')
        call = client.calls.create(
                    twiml='<Response><Say>This is your final warning. Job finished? I dont think so. Get back on the grind!</Say></Response>',
                    to='+16472896168',
                    from_='+14788181450'
                )
