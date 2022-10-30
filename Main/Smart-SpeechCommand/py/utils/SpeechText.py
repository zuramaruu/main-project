import speech_recognition as sr
import pyttsx3 as pyt


class SpeechText:
    def __init__(self):
        self.engine = pyt.init()
        self.voices = self.engine.getProperty('voices')
        self.engine.setProperty('voice', self.voices[1].id)

        self.listen_s = sr.Recognizer()
        self.tx = ["Listening", "Processing", " ..."]
        self.text = self.listen()

    def listen(self):
        service = ""
        # self.speech(self.tx[0])
        try:
            with sr.Microphone() as source:
                print(self.tx[0] + self.tx[2])
                # self.listen_s.pause_threshold = 0.9
                my_voice = self.listen_s.listen(source, phrase_time_limit=5)

                # self.speech(self.tx[1])
                service = self.listen_s.recognize_google(my_voice, language='id-ID')

        except sr.UnknownValueError as e:
            pass

        if service != "":
            print("Command : " + service)
        return service.replace(" ", "")

    @staticmethod
    def speech(txt):
        pyt.speak(txt)

    def talk(self, audio):
        self.engine.say(audio)
        self.engine.runAndWait()
