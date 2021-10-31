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

void Pantalla::drawSensorExterno(Antena* p_antena) 
{   
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(1);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("Exterior ",  80, 10,  2);
    tft.drawString("Interior ",  190, 10, 2);
    tft.drawString("Temp ",  10, 40,  2);
    tft.drawString("h.amb ", 10, 70,  2);
    //tft.drawString("h.sue ", 10, 70,  2);
    tft.drawString("P.Atm ", 10, 100, 2);
    tft.drawString("Gas ",   10, 130, 2);
    tft.drawString("Alt ",   10, 160, 2);
    //tft.drawString("Batt ",  10, 190, 2);

    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(p_antena->temperatura,      80, 40, 4);
    //tft.drawString(p_antena->humedadAmbiente,  90, 40, 4);
    //tft.drawString(p_antena->humedadSuelo,     90, 70, 4); 
    tft.drawString(p_antena->presionAtmosf,    80, 100, 4); 
    //tft.drawString(p_antena->gas,              90, 130, 4); 
    tft.drawString(p_antena->altitud,          80, 160, 4); 
    //tft.drawString(p_antena->nivelBateria,     80, 190, 4); 

    tft.drawRect(298 ,3, 20, 9, TFT_DARKGREEN);  
    IconoBateria(p_antena->nivelBateria);

}

void Pantalla::drawSensorInterno(Sensores *p_sensorBME680) 
{
    tft.drawString(p_sensorBME680->lecturaTemperatura(),           190, 40, 4);
    tft.drawString(p_sensorBME680->lecturaHumedad(),               190, 70, 4); 
    tft.drawString(p_sensorBME680->lecturaPresionAtmosferica(),    190, 100, 4); 
    tft.drawString(p_sensorBME680->lecturaGas(),                   190, 130, 4); 
    tft.drawString(p_sensorBME680->lecturaAltitud(),               190, 160, 4); 
}

void Pantalla::IconoBateria(String nivel){
    int nivelBateria = nivel.toInt();
    nivelBateria = map(nivelBateria, 2600, 4096, 0, 100);
    int longitudRectangulo = map(nivelBateria,0,100,0,18);
    tft.fillRect(299 ,4, longitudRectangulo, 7, TFT_GREEN);
    Serial.print("NivelBateria a Int: ");
    Serial.println(nivelBateria);
    tft.drawString(String(nivelBateria) + "%", 270, 0, 2);
}