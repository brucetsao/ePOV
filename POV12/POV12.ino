
#define SensorInput  5   
#define SensorEnable  6   

unsigned char pos = 0; 
unsigned char i = 0;


void setup() {
  Serial.begin(9600);

  pinMode(SensorInput, INPUT);
  pinMode(SensorEnable, OUTPUT);
  digitalWrite(SensorEnable,HIGH) ;
}

void loop() {
  if (digitalRead(SensorInput) )
  {
      Serial.println("Sensor High") ;
  }
  else
  {
      Serial.println("Sensor Low") ;
  }
  delayMicroseconds(3000);
}



