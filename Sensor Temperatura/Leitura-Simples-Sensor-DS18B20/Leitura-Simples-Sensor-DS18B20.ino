/* ========================================================================================================
       Sensor de Temperatura DS18B20 Dallas
       
            LEITURA SIMPLES DO SENSOR
    
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


// ========================================================================================================
// --- Constantes Auxiliares ---
#define ONE_WIRE_BUS 10


// ========================================================================================================
// --- Declaração de Objetos ---
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer = { 0x28, 0x27, 0x1D, 0x57, 0x04, 0xE1, 0x3C, 0xD1};


// ========================================================================================================
// --- Protótipo das Funções ---
void printTemperature(DeviceAddress deviceAddress);


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
 
  Serial.begin(9600);   //inicializa comunicação serial
 
  sensors.begin();      //inicializa sensores
 
  sensors.setResolution(insideThermometer, 10); //configura para resolução de 10 bits
 
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop(void)
{ 
  
  Serial.println("Sensor DS18B20");
  sensors.requestTemperatures();  // inicialisa a leitura do sensor
  printTemperature(insideThermometer);   // função para imprecao de temperatura do sensor
  
  
  delay(1000);
  
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) 
  {
    Serial.print("Erro de leitura");
  } 
  else 
  {
    Serial.print(tempC);
    Serial.print(" graus C ");
    Serial.print("  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print(" graus F ");
  }

  Serial.print("\n\r");
  
} //end printTemperature








