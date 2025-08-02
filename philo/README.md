# 🧘 Philosophers - 42 Project

## 📚 Descripción

Este proyecto es una simulación del problema clásico de los **filósofos comensales**, un ejercicio de sincronización concurrente. A través de hilos y mutexes, buscamos evitar condiciones de carrera, *deadlocks* y *starvation* mientras varios filósofos comparten recursos limitados (tenedores).

## 🧩 Objetivo del proyecto

- Comprender el uso de **threads** y **mutexes**.
- Evitar condiciones de carrera (*race conditions*).
- Prevenir *deadlocks* y *starvation*.
- Implementar una simulación segura, precisa y eficiente.

## 🛠️ Compilación

Este proyecto se compila usando un `Makefile`. Para compilar, utiliza:

```bash
make
make clean     # Elimina archivos objeto
make fclean    # Elimina objetos y binarios
make re        # Limpia y recompila todo
make norminette # Para lanzar el comando norminette en todos los ficheros que se debe en el programa
```

## 🚀 Uso
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional number meals]
```

## Ejemplo
```bash
./philo 5 800 200 200 3
./philo 3 310 103 103
```

## Explicación
Esto lanza una simulación con:
- 5 filósofos
- Cada filósofo muere si no come en 800ms
- Cada filósofo tarda 200ms en comer
- Cada filósofo duerme 200ms después de comer

**Argumento opcional**: Si se proporciona, la simulación termina cuando cada filósofo haya comido esa cantidad de veces.

## ✅ Normas cumplidas
- Cumple con la Norminette.
- No se usan funciones prohibidas (sleep, printf, etc., según lo permitido por el proyecto).
- Comprobado sin fugas de memoria ni errores con valgrind.
