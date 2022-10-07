#include <Arduino.h>
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 

// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
bool intsalled = false;


void setup() {
  // configure the USB serial monitor 
  Serial.begin(115200); 
  Serial.println("");
  Serial.println("Temperature Application");
  // Start the DS18B20 sensor 
  DS18B20.begin();
  DeviceAddress address;
  if (!DS18B20.getAddress(address, 0)){
    Serial.println("No DS18B20 temperature sensors are installed");
    
  } 
  else{
    intsalled = true;
    Serial.print("Found DS18B20 sensor with address: ");

    for (int i = 0; i <8; i++){
    Serial.print(address[i]);
    }
  }
  Serial.println("");  
}

void loop() {
  
  float fTemp;
  String judgement = "";

  if(intsalled){
    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
  
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0); 
    if(fTemp < 10){
      judgement = "Cold!";
    }
    else if(fTemp < 15){
      judgement = "Cool";
    }
    else if(fTemp < 25){
      judgement = "Perfect";
    }
    else if(fTemp < 30){
      judgement = "Warm";
    }
    else if(fTemp < 35){
      judgement = "Hot";
    }
    else{
      judgement = "Too Hot!";
    }
  
    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + " or " + judgement); 
  }
 
  // wait 2s (2000ms) before doing this again 
  delay(2000); 
}