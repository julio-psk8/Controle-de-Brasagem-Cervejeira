// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <OneWire.h>           // controle de sensor ds18b20
#include <DallasTemperature.h> // controle de sensor ds18b20
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Display

// ========================================================================================================
// --- Mapeamento de Hardware ---
#define    ONE_WIRE_BUS     3          //sinal do sensor DS18B20
#define rele 7                   //sinal rele
//int rele= 7;

// ========================================================================================================
// --- Declaração de Objetos ---
OneWire oneWire(ONE_WIRE_BUS);        //objeto one_wire
DallasTemperature sensor(&oneWire);
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);







void setup() {
  pinMode(rele, OUTPUT);
Serial.begin(9600); // Inicia a porta serial
  Serial.println("Medindo Temperatura"); // Imprime a mensagem inicial
  sensor.begin(); ; // Inicia o sensor

}

void loop() {
  /*digitalWrite(rele, HIGH);
  delay(1000);
  digitalWrite(rele, LOW);
  delay(1000);
  {*/
  sensor.requestTemperatures(); // Envia comando para realizar a conversão de temperatura
  if (!sensor.getAddress(endereco_temp,0)) { // Encontra o endereco do sensor no barramento
    Serial.println("SENSOR NAO CONECTADO"); // Sensor conectado, imprime mensagem de erro
  } else {
    Serial.print("Temperatura = "); // Imprime a temperatura no monitor serial
    Serial.println(sensor.getTempC(endereco_temp), 1); // Busca temperatura para dispositivo
  }
  delay(1000);
}

}

