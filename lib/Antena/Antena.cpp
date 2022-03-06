#include <Antena.h>

Antena::Antena(/* args */)
{     
    temperatura     = "--";
    humedadSuelo    = "--";
    humedadAmbiente = "--";
    presionAtmosf   = "--";
    gas             = "--";
    altitud         = "--";
    nivelBateria    = "--";
}

Antena::~Antena()
{
}

void Antena::setup() 
{
    //initialize Serial Monitor
    Serial.begin(9600);
    while (!Serial);
    Serial.println("LoRa Receiver");
    //Nada

    //setup LoRa transceiver module
    LoRa.setPins(ss, rst, dio0);
    
    //replace the LoRa.begin(---E-) argument with your location's frequency 
    //433E6 for Asia
    //866E6 for Europe
    //915E6 for North America
    while (!LoRa.begin(866E6)) {
        Serial.println(".");
        delay(500);
    }
    // Change sync word (0xF3) to match the receiver
    // The sync word assures you don't get LoRa messages from other LoRa transceivers
    // ranges from 0-0xFF
    LoRa.setSyncWord(0xF3);
    Serial.println("LoRa Initializing OK!");

    semaforoVerde = false;
    semaforoAmarillo = false;
    semaforoRojo = false;  
}

bool Antena::recibeDatos() 
{
     // try to parse packet
    _packetSize = LoRa.parsePacket();
    if (_packetSize) {                               
        // read packet
        _packetSize = 0;
        while (LoRa.available()) {
         
            _datosRecibidos = LoRa.readString();
                     
            if(_datosRecibidos.substring(0, 4) != "dgma")  {
                Serial.println("recibiste un paquete extraño: " + _datosRecibidos);
                              
                return false;
            }else{                
                Serial.println("recibiste un paquete de un tal DGMA: " + _datosRecibidos); 
                _tamanopaquete =_datosRecibidos.length();
                Serial.print("tamaño del paquete: ");
                Serial.println(_tamanopaquete);

                tiempoDatosRecividos = millis();
                semaforoVerde = true;              
                semaforoAmarillo = false;
                semaforoRojo = false; 

                _pos_temperatura =   _datosRecibidos.indexOf("temperatura");
                _pos_humedad =       _datosRecibidos.indexOf("humedad");
                _pos_suelo =         _datosRecibidos.indexOf("suelo");
                _pos_presion =       _datosRecibidos.indexOf("presion");
                _pos_gas =           _datosRecibidos.indexOf("gas");
                _pos_altitud =       _datosRecibidos.indexOf("altitud");
                _pos_bateria =       _datosRecibidos.indexOf("bateria");

                temperatura =       _datosRecibidos.substring(_pos_temperatura+11, _pos_humedad);
                humedadAmbiente =   _datosRecibidos.substring(_pos_humedad+7, _pos_suelo);         
                humedadSuelo =      _datosRecibidos.substring(_pos_suelo+5, _pos_presion);
                presionAtmosf =     _datosRecibidos.substring(_pos_presion+7, _pos_gas);
                gas =               _datosRecibidos.substring(_pos_gas+3, _pos_altitud);
                altitud =           _datosRecibidos.substring(_pos_altitud+7, _pos_bateria);
                nivelBateria =      _datosRecibidos.substring(_pos_bateria+7, _datosRecibidos.length());
                
                return true;               
            }  
        }
    }  
    //Serial.println("recibeDatos.. ");
    return false;
}

void Antena::tiempoDesdeUltimoDato()
{
    
}

