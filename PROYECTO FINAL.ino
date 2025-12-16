#include "DHT.h"

#include <LCD_I2C.h>

// Direcciones I2C de los LCD

//#define LCD2_ADDR 0x26

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according
//LCD_I2C lcd2(LCD2_ADDR, 16, 2);

#define DHTPIN 10 

#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

//PINER DEL ARDUINO
int Movimiento = 2;
int RELEY = 3;
//int BUZZER = 5;
int trigPin = 8;
int echoPin = 9;
int SensorTemp = 10;
int ledCASA = 11;
int Potenciometro = 14; //A0



//VARIABLES 
int valorVOLTAJE;
int distancia;
long tiempo;





void setup() {
 
    //DECLARAMOS SALIDAS Y ENTRADAS
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(SensorTemp,INPUT);
    pinMode(ledCASA, OUTPUT);
    pinMode(Movimiento, INPUT);
    pinMode(RELEY, OUTPUT);
  //  pinMode(BUZZER, OUTPUT);

    lcd.begin(); // If you are using more I2C devices using the Wire library use 
    lcd.begin(false);
    lcd.backlight();

    //lcd2.begin(); // If you are using more I2C devices using the Wire library use 
    //lcd2.backlight();

    dht.begin();

    Serial.begin(9600);
}

void loop() {

  digitalWrite(trigPin, LOW);

  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  tiempo = pulseIn(echoPin, HIGH);

  distancia = 0.017 * tiempo; // formula 343.2m/seg * (100 cm/m) * (1/1000000 microsegundos) = 1(29.2 * 2 cm/microsegundos) = 0.017 cm/microsegundos

  valorVOLTAJE = analogRead(Potenciometro)/4;

  bool valorMOVIMIENTO = digitalRead(Movimiento);

  

    

  


  if(distancia <= 10){
    
    //lcd2.setCursor(0,0);
    //lcd2.clear();
    //lcd2.print("Carro a:");
    //lcd2.setCursor(0,1);
    //lcd2.print(distancia);


    lcd.setCursor(0,0);

    float h = dht.readHumidity();

    float t = dht.readTemperature();

      if (isnan(h) || isnan(t)){

        if(valorVOLTAJE  > 100){
          analogWrite(ledCASA, valorVOLTAJE );
        }
        else {
          analogWrite(ledCASA, LOW);
        }

        if(valorMOVIMIENTO == 1){

        digitalWrite(RELEY,HIGH);
      //tone(BUZZER, 1000); // 1000 Hz
      //delay(1000);           // Espera 1 segundo
      //noTone(BUZZER);     // Detiene el tono
      //delay(1000);           // Espera 1 segundo  

        } else {

        digitalWrite(RELEY,LOW);
        //noTone(BUZZER); 
        }



        lcd.clear();
        lcd.print("failed to read");
        delay(500);

        return;

      }

      else{

        if(valorVOLTAJE  > 100){
          analogWrite(ledCASA, valorVOLTAJE );
        }
        else {
          analogWrite(ledCASA, LOW);
        }  

        if(valorMOVIMIENTO == 1){

          digitalWrite(RELEY,HIGH);
          //tone(BUZZER, 1000); // 1000 Hz
          //delay(1000);           // Espera 1 segundo
          //noTone(BUZZER);     // Detiene el tono
          //delay(1000);           // Espera 1 segundo  

        } else {

          digitalWrite(RELEY,LOW);
          //noTone(BUZZER); 
        }


        lcd.clear();
        lcd.print("temp c: ");
        lcd.print(t);
        lcd.setCursor(0,1);
        lcd.print("humedad: ");
        lcd.print(h);
        delay(2000);

        float hic = dht.computeHeatIndex(t,h);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("indice C: ");
        lcd.print(hic);
        lcd.setCursor(0,1);
        lcd.print("Carro a: ");
        lcd.print(distancia);
        lcd.print(" m");
        delay(2000);


      }

  }

  else{

    if(valorVOLTAJE  > 100){
      analogWrite(ledCASA, valorVOLTAJE );
    }
    else {
      analogWrite(ledCASA, LOW);
    }


    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("CARRO ROBADO");
    delay(1000);

  }

  



}


