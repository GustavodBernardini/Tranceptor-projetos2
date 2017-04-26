#ifndef Tela_h
#define Tela_h

#include "Arduino.h"
class Tela
{
  private:  
    int rw;
    int rs;
    int en;
    int d0;
 
  public:
  Tela(int rs_pin,int rw_pin,int en_pin, int d0_pin)//,int d1_pin,int d2_pin,int d3_pin,int d4_pin,int d5_pin,int d6_pin,int d7_pin)
  {
    rw = rw_pin;
    rs = rs_pin;
    en = en_pin;
    d0 = d0_pin;
    digitalWrite(en,LOW);
    reset();
    displayOnOff(true,true,false);
    //functionSet(true,true,true);    
  }

  void enable()
  {   
    digitalWrite(en,HIGH);
    delay(10);
    digitalWrite(en,LOW);
  }

  void displayOnOff(bool displayOn,bool cursorOn,bool cursorBlink)
  {
    for(int i = d0; i<d0+8;i++)
    {
     digitalWrite(i, LOW);
    }
    digitalWrite(rs,LOW);
    digitalWrite(rw,LOW);
    digitalWrite(d0+3, HIGH);
    digitalWrite(d0+2,displayOn);
    digitalWrite(d0+1,cursorOn);
    digitalWrite(d0,cursorBlink);
    enable();
  }
  
  void reset()
  {
    for(int i = d0; i<d0+8;i++)
    {
     digitalWrite(i, LOW);
    }
    digitalWrite(rs,LOW);
    digitalWrite(rw,LOW);
    digitalWrite(d0,HIGH);
    enable();
   }
  
  void setData(String frase)
  {
    for(int i = 0; i < 16; i++)//letras
    {
      char letter = frase[i];
      byte dispCode = (byte)letter;

      for(int j = d0; j < d0+8; j++)
        {
          digitalWrite(j,dispCode&(1<<(j-d0)));          
        }
      digitalWrite(rs,1);
      digitalWrite(rw,0);  
      enable();
    }
  }

  void returnSpace()
  {
    for(int i = d0; i<d0+8;i++)
    {
     digitalWrite(i, LOW);
    }
    digitalWrite(rs,LOW);
    digitalWrite(rw,LOW);
    digitalWrite(d0+4,HIGH);
    enable();
  }

  void avanceSpace()
  {
    for(int i = d0; i<d0+8;i++)
    {
     digitalWrite(i, LOW);
    }
    digitalWrite(rs,LOW);
    digitalWrite(rw,LOW);
    digitalWrite(d0+4,HIGH);
    digitalWrite(d0+2,HIGH);
    enable();
  }

  void setByte(byte data)
  {    
    for(int j = d0 ; j < d0+8; j++)
    {
      digitalWrite(j,data&(1<<(j-d0)));//pin2 to 9          
    }
    digitalWrite(rw,0);
    digitalWrite(rs,1);  
    enable();
  }

  void backspace()
  {
    returnSpace();
    setByte(32);
    returnSpace();
  }
  
  void functionSet(bool bitBusMode8,bool line2,bool bigFont)
  {
    for(int i = d0; i<d0+8;i++)
    {
     digitalWrite(i, LOW);
    }
    digitalWrite(rs,LOW);
    digitalWrite(rw,LOW);
    digitalWrite(d0+5,HIGH);
    digitalWrite(d0+4,bitBusMode8);
    digitalWrite(d0+3,line2);
    digitalWrite(d0+2,bigFont);
    enable(); 
  }  
};

#endif
