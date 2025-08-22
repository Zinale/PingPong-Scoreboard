# 🏓 PingPong SegnaPunti / Scoreboard

Un sistema di **segnapunti digitale DIY (Do It Yourself / Fai da te)** pensato per le partite di PingPong, che unisce **hardware ⚙️** e **software 💻** per offrire un tabellone interattivo con pulsanti 🔘, display 📺 e interfaccia web 🌐.  
A **DIY digital scoreboard system** for PingPong games, combining **hardware ⚙️** and **software 💻** to provide an interactive scoreboard with buttons 🔘, display 📺, and web interface 🌐.

---

## 🌍 Languages
- 🇮🇹 [Italiano](#-descrizione-in-italiano)
- 🇬🇧 [English](#-english-description)

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

### ▶️ Come usare
1. ⚙️ **Configura l’Arduino**  
   - Inserisci le credenziali WiFi nello sketch `.ino`.  
   - Carica il codice sull’Arduino UNO R4 WiFi.  
   - Collega pulsanti, matrice LED e display Nextion.  

2. 💻 **Avvia il server web**  
   - Assicurati che il PC sia connesso alla **stessa rete WiFi** dell’Arduino.  
   - Vai in `arduinoUNO-R4WIFI-Nextion/` e avvia il server Flask:  

     ```bash
     git clone https://github.com/your-username/CityBeach-Ancona.git
     cd CityBeach-Ancona/CityBeach

     python -m venv venv
     source venv/bin/activate  # Windows: venv\Scripts\activate

     pip install -r requirements.txt

     python server_web.py
     ```

   - 🌍 Il server sarà disponibile su `http://<IP-PC>:5000`.  

3. 🌐 **Accedi all’interfaccia web**  
   - Apri un browser e visita l’indirizzo.  
   - Vedrai il tabellone aggiornato in tempo reale.  

4. 🏓 **Gioca!**  
   - Usa i pulsanti per incrementare/decrementare i punti.  
   - Punteggio sincronizzato su **display**, **matrice LED** e **interfaccia web**.  

---

## 🇬🇧 English Description

### ✨ Main Features
- 🎮 Score updates via physical buttons connected to **Arduino UNO R4 WiFi**.  
- 📺 Score display on **Nextion display** and **LED matrix**.  
- 🎶 Fun sound effects (well-known themes).  
- 🌐 Responsive web interface with smooth CSS animations.  
- 🔄 **Client-server system with Flask**, real-time updates via **Server-Sent Events (SSE)**.  
- 📡 **Current configuration:** Arduino connects to the same WiFi network used by the server host.  

### 🛠️ Technologies Used
**🔌 Hardware:**  
- 🖥️ Arduino UNO R4 WiFi  
- 📺 Nextion Display  
- 🔲 Arduino LED Matrix  
- 🔘 Physical buttons  
- 🔊 Buzzers  

**💻 Software:**  
- 📝 C++ (Arduino)  
- 🐍 Python (Flask)  
- 🌐 HTML + 🎨 CSS + ⚡ JavaScript  
- 🎬 CSS Animations  
- 🔄 Server-Sent Events (SSE)  

**📂 Files & Layouts:**  
- 🗂️ Nextion project files (`.HMI`, `.tft`)  
- 💾 Arduino sketches (`.ino`)  
- 🧩 Flask templates (`index.html`)  
- 🎨 Stylesheets (`scoreboard.css`, `style.css`)  

### ▶️ How to Use
1. ⚙️ **Setup the Arduino**  
   - Enter WiFi credentials inside the `.ino` sketch.  
   - Upload the code to the Arduino UNO R4 WiFi.  
   - Connect buttons, LED matrix, and Nextion display.  

2. 💻 **Start the Web Server**  
   - Ensure your computer is connected to the **same WiFi network** as the Arduino.  
   - Navigate to `arduinoUNO-R4WIFI-Nextion/` and run the Flask server:  

     ```bash
     git clone https://github.com/your-username/CityBeach-Ancona.git
     cd CityBeach-Ancona/CityBeach

     python -m venv venv
     source venv/bin/activate  # Windows: venv\Scripts\activate

     pip install -r requirements.txt

     python server_web.py
     ```

   - 🌍 The server will be available at `http://<PC-IP>:5000`.  

3. 🌐 **Access the Web Interface**  
   - Open a browser and visit the server address.  
   - The live scoreboard will appear.  

4. 🏓 **Play!**  
   - Use the Arduino buttons to update scores.  
   - Scores sync across **Nextion display**, **LED matrix**, and **web app**.  

---

## 📜 License
Distributed under the **MIT** license. See the [LICENSE](./LICENSE) file for more details.  

## 📬 Contact
- 📧 zingaale@gmail.com  | Alessandro Zingaretti
