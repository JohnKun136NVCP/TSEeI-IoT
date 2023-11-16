import pandas as pd #Import pandas for csv files
import socket #Socket will communicate with ESP32 and it sends information
import time #Sleep time to send information
#Class esp32Tools get most important
class esp32Tools:
    def __init__(self,ip):
        self.ipget = ip #IP from ESP32
        self.ipsrc = "" #IP source
        self.ipdst = "" #IP Destination
        self.lengthsize = 0 #Size
        self.protocol = "" #Protocol
        self.greenRange = 100 #Green Led will turn on 
        self.yellowRange = 150#Yellow Led will turn on 
        self.redRange = 200#Red Led will turn on 
        self.esp32Port = 80 #Port for webconnexion
class csvFiles(esp32Tools):
    def __init__(self,ip,name):
        super().__init__(ip)
        self.nameFile = name #File name csv
        self.source= "" #Path from csv
        self.columns = "" #Number of columns
        self.rows = "" #Number of rows
        self.data = pd.read_csv(self.nameFile) #Read csv using Pandas
    def isFileCSV(self): #Method: Check if it is a csv file
        self.nameFile = str(self.nameFile) #Get the path
        if self.nameFile.lower().endswith('.csv'): #Compare .csv file
            print("File attached")
            return 1
        else:
            print("Path is incorrect or your file is broken")
            return -1
    def removeAdditionalID(self): #If column "No." exist, then this method will remove it
        self.columns = self.data.shape[1] #Get columns (Number)
        self.rows = self.data.shape[0] #Get rows (Number)
        if self.columns==7:
            try: #If it fails
                print("Delete ID column") 
                self.data.drop("No.",inplace=True,axis=1) #Delete column "No."
                return self.data #Return data
            except:
                print("Column not found")
                return self.data #If  it doesn't fail, then return data
        return self.data  #If column is not on CSV then it'll return data


class esp32Data(csvFiles): #Subclass esp32Data sends
    def __init__(self,ip,name):
        super().__init__(ip,name)
        self.messageSign = "" #Values for leds to ESP32
        self.messagePort = "" #Message from csv
    def openSocket(self,typeMessage,message): #Open a socket
        self.messageSign = typeMessage
        self.messagePort =message
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((self.ipget, self.esp32Port))
        client_socket.sendall(self.messageSign.encode()) #Sends (0 or 1 or -1)
        time.sleep(1)
        client_socket.sendall(self.messagePort.encode()) #Sends message
        time.sleep(1)
        client_socket.close()
    def systemAlarm(self):
        self.data = self.removeAdditionalID()
        for self.ipsrc ,self.ipdst,self.protocol,self.lengthsize in zip(self.data["Source"],self.data['Destination'],self.data["Protocol"],self.data["Length"]): #loop for values from csv file
            if(self.lengthsize<=self.greenRange):
                time.sleep(3)
                self.messageSign = "0" #Sends a 0
                self.messagePort = "Everything's fine"#Sends message "OK"
                self.openSocket(self.messageSign,self.messagePort)
                time.sleep(3)
                print(self.messagePort)
            elif(self.lengthsize>self.greenRange and self.lengthsize<=self.yellowRange):
                time.sleep(3)
                self.messageSign = "1"#Sends a 1. Sends message "size of packet"
                self.messagePort = "Warning! Length packet: "+str(self.lengthsize)
                self.openSocket(self.messageSign,self.messagePort)
                time.sleep(3)
                print(self.messagePort)
            elif(self.lengthsize>=self.redRange or self.lengthsize>self.yellowRange):
                time.sleep(3)
                self.messageSign = "-1"#Sends a -1. Sends message "ipsrc and ipdst"
                self.messagePort = str(self.ipsrc)+"==>"+str(self.ipdst)+".Protocol: "+str(self.protocol)
                self.openSocket(self.messageSign,self.messagePort)
                time.sleep(3)
                print(self.messagePort)
