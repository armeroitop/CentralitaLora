
#include <Sensores.h>

Sensores::Sensores()
{
    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms   
}

Sensores::~Sensores()
{
}

void Sensores::setup() 
{
    if (!bme.begin()) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
    }else{
        Serial.println("BME680 sensor, funcionando!");
    }

}

String Sensores::lecturaTemperatura() 
{
    _t = bme.readTemperature();
    if (isnan(_t)) {
        Serial.println("Fallo de lectura Temperatura interior!");
        return "--";
    }
    else {
        Serial.print("Temperatura Interior = ");
        Serial.print(_t);
        Serial.println(" *C");    
        return String(_t);
    }
}

String Sensores::lecturaHumedad() 
{
    _h = bme.readHumidity();
    if (isnan(_h)) {
        Serial.println("Fallo de lectura Humedad!");
        return "--";
    }
    else {
        Serial.print("Humedad = ");
        Serial.print(_h);
        Serial.println(" %");    
        return String(_h);
    }
}

String Sensores::lecturaPresionAtmosferica() 
{
    _p = bme.readPressure() / 100.0;
    if (isnan(_p)) {
        Serial.println("Fallo de lectura Presion Atmosferica!");
        return "--";
    }
    else {
        Serial.print("Presion Atmosferica = ");
        Serial.print(_p);
        Serial.println(" hPa");    
        return String(_p);
    }    
}

String Sensores::lecturaGas() 
{
    _g = bme.readGas() / 1000.0;
    if (isnan(_g)) {
        Serial.println("Fallo de lectura Gas!");
        return "--";
    }
    else {
        Serial.print("Gas = ");
        Serial.print(_g);
        Serial.println(" KOhms");    
        return String(_g);
    }
}

String Sensores::lecturaAltitud() 
{
    _alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
    if (isnan(_alt)) {
        Serial.println("Fallo de lectura Altitude!");
        return "--";
    }
    else {
        Serial.print("Approx. Altitude = ");
        Serial.print(_alt);
        Serial.println(" m");    
        return String(_alt);
    }    
}






