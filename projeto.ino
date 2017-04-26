
#include <VirtualWire.h>
#include "Tela.h"
#include "Teclado.h"
#include "Antena.h"

void setup()
{
  //serial start
  Serial.begin(9600);

  //pin to Display
  pinMode(2, OUTPUT);//b0
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);//b7
  pinMode(10, OUTPUT);//rw
  pinMode(11, OUTPUT);//rs
  pinMode(12, OUTPUT);//en

  pinMode(13, OUTPUT); //led >>Free<<

  //display analog pins
  pinMode(A0, OUTPUT); //pin14
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);//manual pull up
  pinMode(A7, INPUT_PULLUP);//manual pull up pin21


  Serial.println(43);
  Tela tela;
  Teclado keyboard;
  Antena antena(0, 1);
  byte tecla;
  uint8_t msg_rec[MSG_LEN] = {0};
  char msg[MSG_LEN] = {0};
  int i = 0;

  tela.setData("aaaabbbbccccdddd");
  delay(1000);
  tela.setData("gusti 123;.SA !?");
  tela.reset();

  for (;;)
  {
    tecla = keyboard.check();

    if (tecla == 12)
    {
      if (i > 0)
      {
        tela.backspace();
        msg[i] = 0;
        i--;
      }
      delay(100);
    }
    else if (tecla == 16)
    {
      //TODO data send
      //if( antena.sendData(msg)) // comunica, fica mandando até receber eco, reseta msg, FAZER TIMEOUT
      //  i=0;
    }
    else if (tecla > 0)
    {
      tela.setByte(tecla + 96);
      msg[i] = (tecla);
      i++;
      delay(100);
    }
    if (antena.dataReceive(msg_rec))
    {
      tela.reset();
      tela.setData((char*)msg_rec);
    }
  }

}


void loop()
{

}
