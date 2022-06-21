#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
//9liters water ki 4cm distance
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
//9-4
//8-8
//7-10
//6-12
//5-13
//4-15
//3-17
//2-19
//1-20
//0-22
#define WIFI_SSID "Redmiharitha"
#define WIFI_PASSWORD "haritha85"

#define trig 27   // Trig pin#define echo 26   // Echo Pin 
#define echo 26
int tankdepth =20;

#define USER_EMAIL "198w1a0523@vrsiddhartha.ac.in"
#define USER_PASSWORD "Haritha8.@"

#define API_KEY "AIzaSyAsYyilvZ6yL3TAW5UkzHXh5wep3nWl-c8"
#define DATABASE_URL "https://finalfuel-c7bfa-default-rtdb.firebaseio.com/" 
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup(){
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println(); 
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;

  

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

   
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);  

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;


  config.timeout.serverResponse = 10 * 1000;

}






void loop() 
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long t = pulseIn(echo, HIGH);
    int cm = t / 29 / 2;
    int d=0;
    int cap=9;//capacity in liters
    int mi=40;//mileage
    int f=9000;//fuelinml
    
    Serial.println("Fuel level is "+cm);
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
    {
          sendDataPrevMillis = millis();
          if(cm<4)
        {
            Serial.println("Full tank");
            d=9*40;
            Serial.println("Maximum distance that can be covered in kms ");
            Serial.println(d);
            if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
                    Serial.print("Writing value: ");
                    Serial.print("fuellevel");
                    Serial.println(cm);
    
             }
           else {
                    Serial.println("FAILED fuel level");
                    Serial.println("REASON: " + fbdo.errorReason());
            }
            if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
                    Serial.print("Writing value: ");
                    Serial.print("dist");
                    Serial.println(d);
    
           }
           else {
                   Serial.println("FAILED fuel level");
                   Serial.println("REASON: " + fbdo.errorReason());
                 }

           if (Firebase.RTDB.setInt(&fbdo,"fuel", 9000)){
                   Serial.print("Writing value: ");
                   Serial.print("fuel");
                   Serial.println(9000);
    
            }
            else {
                   Serial.println("FAILED fuel level");
                   Serial.println("REASON: " + fbdo.errorReason());
            }
           if (Firebase.RTDB.setString(&fbdo,"msg", "Full Tank")){
                   Serial.print("Writing value: ");
                   Serial.print("msg");
                   Serial.println("Full Tank");
    
            }
            else {
                   Serial.println("FAILED fuel level");
                   Serial.println("REASON: " + fbdo.errorReason());
            }
          
      }
      else if(4<=cm && cm<8)
      {
          f=9000-(((cm-4)*1000)/(8-4));      
          Serial.println("Fuel in tank is  in ml"+f);
          d=(f/1000)*40;
          Serial.println("Maximum distance that can be covered in kms "+ d);
          if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
                   Serial.print("Writing value: ");
                   Serial.print("fuellevel");
                   Serial.println(cm);
    
            }
          else {
                   Serial.println("FAILED fuel level");
                   Serial.println("REASON: " + fbdo.errorReason());
            }
          if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
                  Serial.print("Writing value: ");
                  Serial.print("dist");
                  Serial.println(d);
    
            }
          else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
            }

          if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
                  Serial.print("Writing value: ");
                  Serial.print("fuel");
                  Serial.println(f);
    
            }
          else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
            }
          if (Firebase.RTDB.setString(&fbdo,"msg", "You Can GO!!!")){
                  Serial.print("Writing value: ");
                  Serial.print("msg");
                  Serial.println("You Can GO!!!");
    
            }
          else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
           }
     
      
      }
      else if(8<=cm && cm<10)
      {
            f=8000-(((cm-8)*1000)/(10-8));      
            Serial.println("Fuel in tank is in ml"+f);
            d=(f/1000)*40;
            Serial.println("Maximum distance that can be covered in kms "+d);
            if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
                  Serial.print("Writing value: ");
                  Serial.print("fuellevel");
                  Serial.println(cm);
   
            }
            else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
            }
            if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
                  Serial.print("Writing value: ");
                  Serial.print("dist");
                  Serial.println(d);
   
            }
            else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
            }

            if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
                  Serial.print("Writing value: ");
                  Serial.print("fuel");
                  Serial.println(f);
   
            }
            else {
                   Serial.println("FAILED fuel level");
                   Serial.println("REASON: " + fbdo.errorReason());
            }
            if (Firebase.RTDB.setString(&fbdo,"msg", "YOU CAN GO")){
                   Serial.print("Writing value: ");
                   Serial.print("msg");
                   Serial.println("YOU CAN GO");
    
            }
            else {
                   Serial.println("FAILED fuel level");
                   Serial.println("REASON: " + fbdo.errorReason());
            }
      //senString("msg","With  "+cm +"  fuel level,"+f+"milli liters of fuel "+ d +" distance can be covered");
    }
    else if(10<=cm && cm<12)
    {
        f=7000-(((cm-10)*1000)/(12-10));      
        Serial.println("Fuel in tank is in ml"+f);
        d=(f/1000)*40;
        Serial.println("Maximum distance that can be covered in kms "+d);
        if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
                   Serial.print("Writing value: ");
                   Serial.print("fuellevel");
                   Serial.println(cm);
    
        }
        else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
        }
        if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
                  Serial.print("Writing value: ");
                  Serial.print("dist");
                  Serial.println(d);
    
        }
        else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
        }

        if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
                  Serial.print("Writing value: ");
                  Serial.print("fuel");
                  Serial.println(f);
    
        }
        else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
        }
        if (Firebase.RTDB.setString(&fbdo,"msg", "YOU CAN GO")){
                  Serial.print("Writing value: ");
                  Serial.print("msg");
                  Serial.println("YOU CAN GO");
    
        }
        else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
        }
    }
    else if(12<=cm && cm<13)
    {
          f=6000-(((cm-12)*1000)/(13-12));      
          Serial.println("Fuel in tank is in ml");
          Serial.println(f);
          d=(f/1000)*40;
          Serial.println("Maximum distance that can be covered in kms ");
          Serial.println(d);
          if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
                  Serial.print("Writing value: ");
                  Serial.print("fuellevel");
                  Serial.println (cm);
    
         }
          else {
                  Serial.println("FAILED fuel level");
                  Serial.println("REASON: " + fbdo.errorReason());
          }
          if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
                  Serial.print("Writing value: ");
                  Serial.print("dist");
                  Serial.print (d);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }

   if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
    Serial.print("Writing value: ");
    Serial.print("fuel");
    Serial.println (f);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setString(&fbdo,"msg", "YOU CAN GO")){
    Serial.print("Writing value: ");
    Serial.print("msg");
    Serial.println("YOU CAN GO");
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
      
     
    }
    else if(13<=cm && cm<15)
    {
      f=5000-(((cm-13)*1000)/(15-13));      
      Serial.println("Fuel in tank is in ml"+f);
      d=(f/1000)*40;
      Serial.println("Maximum distance that can be covered in kms "+d);
     if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
        Serial.print("Writing value: ");
        Serial.print("fuellevel");
      Serial.println (cm);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
    Serial.print("Writing value: ");
    Serial.print("dist");
    Serial.print (d);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }

   if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
    Serial.print("Writing value: ");
    Serial.print("fuel");
    Serial.println (f);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setString(&fbdo,"msg", "YOU CAN GO")){
    Serial.print("Writing value: ");
    Serial.print("msg");
    Serial.println("YOU CAN GO");
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
      //senString("msg","With  "+cm +"  fuel level,"+f+"milli liters of fuel "+ d +" distance can be covered");
    }
    else if(15<=cm && cm<17)
    {
      f=4000-(((cm-15)*1000)/(17-15));      
      Serial.print("Fuel in tank is in ml");
      Serial.println(f);
      d=(f/1000)*40;
      Serial.print("Maximum distance that can be covered in kms ");
      Serial.println(d);
      if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
        Serial.print("Writing value: ");
        Serial.print("fuellevel");
        Serial.println (cm);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
    Serial.print("Writing value: ");
    Serial.print("dist");
    Serial.println(d);
   
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }

   if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
    Serial.print("Writing value: ");
    Serial.print("fuel");
    Serial.println(f);
   
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setString(&fbdo,"msg", "YOU CAN GO")){
    Serial.print("Writing value: ");
    Serial.print("msg");
    Serial.println("YOU CAN GO");
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
     
    }
     else if(17<=cm && cm<19)
    {
      f=3000-(((cm-17)*1000)/(19-17));      
      Serial.println("Fuel in tank is in ml");
      Serial.print(f);
      d=(f/1000)*40;
      Serial.print("Maximum distance that can be covered in kms ");
      Serial.println(d);
      
      
    }
     else if(19<=cm && cm<20)
    {
      f=2000-(((cm-19)*1000)/(20-19));      
      Serial.println("Fuel in tank is in ml");
      Serial.print(f);
      d=(f/1000)*40;
      Serial.println("Maximum distance that can be covered in kms ");
      Serial.print(d);
      if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
        Serial.print("Writing value: ");
        Serial.print("fuellevel");
        Serial.println(cm);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
    Serial.print("Writing value: ");
    Serial.print("dist");
    Serial.println(d);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }

   if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
    Serial.print("Writing value: ");
    Serial.print("fuel");
    Serial.println(f);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setString(&fbdo,"msg", "YOU CAN GO")){
    Serial.print("Writing value: ");
    Serial.print("msg");
    Serial.println("YOU CAN GO");
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
    
    }
    else if(20<=cm && cm<22)
    {
      f=2000-(((cm-19)*1000)/(20-19));      
      Serial.println("Fuel in tank is in ml");
      Serial.print(f);
      d=(f/1000)*40;
      Serial.println("Maximum distance that can be covered in kms "+d);
      if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
          Serial.print("Writing value: ");
          Serial.print("fuellevel");
          Serial.println(cm);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setInt(&fbdo,"dist", d)){
    Serial.print("Writing value: ");
    Serial.print("dist");
    Serial.println(d);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }

   if (Firebase.RTDB.setInt(&fbdo,"fuel", f)){
    Serial.print("Writing value: ");
    Serial.print("fuel");
    Serial.println(f);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setString(&fbdo,"msg", "ONLY ONE LITRE FUEL IN TANK!")){
    Serial.print("Writing value: ");
    Serial.print("msg");
    Serial.println("ONLY ONE LITRE FUEL IN TANK!");
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
     
    }
    else if(cm>=22)
    {
      Serial.println("No Fuel!!!!");
      Serial.println("Vehicle may stop at any moment");
      
      if (Firebase.RTDB.setInt(&fbdo,"fuellevel", cm)){
    Serial.print("Writing value: ");
    Serial.print("fuellevel");
    Serial.println(cm);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setInt(&fbdo,"dist", 0)){
    Serial.print("Writing value: ");
    Serial.print("dist");
    Serial.println(0);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }

   if (Firebase.RTDB.setInt(&fbdo,"fuel", 0)){
    Serial.print("Writing value: ");
    Serial.print("fuel");
    Serial.println(0);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setString(&fbdo,"msg", "No Fuel!!!!")){
    Serial.print("Writing value: ");
    Serial.print("msg");
    Serial.println("No Fuel!!!!");
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
    }
    delay(50000);
}
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
      if (Firebase.RTDB.setString(&fbdo,"msg", "OUT OF RANGE ERROR")){
    Serial.print("Writing value: ");
    Serial.print("msg");
    Serial.println( "OUT OF RANGE ERROR");
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
   if (Firebase.RTDB.setInt(&fbdo,"fuel", 0)){
    Serial.print("Writing value: ");
    Serial.print("fuel");
    Serial.println (0);
   
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
   if (Firebase.RTDB.setInt(&fbdo,"dist", 0)){
    Serial.print("Writing value: ");
    Serial.print("dist");
    Serial.println (0);
    
  }
  else {
    Serial.println("FAILED fuel level");
    Serial.println("REASON: " + fbdo.errorReason());
  }
    } 
    delay(500);
  
    
  }
