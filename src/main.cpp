
#include <Arduino.h>
#include <Antena.h>
#include <Pantalla.h>

Antena   *p_antena = new Antena();
Pantalla *p_pantalla = new Pantalla();



String LoRaData, LoRaDataAntigua;

void setup() {
    p_antena->setup();
    p_pantalla->setup();

    p_pantalla->draw(p_antena);
}

void loop() 
{  
   if(p_antena->recibeDatos()){
        Serial.println("Puedes dibujar los datos porfa ");
        p_pantalla->draw(p_antena);
   }     
}