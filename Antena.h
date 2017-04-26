

#include "Arduino.h"

#ifndef Antena_h
#define Antena_h
#define MSG_LEN 16
#define BITS_PER_SEC 2000

class Antena
{
private:
  int rx;
  int tx;

public:
  Antena(int rx_pin, int tx_pin)
  {
    rx = rx_pin;
    tx = tx_pin;
    
    vw_set_rx_pin(rx_pin);
    vw_set_tx_pin(tx_pin);
    vw_setup(BITS_PER_SEC);

    vw_rx_start();
  }

  bool dataReceive(uint8_t* buf)
  {
    
    uint8_t buflen = MSG_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      vw_send(buf,MSG_LEN);
      vw_wait_tx();
      return true;
    }
    return false;
  }

  void dataSend(String msg)
  {
    char msg_array[MSG_LEN];
    msg.toCharArray(msg_array,MSG_LEN);
    vw_send((uint8_t*)msg_array,MSG_LEN);
    vw_wait_tx();
  }



};

#endif
