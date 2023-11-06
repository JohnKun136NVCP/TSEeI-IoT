import serial
import serialpports as serport
import time
import os.path
def getIPs():
    ips = []
    try:
        nameport = serport.ports()
        esp = serial.Serial(nameport,115200)
        print("REBOOT your ESP32 to get IPS")
        while (len(ips)<1):
            line = esp.readline().decode('utf-8').rstrip()
            ips.append(line)
        esp.close()
        return ips
    except:
        return []

def generateTxtFile(ipSta):
    path = '~/.ips/ips.txt'
    if(os.path.isfile(path)!=True):
        with open("ips.txt","a") as file:
            file.write(ipSta)
    else:
        print("Do you want to overwrite it? [Y/N]")
        option = input()
        if(option=="Y" or option=="yes" or option == "YES"):
            with open("ips.txt","w") as file:
                file.write(ipSta)
        else:
            print("Nothing to do here")


while (True):
    iplist = getIPs()
    if(iplist==[]):
        time.sleep(0.5)
        print("Fist, connect your esp32 to port serial,please")
    elif(iplist!=[]):
        ipsta = iplist[0]
        print("La IP publica STA es: ",ipsta)
        print("Now you can unplugged your ESP32")
        break
generateTxtFile(ipsta)
