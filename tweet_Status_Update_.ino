#include <cstdlib>
#include <ctime>

#include <SPI.h>
#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <TembooSSL.h>
#include "TembooAccount.h" // Contains Temboo account information

WiFiSSLClient client;

int calls = 1;   // Execution count, so this doesn't run forever
int minCalls = 2;   // Minimum number of times the Choreo be executed before conditional flows

void setup() {
  Serial.begin(9600);
  srand(analogRead(A1)*analogRead(A0)*analogRead(A4));    //A0,A1,A4 are empty pins as seeds for rand()
  // For debugging, wait until the serial console is connected
  delay(4000);
  
  pinMode(A3,INPUT);
  digitalWrite(A3,HIGH);
  pinMode(A4,OUTPUT);
  digitalWrite(A4,HIGH);
  
  //while(!Serial);
}

void loop() {
  
  Serial.println("start");
  int sensorValue = analogRead(A3);
  float voltage = sensorValue * (3.0 / 1023.0);
  
  int wifiStatus = WL_IDLE_STATUS;

  // Determine if the WiFi Shield is present
  Serial.print("\n\nShield:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("FAIL");

    // If there's no WiFi shield, stop here
    while(true);
  }

  Serial.println("OK");

  // Try to connect to the local WiFi network

  if ( WiFi.status() != WL_CONNECTED) {
      while (WiFi.begin(WIFI_SSID) != WL_CONNECTED) {
        // unsuccessful, retry in 4 seconds
        Serial.print("failed ... ");
        delay(4000);
        Serial.print("retrying ... ");
      }
  }

  /*
  while(wifiStatus != WL_CONNECTED) {
    //delay(1000);
    Serial.print("WiFi:");
    wifiStatus = WiFi.begin(WIFI_SSID);
    if (wifiStatus == WL_CONNECTED) {
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }
  }

  */

  Serial.println("Setup complete.\n");
  
  if (calls >= minCalls) {
    
    Serial.println("Running StatusesUpdate - Run #" + String(calls));

    if(voltage>1.0&&digitalRead(A4)==LOW){
        digitalWrite(A3,HIGH);
        Serial.println("normal");
        Serial.print("A4 pin is: ");
        Serial.println(digitalRead(A4));
        
        TembooChoreoSSL StatusesUpdateChoreo(client);
    
        // Invoke the Temboo client
        StatusesUpdateChoreo.begin();
    
        // Set Temboo account credentials
        StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
        StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
        StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);
        StatusesUpdateChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
    
        // Set Choreo inputs
        String StatusUpdateValue = "NORMAL: "+String(rand());
        StatusesUpdateChoreo.addInput("StatusUpdate", StatusUpdateValue);
        String AccessTokenValue = "1021408926514937856-M4SRadfHn91uiUiK25ASZNIAdW7czZ";
        StatusesUpdateChoreo.addInput("AccessToken", AccessTokenValue);
        String ConsumerKeyValue = "eFo9TpWVU9YvmRPlHcqFB4NCa";
        StatusesUpdateChoreo.addInput("ConsumerKey", ConsumerKeyValue);
        String ConsumerSecretValue = "ONVA4QTXFgBdx1lczm50Gulu8y3T39QZaW3203Cr2Zwvn9iNi1";
        StatusesUpdateChoreo.addInput("ConsumerSecret", ConsumerSecretValue);
        String AccessTokenSecretValue = "bVf4S8wgajEU8dIo3G6i1mKlqLWZGcKYxJWuLMj29WVs8";
        StatusesUpdateChoreo.addInput("AccessTokenSecret", AccessTokenSecretValue);
    
        // Identify the Choreo to run
        StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");
        Serial.println("checkpoint1");
        // Run the Choreo; when results are available, print them to serial
    
        
        if (wifiStatus == WL_CONNECTED) {
          Serial.println("OK");
        } else {
          Serial.println("FAIL");
          delay(1000);
        }
      
    
        
        StatusesUpdateChoreo.run();
        Serial.println("checkpoint2");
        while(StatusesUpdateChoreo.available()) {
          char c = StatusesUpdateChoreo.read();
          Serial.print(c);
        }
        StatusesUpdateChoreo.close();
        digitalWrite(A4,HIGH);
    }

    if(voltage<=1.0&&digitalRead(A4)==HIGH){
        digitalWrite(A3,HIGH);
        Serial.println("low");
        Serial.print("A4 pin is: ");
        Serial.println(digitalRead(A4));
        
        TembooChoreoSSL StatusesUpdateChoreo(client);
    
        // Invoke the Temboo client
        StatusesUpdateChoreo.begin();
    
        // Set Temboo account credentials
        StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
        StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
        StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);
        StatusesUpdateChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
    
        // Set Choreo inputs
        String StatusUpdateValue = "LOW: "+String(rand());
        StatusesUpdateChoreo.addInput("StatusUpdate", StatusUpdateValue);
        String AccessTokenValue = "1021408926514937856-M4SRadfHn91uiUiK25ASZNIAdW7czZ";
        StatusesUpdateChoreo.addInput("AccessToken", AccessTokenValue);
        String ConsumerKeyValue = "eFo9TpWVU9YvmRPlHcqFB4NCa";
        StatusesUpdateChoreo.addInput("ConsumerKey", ConsumerKeyValue);
        String ConsumerSecretValue = "ONVA4QTXFgBdx1lczm50Gulu8y3T39QZaW3203Cr2Zwvn9iNi1";
        StatusesUpdateChoreo.addInput("ConsumerSecret", ConsumerSecretValue);
        String AccessTokenSecretValue = "bVf4S8wgajEU8dIo3G6i1mKlqLWZGcKYxJWuLMj29WVs8";
        StatusesUpdateChoreo.addInput("AccessTokenSecret", AccessTokenSecretValue);
    
        // Identify the Choreo to run
        StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");
        Serial.println("checkpoint1");
        // Run the Choreo; when results are available, print them to serial
    
        
        if (wifiStatus == WL_CONNECTED) {
          Serial.println("OK");
        } else {
          Serial.println("FAIL");
          delay(1000);
        }
      
        StatusesUpdateChoreo.run();
        Serial.println("checkpoint2");
        while(StatusesUpdateChoreo.available()) {
          char c = StatusesUpdateChoreo.read();
          Serial.print(c);
        }
        StatusesUpdateChoreo.close();
        digitalWrite(A4,LOW);
    }

  }
  calls++;
  Serial.println("\nWaiting...\n");
  delay(30000); // wait 30 seconds between StatusesUpdate calls
}
