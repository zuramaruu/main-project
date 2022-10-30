from utils.SpeechText import SpeechText
from api.api import app
import requests


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
        if txt is not None:
            # print(txt)
            for i in range(10):
                self.send(txt)

    def onRequest(self):
        if self.commandRequest() == "ON":
            buff = int(self.valueRequest())
            buff = buff * (3.3 / 4095)
            buff = round(buff, 2)
            print(f"Volt = {buff}")


if __name__ == '__main__':
    h = Handler()
    while True:
        try:
            h.onRun()
            h.onRequest()
        except IOError as e:
            print(e)
