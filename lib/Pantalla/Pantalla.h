#ifndef __PANTALLA_H__
#define __PANTALLA_H__

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <Antena.h>



#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define MC_DATUM 4

class Pantalla
{
    private:
        String _datosRecibidos;
        String _temperatura, _humedadAmbiente, _humedadSuelo, _presionAtmosf, _gas, _altitud, _nivelBateria;
        int _pos_temperatura, 
            _pos_humedad, 
            _pos_suelo, 
            _pos_presion,
            _pos_gas,   
            _pos_altitud,
            _pos_bateria;
   
    public:
        TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
        Pantalla(/* args */);
        ~Pantalla();
        void setup();
        void draw(Antena* p_antena);
};



#endif // __PANTALLA_H__