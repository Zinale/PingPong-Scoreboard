# 🏓 PingPong SegnaPunti


Un sistema di **segnapunti digitale DIY (Do It Yourself / Fai da te)** pensato per le partite di PingPong, che unisce **hardware ⚙️** e **software 💻** per offrire un tabellone interattivo con pulsanti 🔘, display 📺 e interfaccia web 🌐.


---


## 🇮🇹 Descrizione in Italiano


### ✨ Funzionalità principali
- 🎮 Aggiornamento del punteggio con pulsanti fisici collegati ad **Arduino UNO R4 WiFi**.
- 📺 Visualizzazione punteggio su **display Nextion** e **matrice LED**.
- 🎶 Effetti sonori (temi **noti**).
- 🌐 Interfaccia web responsive con animazioni CSS per mostrare i punti live.
- 🔄 Sistema **server-client con Flask** e aggiornamenti in tempo reale via **Server-Sent Events (SSE)**.
- 📡 **Configurazione attuale:** l’Arduino si connette ad una rete WiFi che deve essere la stessa usata dal dispositivo che ospita il server web.


### 🛠️ Tecnologie utilizzate
**🔌 Hardware:**
- 🖥️ Arduino UNO R4 WiFi
- 📺 Display Nextion
- 🔲 Arduino LED Matrix
- 🔘 Pulsanti fisici
- 🔊 Buzzer


**💻 Software:**
- 📝 C++ (Arduino)
- 🐍 Python (Flask)
- 🌐 HTML + 🎨 CSS + ⚡ JavaScript
- 🎬 Animazioni CSS
- 🔄 Server-Sent Events (SSE)


**📂 File e Layout:**
- 🗂️ Progetti Nextion (`.HMI`, `.tft`)
- 💾 Sketch Arduino (`.ino`)
- 🧩 Template Flask (`index.html`)
- 🎨 Fogli di stile (`scoreboard.css`, `style.css`)

---

### ▶️ Come usare 
1. ⚙️ **Configura l’Arduino**
- 📡 Inserisci le credenziali della tua rete WiFi nello sketch `.ino`.
- 🔄 Carica il codice sull’Arduino UNO R4 WiFi.
- 🔌 Collega i pulsanti, la matrice LED (integrata in questo modello) e il display Nextion.


2. 💻 **Avvia il server web**
- 📡 Assicurati che il tuo computer sia connesso alla **stessa rete WiFi** dell’Arduino.
- 🖥️ Vai nella cartella `arduinoUNO-R4WIFI-Nextion/` e, dopo avvia il server Flask:
  - **1.** Copia la Repository:
    ```bash
    git clone https://github.com/your-username/CityBeach-Ancona.git
    cd CityBeach-Ancona/CityBeach
    ```
  - **2.** Imposta l'ambiente virtuale python:
    ```bash
    python -m venv venv
    source venv/bin/activate  # Windows: venv\Scripts\activate
    ```
  - **3.** Installa le librerie richieste:
    ```bash
    pip install -r requirements.txt
    ```
  - **4.** Avvia l'applicazione:
    ```bash
    python server_web.py
    ```
- 🌍 Il server sarà attivo su `http://<IP-PC>:5000`.



3. 🌐 **Accedi all’interfaccia web**
- 🔎 Apri un browser e visita l’indirizzo del server.
- 📺 Vedrai il tabellone segnapunti in tempo reale.



4. 🏓 **Gioca!**
- 🔘 Usa i pulsanti collegati all’Arduino per incrementare o decrementare i punti.
- 📺🔲🌐 Il punteggio verrà aggiornato in tempo reale su display, matrice LED e interfaccia web.


---


## 📜 Licenza

Distribuito sotto licenza **MIT**. Vedi il file [LICENSE](./LICENSE) per maggiori dettagli.

## 📬 Contact

Per domande, suggerimenti o collaborioni, contattat:

- 📧 zingaale@gmail.com  | Alessandro Zingaretti