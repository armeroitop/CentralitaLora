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

            //Primero borramos en pantalla los datos que existen pintandolos otra vez pero en negr
            /* if(LoRaDataAntigua){
                tft.setTextColor(TFT_BLACK, TFT_BLACK);
                //tft.drawString(LoRaDataAntigua, 120, 50, 4); 
                tft.drawString(temperatura, 120, 50, 4);
                tft.drawString(humedadAmbiente, 120, 100, 4);
                tft.drawString(humedadSuelo, 120, 150, 4); 
            }  */

            _datosRecibidos = LoRa.readString();
                     
            if(_datosRecibidos.substring(0, 4) != "dgma")  {
                Serial.println("recibiste un paquete extraño: " + _datosRecibidos);
                return "mal";
            }else{                
                Serial.println("recibiste un paquete de un tal DGMA: " + _datosRecibidos);                
            }  

        }

      
    }  
    return _datosRecibidos;
}

