
#define SensorInput  5   
#define SensorEnable  6   



const int ledcount = 7;
int ledPin[] = { 
  22, 24, 26, 28, 30, 32, 34, 36, 38, 40 , 42, 44, 46,48,50,52 };


byte bitmap[] = {
  0b00000000,
  0b01000001,
  0b01111111,
  0b01000001,
  0b00000000,
  0b00000000,
  0b00001110,
  0b00011111,
  0b00111111,
  0b01111110,
  0b00111111,
  0b00011111,
  0b00001110,
  0b00000000,
  0b00000000,
  0b00111111,
  0b01000000,
  0b01000000,
  0b00111111,
  0b10000000   
};


unsigned char pos = 0; 
unsigned char i = 0;


void setup() {
  Serial.begin(9600);

  for(int pin = 1; pin < ledcount + 7; pin++) {
    pinMode(ledPin[pin], OUTPUT);
  }

  pinMode(SensorInput, INPUT);
  pinMode(SensorEnable, OUTPUT);
  digitalWrite(SensorEnable,HIGH) ;
}

void loop() {
  if (!digitalRead(SensorInput)  )
  {
    while(bitmap[++pos] != 0b10000000) { 
      for(i = 0; i < 7; i++) 
      {  
        digitalWrite(ledPin[2*i], (bitmap[pos] >> i) & 0b00000001);
        digitalWrite(ledPin[2*i+1], (bitmap[pos] >> i) & 0b00000001);
      }
      delay(5); 
    }

    for(i = 0; i < ledcount; i++) {  
      digitalWrite(ledPin[i*2], LOW);
      digitalWrite(ledPin[i*2+1], LOW);
    }

  }
}



