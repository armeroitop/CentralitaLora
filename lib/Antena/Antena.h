#ifndef __ANTENA_H__
#define __ANTENA_H__

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 26
#define dio0 2



class Antena
{
private:
    
    String _datosRecibidos, _datosRecibidosAntiguos; 
    int _pos_temperatura, 
        _pos_humedad, 
        _pos_suelo, 
        _pos_presion,
        _pos_gas,   
        _pos_altitud,
        _pos_bateria;
public:
    Antena(/* args */);
    ~Antena();
    void setup();
    bool recibeDatos();

    String datosRecibidosAntiguos; 
    String temperatura, humedadAmbiente, humedadSuelo, presionAtmosf, gas, altitud, nivelBateria;
};


#endif // __ANTENA_H__