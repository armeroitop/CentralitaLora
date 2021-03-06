/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>


#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

//define the pins used by the transceiver module
#define ss 5
#define rst 26
#define dio0 2

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define MC_DATUM 4



String LoRaDataNueva, LoRaDataAntigua;

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
}

void loop() {
    
    tft.setTextColor(TFT_WHITE, TFT_BLACK);    
    // Datum is middle centre
    tft.setTextDatum(TL_DATUM);

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
        // received a packet
                       
        // read packet
        while (LoRa.available()) {
            LoRaDataNueva = LoRa.readString();

            //Borramos los datos en la pantalla pintandolos otra vez pero en negro 
            if(LoRaDataAntigua){
              tft.setTextColor(TFT_BLACK, TFT_BLACK);
              tft.drawString("Temp "+ LoRaDataAntigua, 50, 50, 4); 
            }           
            
            const char *datosRecividos=LoRaDataNueva.c_str();
            LoRaDataNueva = datosRecividos;
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString("Temp " + LoRaDataNueva, 50, 50, 4);

            LoRaDataAntigua = datosRecividos;
        }

        // print RSSI of packet
        //Serial.print("' with RSSI ");
        //Serial.println(LoRa.packetRssi());
        
    }     
}