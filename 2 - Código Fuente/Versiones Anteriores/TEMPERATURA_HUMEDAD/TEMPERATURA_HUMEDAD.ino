
#include <PID_v1.h> // libreria PID
#include "WiFi.h"
#include "DHT.h"
#include "Adafruit_BMP085.h"
#define pin1 13       //Pin del DHT11.
#define pin2 32       //Pin del DHT22.

const char* ssid = "*****";                        //SSID de vuestro router.
const char* password = "******";                //Contraseña de vuestro router.

WiFiClient cliente;

DHT dht1(pin1, DHT11);    //El azul.
DHT dht2(pin2, DHT22);    //El blanco.

//Define Variables
double Setpoint, Input, Output;

//Iniciar parametros
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

unsigned long previousMillis = 0;   
const long interval = 2000;   //Gráfica cada 2''
float t1 = 0;
float h1 = 0;

void setup() {
    
    Serial.begin(9600);
    Serial.println("Test de sensores:");

    WiFi.begin(ssid,password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Wifi conectado!");

    dht1.begin();
    dht2.begin();
  
    Setpoint = 45;              //La temperatura que queremos mantener
    // ponemos el PID en ON
    myPID.SetMode(AUTOMATIC);
}

void loop() {

  delay(2000);
  leerdht1();

  delay(2000);
  leerdht2();
}

void leerdht1() {
  
  unsigned long currentMillis = millis();

  t1 = dht1.readTemperature();
  h1 = dht1.readHumidity();

  while (isnan(t1) || isnan(h1)){
    Serial.println("Lectura fallida en el sensor DHT11, repitiendo lectura...");
    delay(2000);
    t1 = dht1.readTemperature();
    h1 = dht1.readHumidity();
  }

  Input = t1;
  myPID.Compute();                    //Se hace el calculo en el PID

  if (currentMillis - previousMillis >= interval) { 
    previousMillis = currentMillis;
    // grafica
    Serial.print(46);   //linea referencia +1 grado
    Serial.print(",");   
    Serial.print(45);   //linea SetPoint
    Serial.print(","); 
    Serial.print(44);   //linea referencia -1 grado
    Serial.print(",");  
    Serial.print(Output/10);  //  /10 para mejor gráfica
    Serial.print(",");
    Serial.println(Input);   
  }


  Serial.print("Temperatura DHT11: ");
  Serial.print(t1);
  Serial.println(" ºC.");

  Serial.print("Humedad DHT11: ");
  Serial.print(h1);
  Serial.println(" %."); 

  Serial.println("-----------------------");
}

void leerdht2() {
  
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();

  while (isnan(t2) || isnan(h2)){
    Serial.println("Lectura fallida en el sensor DHT22, repitiendo lectura...");
    delay(2000);
  
  }

  Serial.print("Temperatura DHT22: ");
  Serial.print(t2);
  Serial.println(" ºC.");

  Serial.print("Humedad DHT22: ");
  Serial.print(h2);
  Serial.println(" %."); 

  Serial.println("-----------------------");
}
