#include "Arduino_LED_Matrix.h"
#include <WiFiS3.h>        
#include <ArduinoHttpClient.h>  
#include "pitches.h"

// Credenziali WiFi
//const char* ssid     = "Gigante-Fondatore";
//const char* password = "grisha-jaeger";



// Server Flask 
const char* serverHost = "192.168.0.242";
int serverPort = 5000;
String serverPath = "/score";

#define BTN1_PLUS  2
#define BTN1_MINUS 3
#define BTN2_PLUS  4
#define BTN2_MINUS 5
#define LED        LED_BUILTIN
#define BUZZ1 10
#define BUZZ2 11

ArduinoLEDMatrix matrix;
byte frame[8][12] = {0};

const unsigned long debounceMs = 10;
bool start = true;

struct Button {
  byte pin;
  bool lastStableState;
  unsigned long lastChange;
};

Button btn1_plus  = {BTN1_PLUS,  HIGH, 0};
Button btn1_minus = {BTN1_MINUS, HIGH, 0};
Button btn2_plus  = {BTN2_PLUS,  HIGH, 0};
Button btn2_minus = {BTN2_MINUS, HIGH, 0};

int score1 = 0;
int score2 = 0;

//display IP on matrix
unsigned long lastSwitch = 0;
String ipString = "";
String ipParts[4];  

//WiFi
WiFiClient wifi;
HttpClient http(wifi, serverHost, serverPort);

int melody_superMario[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  // --- Parte B ---
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

int noteDurations_superMario[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  // parte B
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

void playSong(int buzz, int melody[],int noteDurations[]) {
  Serial.println("Playing music!!!");
  int notes = sizeof(melody) / sizeof(melody[0]);

  for (int thisNote = 0; thisNote < notes; thisNote++) {
    int duration = 1000 / noteDurations[thisNote];
    int note = melody[thisNote];

    if (note > 0) tone(buzz, note, duration);

    delay(duration * 1.30);
    noTone(buzz);
  }
}


bool buttonPressed(Button &btn) {
  bool reading = digitalRead(btn.pin);
  if (reading != btn.lastStableState && (millis() - btn.lastChange) > debounceMs) {
    btn.lastChange = millis();
    btn.lastStableState = reading;
    if (reading == LOW) return true; 
  }
  return false;
}

void sendToNextion(String cmd) {
  Serial1.print(cmd);
  Serial1.write(0xFF);  
  Serial1.write(0xFF);
  Serial1.write(0xFF);
}

void clearDisplay(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = 0;
    }  
  }
}
void digit(int n, int offx, int offy){      //on matrix
  switch(n) {
    case 0:
      frame[offy][offx+0] = 1;
      frame[offy][offx+1] = 1;
      frame[offy][offx+2] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 1;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 0;
      frame[offy+2][offx+2] = 1;

      frame[offy+3][offx+0] = 1;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      break;
    case 1:
      frame[offy][offx+0] = 0;
      frame[offy][offx+1] = 1;
      frame[offy][offx+2] = 1;

      frame[offy+1][offx+0] = 0;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 1;

      frame[offy+2][offx+0] = 0;
      frame[offy+2][offx+1] = 0;
      frame[offy+2][offx+2] = 1;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 1;

      frame[offy+4][offx+0] = 0;
      frame[offy+4][offx+1] = 0;
      frame[offy+4][offx+2] = 1;
      break;
    case 2:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 0;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 1;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 0;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 3:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 0;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 4:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 0;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 0;
    frame[offy+4][offx+1] = 0;
    frame[offy+4][offx+2] = 1;
    break;
    case 5:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 0;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 6:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 0;
    frame[offy][offx+2] = 0;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 0;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 1;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 7:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 0;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 0;
    frame[offy+2][offx+1] = 0;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 0;
    frame[offy+4][offx+1] = 0;
    frame[offy+4][offx+2] = 1;
    break;
    case 8:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 1;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 9:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
  }}


void updateDataMatrix(int value){
  clearDisplay();
  int c = value / 100;
  int d = (value / 10) % 10;
  int u = value % 10;

  int offsetY = 1;
  int offsetX = 1;

  if(value >= 100){
    digit(c, offsetX, offsetY); offsetX += 4;
  }
  if(value >= 10){
    digit(d, offsetX, offsetY); offsetX += 4;
  }
  digit(u, offsetX, offsetY);

  matrix.renderBitmap(frame,8,12);
}

void splitIP(String ip) {
  int start = 0;
  int idx = 0;
  while (idx < 4) {
    int dot = ip.indexOf('.', start);
    if (dot == -1) dot = ip.length();
    ipParts[idx] = ip.substring(start, dot);
    start = dot + 1;
    idx++;
  }
}

void renderIP() {
  static int index = 0;
  updateDataMatrix(ipParts[index].toInt()); 
  index = (index + 1) % 4;    
}

void updateDisplay() {
  if (millis() - lastSwitch > 2000) {
    renderIP();
    lastSwitch = millis();
  }
}

void sendScores() {
  Serial.print("Wifi status: ");
  Serial.println(WiFi.status());
  if(WiFi.status()== WL_CONNECTED){
    String msg = "{\"player1\":" + String(score1) + ",\"player2\":" + String(score2) + "}";
    http.setTimeout(5000);       
    http.beginRequest();
    http.post(serverPath);
    http.sendHeader("Content-Type", "application/json");
    http.sendHeader("Content-Length", msg.length());
    http.beginBody();
    http.print(msg);
    http.endRequest();
  
    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    Serial.print("HTTP status: "); Serial.println(statusCode);
    Serial.print("Response: "); Serial.println(response);
  }
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);

  pinMode(BTN1_PLUS,  INPUT_PULLUP);
  pinMode(BTN1_MINUS, INPUT_PULLUP);
  pinMode(BTN2_PLUS,  INPUT_PULLUP);
  pinMode(BTN2_MINUS, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // Connessione WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connessione al WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  tone(11,1000,1000);
  Serial.println("\nConnesso al WiFi!");
  IPAddress ip = WiFi.localIP();
  ipString = ip.toString();
  Serial.print("IP Arduino: "); Serial.println(ipString);

  splitIP(ipString);
  matrix.begin();
  playSong(BUZZ1,melody_superMario,noteDurations_superMario);
  //sendScores();
}

// ===== LOOP =====
void loop() {
  if (start){
    Serial.println("Arduino STARTED");
    sendScores();
    start=false;
  }
  if (buttonPressed(btn1_plus)) {Serial.println("1!"); score1++; sendScores();tone(10,1000,1000);}
  if (buttonPressed(btn1_minus) && score1 > 0) { score1--; sendScores();  tone(10,1000,1000); }
  if (buttonPressed(btn2_plus)) {Serial.println("2!"); score2++;  sendScores(); tone(11,1000,1000); }
  if (buttonPressed(btn2_minus) && score2 > 0) { score2--;sendScores(); tone(11,1000,1000); }

  sendToNextion("score1.txt=\"" + String(score1) + "\"");
  sendToNextion("score2.txt=\"" + String(score2) + "\"");
  
  updateDisplay();
  delay(10);
}
