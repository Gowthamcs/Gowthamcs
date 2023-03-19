#include <SoftwareSerial.h>

SoftwareSerial BT(2, 3); //TX, RX respetively
String readvoice, currentControlString = "", temp;
float distance;
long duration;
int isForward;

void setup() {
 BT.begin(9600);
 Serial.begin(9600);
 isForward=-1;
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(8, OUTPUT); //TRIG PIN
 pinMode(7, INPUT); //ECHO PIN
}

void forward(){
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
}

void left(){
  digitalWrite (9,LOW);
  digitalWrite (10,HIGH);
  digitalWrite (11,HIGH);
  digitalWrite (12,LOW);
  delay (500);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
}

void right(){
  digitalWrite (9, HIGH);
  digitalWrite (10, LOW);
  digitalWrite (11, LOW);
  digitalWrite (12, HIGH);
  delay (500);
  digitalWrite(9, LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
}

void back(){
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12,HIGH);
}

void stop_bot(){
  digitalWrite (9, LOW);
  digitalWrite (10, LOW);
  digitalWrite (11, LOW);
  digitalWrite (12, LOW);  
}

void updateDistance(){
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  duration = pulseIn(7, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance=");
  Serial.println(distance);
}

String splitString(String controlString){
  String controlWord = "";
  int i=0;
  Serial.print("Control String = ");
  Serial.println(controlString);
  while(controlString.length() > 0 && i<30){
    Serial.print("Control Character = ");
    Serial.println(controlString[i]);
    if(controlString[i]==32){
      Serial.println("Space Found");
      i++;
      while(controlString[i]!=32){
        controlWord+=controlString[i];
        Serial.println(controlString[i]);
        i++;
      }
      if(controlWord.length()>3){
        Serial.print("Control Word");
        Serial.println(controlWord);
        return controlWord;
      }
    }
    i++;
  }
}

void loop() {
  while (BT.available()){  //Check if there is an available byte to read
    delay(20); //Delay added to make thing stable
    readvoice = BT.readString(); //Conduct a serial read
    //readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  Serial.print("Received Command=");
  Serial.println(readvoice);
  
  if(readvoice.length()>=9){
    Serial.println("Split String Called");
    temp = splitString(readvoice);
  }else{
    temp = readvoice;
  }

  Serial.print("Command=");
  Serial.println(temp);
  
  if ((temp.length() > 0)) {
    currentControlString = temp;
    Serial.print("Current Command=");
    Serial.println(currentControlString);
    if(currentControlString == "forward"){
      Serial.println("Forward");
      forward();
      isForward=1;
    }
    else if(currentControlString == "back"){
      Serial.println("Back");
      back();
      isForward=0;
    }
    else if (currentControlString == "left"){
      Serial.println("Left");
      left();
      isForward=-1;
    }
    else if ( currentControlString == "right"){
      Serial.println("Right");
      right();
      isForward=-1;
    }
    else if (currentControlString == "stop"){
      Serial.println("Stop");
      stop_bot();
      isForward=-1;
    }
  }
  Serial.println();
  Serial.println();
  Serial.println();
  readvoice="";
  updateDistance();
  if(distance<=10){
    stop_bot();
    delay(500);
    left();
    delay(1000);
    if(isForward==1){
      forward();
      isForward=1;
    }
    else if(isForward==0){
      back();
      isForward = 0;
    }
  }
} 
