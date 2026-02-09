#include <Keypad.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>

//LCD initailiation
#define I2C_ADDR    0x27  // <<----- Replace your address here by scanning your i2c display using i2c scanner program to find the code
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

//Keypad initialiation
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, 4};
byte colPins[COLS] = {12, 13, 8, 7}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Password system initialiation 
String passwords[] = {"1234", "5678", "9012","2024"};
String users[] = {"Adityan", "Yuvraj", "Bhoomika","Admin"};
int visitorsAuthed[] = {1,2,3,4};

String input_password = "";

//Buzzer initailation
int i = 0;
int buzzerPin = 2;

//Servo initialiation 
Servo myservo;    
int pos = 0;                // variable to store the servo position
int servoPin = 5;   

//Ultrasonic initialisation
// Define the pins for the first ultrasonic sensor
const int trigPin1 = 11;
const int echoPin1 = 3;

int wrongPassCount = 0;
bool timeUpFlag = false;

char caseVar = 's';
int caseCount = 0;
bool caseFlag = true;
bool Sflag = false;
bool Rflag = false;
bool msgFlag = false;

SoftwareSerial mySerial(9, 10);

unsigned long startTime1 = millis(); // get the start time
unsigned long elapsedTime1 = 0;
unsigned long startTime2 = millis(); // get the start time
unsigned long elapsedTime2 = 0;

String msgToSend = "";
int visitorCount = 0;
bool visitorFlag = false;
bool callFlag = false;

