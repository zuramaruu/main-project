from utils.SpeechText import SpeechText
from api.api import app
import requests
import threading


class Handler:
    def __init__(self):
        self.domain = "http://192.168.200.6:5000"
        self.st = SpeechText()

    def send(self, data):
        requests.get(self.domain + "/set_data?set=" + data)

    def request(self):
        requests.get(self.domain)

    def valueRequest(self):
        value = requests.get(
            self.domain).content.decode(
            "utf-8").split(" ")
        return value[3]

    def commandRequest(self):
        value = requests.get(
            self.domain).content.decode(
            "utf-8").split(" ")
        return value[2]

    def print(self):
        print(self.valueRequest())

    @staticmethod
    def onSpeech():
        St = SpeechText()
        St.listen()

    @staticmethod
    def onServer():
        app.run(host='0.0.0.0', debug=True, port=5000)

    def onRun(self):
        txt = self.st.listen()
        self.send(txt)

    def onRequest(self):
        if self.commandRequest() == "ON":
            print(f"Value = {self.valueRequest()}")


class Process:
    def __init__(self):
        self.t = Handler()

        self.process1 = threading.Thread(
            target=self.t.onRun,
            name='1')
        self.process2 = threading.Thread(
            target=self.t.onRequest,
            name='t2')

    def onStart(self):
        self.process1.start()
        self.process2.start()

    def onJoin(self):
        self.process1.join()
        self.process2.join()


if __name__ == '__main__':
    while True:
        try:
            p = Process()
            p.onStart()
            p.onJoin()
        except IOError as e:
            print(e)
