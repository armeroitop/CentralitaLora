
#include <Arduino.h>
#include <Antena.h>
#include <Pantalla.h>
#include <Sensores.h>


Antena   *p_antena = new Antena();
Pantalla *p_pantalla = new Pantalla();
Sensores *p_sensorBME680 = new Sensores();

/* #define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 4 */



//Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme2(4);

void setup() {
    p_antena->setup();
    p_pantalla->setup();

    p_pantalla->drawSensorExterno(p_antena);
    
    p_sensorBME680->setup(); 
    p_pantalla->drawSensorInterno(p_sensorBME680);
    /* if (!bme2.begin()) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
    }else{
        Serial.println("Cojonudo!");
    } */
}

void loop() 
{  
   if(p_antena->recibeDatos()){
        Serial.println("Puedes dibujar los datos porfa ");
        p_pantalla->drawSensorExterno(p_antena);
        p_pantalla->drawSensorInterno(p_sensorBME680);
        
        //p_sensorBME680->lecturaTemperatura();      
   }    
   p_pantalla->drawSemaforo(p_antena); 
}