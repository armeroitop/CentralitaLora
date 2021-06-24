
#include <Arduino.h>
#include <Antena.h>
#include <Pantalla.h>

Antena antena;
Pantalla pantalla;



String LoRaData, LoRaDataAntigua;

void setup() {
  antena.setup();
  pantalla.setup();

}

void loop() 
{       
    // Datum is middle centre
   // tft.setTextDatum(TL_DATUM);
   pantalla.draw(antena.recibeDatos());
   ;
      
}