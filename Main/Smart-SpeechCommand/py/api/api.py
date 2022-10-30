from flask import Flask, render_template, request

app = Flask(__name__)

Query = ["OFF", "OFF", "COMMAND", "VALUES"]


class Data:
    def __init__(self):
        global Query
        self.txt = "relay"
        self.monitoring = "monitoring"
        self.condition = ["mati", "menyala"]

    @staticmethod
    def onProcess(buff):
        pass

    def onCheck(self, buff):
        data = buff[5:6]
        if buff == self.txt + str(data) + self.condition[1]:
            Query[int(data) - 1] = "ON"
        elif buff == self.txt + str(data) + self.condition[0]:
            Query[int(data) - 1] = "OFF"

        if buff == self.monitoring + self.condition[1]:
            Query[2] = "ON"
        elif buff == self.monitoring + self.condition[0]:
            Query[2] = "OFF"


# Instance Class Data
d = Data()


@app.route("/")
@app.route("/state", methods=['GET'])
def onState():
    return render_template("state.php", state=Query)


@app.route("/set_data", methods=['GET'])
def onCommand():
    buff = request.args.get("set")
    d.onCheck(buff)
    return render_template("state.php", state=Query)


@app.route("/set_value", methods=['GET'])
def onData():
    Query[3] = request.args.get("set")
    return render_template("state.php", state=Query)
