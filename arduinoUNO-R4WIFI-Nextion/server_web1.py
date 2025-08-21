# app.py
from flask import Flask, request, jsonify, Response, render_template
from datetime import datetime
from queue import Queue
import json
import threading
import time

app = Flask(__name__)

# Stato condiviso
state = {
    "player1": 0,
    "player2": 0,
    "updated_at": datetime.utcnow().isoformat() + "Z"
}

# Coda per notificare gli aggiornamenti agli stream SSE
listeners = []

def push_event(payload: dict):
    """Invia l'evento a tutti i client SSE con backpressure-safe queues."""
    dead = []
    for q in listeners:
        try:
            q.put_nowait(payload)
        except Exception:
            dead.append(q)
    # Pulisce listener morti
    for q in dead:
        try:
            listeners.remove(q)
        except ValueError:
            pass

@app.route("/", methods=["GET"])
def index():
    # Dashboard HTML
    return render_template("index3.html")

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
            # Notifica a chi è in ascolto
            push_event(state.copy())
            return jsonify({"ok": True, "state": state}), 200
        except Exception as e:
            return jsonify({"ok": False, "error": str(e)}), 400
    else:
        return jsonify(state)

@app.route("/events")
def sse_stream():
    """Endpoint SSE: i browser si connettono qui per ricevere gli aggiornamenti live."""
    q = Queue()
    listeners.append(q)

    # Invia subito lo stato corrente al nuovo client
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
            # Il client si è disconnesso
            pass
        finally:
            try:
                listeners.remove(q)
            except ValueError:
                pass

    # headers SSE
    return Response(stream(), mimetype="text/event-stream", headers={
        "Cache-Control": "no-cache",
        "Connection": "keep-alive",
        "X-Accel-Buffering": "no"
    })

if __name__ == "__main__":
    # Avvia su tutte le interfacce, porta 5000 (come nel tuo Arduino)
    app.run(host="0.0.0.0", port=5000, threaded=True)
