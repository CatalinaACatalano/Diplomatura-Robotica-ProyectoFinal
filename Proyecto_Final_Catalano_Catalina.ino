// Librerías utilizadas

#include <DHT.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// Definición de sensores y los pines utilizados

#define DHTPIN 13
#define DHTTYPE DHT11 
#define sensorHumedad A3 // Sensor de humedad de suelo
 
// Creación del objeto sensor para el sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

// Creación de los objetos display para cada sensor

LiquidCrystal_I2C lcdAmbiente(0x27, 2, 1, 0, 4, 5, 6, 7);
LiquidCrystal_I2C lcdSuelo(0x20, 2, 1, 0, 4, 5, 6, 7);

//Definición de variables

float humedadAmbiente;
float temperaturaAmbiente;
float humedadSuelo;

void setup() {
  
  // Inicialización comunicación serie
  Serial.begin(9600);
 
  // Inicialización del sensor DHT
  
  dht.begin();

  // Configuración de los LCD
  
  lcdAmbiente.setBacklightPin(3, POSITIVE);
  lcdAmbiente.setBacklight(HIGH);
  lcdAmbiente.begin(16,2);
  lcdAmbiente.clear();

  lcdSuelo.setBacklightPin(3, POSITIVE);
  lcdSuelo.setBacklight(HIGH);
  lcdSuelo.begin(16,2);
  lcdSuelo.clear();
 
}
 
void loop() {
 
  // Intevalo entre medidas de 1 segundos
 delay(1000);


//Sensor DHT11   

  humedadAmbiente = dht.readHumidity();  // Lectura de la humedad ambiente relativa
  
  temperaturaAmbiente = dht.readTemperature();// Lectura la temperatura ambiente en grados centígrados (por defecto)
   
 // Verificación de error en la lectura de datos
  
  if (isnan(humedadAmbiente) || isnan(temperaturaAmbiente)) {
    
    lcdAmbiente.print("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
 
 // Muestra de resultados en la pantalla
  lcdAmbiente.clear();
  lcdAmbiente.setCursor(0,0);
  lcdAmbiente.print("Temp. = ");
  lcdAmbiente.print(temperaturaAmbiente);
  lcdAmbiente.print(" ");
  lcdAmbiente.print((char)223);
  lcdAmbiente.print("C");
  lcdAmbiente.setCursor(0,1);
  lcdAmbiente.print("Humed. = ");
  lcdAmbiente.print(humedadAmbiente);
  lcdAmbiente.print(" % ");
 

 //Sensor Humedad Suelo

  humedadSuelo = map(analogRead(sensorHumedad), 0, 1023, 100, 0);  //Realiza el mapeo de la lectura del sensor a porcentual
  
  // Muestra de resultados en la pantalla
  lcdSuelo.clear();
  lcdSuelo.setCursor(0,0);
  lcdSuelo.print("Humedad suelo: ");  
  lcdSuelo.setCursor(0,1);
  lcdSuelo.print(humedadSuelo);  
  lcdSuelo.print(" %"); 
  
}
