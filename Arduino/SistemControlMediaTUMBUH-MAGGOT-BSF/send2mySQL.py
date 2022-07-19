import time
import serial
import mysql.connector
import datetime
import random


# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

mydb = mysql.connector.connect(
  host="localhost",
  user="phpmyadmin",
  password="Maggot123",
  database="project_monitoring-system"
)

mycursor = mydb.cursor()

while 1 :
    tbl_db = ["data_sensor_a", "data_sensor_b", "data_sensor_c", "data_sensor_d",
                "data_sensor_e", "data_sensor_f", "data_sensor_g", "data_sensor_h",
                "data_sensor_i"]
    
    t = datetime.datetime.now()
    arduinoData = ser.readline().decode('ascii')
    #print(arduinoData)
    
    x = arduinoData.split(" ")
    
    if len(x) == 10 :
        for i, datas in enumerate(x):
            if i == 9:
                break
            sql = "INSERT INTO "+ str(tbl_db[i])  +" (tanggal , jam, nilai_sensor) VALUES (%s, %s, %s)"
            val = [("{}/{}/{}".format(t.day, t.month, t.year)),
                              ("{}:{}".format(t.hour, t.minute)), 
                              ("{}".format(str(datas)))]
            
           #print(val)
            mycursor.execute(sql, val)
            mydb.commit()
            
            print(mycursor.rowcount, " "+ str(tbl_db[i]) +" record inserted
            #print(sql, " " + str(tbl_db[i]) +" record inserted.")

            #print("Data ke-{} = {}".format(i+1,datas))
