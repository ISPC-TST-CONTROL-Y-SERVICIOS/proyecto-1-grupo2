import numpy as np
import matplotlib.pyplot as plt

from machine import Pin
from time import sleep
import dht 

sensor = dht.DHT11(Pin(4))

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
    casa = CasaInteligente(sensor, K=10, tau=3)
    casa.simular_dia(sensor, Kp=10, Ki=7)  #90,0.1,0
    casa.graficar_temperaturas()

if __name__ == "__main__":
    main()
