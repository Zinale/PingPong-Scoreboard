# 🏓 PingPong Scoreboard


A **DIY (Do It Yourself)** digital scoreboard system designed for PingPong games, combining **hardware ⚙️** and **software 💻** to offer an interactive scoreboard with buttons 🔘, display 📺 and web interface 🌐.

---

## 🇬🇧 English Description


### ✨ Main Features ✨


- 🎮 Score updates via physical buttons connected to **Arduino UNO R4 WiFi**.
- 📺 Score display on **Nextion display** and **LED matrix**.
- 🎶 Fun sound effects (including Super Mario theme ;) ).
- 🌐 Responsive web interface with smooth CSS animations.
- 🔄 **Client-server system with Flask**, real-time updates via **Server-Sent Events (SSE)**.
- 📡 **Current configuration:** the Arduino connects to a WiFi network, which must be the same network used by the device hosting the web server.


### 🛠️ Technologies Used 🛠️


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
- 🎨 Custom stylesheets (`scoreboard.css`, `style.css`)


### ▶️ How to Use ▶️


1. ⚙️ **Setup the Arduino**
- 📡 Enter your WiFi credentials inside the `.ino` sketch.
- 🔄 Upload the code to the Arduino UNO R4 WiFi.
- 🔌 Connect buttons, LED matrix, and Nextion display.


2. 💻 **Start the web server**
- 📡 Ensure your computer is connected to the **same WiFi network** as the Arduino.
- 🖥️ Navigate to `arduinoUNO-R4WIFI-Nextion/` and run the Flask server:
  - **1.** Clone the Repository:
    ```bash
    git clone https://github.com/your-username/CityBeach-Ancona.git
    cd CityBeach-Ancona/CityBeach
    ```
  - **2.** Set Up Environment:
    ```bash
    python -m venv venv
    source venv/bin/activate  # Windows: venv\Scripts\activate
    ```
  - **3.** Install Requirements:
    ```bash
    pip install -r requirements.txt
    ```
  - **4.** Run the Application:
    ```bash
    python server_web.py
    ```
- 🌍 The server will be available at `http://<PC-IP>:5000`.


3. 🌐 **Access the web interface**  
   - 🔎 Open a browser and visit the server address.  
   - 📺 You will see the live scoreboard.  


4. 🏓 **Play!**  
   - 🔘 Use the Arduino buttons to increase or decrease scores.  
   - 📺🔲🌐 Scores update in real time on Nextion display, LED matrix, and the web app.  

---


## 📄 License

Distributed under the **MIT** license. See the [LICENSE](./LICENSE) file for more details.
## 📬 Contact

For questions, suggestions, or collaboration, please contact:

- 📧 zingaale@gmail.com  | Alessandro Zingaretti
