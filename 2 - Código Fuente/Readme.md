![Proyecto #1 - Programacion](https://user-images.githubusercontent.com/46485082/231872302-e02cab2e-70a4-4308-81c2-8824a3f705de.png)






## $\textcolor{orange}{Lenguaje\ de\ programacion:}$

El lenguaje elejido para desarrollar el codigo es C++.



## $\textcolor{orange}{Librerias\ necesarias:}$

Para el correcto funcionamiento del controlador PID, se utilizaron las siguientes librerias:

- [x] <Wire.h>
- [x] <LiquidCrystal_I2C.h>
- [x] <DHTesp.h>





## $\textcolor{orange}{Codigo:}$

> __Note__ : Se agrega codigo en C++.

```c++

#include <DHTesp.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define RELAY_PIN 14
#define TEMP_SET_PIN 34
#define LCD_ADDRESS 0x3F
#define LCD_COLUMNS 16
#define LCD_ROWS 4

DHTesp dht11_1;
DHTesp dht11_2;

const int pin1 = 26;
const int pin2 = 27;

double Kp =  8;//2
double Ki = 10; //5
double Kd = 0.08; //1
double Ts = 1;
//double set_point = 24; //OAG
double set_point = 0; //pruebo esta otra
double integral = 0;
double error_prev = 0;
double output = 0;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  //digitalWrite(RELAY_PIN, LOW);//codigo original
  digitalWrite(RELAY_PIN, HIGH); // cambio estado a HIGH
  Serial.begin(9600); //OAG
  lcd.init();
  lcd.backlight();

  dht11_1.setup(pin1, DHTesp::DHT11); // inicializo el sensor
  dht11_2.setup(pin2, DHTesp::DHT11); // inicializo el sensor

}

void loop() {


  float temp1 = dht11_1.getTemperature();
  //float hum1 = dht11_1.getHumidity();

  float temp2 = dht11_2.getTemperature();
  //float hum2 = dht11_2.getHumidity();

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
  //int relay_output = temp_avg >= set_point ? 1 : 0; // codigo original anterior

  int relay_output = temp_avg >= set_point ? 0 : 1;



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

  // Imprimir información de depuración - OAG
  
  Serial.print("Temperatura Ambiente: "); //OAG
  Serial.println(temp_avg); //OAG
  Serial.print("Set: "); //OAG
  Serial.println(set_point); //OAG
  Serial.print("La temperatura que mide el sensor 1 es:"); // MAS
  Serial.println(temp1);
  Serial.print("La temperatura que mide el sensor 2 es:"); // MAS
  Serial.println(temp2);
  Serial.print("La salida del rele esta en:"); // MAS
  Serial.println(relay_output);
 
}

```




## $\textcolor{orange}{Simulacion:}$

El funcionamiento del dispositivo se puede ver simulado en Wokwi.


https://wokwi.com/projects/362829563574636545

![image](https://user-images.githubusercontent.com/46485082/233877863-977bc1a8-0b66-4a6d-8e4f-608715918872.png)




