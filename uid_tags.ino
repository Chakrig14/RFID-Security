/*PinWiring to Arduino Uno

SDA------------------------Digital 10

SCK------------------------Digital 13

MOSI----------------------Digital 11

MISO----------------------Digital 12

IRQ------------------------unconnected

GND-----------------------GND

RST------------------------Digital 9

3.3V------------------------3.3V (DO NOT CONNECT TO 5V) */
 
#include <SPI.h>
#include<Servo.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myservo;
int buzz=7;
int i; 
int pos = 0;
void setup() 
{
  myservo.attach(9);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(buzz,OUTPUT);
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}
void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "95 9E 46 BE" ) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("WELCOME Vignan");
    if(i==1)
    {
      digitalWrite(buzz,LOW);
      Serial.println("OFF");
      i=0;
     }
     else if(i==0)
     {
    digitalWrite(buzz,HIGH);
    Serial.println("On");
    i=1;
     }
     
    Serial.println();
    delay(3000);
  }
 else if(content.substring(1) == "06 F4 17 9E")
 {
  Serial.println("WELCOME MANI");
    if(i==1)
    {
      digitalWrite(buzz,LOW);
      Serial.println("OFF");
      i=0;
     }
     else if(i==0)
     {
    digitalWrite(buzz,HIGH);
    Serial.println("On");
    i=1;
     }
     
    Serial.println();
    delay(3000);
  
 }
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
} 

void sweep()
{
 for (pos = 0; pos <= 180; pos += 1)
 { 
    myservo.write(pos);             
    delay(15);                      
  }
  delay(5000);
  for (pos = 180; pos >= 0; pos -= 1) 
  { 
    myservo.write(pos);             
    delay(15);                      
  } 
}
