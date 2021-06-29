#include <Antena.h>

Antena::Antena(/* args */)
{     
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
}

String Antena::recibeDatos() 
{
     // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {                               
        // read packet
        while (LoRa.available()) {
         
            _datosRecibidos = LoRa.readString();
                     
            if(_datosRecibidos.substring(0, 4) != "dgma")  {
                Serial.println("recibiste un paquete extraño: " + _datosRecibidos);
                return "mal";
            }else{                
                Serial.println("recibiste un paquete de un tal DGMA: " + _datosRecibidos);                
            }  
        }
    }  
    //Serial.println("recibeDatos.. ");
    return _datosRecibidos;
}

