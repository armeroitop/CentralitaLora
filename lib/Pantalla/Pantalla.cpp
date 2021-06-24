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
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString("Temp ", 30, 10, 4);
    tft.drawString("h.amb ", 30, 40, 4);
    tft.drawString("h.sue ", 30, 70, 4);
    tft.drawString("P.Atm ", 30, 100, 4);
    tft.drawString("Gas ", 30, 130, 4);
    tft.drawString("Alt ", 30, 160, 4);
    tft.drawString("Batt ", 30, 190, 4);
    
}

void Pantalla::draw(String datosRecibidos) 
{
    _datosRecibidos = datosRecibidos;

    int pos_temperatura =   _datosRecibidos.indexOf("temperatura");
    int pos_humedad =       _datosRecibidos.indexOf("humedad");
    int pos_suelo =         _datosRecibidos.indexOf("suelo");
    int pos_presion =       _datosRecibidos.indexOf("presion");
    int pos_gas =           _datosRecibidos.indexOf("gas");
    int pos_altitud =       _datosRecibidos.indexOf("altitud");
    int pos_bateria =       _datosRecibidos.indexOf("bateria");

    
    

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);

    _temperatura =       _datosRecibidos.substring(pos_temperatura+11, pos_humedad);
    _humedadAmbiente =   _datosRecibidos.substring(pos_humedad+7, pos_suelo);         
    _humedadSuelo =      _datosRecibidos.substring(pos_suelo+5, pos_presion);
    _presionAtmosf =     _datosRecibidos.substring(pos_presion+7, pos_gas);
    _gas =               _datosRecibidos.substring(pos_gas+3, pos_altitud);
    _altitud =           _datosRecibidos.substring(pos_altitud+7, pos_bateria);
    _nivelBateria =      _datosRecibidos.substring(pos_bateria+7, _datosRecibidos.length());

    

    tft.drawString(_temperatura,      120, 10, 4);
    tft.drawString(_humedadAmbiente,  130, 40, 4);
    tft.drawString(_humedadSuelo,     120, 70, 4); 
    tft.drawString(_presionAtmosf,    120, 100, 4); 
    tft.drawString(_gas,              120, 130, 4); 
    tft.drawString(_altitud,          120, 160, 4); 
    tft.drawString(_nivelBateria,     120, 190, 4); 
}