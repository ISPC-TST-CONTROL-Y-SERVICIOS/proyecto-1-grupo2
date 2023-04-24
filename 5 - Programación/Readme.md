![Proyecto #1 - Programacion](https://user-images.githubusercontent.com/46485082/231872302-e02cab2e-70a4-4308-81c2-8824a3f705de.png)






## $\textcolor{orange}{Lenguaje\ de\ programacion:}$

> __Note__ : Describir brevemente el lenguaje elegido para la programacion.



## $\textcolor{orange}{Sistema\ de\ control:}$

> __Note__ : Describir brevemente el principio sobre el cual se basa el dispositivo.




## $\textcolor{orange}{Librerias:}$

> __Note__ : Mencionar las librerias que se utilizan para que el desarrollo pueda funcionar correctamente.



## $\textcolor{orange}{Codigo:}$

> __Note__ : Se agrega codigo en C++ en el cual se estuvo trabajando.

```c++

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHT22_1_PIN 26
#define DHT22_2_PIN 27
#define RELAY_PIN 14
#define TEMP_SET_PIN 34

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

DHT dht22_1(DHT22_1_PIN, DHT22);
DHT dht22_2(DHT22_2_PIN, DHT22);

double Kp = 2;
double Ki = 5;
double Kd = 1;
double Ts = 1;
double set_point = 25;
double integral = 0;
double error_prev = 0;
double output = 0;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  lcd.init();
  lcd.backlight();
  dht22_1.begin();
  dht22_2.begin();
}

void loop() {
  // Leer la temperatura de los sensores DHT22
  float temp1 = dht22_1.readTemperature();
  float hum1 = dht22_1.readHumidity();
  float temp2 = dht22_2.readTemperature();
  float hum2 = dht22_2.readHumidity();
  float temp_avg = (temp1 + temp2) / 2.0;

  // Leer el valor del potenciómetro en el pin 34
  int pot_value = analogRead(TEMP_SET_PIN);

  // Mapear el valor del potenciómetro al rango de temperaturas deseadas
  set_point = map(pot_value, 0, 4095, 0, 50);

  // Calcular la salida del controlador PID
  double error = set_point - temp_avg;
  integral += error * Ts;
  double derivative = (error - error_prev) / Ts;
  output = Kp * error + Ki * integral + Kd * derivative;
  error_prev = error;

  // Limitar la salida entre 0 y 100
  output = output > 100 ? 100 : output < 0 ? 0 : output;

  // Convertir la salida a un valor de 0 o 1 para el relé
  int relay_output = temp_avg >= set_point ? 1 : 0;

  // Controlar el relé con el valor de salida
  digitalWrite(RELAY_PIN, relay_output);

  // Actualizar el display LCD con la temperatura, la humedad y el seteo
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp_avg);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Set: ");
  lcd.print(set_point);
  lcd.print(" C");
  delay(1000);  
}

```




## $\textcolor{orange}{Simulacion:}$

El dispositivo fue simulado en Wokwi.

https://wokwi.com/projects/362829563574636545



## $\textcolor{orange}{PAPERS:}$

> __Note__ : En esta carpeta encontraran documentacion de soporte de los diferentes componentes del proyecto.

