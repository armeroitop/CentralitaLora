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
    tft.drawString("P.Atm ", 10, 100, 2);
    tft.drawString("Gas ",   10, 130, 2);
    tft.drawString("Alt ",   10, 160, 2);
   

    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(p_antena->temperatura,      80, 40, 4);
    //tft.drawString(p_antena->humedadAmbiente,  90, 40, 4);
    //tft.drawString(p_antena->humedadSuelo,     90, 70, 4); 
    tft.drawString(p_antena->presionAtmosf,    80, 100, 4); 
    //tft.drawString(p_antena->gas,              90, 130, 4); 
    tft.drawString(p_antena->altitud,          80, 160, 4); 
    //tft.drawString(p_antena->nivelBateria,     80, 190, 4); 

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

void Pantalla::drawSemaforo(Antena* p_antena)
{
    if (millis()-p_antena->tiempoDatosRecividos >= 90000 && p_antena->semaforoAmarillo){
        p_antena->semaforoVerde = false;
        p_antena->semaforoAmarillo = false;
        p_antena->semaforoRojo = true;      
        tft.fillCircle(300,230,5,TFT_YELLOW);
        Serial.println("semaforo amarillo encendido");

    }else if(millis()-p_antena->tiempoDatosRecividos >= 115000 && p_antena->semaforoRojo)    {
        p_antena->semaforoVerde = false;
        p_antena->semaforoAmarillo = false;
        p_antena->semaforoRojo = false;
        tft.fillCircle(300,230,5,TFT_RED);
        Serial.println("semaforo rojo encendido");

    }else if (p_antena->semaforoVerde)    {
        p_antena->semaforoVerde = false;
        p_antena->semaforoAmarillo = true;
        p_antena->semaforoRojo = false;
        tft.fillCircle(300,230,5,TFT_GREEN);
        Serial.println("semaforo verde encendido");
    }
    //Serial.println(millis());
    
}

void Pantalla::IconoBateria(String nivel){
    _nivelBateriaDato = nivel.toInt();
    _nivelBateriaDato = map(_nivelBateriaDato, 2600, 4096, 0, 100);
    _longitudRectangulo = map(_nivelBateriaDato,0,100,0,18);
    
    tft.setTextDatum(2);
    tft.drawString(String(_nivelBateriaDato) + "%", 296, 0, 2);
    tft.setTextDatum(0);

    tft.fillRect(299 ,4, _longitudRectangulo, 7, TFT_GREEN);
    tft.drawRect(298 ,3, 20, 9, TFT_DARKGREEN);  

    Serial.print("NivelBateria a Int: ");
    Serial.println(_nivelBateriaDato);

}