from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

score = {"a": 0, "b": 0}

@app.route("/")
def index():
    return render_template("index.html", score=score)

@socketio.on("update_point")
def handle_update_point(data):
    player = data.get("player")
    change = data.get("change", 0)  # +1 o -1
    if player in score:
        score[player] += change
        if score[player] < 0:
            score[player] = 0
        socketio.emit("update_score", score)

@socketio.on("reset_score")
def handle_reset_score():
    score["a"] = 0
    score["b"] = 0
    socketio.emit("update_score", score)

if __name__ == "__main__":
    socketio.run(app, host="0.0.0.0", port=5001,allow_unsafe_werkzeug=True)