void setup(){
  // Set the trigger pins as outputs
  pinMode(trigPin1, OUTPUT);
  
  // Set the echo pins as inputs
  pinMode(echoPin1, INPUT);

  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();

  lcd.print("Enter Password:");
  lcd.setCursor (0,1);

  pinMode(buzzerPin, OUTPUT);

  myservo.attach(servoPin);

  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop(){
    myservo.write(0);
    
    input_password = "";

    char key = keypad.getKey();// Read the key
    // Print if key pressed
    while(key != '#'){
      if (key){
        Serial.print("Key Pressed : ");
        Serial.println(key);

        lcd.print(key);
        lcd.setCursor (++i,1);

        tone(buzzerPin,1500);
        delay(125);
        noTone(buzzerPin);

        input_password += key;

        if(key == '*'){
          break;
        }
      }

      key = keypad.getKey();
    }

    int LoggedUser = checkPass(input_password);
    lcd.clear();
    lcd.home();

    if(LoggedUser >= 0){
      wrongPassCount = 0;
      timeUpFlag = false;

      lcd.clear();
      lcd.home();
      lcd.print("Access Granted!");
      lcd.setCursor(0,1);
      lcd.print("User: " + users[LoggedUser]);

      delay(500);

      correctPassword();

      delay(3000);

      lcd.clear();
      lcd.home();
      lcd.print("Notifying Owner:");
      lcd.setCursor(0,1);
      lcd.print("Progress:sending");

      msgToSend = "The user: " + users[LoggedUser] + " has entered the house"; 
      sendSMS(msgToSend);
      sendSMS2(msgToSend);

      lcd.clear();
      lcd.home();
      lcd.print("Notifying Owner:");
      lcd.setCursor(0,1);
      lcd.print("Progress:sent!");

      delay(500);

      //lcd.setBacklight(LOW);

      digitalWrite(trigPin1, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin1, LOW);
      long duration2 = pulseIn(echoPin1, HIGH);
      int distance2 = duration2 / 58;

      Serial.print("Calibration: ");
      Serial.print(distance2);
      Serial.println(" cm");

      for (pos = 0; pos <= 180; pos += 1) {
        // in steps of 1 degree
        myservo.write(pos);      
        delay(15);
      }          

      lcd.clear();
      lcd.home();
      lcd.print("Welcome,");
      lcd.setCursor(8, 0);
      lcd.print(users[LoggedUser] + "!");
      lcd.setCursor(0,1);
      lcd.print("Enter Time: 20s");
      delay(100);

      lcd.setBacklight(HIGH);  

      delay(1000);   

      lcd.setCursor(0, 1);

      unsigned long startTime = millis(); // get the start time
      unsigned long elapsedTime = 0; // to keep track of the elapsed time

      while (elapsedTime < 20000) { // run the loop for 20 seconds
        // Measure distance for the first sensor
        

        digitalWrite(trigPin1, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin1, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin1, LOW);
        long duration1 = pulseIn(echoPin1, HIGH);
        int distance1 = duration1 / 58;

        // Print the distances to the serial monitor
        Serial.print("Distance 1: ");
        Serial.print(distance1);
        Serial.print(" cm - V:");
        Serial.println(visitorCount);

        String D1 = String(distance1);

        delay(20);

        if(distance2 - distance1 > 10 && visitorFlag == false){
          visitorCount++;
          visitorFlag = true;
          if(visitorCount > visitorsAuthed[LoggedUser]){
            Serial.println(visitorCount);
            Serial.println(visitorsAuthed[LoggedUser]);
            alarmTone();
            delay(500);
            alarmTone();
            delay(500);

            msgToSend = "Too many people detected!";
            sendSMS(msgToSend);
            sendSMS2(msgToSend);
            callOwner();
            callOwner2();

            resetLCD(); 
            resetLCD(); 
            break;
          }
        }
        else if(distance2 - distance1 < 10 && (distance1 < distance2 + 5)){
          visitorFlag = false;
        }

        if(elapsedTime > 20000){
          Serial.print("TIME UP - ");
          if(timeUpFlag == false){
            lcd.clear();
            lcd.home();
            lcd.print("Welcome,");
            lcd.setCursor(8, 0);
            lcd.print(users[LoggedUser] + "!");
            lcd.setCursor(0,1);
            lcd.print("Time's up!");
            timeUpFlag = true;
          }
          
          if(distance2 - distance1 > 10){
            alarmTone();
            delay(500);
            alarmTone();
            delay(500);
            resetLCD(); 
            resetLCD(); 
            break;
          }
        }
        // Wait for a short time before measuring again
        delay(300);

        elapsedTime = millis() - startTime; // update the elapsed time
      }


    }else if(key != '*'){
      int delayTime = 700;

      wrongPassCount++;
      Serial.print(wrongPassCount);

      lcd.setBacklight(LOW);
      delay(delayTime);
      lcd.print("Access Denied!");
      delay(50);
      lcd.setBacklight(HIGH);
      delay(delayTime);
      lcd.setBacklight(LOW);  
      delay(delayTime);

      lcd.setCursor(0,1);
      lcd.print("Wrong Password!");
      delay(50);
      lcd.setBacklight(HIGH);
      delay(1000);
      lcd.setBacklight(LOW);
      delay(500);
      lcd.setBacklight(HIGH);
      delay(1000);
      lcd.setBacklight(LOW);
      delay(500);
      lcd.setBacklight(HIGH);
      delay(1000);

      if(wrongPassCount == 3){
        alarmTone();
        delay(500);
        alarmTone();
        delay(500);
        alarmTone();
        delay(500);
        alarmTone();
        delay(500);
        alarmTone();

        callOwner();
        callOwner2();
      }else{
        incorrectPassword();
      }

      delay(1000);

      lcd.clear();
      lcd.home();
      lcd.print("Number of tries");
      lcd.setCursor(0, 1);

      int triesLeft = 3 - wrongPassCount;
      lcd.print("left: ");
      lcd.setCursor(6, 1);
      lcd.print(triesLeft);

      delay(4000);

      resetLCD(); 
    }

    i = 0;

    resetLCD(); 

}

int checkPass(String pass){
  for (int i = 0; i < sizeof(passwords)/sizeof(passwords[0]); i++) {
    if (input_password == passwords[i]) {
      Serial.println("Access granted.");
      return i;
    }
  }

  return -1;
}

void correctPassword() {
  tone(buzzerPin, 440); // A4
  delay(200);
  noTone(buzzerPin);
  delay(50);
  
  tone(buzzerPin, 554); // C#5
  delay(200);
  noTone(buzzerPin);
  delay(50);
  
  tone(buzzerPin, 659); // E5
  delay(200);
  noTone(buzzerPin);
}

void incorrectPassword() {
  tone(buzzerPin, 659); // E5
  delay(200);
  noTone(buzzerPin);
  delay(50);
  
  tone(buzzerPin, 554); // C#5
  delay(200);
  noTone(buzzerPin);
  delay(50);
  
  tone(buzzerPin, 440); // A4
  delay(200);
  noTone(buzzerPin);
}

void resetLCD(){
  int delayTime = 200;
  lcd.clear();
  lcd.home();

  lcd.print("Resetting");
  delay(delayTime);
  lcd.clear();

  lcd.print("Resetting.");
  delay(delayTime);
  lcd.clear();

  lcd.print("Resetting..");
  delay(delayTime);
  lcd.clear();

  lcd.print("Resetting...");
  delay(delayTime);
  lcd.clear();

  lcd.print("Resetting....");
  delay(delayTime);
  lcd.clear();

  lcd.print("Resetting.....");
  delay(delayTime);
  lcd.clear();

  lcd.home();
  lcd.print("Enter Password:");
  lcd.setCursor (0,1);
}

void alarmTone(){
  for (int i = 0; i < 12; i++) {
    tone(buzzerPin, 1000); // Generate a 1KHz sound
    delay(200); // Play the tone for 200 milliseconds
    noTone(buzzerPin); // Stop the sound
    delay(200); // Pause for 200 milliseconds
  }
}

void sendSMS(String msg){
      caseVar = 's';
      caseCount = 0;

      lcd.clear();
      lcd.home();
      lcd.print("Notifying Owner:");
      lcd.setCursor(0,1);
      lcd.print("Progress:sending");

      while(true)
      {
          if(caseCount > 1500){
            Serial.println("Breaking");
            break;
          }

          switch(caseVar)
        {
          case 's':
            Serial.println("In case s");
            mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
            delay(1000);  // Delay of 1 second
            mySerial.println("AT+CMGS=\"+919952439130\"\r"); // Replace x with mobile number
            delay(1000);
            mySerial.println(msg);// The SMS text you want to send
            delay(100);
            mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
            delay(1000);
            caseVar = 'p';
            break;
        }
        if (mySerial.available()>0){
          Serial.write(mySerial.read());
        }
        

        delay(5);
        caseCount++;

      }

      lcd.clear();
      lcd.home();
      lcd.print("Notifying Owner:");
      lcd.setCursor(0,1);
      lcd.print("Progress:sent!");

      delay(1000);
}

void sendSMS2(String msg){
      caseVar = 's';
      caseCount = 0;

      lcd.clear();
      lcd.home();
      lcd.print("Notifying Other:");
      lcd.setCursor(0,1);
      lcd.print("Progress:sending");

      while(true)
      {
          if(caseCount > 1500){
            Serial.println("Breaking");
            break;
          }

          switch(caseVar)
        {
          case 's':
            Serial.println("In case s");
            mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
            delay(1000);  // Delay of 1 second
            mySerial.println("AT+CMGS=\"+918433077031\"\r"); // Replace x with mobile number
            delay(1000);
            mySerial.println(msg);// The SMS text you want to send
            delay(100);
            mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
            delay(1000);
            caseVar = 'p';
            break;
        }
        if (mySerial.available()>0){
          Serial.write(mySerial.read());
        }
        

        delay(5);
        caseCount++;

      }

      lcd.clear();
      lcd.home();
      lcd.print("Notifying Other:");
      lcd.setCursor(0,1);
      lcd.print("Progress:sent!");

      delay(1000);
}

void callOwner(){
  callFlag = false;
  caseCount = 0;
  while(true)
      {
        if(caseCount > 1500){
          Serial.println("Breaking");
          break;
        }

        if(callFlag == false)
        {
          Serial.println("Calling through GSM Modem");
          delay(1000);
          mySerial.println("ATD9952439130;"); // ATDxxxxxxxxxx; semicolon should be at the last ;AT command that follows UART protocol;
          Serial.println("Called ATD9952439130");
          delay(1000);
          callFlag = true;

          if (mySerial.available()>0);
            Serial.write(mySerial.read());
        }

        delay(5);
        caseCount++;
      }
}

void callOwner2(){
  callFlag = false;
  caseCount = 0;
  while(true)
      {
        if(caseCount > 1500){
          Serial.println("Breaking");
          break;
        }

        if(callFlag == false)
        {
          Serial.println("Calling through GSM Modem");
          delay(1000);
          mySerial.println("ATD8433077031;"); // ATDxxxxxxxxxx; semicolon should be at the last ;AT command that follows UART protocol;
          Serial.println("Called ATD8433077031");
          delay(1000);
          callFlag = true;

          if (mySerial.available()>0);
            Serial.write(mySerial.read());
        }

        delay(5);
        caseCount++;
      }
}
