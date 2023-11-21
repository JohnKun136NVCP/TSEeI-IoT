# Bibliotecas necesarias
import mysql.connector as mariadb
import paho.mqtt.client as mqtt
import sys

# Variables para la conexión a la base de datos
dbName = "PruebaClase"
mysqlHost = "localhost"
mysqlUser = "vazzvel"
mysqlPassword = "12345pass"
mysqlPort = 3306

# Variables para la conexión al bróker de MQTT
# mqttBroker = "192.168.3.243"
mqttBroker = "localhost"
#mqttBroker = "test.mosquitto.org"

mqttBrokerPort = 1883
mqttUser = None
mqttPassword = None

# Tópicos
numberTopics = 4
topicUser = "ClaseIoT/User"
topicTemp = "ClaseIoT/Sensores/DHT/Temp"
topicHum = "ClaseIoT/Sensores/DHT/Hume"
topicLDR = "ClaseIoT/Sensores/LDR"
lista = []

# Función de suscripción a tópicos y a base de datos
def on_connect(client, userdata, flags, rc):
    print("MQTT Client Connected")
    client.subscribe([(topicUser,0),(topicTemp,0),(topicHum,0),(topicLDR,0)])
    try:
        print("MySQL Client Connected")
        db = mariadb.connect(host=mysqlHost, user=mysqlUser, password=mysqlPassword, database=dbName)
        db.close()     
    except:
        sys.exit("Connection to MySQL failed")
        
# Función de lectura de mensajes        
def on_message(client, userdata, msg):
    ms = str(msg.payload.decode("utf-8","ignore"))
    lista.append(ms)
    if len(lista) == numberTopics:
        db = mariadb.connect(host=mysqlHost, user=mysqlUser, password=mysqlPassword, database=dbName) #Conecto con MariaDB
        cursor = db.cursor() #Área de trabajo temporal
        insertRequest = """INSERT INTO BasePrueba.datos (IDclient, Temp, Hum, LDR) VALUES (%s,%s,%s,%s)""" #Instrucción mySQL para insertar dato
        val = (lista[0], lista[1], lista[2], lista[3])
        cursor.execute(insertRequest, val) #Se ejecuta la instrucción
        db.commit() #Confirmar los cambios en la base de datos
        db.close() #Cierro la comunicación
        print(lista)
        print('Save data!')
        del lista[:]

# Conexión al cliente MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
# client.username_pw_set(username=mqttUser, password=mqttPassword)
try:
    client.connect(mqttBroker, mqttBrokerPort, 60)
except:
    sys.exit("Connection to MQTT Broker failed")

client.loop_forever()



