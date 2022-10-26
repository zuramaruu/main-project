from flask import Flask, render_template, request
import sys

app = Flask(__name__)

buff = ["OFF", "OFF"]


@app.route("/")
@app.route("/home", methods=['GET', 'POST'])
def home():
    global buff
    try:
        if request.method == 'POST':
            output = request.form.to_dict()
            state = output["state"]
            if state == "1":
                buff[0] = "ON"
            elif state == "0":
                buff[0] = "OFF"
            elif state == "3":
                buff[1] = "ON"
            elif state == "2":
                buff[1] = "OFF"
    except ValueError:
        pass

    return render_template("index.html", state=buff)


@app.route("/state", methods=['GET'])
def st():
    return render_template("state.php", state=buff)


@app.route("/set_state", methods=['GET'])
def set_state():
    buffer = request.args.get("set")
    if buffer == "1":
        buff[0] = "ON"
    elif buffer == "0":
        buff[0] = "OFF"
    elif buffer == "3":
        buff[1] = "ON"
    elif buffer == "2":
        buff[1] = "OFF"
    return render_template("state.php", state=buff)


if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True, port=5000)
