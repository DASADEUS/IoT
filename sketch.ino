#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);


// defining the pins
const int trigPinR = 3;
const int echoPinR = 2;
const int trigPinM = 5;
const int echoPinM = 4;
const int trigPinL = 7;
const int echoPinL = 6;
const int trigPinF = 9;
const int echoPinF = 8;
const int stepperLactiv=11;
const int stepperLdirection=13;
const int stepperRactiv=10;
const int stepperRdirection=12;


void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinM, OUTPUT);
  pinMode(echoPinM, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(stepperLactiv, OUTPUT);
  pinMode(stepperRactiv, OUTPUT);
  }
float readDistanceCM(int TRIG_PIN,int ECHO_PIN) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}
void GoRight(){
  delay(10);
  digitalWrite(stepperLdirection, 1);
  analogWrite(stepperLactiv, 1);
  digitalWrite(stepperRdirection, 0);
  analogWrite(stepperRactiv, 1);
}
void GoLeft(){
  delay(10);
  digitalWrite(stepperLdirection, 0);
  analogWrite(stepperLactiv, 1);
  digitalWrite(stepperRdirection, 1);
  analogWrite(stepperRactiv, 1);
}
void GoOn(){
  delay(10);
  digitalWrite(stepperLdirection, 1);
  analogWrite(stepperLactiv, 1);
  digitalWrite(stepperRdirection, 1);
  analogWrite(stepperRactiv, 1);
}
void GoRound(){

  delay(3000);
  digitalWrite(stepperLdirection, 1);
  analogWrite(stepperLactiv, 1);
  digitalWrite(stepperRdirection, 0);
  analogWrite(stepperRactiv, 1);
}

void Emergency(){
  analogWrite(stepperLactiv, 0);
  analogWrite(stepperRactiv, 0);
}

void loop() {
  
  float distanceR = readDistanceCM(trigPinR,echoPinR);
  float distanceM = readDistanceCM(trigPinM,echoPinM);
  float distanceL = readDistanceCM(trigPinL,echoPinL);
  float distanceF = readDistanceCM(trigPinF,echoPinF);
  int status=analogRead(3);
  if(status!=0){

  if (distanceF<5){//проверка пола
    if (distanceM<10){
      if (distanceL<=distanceR){        
        lcd.clear();
        lcd.setCursor(7, 1);
        lcd.print("GO RIGHT");
        GoRight();
      }
      else if (distanceL>distanceR){        
        lcd.clear();
        lcd.setCursor(7, 1);
        lcd.print("GO LEFT");
        GoLeft();
      }
      else{
        
        lcd.clear();
        lcd.setCursor(7, 1);
        lcd.print("GO ROUND1");
        GoRound();
        
      }
    }
    else if ((distanceR<14)&&(distanceL<14)){
      
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("GO ROUND2");
      GoRound();
    }
    else if (distanceR<=14){
      
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("GO left");
      GoLeft();
    }
    else if (distanceL<=14){
      
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("GO Right");
      GoRight();
    }
    else{
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("GO ON");
      GoOn();
    }
  }
  else{
    lcd.clear();
    lcd.setCursor(7, 1);
    lcd.print("emergency");
    Emergency();
  }


  }
  else
  {
    Emergency();
    lcd.clear();
  }


}
