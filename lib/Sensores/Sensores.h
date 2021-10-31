#ifndef SENSORES_H
#define SENSORES_H


#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define cs_pin 4
#define mosi_pin 23
#define miso_pin 19
#define sck_pin 18


#define SEALEVELPRESSURE_HPA (1009.00)



class Sensores
{
    private:
        
        
    public:
        Sensores();
        ~Sensores();
        Adafruit_BME680 bme = Adafruit_BME680(cs_pin);

        void setup();
        String lecturaTemperatura();
        String lecturaHumedad();
        String lecturaPresionAtmosferica();
        String lecturaGas();
        String lecturaAltitud(); 
        
    
}; 




#endif
