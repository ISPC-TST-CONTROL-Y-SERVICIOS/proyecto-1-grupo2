![Proyecto #1 - Proyecto](https://user-images.githubusercontent.com/46485082/231865472-c5512f07-7ed4-4264-a168-755b2fdeed73.png)



## $\textcolor{orange}{Descripción\ del\ proyecto:}$

Control de temperatura

Para el desarrollo de este proyecto se tomó como referencia un departamento de dos ambientes que cuenta con un sistema de control de temperatura centralizado.

Locación donde se utilizará el sistema:

![image](https://user-images.githubusercontent.com/46485082/232330151-95e00975-c406-459d-9b26-b272c60c4625.png)

En la imagen siguiente, las flechas negras indican la ubicación de los actuadores y las flechas azules la de los sensores.

![image](https://user-images.githubusercontent.com/46485082/232330179-7fc4ff5d-1a46-4858-99cd-7c98618b0e98.png)

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

El sensor de temperatura propuesto es el  DS18B20, el mismo es un dispositivo digital de medición de temperatura de alta precisión que utiliza una interfaz de 
bus serie de 1 cable 
(protocolo 1 Wire de Dasllas Semiconductor) . 
Es capaz de medir temperaturas en un rango de -55 °C a 125 °C con una precisión de ± 0.5 °C. 

Algunas de sus ventajas son:

* Comunicación de datos a través de un solo cable, lo que simplifica su conexión y reduce el costo del sistema.
* No necesita calibración debido a su alta precisión y bajo error de medición.
* Es resistente al agua y puede ser sumergido en líquidos.
* Es compatible con una amplia variedad de microcontroladores y dispositivos electrónicos.

Algunas de sus desventajas en comparación con otros sensores de temperatura son:

* El rango de medición es menor en comparación con otros sensores de temperatura.
* Es más costoso en comparación con algunos sensores de temperatura analógicos.
* No tiene una respuesta de temperatura inmediata ya que necesita un tiempo para alcanzar la estabilidad térmica.
* No tiene la capacidad de medir la temperatura de la superficie en contacto con el sensor.

![image](https://user-images.githubusercontent.com/46485082/232333839-a2e7106b-7764-4c70-a872-2db3823f146c.png)


## $\textcolor{orange}{Esquema\ electrico\ del\ controlador:}$




## $\textcolor{orange}{PAPERS:}$


En esta carpeta encontraran documentacion de soporte de los diferentes componentes del proyecto.
