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

void Pantalla::draw(Antena* p_antena) 
{   
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(1);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("Temp ",  30, 10,  2);
    tft.drawString("h.amb ", 30, 40,  2);
    tft.drawString("h.sue ", 30, 70,  2);
    tft.drawString("P.Atm ", 30, 100, 2);
    tft.drawString("Gas ",   30, 130, 2);
    tft.drawString("Alt ",   30, 160, 2);
    tft.drawString("Batt ",  30, 190, 2);

    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(p_antena->temperatura,      120, 10, 4);
    tft.drawString(p_antena->humedadAmbiente,  120, 40, 4);
    tft.drawString(p_antena->humedadSuelo,     120, 70, 4); 
    tft.drawString(p_antena->presionAtmosf,    120, 100, 4); 
    tft.drawString(p_antena->gas,              120, 130, 4); 
    tft.drawString(p_antena->altitud,          120, 160, 4); 
    tft.drawString(p_antena->nivelBateria,     120, 190, 4);   

}