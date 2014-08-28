
#include <EEPROM.h>

#define SensorInput  5   
#define SensorEnable  6   

unsigned char pos = 0; 
unsigned char i = 0;


const int ledcount = 16;
int ledPin[] = { 
  22, 24, 26, 28, 30, 32, 34, 36, 38, 40 , 42, 44, 46,48,50,52 };
int datacontroladdress = 10;      // 
int datastartaddress = 20;
int ledsize = 20 ;
int displaystyle = 1 ;
int debugmode = 0 ;
byte bitmapa[100] ;
byte bitmap[] = {
  0b01011100,0b01111100,
  0b01000001,0b01000001,
  0b01111111,0b01111111,
  0b01000001,0b01000001,
  0b00000000,0b00000000,
  0b00000000,0b00000000,
  0b00001110,0b00001110,
  0b00011111,0b00011111,
  0b00111111,0b00111111,
  0b01111110,0b01111110,
  0b00111111,0b00111111,
  0b00011111,0b00011111,
  0b00001110,0b00001110,
  0b00000000,0b00000000,
  0b00000000,0b00000000,
  0b00111111,0b00111111,
  0b01000000,0b01000000,
  0b01000000,0b01000000,
  0b00111111,0b00111111,
  0b10000000,0b10000000   
};


void setup() {
  Serial.begin(9600);
  Serial.println("Program Start here ");
  Serial.begin(9600);
  pinMode(SensorInput, INPUT);
  pinMode(SensorEnable, OUTPUT);
  digitalWrite(SensorEnable,HIGH) ;

  for(int pin = 0; pin < ledcount ; pin++) {
    pinMode(ledPin[pin], OUTPUT);
    digitalWrite(ledPin[pin],LOW);
  }

  //digitalWrite(SWPIN, HIGH);  
  if (EEPROM.read(datacontroladdress) == 100 )
  {
    ledsize = EEPROM.read(datacontroladdress+2);
    readleddata(datastartaddress, &bitmapa[0],ledsize );
    displaystyle = 2 ;
    if (debugmode == 1)
    {
      Serial.println("memory type is 2");
      for(i = 0 ; i < ledsize; i++)
      {     
        Serial.print("The Row :(")  ;
        Serial.print(i)  ;
        Serial.print(") is (")  ;
        Serial.print(bitmapa[i*2],HEX);
        Serial.print("/")  ;
        Serial.print(bitmapa[i*2+1],HEX);
        Serial.print(") \n");

      }
    }
  }
}

void loop() {

  if (!digitalRead(SensorInput)  )
    Serial.print("Turn Right  \n ") ;
  int p, i ;

  for(p = 0 ; p <  ledsize ; p++)
  { 
    for(i = 0; i < 8; i++) 
    {  
      if (displaystyle == 1)
      {
        digitalWrite(ledPin[i], (bitmap[p*2] >> i) & 0b00000001);
        digitalWrite(ledPin[i+8], (bitmap[p*2+1] >> i) & 0b00000001);
        if (debugmode == 1)
        {
          digitalWrite(ledPin[i], HIGH);
          digitalWrite(ledPin[i+8], HIGH);
          Serial.print("test here (");
          Serial.print(i);
          Serial.print("/");
          Serial.print(ledPin[i]);
          Serial.print("/");
          Serial.print(ledPin[i+8]);
          Serial.print("\n");
        }
      }
      else
      {
        digitalWrite(ledPin[i], (bitmapa[p*2] >> i) & 0b00000001);
        digitalWrite(ledPin[i+8], (bitmapa[p*2+1] >> i) & 0b00000001);
      }

    }
    delay(5); 
  }

  for(i = 0; i < ledcount; i++) {  
    digitalWrite(ledPin[i], LOW);
  }
}

void writeleddata(int keyarea, byte *leddata, int ledlength)
{
  int i = 0 ;
  for (i = 0 ; i < ledlength ; i++)  
  {
    EEPROM.write((keyarea + i * 2 ),*(leddata + i * 2 ));
    EEPROM.write((keyarea + i * 2 +1),*(leddata + i * 2 +1 ));
  }
}

void readleddata(int keyarea, byte *leddata, int ledlength)
{
  int i = 0 ;
  for (i = 0 ; i < ledlength ; i++)  
  {
    *(leddata + i * 2 ) =  EEPROM.read(keyarea + i * 2 );
    *(leddata + i * 2 +1 ) =  EEPROM.read(keyarea + i * 2 +1);
  }
}



