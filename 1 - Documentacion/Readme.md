![Proyecto #1 - Proyecto](https://user-images.githubusercontent.com/46485082/231865472-c5512f07-7ed4-4264-a168-755b2fdeed73.png)



## $\textcolor{orange}{Descripción\ del\ proyecto:}$

Control de temperatura

Para el desarrollo de este proyecto se tomó como referencia un departamento de dos ambientes que cuenta con un sistema de control de temperatura centralizado.

Locación donde se utilizará el sistema:

![image](https://user-images.githubusercontent.com/46485082/232330151-95e00975-c406-459d-9b26-b272c60c4625.png)

En la imagen siguiente, las flechas negras indican la ubicación de los actuadores y las flechas azules la de los sensores.

![image](https://user-images.githubusercontent.com/46485082/235246291-2ebb14f0-7052-40ea-b790-83b55cadb9e6.png)



Para el modelado matemático se tomo en cuenta que un sistema derivativo (D) o PID representaría variaciones muy amplias debido que en los momentos donde se activa el actuador se produce un cambio repentino de temperatura, por lo tanto, el error es considerablemente grande en ese periodo de tiempo. Teniendo esto en cuenta, se procedió al desarrollo de un sistema proporcional e integral (PI). El código para el control del sistema es el siguiente:


```python
import numpy as np
import matplotlib.pyplot as plt

class CasaInteligente:
    def __init__(self, temperatura_inicial, K, tau):
        self.temperatura_actual = temperatura_inicial
        self.temperatura_deseada = temperatura_inicial
        self.historial_temperaturas = [temperatura_inicial]
        self.K = K
        self.tau = tau
        self.dt = 1.0 / 60  # Paso de tiempo en horas (1 minuto)
        self.error_integral = 0
        self.error_anterior = 0

    def actualizar_temperatura(self, nueva_temperatura):
        self.temperatura_actual = nueva_temperatura
        self.historial_temperaturas.append(nueva_temperatura)

    def controlador_pi(self, Kp, Ki):
        error = self.temperatura_deseada - self.temperatura_actual
        self.error_integral += error * self.dt
     

        u = Kp * error + Ki * self.error_integral
        self.error_anterior = error
        return u

    def simular_dia(self, temperatura_deseada, Kp, Ki):
        self.temperatura_deseada = temperatura_deseada
        for _ in range(24 * 60):  # Simular durante 24 horas en intervalos de 1 minuto
            u = self.controlador_pi(Kp, Ki)
            dydt = (self.K * u - self.temperatura_actual) / self.tau
            nueva_temperatura = self.temperatura_actual + dydt * self.dt
            self.actualizar_temperatura(nueva_temperatura)

    def graficar_temperaturas(self):
        plt.plot(np.arange(len(self.historial_temperaturas)) / 60, self.historial_temperaturas, label="Temperatura")
        plt.axhline(self.temperatura_deseada, color="r", linestyle="--", label="Temperatura deseada")
        plt.xlabel("Hora")
        plt.ylabel("Temperatura (°C)")
        plt.title("Control de temperatura en una casa inteligente")
        plt.legend()
        plt.ylim(21,23)
        plt.xlim(0,1)
        plt.show()

def main():
    casa = CasaInteligente(27, K=10, tau=3)
    casa.simular_dia(22, Kp=10, Ki=7)  #90,0.1,0
    casa.graficar_temperaturas()

if __name__ == "__main__":
    main()


```

El gráfico del comportamiento queda de la siguiente manera:

![image](https://user-images.githubusercontent.com/46485082/232332772-fda8ed1e-7f97-4ae8-a67e-85b9c0308c31.png)


Como se ve en el gráfico, la curva es considerablemente suave como para no percibir cambios abruptos de temperatura.



## $\textcolor{orange}{Descripcion\ del\ principio\ de\ funcionamiento:}$

El controlador PID (Proporcional-Integral-Derivativo) es un algoritmo utilizado para controlar sistemas en tiempo real, incluyendo sistemas de refrigeración. El objetivo del controlador es ajustar automáticamente la cantidad de enfriamiento suministrada por el sistema para mantener una temperatura deseada.

En el caso de la refrigeración con dos sensores DHT11 y DHT22 y una placa de desarrollo ESP32, los sensores miden la temperatura y la humedad ambiente, y envían esta información a la placa ESP32. La placa utiliza esta información para calcular el error entre la temperatura deseada y la temperatura actual, y luego ajusta la cantidad de enfriamiento proporcionado por el sistema de refrigeración para minimizar ese error.

El control PID utiliza tres parámetros: la ganancia proporcional, la ganancia integral y la ganancia derivativa. Estos parámetros ajustan la cantidad de corrección que se aplica al sistema en función de la magnitud y la dirección del error. En otras palabras, si el error es grande y está aumentando, el controlador aumentará la cantidad de enfriamiento proporcionada para corregirlo. Si el error es pequeño y está disminuyendo, el controlador reducirá la cantidad de enfriamiento para evitar sobrecorrección.

En resumen, el control PID para refrigeración con dos sensores DHT11 y DHT22 y una placa de desarrollo ESP32 utiliza la información de los sensores para ajustar automáticamente la cantidad de enfriamiento proporcionada por el sistema para mantener una temperatura deseada, y utiliza una combinación de ganancia proporcional, ganancia integral y ganancia derivativa para minimizar el error y evitar sobrecorrección.



## $\textcolor{orange}{Eleccion\ de\ la\ placa\ de\ desarrollo:}$

La placa base para el desarrollo es la ESP32.
El ESP32 es una placa de desarrollo de bajo costo y alto rendimiento basada en un chip de microcontrolador de doble núcleo Tensilica LX6 de 32 bits.
Es una plataforma popular para proyectos de Internet de las cosas (IoT) debido a sus capacidades Wi-Fi, Bluetooth y bajo consumo de energía.


Algunas de sus ventajas son:

* Es fácil de programar y es compatible con el entorno de desarrollo integrado (IDE) de Arduino.
* Es una placa de desarrollo muy económica en comparación con otras plataformas de hardware similares.
* Tiene un bajo consumo de energía y puede operar con baterías durante un largo período de tiempo.
* Tiene una capacidad incorporada de Wi-Fi y Bluetooth, lo que lo hace fácilmente conectable a otros dispositivos IoT.

Algunas de sus desventajas en comparación con otras placas de desarrollo son:

* La memoria RAM disponible es limitada, lo que puede ser una limitación para algunos proyectos.
* No tiene soporte para comunicación de alta velocidad, como USB 3.0.
* Aunque es compatible con Arduino, no tiene una comunidad tan grande como otras placas de desarrollo de código abierto.


![ESP32](https://user-images.githubusercontent.com/46485082/232334510-c55dec8f-d9e6-456f-92dc-0de1c38f7594.png)


## $\textcolor{orange}{Sensores\ y\ Actuadores:}$

Tanto el sensor DHT11 como el DHT22 son sensores de humedad y temperatura de la familia de sensores digitales de un solo cable de la marca "Aosong". Ambos sensores utilizan un termistor para medir la temperatura y un sensor capacitivo para medir la humedad relativa del aire.

El DHT11 es el modelo más básico y económico de los dos, y tiene una precisión de ± 2 grados Celsius para la medición de temperatura y ± 5% de humedad relativa para la medición de humedad. Tiene un rango de medición de 0 a 50 grados Celsius para la temperatura y del 20% al 80% para la humedad relativa.

Por otro lado, el DHT22 tiene una mayor precisión que el DHT11, con una precisión de ± 0.5 grados Celsius para la medición de temperatura y ± 2% de humedad relativa para la medición de humedad. Tiene un rango de medición de -40 a 80 grados Celsius para la temperatura y del 0% al 100% para la humedad relativa.

Ambos sensores son ampliamente utilizados en proyectos de electrónica y robótica para medir la temperatura y la humedad del ambiente, y son compatibles con una amplia gama de microcontroladores y placas de desarrollo, como la ESP32 mencionada anteriormente.

![image](https://user-images.githubusercontent.com/46485082/233860876-b120d3d3-ec9e-474c-adc5-ccb7ecfc0a25.png)

Como actuador se utiliza un rele del tipo HK4100F, el cual proporciona una corriente maxima de 3A/250VCA, lo cual es suficiente para comandar cualquier otro actuador de mayor potencia como ser algun contactor.


![conexion-rele](https://user-images.githubusercontent.com/46485082/233861167-1db9fb50-9c41-4def-a076-9b08ac166d65.png)


## $\textcolor{orange}{Esquema\ electrico\ del\ controlador:}$

> __Note__ :

Aqui se agrega  el esquema electrico del dispositivo.


## $\textcolor{orange}{PAPERS:}$


En esta carpeta encontraran documentacion de soporte de los diferentes componentes del proyecto.
