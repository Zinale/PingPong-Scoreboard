#include <WiFiS3.h>

// === CONFIGURAZIONE Wi-Fi ===
char ssid[] = "SKYWIFI_K7TC9";     // <-- Cambia con il tuo SSID
char pass[] = "bj9wJTbhaAg4";     // <-- Cambia con la tua password
int status = WL_IDLE_STATUS;

// === SERVER HTTP sulla porta 80 ===
WiFiServer server(80);

// === Punteggi ===
int scoreA = 0;
int scoreB = 0;

void setup() {
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Connessione a ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(3000);
  }

  Serial.println("Connesso al Wi-Fi");
  Serial.print("IP assegnato: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    String response;
    String contentType = "text/html";

    // === API per punteggio JSON ===
    if (request.indexOf("GET /score") != -1) {
      contentType = "application/json";
      response = "{\"A\":" + String(scoreA) + ",\"B\":" + String(scoreB) + "}";
    }
    // Incrementa A
    else if (request.indexOf("GET /addA") != -1) {
      scoreA++;
      contentType = "application/json";
      response = "{\"A\":" + String(scoreA) + ",\"B\":" + String(scoreB) + "}";
    }
    // Incrementa B
    else if (request.indexOf("GET /addB") != -1) {
      scoreB++;
      contentType = "application/json";
      response = "{\"A\":" + String(scoreA) + ",\"B\":" + String(scoreB) + "}";
    }
    // Pagina HTML principale
    else {
      response = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
          <meta charset="UTF-8">
          <title>Punteggio Ping Pong</title>
          <style>
            body { font-family: Arial; text-align: center; }
            button { font-size: 20px; padding: 10px 20px; margin: 10px; }
            h1 { font-size: 28px; }
          </style>
        </head>
        <body>
          <h1>Punteggio</h1>
          <h2>Giocatore A: <span id="scoreA">0</span></h2>
          <h2>Giocatore B: <span id="scoreB">0</span></h2>
          <button onclick="addPoint('A')">+1 Giocatore A</button>
          <button onclick="addPoint('B')">+1 Giocatore B</button>
          
          <script>
            async function updateScore() {
              let res = await fetch('/score');
              let data = await res.json();
              document.getElementById('scoreA').innerText = data.A;
              document.getElementById('scoreB').innerText = data.B;
            }
            async function addPoint(player) {
              await fetch('/add' + player);
              updateScore();
            }
            setInterval(updateScore, 1000); // Aggiorna ogni 1s
            updateScore();
          </script>
        </body>
        </html>
      )rawliteral";
    }

    // === Invio risposta ===
    client.println("HTTP/1.1 200 OK");
    client.print("Content-Type: ");
    client.println(contentType);
    client.println("Connection: close");
    client.println();
    client.print(response);

    delay(0.1);
    client.stop();
  }
}
