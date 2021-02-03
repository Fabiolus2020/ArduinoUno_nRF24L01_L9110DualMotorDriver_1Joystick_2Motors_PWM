
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

struct package
{
  int joyposX;
  int joyposY;
  int potValue1;
  int potValue2;
  int modeNow;
};

typedef struct package Package;
Package data;



const int A1A = 2;//define pin 2 for A1A
const int A1B = 3;//define pin 3 for A1B

const int B1A = 4;//define pin 8 for B1A
const int B1B = 5;//define pin 9 for B1B

int motorspeed = 0;

void setup() {
  while (!Serial);

  Serial.begin(9600);
  myRadio.begin();
  //set the address
  myRadio.openReadingPipe(0, address);
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  //Set module as receiver
  myRadio.startListening();
  pinMode(B1A, OUTPUT); // define pin as output
  pinMode(B1B, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, LOW);
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( myRadio.available())
  {

    myRadio.read( &data, sizeof(data) );

    // Serial.print("X : ");
    // Serial.println(data.joyposX);
    //Serial.print("Y : ");
    Serial.println(data.joyposY);
     //Serial.print("potValue : ");
    //Serial.println(data.potValue);
    delay(10);

    if (data.joyposX > 510)
    {

      // This is BACWARD
        motorspeed = map(data.joyposX, 1023, 510, 0, 255);
      digitalWrite(A1A, HIGH);
      analogWrite(A1B, motorspeed);
      digitalWrite(B1A, HIGH);
      analogWrite(B1B, motorspeed);
    

    }

    else if (data.joyposX < 480)
    {

      // This is FORWARD
      motorspeed = map(data.joyposX, 480, 0, 0, 255);
      digitalWrite(A1A, LOW);
      analogWrite(A1B, motorspeed);
      digitalWrite(B1A, LOW);
      analogWrite(B1B, motorspeed);
      
    }

    else if (data.joyposY < 480)
    {
      // This is right
      motorspeed = map(data.joyposY, 480, 0, 0, 255);
      digitalWrite(A1A, LOW);
      analogWrite(A1B, motorspeed);
      digitalWrite(B1A, HIGH);
      analogWrite(B1B, 255-motorspeed);
     
    }

    else if (data.joyposY > 520)
    {
    
      // This is right
           motorspeed = map(data.joyposY, 520, 1023, 0, 255);
      digitalWrite(A1A, HIGH);
      analogWrite(A1B, 255-motorspeed);
      digitalWrite(B1A, LOW);
      analogWrite(B1B, motorspeed);
     
    }

    else
    {
      digitalWrite(B1A, LOW);
      digitalWrite(B1B, LOW);
      digitalWrite(A1A, LOW);
      digitalWrite(A1B, LOW);
     
    }
  }
}
