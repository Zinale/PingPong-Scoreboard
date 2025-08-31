#include "Arduino_LED_Matrix.h"
#include <WiFiS3.h>        
#include <ArduinoHttpClient.h>  
#include "notes.h"

// WiFi setup

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

#define POINT_AT_SET 21

ArduinoLEDMatrix matrix;
byte frame[8][12] = {0};

const unsigned long debounceMs = 40;

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
int set1 = 0;
int set2 = 0;
int nSet = 3;

unsigned long int lastTryToSend = millis();
short int last_score_of_5 = 0;
bool set_is_finished = false;
bool swapScores = false;
Song songs[] = {pokemon,conan,dragonball};
int nSongs = sizeof(songs) / sizeof(songs[0]);
unsigned long lastBuzz = millis();
bool changeFieldShown = false;

//display IP on matrix
unsigned long lastSwitch = 0;
String ipString = "";
String ipParts[4];  

//WiFi
WiFiClient wifi;
HttpClient http(wifi, serverHost, serverPort);

//Check if the server is on
unsigned long lastServerCheck = millis();
bool retryToSend = false;

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

bool checkIfServerIsOn(){
    Serial.println("Pinging server");
    WiFiClient testClient;
    if (!testClient.connect(serverHost, serverPort)) {
      Serial.println("Server non raggiungibile");
      testClient.stop();
      return false;
    }
    testClient.stop();
    Serial.println("Server ONLINE!");
    return true;
}

void sendScores() {
  Serial.println("Sending data...");
  Serial.print("Wifi status: ");
  Serial.println(WiFi.status());
  if(WiFi.status()== WL_CONNECTED){
    if (!checkIfServerIsOn()) {
      retryToSend = true;
      lastTryToSend = millis();
      return;
    }
    Serial.println("Writing msg...");
    retryToSend = false;
    String msg;
    if (swapScores){    //avoid player's color change
      msg = "{\"player1\":" + String(score2) + ",\"player2\":" + String(score1) + ",\"set1\":" + String(set1) + ",\"set2\":" + String(set2) + ",\"nSet\":" + String(nSet) + "}";
    }else{
      msg = "{\"player1\":" + String(score1) + ",\"player2\":" + String(score2) + ",\"set1\":" + String(set1) + ",\"set2\":" + String(set2) + ",\"nSet\":" + String(nSet) + "}";
    }
    Serial.println(msg);
    http.setTimeout(200); 
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
  return;
}

void updateScore(int &score, int delta, Song sound) {
  score = max(0, score + delta);
  sendScores();
  playSong(sound);
  lastBuzz = millis();
}

void checkSetFinished() {
  Serial.println("==============================\n\rChecking Set is finished...");
  if (!set_is_finished) {
    if (score1 >= POINT_AT_SET && score1 >= score2 + 2) {
      declareWinner(1);
    } else if (score2 >= POINT_AT_SET && score2 >= score1 + 2) {
      declareWinner(2);
    }
  }
  int midSet = (POINT_AT_SET + 1) / 2;
  if(set1+set2==(nSet-1) && score1+score2==midSet && !changeFieldShown){
    delay(100);
    playSong(fieldAlert);
    changeFieldShown=true;
    int a = score1;
    score1=score2;
    score2=a;
    swapScores = !swapScores;   //change of field
  }
  Serial.println("==============================");
}

void declareWinner(int player) {
  Serial.print("Set finito! Ha vinto P");
  Serial.println(player);
  set_is_finished = true;
  if (!swapScores){
    if (player == 1) set1++; else set2++;
  } else{if (player == 1) set2++; else set1++;}
  sendScores();
  playSong(songs[random(nSongs)]);
  lastBuzz = millis();
}

void resetSet() {
  Serial.println((set1+set2));
  Serial.println(nSet-1);
  Serial.println((set1+set2)!=nSet-1);
  Serial.print(swapScores);Serial.print("->");
  if ((set1+set2)%2!=0 && (set1+set2)!=nSet-1){swapScores = !swapScores;}
  Serial.println(swapScores);
  delay(4000);
  set_is_finished = false;
  last_score_of_5 = 0;
  score1 = 0;
  score2 = 0;
  sendScores();
}


void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial.println("#############################\n\rSTARTING\n\r#############################");

  pinMode(BTN1_PLUS,  INPUT_PULLUP);
  pinMode(BTN1_MINUS, INPUT_PULLUP);
  pinMode(BTN2_PLUS,  INPUT_PULLUP);
  pinMode(BTN2_MINUS, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Connessione WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connessione al WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  tone(BUZZER,1000,1000);
  Serial.println("\nConnesso al WiFi!");
  IPAddress ip = WiFi.localIP();
  ipString = ip.toString();
  Serial.print("IP Arduino: "); Serial.println(ipString);

  //check if the server is ON
  //if the server is not on, retry on loop else press a button
  while (!checkIfServerIsOn())
  {
    unsigned long mil = millis();
    if (mil - lastBuzz > 5000) {playSong(alertLong);lastBuzz = mil;}
    if (buttonPressed(btn1_plus) or buttonPressed(btn1_minus) or buttonPressed(btn2_minus) or buttonPressed(btn2_plus)){
      break;
    }
  }
  sendScores();
  splitIP(ipString);
  matrix.begin();
  playSong(superMario);
  Serial.println("\nConnesso al WiFi!");
  ip = WiFi.localIP();
  ipString = ip.toString();
  Serial.print("IP Arduino: "); Serial.println(ipString);
}


// ========================================================================
// ========================================================================
// ========================= LOOP =========================
void loop() {
  bool b1p = buttonPressed(btn1_plus);
  bool b1m = buttonPressed(btn1_minus);
  bool b2p = buttonPressed(btn2_plus);
  bool b2m = buttonPressed(btn2_minus);

  checkSetFinished(); 
  Serial.println("In game...");
  
  //change nSet
  if(b1p && b2p){
    if (nSet==3){
      nSet =5;
    }else{
      nSet=3;
    }
  }

  if (!set_is_finished){
    if (b1p)  updateScore(score1, +1, levelUp);
    if (b1m) updateScore(score1, -1, levelDown);
    if (b2p)  updateScore(score2, +1, levelUp);
    if (b2m) updateScore(score2, -1, levelDown);
    Serial.println("Score:");Serial.println(score1);Serial.println(score2);
  }else{
    if (b1m || b1p || b2m || b2p){
      resetSet();
    }
  }

  sendToNextion("score1.txt=\"" + String(score1) + "\"");
  sendToNextion("score2.txt=\"" + String(score2) + "\"");
  
  updateDisplay();

  if ((score1+score2)%5==0 && (score1+score2)!= last_score_of_5){
    Serial.println("Controllo cambio servizio");
    unsigned long mil = millis();
    if (mil - lastBuzz > 3000){
      Serial.println("-----Alert cambio servizio--------");
      lastBuzz = mil;
      playSong(alertShort);
      last_score_of_5 = score1+score2;
    }
  }

  if (retryToSend && millis()-lastTryToSend > 30000 ) {sendScores();lastTryToSend = millis();}

  if (millis() - lastServerCheck > 60000)   //60s
  { 
    Serial.println("Verifica se server ON...");
    if (!checkIfServerIsOn()){
      playSong(alertLong);
    }
    lastServerCheck = millis();
  }
  
  delay(5);
  
}
