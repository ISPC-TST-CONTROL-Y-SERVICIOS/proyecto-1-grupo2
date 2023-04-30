#include <DHT.h> //Libreria DHT
#include <DHT_U.h>  //Libreria DHT
#include <LiquidCrystal.h>  //Libreria LCD

// Definir constantes
const int DHT_PIN_1 = 14;
const int DHT_PIN_2 = 15;
const int ACTUATOR_PIN = 13;
const int BAUD_RATE = 9600;
const int SETPOINT = 23;

// Definir variables globales
DHT dht1(DHT_PIN_1, DHT22);
DHT dht2(DHT_PIN_2, DHT22);
double input, input2, output, integral, prev_error;
//int humidity;
//float tempC;

// Define los port del LCD y su relación en el ESP32
int V0 = 32; 
int RS = 22;
int E = 23;
int D4 = 21;
int D5 = 19;
int D6 = 18;
int D7 = 5;
LiquidCrystal lcd (RS, E, D4, D5, D6, D7);

// Definir funciones
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(ACTUATOR_PIN, OUTPUT);
  dht1.begin();
  dht2.begin();


//  analogWrite(V0, 150); // Ahorro uso del potenciometro para lcd
  lcd.begin(16,2);  // Inicializa LCD

}

void loop() {
  // Leer la temperatura de los sensores
  float temperature1 = dht1.readTemperature();
  float temperature2 = dht2.readTemperature();
  float Humidity1 = dht1.readHumidity();
  float Humidity2 = dht2.readHumidity();

  //humidity = dht1.readHumidity();  // Toma lectura de Humedad del DHT1
  //tempC = dht1.readTemperature();  // Toma lectura de Temperatura del DHT1

  // Calcular la entrada del controlador PI como la media de las dos temperaturas
  input = (temperature1 + temperature2) / 2.0;
  input2 = (Humidity1 + Humidity2) / 2.0;

  // Calcular la salida del controlador PI
  double error = SETPOINT - input;
  integral += error;
  output = 10.0 * error + 0.5 * integral;

  // Limitar la salida del controlador PI a un rango adecuado
  output = constrain(output, 0.0, 1.0);

  // Actualizar el estado del actuador
  digitalWrite(ACTUATOR_PIN, output > 0.5);

  // Imprimir información de depuración
  
  Serial.print("Temperatura Ambiente: ");
  Serial.println(input);
  Serial.print("Output: ");
  Serial.println(output);

  lcd.setCursor(0, 0);  // Setea Posición inicial cursor Columna 0 Fila 0
  lcd.print("Temp. = ");
  lcd.print(input);
  lcd.print(" *C");

  lcd.setCursor(0, 1);  // Setea Posición inicial cursor Columna 0 Fila 1 
  lcd.print("Hume. = ");
  lcd.print(input2);
  lcd.print(" %");

  delay(500);
  lcd.clear();
  //lcd.scrollDisplayLeft();
 }
