from flask import Flask, request, jsonify, Response, render_template
from datetime import datetime
from queue import Queue
import json

app = Flask(__name__)

state = {
    "player1": 0,
    "player2": 0,
    "updated_at": datetime.utcnow().isoformat() + "Z"
}

listeners = []

def push_event(payload: dict):
    dead = []
    for q in listeners:
        try:
            q.put_nowait(payload)
        except Exception:
            dead.append(q)
    for q in dead:
        try:
            listeners.remove(q)
        except ValueError:
            pass

@app.route("/", methods=["GET"])
def index():
    return render_template("index.html")

@app.route("/score", methods=["GET", "POST"])
def score():
    global state
    if request.method == "POST":
        try:
            data = request.get_json(force=True, silent=False)
            p1 = int(data.get("player1", state["player1"]))
            p2 = int(data.get("player2", state["player2"]))
            state["player1"] = max(0, p1)
            state["player2"] = max(0, p2)
            state["updated_at"] = datetime.utcnow().isoformat() + "Z"
            push_event(state.copy())
            return jsonify({"ok": True, "state": state}), 200
        except Exception as e:
            return jsonify({"ok": False, "error": str(e)}), 400
    else:
        return jsonify(state)

@app.route("/events")
def sse_stream():
    q = Queue()
    listeners.append(q)

    try:
        q.put_nowait(state.copy())
    except Exception:
        pass

    def stream():
        try:
            while True:
                payload = q.get()
                data = json.dumps(payload)
                yield f"event: score\n"
                yield f"data: {data}\n\n"
        except GeneratorExit:
            pass
        finally:
            try:
                listeners.remove(q)
            except ValueError:
                pass

    return Response(stream(), mimetype="text/event-stream", headers={
        "Cache-Control": "no-cache",
        "Connection": "keep-alive",
        "X-Accel-Buffering": "no"
    })

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, threaded=True)
