#define LED LED_BUILTIN

const byte BTN1_PLUS  = 2;
const byte BTN1_MINUS = 3;
const byte BTN2_PLUS  = 4;
const byte BTN2_MINUS = 5;

const unsigned long debounceMs = 30;

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

void setup() {
  Serial.begin(9600);  
  Serial1.begin(115200);  //for Nextion

  pinMode(BTN1_PLUS,  INPUT_PULLUP);
  pinMode(BTN1_MINUS, INPUT_PULLUP);
  pinMode(BTN2_PLUS,  INPUT_PULLUP);
  pinMode(BTN2_MINUS, INPUT_PULLUP);

  pinMode(LED, OUTPUT);

  Serial.println("SETUP COMPLETED\n\r--------------------------------------------------------------.");
}

// debounce function
bool buttonPressed(Button &btn) {
  bool reading = digitalRead(btn.pin);
  if (reading != btn.lastStableState && (millis() - btn.lastChange) > debounceMs) {
    btn.lastChange = millis();
    btn.lastStableState = reading;
    if (reading == LOW) return true;  //true only if btn is pressed
  }
  return false;
}

void loop() {
  if (buttonPressed(btn1_plus)) {
    score1++;
    digitalWrite(LED, HIGH);
    Serial.print("Player 1 Score: "); Serial.println(score1);
  }
  if (buttonPressed(btn1_minus) && score1 > 0) {
    if (score1>0){
      score1--;
      digitalWrite(LED, LOW);
      }
    Serial.print("Player 1 Score: "); Serial.println(score1);
  }

  if (buttonPressed(btn2_plus)) {
    score2++;
    Serial.print("Player 2 Score: "); Serial.println(score2);
  }
  if (buttonPressed(btn2_minus) && score2 > 0) {
    if (score2>0){
      score2--;
      }
    Serial.print("Player 2 Score: "); Serial.println(score2);
  }

  //update Nextion 
  sendToNextion("score1.txt=\"" + String(score1) + "\"");
  sendToNextion("score2.txt=\"" + String(score2) + "\"");
  delay(1);
}

void sendToNextion(String cmd) {
  Serial1.print(cmd);
  Serial1.write(0xFF);  
  Serial1.write(0xFF);
  Serial1.write(0xFF);
}
