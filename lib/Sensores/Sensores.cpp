
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
    float t = bme.readTemperature();
    if (isnan(t)) {
        Serial.println("Fallo de lectura Temperatura interior!");
        return "--";
    }
    else {
        Serial.print("Temperatura Interior = ");
        Serial.print(t);
        Serial.println(" *C");    
        return String(t);
    }
}

String Sensores::lecturaHumedad() 
{
    float h = bme.readHumidity();
  if (isnan(h)) {
    Serial.println("Fallo de lectura Humedad!");
    return "--";
  }
  else {
    Serial.print("Humedad = ");
    Serial.print(h);
    Serial.println(" %");    
    return String(h);
  }
}

String Sensores::lecturaPresionAtmosferica() 
{
      float p = bme.readPressure() / 100.0;
  if (isnan(p)) {
    Serial.println("Fallo de lectura Presion Atmosferica!");
    return "--";
  }
  else {
    Serial.print("Presion Atmosferica = ");
    Serial.print(p);
    Serial.println(" hPa");    
    return String(p);
  }    
}

String Sensores::lecturaGas() 
{
     float g = bme.readGas() / 1000.0;
  if (isnan(g)) {
    Serial.println("Fallo de lectura Gas!");
    return "--";
  }
  else {
    Serial.print("Gas = ");
    Serial.print(g);
    Serial.println(" KOhms");    
    return String(g);
  }
}

String Sensores::lecturaAltitud() 
{
      float alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  if (isnan(alt)) {
    Serial.println("Fallo de lectura Altitude!");
    return "--";
  }
  else {
    Serial.print("Approx. Altitude = ");
    Serial.print(alt);
    Serial.println(" m");    
    return String(alt);
  }    
}






