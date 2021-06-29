#include <Pantalla.h>


Pantalla::Pantalla(/* args */)
{   
}

Pantalla::~Pantalla()
{
}

void Pantalla::setup() 
{
     //Iniciamos la pantalla TFT
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    
}

void Pantalla::draw(String datosRecibidos) 
{
    _datosRecibidos = datosRecibidos;

    _pos_temperatura =   _datosRecibidos.indexOf("temperatura");
    _pos_humedad =       _datosRecibidos.indexOf("humedad");
    _pos_suelo =         _datosRecibidos.indexOf("suelo");
    _pos_presion =       _datosRecibidos.indexOf("presion");
    _pos_gas =           _datosRecibidos.indexOf("gas");
    _pos_altitud =       _datosRecibidos.indexOf("altitud");
    _pos_bateria =       _datosRecibidos.indexOf("bateria");

    

    _temperatura =       _datosRecibidos.substring(_pos_temperatura+11, _pos_humedad);
    _humedadAmbiente =   _datosRecibidos.substring(_pos_humedad+7, _pos_suelo);         
    _humedadSuelo =      _datosRecibidos.substring(_pos_suelo+5, _pos_presion);
    _presionAtmosf =     _datosRecibidos.substring(_pos_presion+7, _pos_gas);
    _gas =               _datosRecibidos.substring(_pos_gas+3, _pos_altitud);
    _altitud =           _datosRecibidos.substring(_pos_altitud+7, _pos_bateria);
    _nivelBateria =      _datosRecibidos.substring(_pos_bateria+7, _datosRecibidos.length());
    
    tft.setTextSize(2);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("Temp ", 30, 10, 1);
    tft.drawString("h.amb ", 30, 40,  1);
    tft.drawString("h.sue ", 30, 70,  1);
    tft.drawString("P.Atm ", 30, 100,  1);
    tft.drawString("Gas ", 30, 130,  1);
    tft.drawString("Alt ", 30, 160, 1);
    tft.drawString("Batt ", 30, 190,  1);

    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(_temperatura,      120, 10, 4);
    tft.drawString(_humedadAmbiente,  130, 40, 4);
    tft.drawString(_humedadSuelo,     120, 70, 4); 
    tft.drawString(_presionAtmosf,    120, 100, 4); 
    tft.drawString(_gas,              120, 130, 4); 
    tft.drawString(_altitud,          120, 160, 4); 
    tft.drawString(_nivelBateria,     120, 190, 4); 
}