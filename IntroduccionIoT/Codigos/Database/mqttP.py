import paho.mqtt.client as mqtt
import sys
import json

lista = []

# Variables para la conexión del broker MQTT
# mqttBroker = "test.mosquitto.org"
# mqttBroker = "192.168.3.243"
mqttBroker = "localhost"
mqttBrokerPort = 1883
mqttUser = None
mqttPassword = None

# Tópicos
numberTopics = 4
topicUser = "ClaseIoT/User"
topicTemp = "ClaseIoT/Sensores/DHT/Temp"
topicHum = "ClaseIoT/Sensores/DHT/Hume"
topicLDR = "ClaseIoT/Sensores/LDR"

# Función de suscripción a tópicos
def on_connect(client, userdata, flags, rc):
    print("MQTT Client Connected")
    client.subscribe([(topicUser,0),(topicTemp,0),(topicHum,0),(topicLDR,0)])

# Función de lectura de mensajes
def on_message(client, userdata, msg):
    ms = str(msg.payload.decode("utf-8","ignore")) #Mensaje
    lista.append(ms) #Creamos lista
    if len(lista) == numberTopics:
        print(lista) #Imprimimos lista
        del lista[:] #Borramos lista
    

# Conexión al cliente MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
# client.username_pw_set(username=mqttUser, password=mqttPassword)

try:
    client.connect(mqttBroker, mqttBrokerPort, 60)
except:
    sys.exit("Connection to MQTT Broker failed")

# Ciclo de conexión infinito al bróker MQTT
client.loop_forever()