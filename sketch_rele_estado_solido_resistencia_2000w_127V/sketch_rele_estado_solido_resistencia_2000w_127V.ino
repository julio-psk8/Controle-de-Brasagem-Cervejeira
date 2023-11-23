 /*
* Este é o código do Arduino para o Relé de Estado Sólido
* fabricado pela FOTEK
* para controlar ligar ou desligar a carga CA ou CC
* Este código funcionará com:
 * SSR-25DA
 * SSR-40DA
 * SSR-25DA-H
 * SSR-40DA-H
 * 
 */

#include <OneWire.h> // Do sensor de temperatura DS14
#include <DallasTemperature.h>
// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 12  // Define a porta 14 do UNO R3
// 14 // Define a porta 14 do UNO R3

// Define uma instancia do oneWire para comunicacao com o sensor de temperatura
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

#include <Wire.h> // i2c
//Essa é a bliblioteca do LCD 
#include <LiquidCrystal_I2C.h>

const int buttonMenos = 11; 
const int buttonMais  = 12; 
const int buttonLigaDesliga = 13; 

float tempC = 0;

int tempo = 60; // inicializa o tempo que a resistencia fica ligada em 30 segundos;

// criacao do lcd 16x2
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


 
//void mostra_endereco_sensor(DeviceAddress deviceAddress)
//{
//  for (uint8_t i = 0; i < 8; i++)
//  {
//    // Adiciona zeros se necessário
//    if (deviceAddress[i] < 16) Serial.print("0");
//    Serial.print(deviceAddress[i], HEX);
//  }
//
//  // Localiza e mostra enderecos dos sensores
//  Serial.println("Localizando sensores DS18B20...");
//  Serial.print("Foram encontrados ");
//  Serial.print(sensors.getDeviceCount(), DEC);
//  Serial.println(" sensores.");
//  if (!sensors.getAddress(sensor1, 0))
//    Serial.println("Sensores nao encontrados !");
//   // Mostra o endereco do sensor encontrado no barramento
//   Serial.print("Endereco sensor: ");
//   mostra_endereco_sensor(sensor1);
//  
//}
 // Relé SSR
int relePino = 8;// define o pino 8 para saída ao relé


void setup() {
  pinMode(buttonMais, INPUT);
  pinMode(buttonMenos, INPUT);
  pinMode(buttonLigaDesliga, INPUT);
  
  // inicializa a porta serial a 9600 bps
  Serial.begin(9600);
  Serial.println("Teste de Relé de Estado Sólido FOTEK SSR-40-DA");
  pinMode(relePino, OUTPUT);

  lcd.begin(16,2);
  
  lcd.clear();
  lcd.print(" ARDUINO MAKER");
  lcd.setCursor(0,1);
  lcd.print(" RELE SSR-40 DA");
  delay(3000);
  lcd.clear();
 //  mostra_endereco_sensor(sensor1);
}

// loop para controlar o relé
void loop() {
 
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  // Mostra dados no serial monitor
  Serial.print("Temp C: ");
  Serial.println(tempC);
  lcd.setCursor(0,0);
  lcd.print("Temperatura " );
  lcd.setCursor(12,0);
  lcd.print(tempC);

  int estadoBotaoMais = digitalRead(buttonMais);
     if(estadoBotaoMais == HIGH) {
        tempo = tempo + 10;
        lcd.setCursor(12,1);
        lcd.print("+   ");
        lcd.setCursor(13,1);
        lcd.print(tempo);
     }

  int estadoBotaoMenos = digitalRead(buttonMenos);
     if(estadoBotaoMenos == HIGH) {
        tempo = tempo -10;
        if (tempo < 0) tempo = 0;
        lcd.setCursor(12,1);
        lcd.print("-   ");
        lcd.setCursor(13,1);
        lcd.print(tempo);
     }
     
   int estadoBotaoLigaDesliga = digitalRead(buttonLigaDesliga);
     if(estadoBotaoLigaDesliga == HIGH) {
        if(tempo > 0) {
           tempo = 0;
           // Desliga a resistencia
           digitalWrite(relePino, LOW);// seta o pino do relé para LOW
           lcd.setCursor(0,1);
           lcd.print("Desligado          ");
           delay(2000);
        }else {
          tempo = 60;
          // Liga a resistencia
          digitalWrite(relePino, HIGH);// seta o pino do relé para HIGH
          lcd.setCursor(0,1);
          lcd.print("Acionado         ");
          delay(2000);
        }
     }

     if (tempo > 0) {
         tempo = tempo -1;
         lcd.setCursor(13,1);
         lcd.print(tempo);
         
         if(tempo<10) {
          lcd.setCursor(14,1);
          lcd.print("  ");
         }
         delay(1000);
         lcd.setCursor(13,1);
        lcd.print("    ");
     } else {
           digitalWrite(relePino, LOW);// seta o pino do relé para LOW
           lcd.setCursor(0,1);
           lcd.print("Desligado          ");
           delay(1000);
     }
}
