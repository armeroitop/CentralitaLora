/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>
#include <TFT_eSPI.h> // Hardware-specific library


TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

//define the pins used by the transceiver module
#define ss 5
#define rst 26
#define dio0 2

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define MC_DATUM 4

String temperatura, humedadAmbiente, humedadSuelo, presionAtmosf, gas, altitud, nivelBateria; 


String LoRaData, LoRaDataAntigua;

void setup() {
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

void loop() 
{       
    // Datum is middle centre
    tft.setTextDatum(TL_DATUM);

    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {                               
        // read packet
        while (LoRa.available()) {

            //Primero borramos en pantalla los datos que existen pintandolos otra vez pero en negr
            if(LoRaDataAntigua){
                tft.setTextColor(TFT_BLACK, TFT_BLACK);
                //tft.drawString(LoRaDataAntigua, 120, 50, 4); 
                tft.drawString(temperatura, 120, 50, 4);
                tft.drawString(humedadAmbiente, 120, 100, 4);
                tft.drawString(humedadSuelo, 120, 150, 4); 
            } 

            LoRaData = LoRa.readString();
                     
            if(LoRaData.substring(0, 4) != "dgma")  {
                Serial.println("recibiste un paquete extraño: " + LoRaData);
                return;
            }else{                
                Serial.println("recibiste un paquete de un tal DGMA: " + LoRaData);                
            }  


            int pos_temperatura = LoRaData.indexOf("temperatura");
            int pos_humedad = LoRaData.indexOf("humedad");
            int pos_suelo = LoRaData.indexOf("suelo");
            int pos_presion = LoRaData.indexOf("presion");
            int pos_gas = LoRaData.indexOf("gas");
            int pos_altitud = LoRaData.indexOf("altitud");
            int pos_bateria = LoRaData.indexOf("bateria");

            Serial.println(pos_temperatura);
            //Serial.println("humedadAmbiente "+pos_humedad);
            //Serial.println("humedadSuelo "+pos_suelo);
         

            tft.setTextColor(TFT_YELLOW, TFT_BLACK);

            temperatura =       LoRaData.substring(pos_temperatura+11, pos_humedad);
            humedadAmbiente =   LoRaData.substring(pos_humedad+7, pos_suelo);         
            humedadSuelo =      LoRaData.substring(pos_suelo+5, pos_presion);
            presionAtmosf =     LoRaData.substring(pos_presion+7, pos_gas);
            gas =               LoRaData.substring(pos_gas+3, pos_altitud);
            altitud =           LoRaData.substring(pos_altitud+7, pos_bateria);
            nivelBateria =      LoRaData.substring(pos_bateria+7, LoRaData.length());

            

            tft.drawString(temperatura,      120, 10, 4);
            tft.drawString(humedadAmbiente,  130, 40, 4);
            tft.drawString(humedadSuelo,     120, 70, 4); 
            tft.drawString(presionAtmosf,    120, 100, 4); 
            tft.drawString(gas,              120, 130, 4); 
            tft.drawString(altitud,          120, 160, 4); 
            tft.drawString(nivelBateria,     120, 190, 4); 
            
            
        }

        // print RSSI of packet
        //Serial.print("' with RSSI ");
        //Serial.println(LoRa.packetRssi());
        
    }     
}