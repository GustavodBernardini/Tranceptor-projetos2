#ifndef Teclado_h
#define Teclado_h

#include "Arduino.h"
class Teclado
{
  private:
  int keyMaping[4][4];
  public:
  Teclado()
  {
    for(int i = 3; i >= 0 ; i--)
    {
      for(int j = 3;j >= 0 ;j--)
      {
        keyMaping[i][j] = (1 + 4*(3-j)) +(3- i);
      }
    }
         
  }
  byte check()
  {  
    bool encontrado = false;
    int lastColuna = 0;
    int lastLinha = 0;
    digitalWrite(14,1);
    digitalWrite(15,1);
    digitalWrite(16,1);
    digitalWrite(17,1);  
    for(int linha = 14; linha < 18; linha++)
    {
      digitalWrite(linha,0);      
      for(int coluna = 18; coluna < 22; coluna++)
      {
        int a = analogRead(coluna);
        Serial.println("linha "+String(linha)+"  coluna "+String(coluna)+"  a "+String(a));       
        if(a < 500)
        {
          lastColuna = coluna-18;
          lastLinha = linha-14;
          encontrado = true;
          break;
        }         
      }
      digitalWrite(linha,1);  
      if(encontrado)
      {
        break;
      }
    } 
    if(encontrado)
    {
      Serial.println(String(lastLinha) +"  "+ String(lastColuna) +"  "+ String(keyMaping[lastLinha][lastColuna]));
      
      
      return keyMaping[lastLinha][lastColuna];
    }
    return 0;
  }     
};
#endif
