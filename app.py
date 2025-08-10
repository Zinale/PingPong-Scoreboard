from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

score = {"a": 0, "b": 0}

@app.route("/")
def index():
    return render_template("index.html", score=score)

@socketio.on("add_point")
def handle_add_point(data):
    player = data.get("player")
    if player in score:
        score[player] += 1
        socketio.emit("update_score", score)

@socketio.on("reset_score")
def handle_reset_score():
    score["a"] = 0
    score["b"] = 0
    socketio.emit("update_score", score)

if __name__ == "__main__":
    socketio.run(app, host="0.0.0.0", port=6000) 
