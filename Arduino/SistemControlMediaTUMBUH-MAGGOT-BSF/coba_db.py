import mysql.connector
import time
import datetime
import random


mydb = mysql.connector.connect(
  host="localhost",
  user="phpmyadmin",
  password="Maggot123",
  database="project_monitoring-system"
)

mycursor = mydb.cursor()

while True:
  t = datetime.datetime.now()
  sql = "INSERT INTO data_sensor_a (tanggal , jam, nilai_sensor) VALUES (%s, %s, %s)"
  val = [("{}/{}/{}".format(t.day, t.month, t.year)),
                  ("{}:{}".format(t.hour, t.minute)), 
                  ("{}".format(random.random()))]
  mycursor.execute(sql, val)
  mydb.commit()
  print(mycursor.rowcount, "record inserted.")
