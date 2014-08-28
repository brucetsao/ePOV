#include <EEPROM.h>

int keycontroladdress = 10;
int keystartaddress = 20;
int ledsize = 14 ;
byte bitmap[] = {
  0b00000000,0b00000000,
  0b00110000,0b00000011,
  0b00111111,0b11111111,
  0b00110000,0b00000011,
  0b00000000,0b00000000,
  0b00000000,0b00000000,
  0b00000000,0b11111100,
  0b00000011,0b11111111,
  0b00001111,0b11111111,
  0b00111111,0b11111100,
  0b00001111,0b11111111,
  0b00000011,0b11111111,
  0b00000000,0b11111100,
  0b00000000,0b00000000
};
byte bitmapa[14*2]  ;
int debugmode = 0; 


void setup() {
  int i ;
  Serial.begin(9600);
  Serial.println("Now Write key data") ;
  // 在 keycontroladdress = 20 上寫入數值100
  EEPROM.write(keycontroladdress, 100);  //mean activate key store function
  EEPROM.write(keycontroladdress+2, 14);  //mean activate key store function
  writeleddata(keystartaddress, &bitmap[0],ledsize );
  readleddata(keystartaddress, &bitmapa[0],ledsize );
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

void loop()
{
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


String strzero(long num, int len, int base)
{
  String retstring = String("");
  int ln = 1 ;
  int i = 0 ; 
  char tmp[10] ;
  long tmpnum = num ;
  int tmpchr = 0 ;
  char hexcode[]={
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'  } 
  ;
  while (ln <= len)
  {
    tmpchr = (int)(tmpnum % base) ;
    tmp[ln-1] = hexcode[tmpchr] ;
    ln++ ;
    tmpnum = (long)(tmpnum/base) ;
  }
  for (i = len-1; i >= 0 ; i --)
  {
    retstring.concat(tmp[i]);
  }

  return retstring;
}

unsigned long unstrzero(String hexstr, int base)
{
  String chkstring  ;
  int len = hexstr.length() ;
  if (debugmode == 1)
  {
    Serial.print("String ");
    Serial.println(hexstr);
    Serial.print("len:");
    Serial.println(len);
  }
  unsigned int i = 0 ;
  unsigned int tmp = 0 ;
  unsigned int tmp1 = 0 ;
  unsigned long tmpnum = 0 ;
  String hexcode = String("0123456789ABCDEF") ;
  for (i = 0 ; i < (len ) ; i++)
  {
    //     chkstring= hexstr.substring(i,i) ; 
    hexstr.toUpperCase() ;
    tmp = hexstr.charAt(i) ;   // give i th char and return this char
    tmp1 = hexcode.indexOf(tmp) ;
    tmpnum = tmpnum + tmp1* POW(base,(len -i -1) )  ;

    if (debugmode == 1)
    {
      Serial.print("char:( ");
      Serial.print(i);
      Serial.print(")/(");
      Serial.print(hexstr);
      Serial.print(")/(");
      Serial.print(tmpnum);
      Serial.print(")/(");
      Serial.print((long)pow(16,(len -i -1)));
      Serial.print(")/(");
      Serial.print(pow(16,(len -i -1) ));
      Serial.print(")/(");
      Serial.print((char)tmp);
      Serial.print(")/(");
      Serial.print(tmp1);
      Serial.print(")");
      Serial.println("");
    }
  }
  return tmpnum;
}

long POW(long num, int expo)
{
  long tmp =1 ;
  if (expo > 0)
  { 
    for(int i = 0 ; i< expo ; i++)
      tmp = tmp * num ;
    return tmp ; 
  } 
  else
  {
    return tmp ; 
  }
}

String getcardnumber(byte c1, byte c2, byte c3, byte c4)
{
  String retstring = String("");
  retstring.concat(strzero(c1,2,16));
  retstring.concat(strzero(c2,2,16));
  retstring.concat(strzero(c3,2,16));
  retstring.concat(strzero(c4,2,16));
  return retstring;
}


