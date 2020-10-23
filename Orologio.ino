#include <Wire.h>
#include "RTClib.h"

// SCL = A5
//SDA = A4


/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */
 
// Pin 2-8 is connected to the 7 segments of the display.

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

bool date = false;
int show_btn = A0;
int date_btn = A1;
bool date_btn_clicked = false;
bool show_btn_clicked = false;


RTC_DS3231 rtc;

char *res = malloc(5);



// the setup routine runs once when you press reset:
void setup() { 
  Serial.begin(9600);               
  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  


  if (!rtc.begin()) {
    Serial.println("Controlla le connessioni");
    while(true);
  }

  if (rtc.lostPower()) {
    Serial.println("Imposto data/ora");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void display(int pos, int num){
  
  switch (pos){
    case 0:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      break;
    case 1:
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      break;
    case 2:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      break;
    case 3:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH);
      break;
    case 4:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      break;
    default:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      break;
      
  }
  
  switch (num) {
    case 0:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, LOW);
      break;
    case 1:
      digitalWrite(pinA, LOW);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, LOW);
      break;
    case 2:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, LOW);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, HIGH);
      break;
    case 3:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, HIGH);
      break;
    case 4:
      digitalWrite(pinA, LOW);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);
      break;
    case 5:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, LOW);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);
      break;
    case 6:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, LOW);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);
      break;
    case 7:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, LOW);
      break;
    case 8:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, HIGH);   
      digitalWrite(pinE, HIGH);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);
      break;
    case 9:
      digitalWrite(pinA, HIGH);   
      digitalWrite(pinB, HIGH);   
      digitalWrite(pinC, HIGH);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, HIGH);   
      digitalWrite(pinG, HIGH);
      break;
    default:
      digitalWrite(pinA, LOW);   
      digitalWrite(pinB, LOW);   
      digitalWrite(pinC, LOW);   
      digitalWrite(pinD, LOW);   
      digitalWrite(pinE, LOW);   
      digitalWrite(pinF, LOW);   
      digitalWrite(pinG, LOW);
      break;
  }
};

int first_digit(int num) {
  int first_digit = floor(num/10);
  
  return first_digit;
};

int second_digit(int num, int first_digit) {
  int second_digit = num - (first_digit*10);
  
  return second_digit;
};

// the loop routine runs over and over again forever:
void loop() {
  
  
  DateTime now = rtc.now();

  int month = now.month();
  int day = now.day();
  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

  
  int first_digit_hour = first_digit(hour);
  int second_digit_hour = second_digit(hour, first_digit_hour);

  int first_digit_minute = first_digit(minute);
  int second_digit_minute = second_digit(minute, first_digit_minute);

  int first_digit_second = first_digit(second);
  int second_digit_second = second_digit(second, first_digit_second);

  int first_digit_month = first_digit(month);
  int second_digit_month = second_digit(month, first_digit_month);

  int first_digit_day = first_digit(day);
  int second_digit_day = second_digit(day, first_digit_day);
  
  

  if (digitalRead(show_btn) == HIGH){
    //Serial.println("Schiaccio");
    if (date == false) {
      display(1, first_digit_hour);
      delay(5);
      display(2, second_digit_hour);
      delay(5);
      display(3, first_digit_minute);
      delay(5);
      display(4, second_digit_minute);
      
    }else{
      display(1, first_digit_day);
      delay(5);
      display(2, second_digit_day);
      delay(5);
      display(3, first_digit_month);
      delay(5);
      display(4, second_digit_month);
      delay(5);
    }
  }else{
    //Serial.println("Rilascio");
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
    delay(100);
  }

  if (digitalRead(date_btn) == HIGH){
    if (date_btn_clicked == false){
      date = !date;
      Serial.println(date);
      date_btn_clicked = true;
    }
  }else{
    date_btn_clicked = false;
  }

  
  

}
