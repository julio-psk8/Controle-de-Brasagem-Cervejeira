/* ========================================================================================================
       Sensor de Temperatura DS18B20 Dallas
       
            LEITURA NO DISPLAY I2C
                
   Autor: julio 23-11-2023
   
      HARDWARE Termômetro olhando-o de frente:

   Terminal da direita   -> 5V do Arduino
   Terminal da esquerda  -> GND do Arduino
   Terminal central      -> digital 10 do Arduino (ligar um resistor de 4,7k entre esta entrada e os 5V)
   
   
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// ========================================================================================================
// --- Constantes Auxiliares ---
#define ONE_WIRE_BUS 10
#define rele 7

// ========================================================================================================
// --- variaveis ---
int rel ;

// ========================================================================================================
// --- Declaração de Objetos ---
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor{ 0x28, 0x27, 0x1D, 0x57, 0x04, 0xE1, 0x3C, 0xD1 };
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


// ========================================================================================================
// --- Protótipo das Funções ---
void printTemperature(DeviceAddress deviceAddress);


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() {
  
  pinMode(rele, OUTPUT);
  lcd.begin(16,2);
  Serial.begin(9600);  //inicializa comunicação serial

  sensors.begin();  //inicializa sensores

  sensors.setResolution(sensor, 10);  //configura para resolução de 10 bits

}  //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop(void) {
  rel = digitalRead(rele);
  sensors.requestTemperatures();      // inicialisa a leitura do sensor
  Serial.println("Sensor DS18B20");
  printTemperature(sensor); // função para imprecao de temperatura do sensor
  lcd.setCursor(0,0);
  printTemperature(sensor); // função para imprecao de temperatura do sensor
  lcd.setCursor(0,1);
  lcd.print("rele");
  lcd.setCursor(15,1);
  lcd.print(rel);
  delay(1000);
  

  delay(1000);

}  //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---
void printTemperature(DeviceAddress deviceAddress) {
  float tempC = sensors.getTempC(deviceAddress);  // variavel para imprimir a tenperatura em graus celcius
  
  lcd.print(tempC);
  if (tempC >= 60  
    digitalWrite(rele, HIGH);
  else
    digitalWrite(rele, LOW);
    
  lcd.print("\n\r");

}  //end printTemperature
