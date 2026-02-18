# 🧠 Philosophers — El Banquete de la Concurrencia

Este proyecto de la escuela **42** explora los conceptos fundamentales de **concurrencia**, **sincronización de hilos** y **gestión de recursos compartidos**.  
Tu objetivo será evitar que los filósofos **mueran de hambre** o **caigan en un deadlock**, mientras intentan comer con los mismos cubiertos.

---

## ⚙️ Procesos vs. Hilos: Una Breve Explicación

Para comprender la naturaleza del proyecto, es importante entender la diferencia entre **procesos** e **hilos**.

### 🧩 Procesos

- Cada proceso posee su propio **espacio de memoria**, **conjunto de registros** y **contexto de ejecución**.  
- Se ejecutan de manera **independiente** y **no comparten memoria** entre diferentes procesos.  
- La **comunicación entre procesos** requiere mecanismos explícitos como **pipes**, **sockets** o **colas de mensajes**.  

### 🧵 Hilos

- Los hilos **comparten el mismo espacio de memoria y recursos** que su proceso padre.  
- Permiten una **comunicación más eficiente**, accediendo directamente a las variables compartidas.  
- Es esencial **sincronizar el acceso a los datos compartidos** para evitar **condiciones de carrera (data races)** y **deadlocks**.

### 🔍 Diferencias Clave

| Característica | Procesos | Hilos |
|----------------|-----------|--------|
| Espacio de memoria | Independiente | Compartido |
| Creación | `fork()` | `pthread_create()` |
| Comunicación | IPC (pipes, sockets) | Memoria compartida |
| Rendimiento | Más pesado | Más ligero |
| Fallo en uno | No afecta a otros | Puede afectar al proceso completo |

---

## 🕹️ Estados de un Hilo

Durante su ciclo de vida, un hilo atraviesa diferentes estados que determinan su comportamiento:

- **Nuevo (New):** Creado, pero aún no iniciado.  
- **Ejecutable (Runnable):** Listo para correr, esperando tiempo de CPU.  
- **En ejecución (Running):** Actualmente ejecutando en la CPU.  
- **Bloqueado (Blocked) o Esperando (Waiting):** Pausado hasta que se cumpla una condición (liberación de un recurso, señal, etc.).  
- **En espera con tiempo (Timed Waiting):** Esperando un tiempo limitado antes de volver a ejecutarse.  
- **Terminado (Terminated):** Ha completado su tarea y liberado sus recursos.  

---

## 🍝 Sobre el Proyecto Philosophers

El **problema de los filósofos comensales** es un ejercicio clásico de sincronización creado por **Edsger Dijkstra**.  
Representa varios filósofos sentados alrededor de una mesa con un plato de comida y un tenedor entre cada uno (Es decir, un tenedor por cada filosofo en la mesa).  
Cada filósofo debe pensar y comer, pero solo puede hacerlo cuando tiene ambos tenedores.

**Tu misión** es encontrar una estrategia de sincronización eficiente que:
- Evite los **deadlocks** (cuando dos hilos se quedan infinitamente esperando ).  
- Evite la **inanición** ("starvation", es decir, cuando varios procesos o hilos nunca obtienen acceso a los recursos que necesitan para poder continuar con su ejecución).  
- Simule el comportamiento de los filósofos en tiempo real con precisión.  

---

## Reglas del Proyecto 📜

1. Todos los filosofos deben de pasar por todos los estados (comer, dormir y pensar).
2. Para que un filosofo pueda comer, necesita tener dos tenedores a la vez, el de la izquierda y el de la derecha (Simulados con recursos compartidos).
3. Evitar que los filosofos se mueran de hambre
4. Evitar las condiciones de carrera ("data race") y los bloqueos entre los filosofoso ("dead locks").

---

## ⚠️ Condiciones de Carrera (Data Race)
Una condición de carrera sucede cuando dos o más hilos o procesos acceden simultáneamente a un mismo recurso compartido (como una variable o estructura de datos) y al menos uno de ellos está modificando dicho recurso sin ninguna sincronización.
Esto puede crear comportamientos impredecibles, datos incorrectos o inconsistentes. 
Para poder evitar estas condiciones de carrera, se utilizan mutex para que vayan accediendo a esa variable de uno en uno.

---

## 🔒 Deadlock (Interbloqueo)
Es una situacion donde dos o más hilos quedan bloqueados indefinidamente, cada uno esperando que otro libere un recurso para poder continuar con la ejecución. Esto crea un ciclo de espera sin fin. En este caso, si varios filosofos estan esperando tenedores, para poder comer, que nunca se liberan porque estan siendo utilizados, hace que ninguno de los dos pueda continuar.

---

## ⛓️ Mutex
Es un mecanismo de sincronizacion fundamental en programacion concurrente que asegura que solamente un solo hilo pueda acceder a un recurso o a una sección critica a la vez; evitando errores o inconsistencias.
Cuando un hilo necesita acceder a un recurso protegido por un mutex, primero debe "adquirirlo" (bloquearlo). Si otro hilo ya tiene el mutex, el hilo solicitante esperará hasta que se libere. Luego, tras finalizar, el mutex se libera permitiendo que otros accedan

---

## 🚦 Semaforo 
Un semaforo es otro mecanismo de sincronización que controla el acceso a recursos limitados mediante un contador. A diferencia del mutex, que permite acceso exclusivo a un solo hilo, un semáforo permite que un número limitado de hilos accedan simultáneamente. El semáforo decrementa su contador al adquirir un recurso y lo incrementa al liberarlo. Cuando el contador es cero, los hilos que intentan acceder deben esperar. Esto es útil para manejar un conjunto finito de recursos, como un número limitado de tenedores en el problema de los filósofos.
Tiene dos tipologias:

1. Semaforo Nombrado

   - Es un semáforo "público" y accesible por múltiples procesos mediante un nombre en el sistema operativo.
   - Puede ser abierto y usado por cualquier proceso que conozca su nombre y tenga los permisos adecuados.
   - Es útil para sincronizar procesos independientes que no comparten memoria directamente.
   - En POSIX se crean con funciones como sem_open y son gestionados por el sistema.
   
2. Semaforo Anónimo

   - Solo existe en el espacio de memoria del proceso que lo creó, por lo que es local a ese proceso y sus hilos.
   - Para sincronizar procesos distintos con semáforos anónimos, es necesario colocarlos en una región de memoria compartida previamente creada.
   - En POSIX, se inicializan con sem_init y un parámetro pshared diferente de cero para indicar que puede ser compartido entre procesos.
   - En sistemas que no soportan memoria compartida para semáforos, se usan principalmente para sincronizar hilos dentro del mismo proceso.
  
  ---

  ## Compilación 🚀

  1. Clona el repositorio en tu máquina local

     ```bash
     git clone git@github.com:pauss12/42_PHILOSOPHERS.git
     ```

  2. Navega a la carpeta del proyecto (philo o philo bonus)
     ```bash
     cd philo
     ```
     o
     ```bash
     cd philo_bonus
     ```

  4. Compilar el proyecto
     Dentro de la carpeta, ejecutar el siguiente comando:
     ```bash
      make
      make clean     # Elimina archivos objeto
      make fclean    # Elimina objetos y binarios
      make re        # Limpia y recompila todo
      make norminette # Para lanzar el comando norminette en todos los ficheros que se debe en el programa
     ``` 

---

## Ejecución
Ejecuta el programa de la siguiente manera:
```bash
./philo <num_filosofos> <tiempo_para_morir> <tiempo_para_comer> <tiempo_para_dormir> [<num_de_comidas>]
```
o 
```bash
./philo_bonus <num_filosofos> <tiempo_para_morir> <tiempo_para_comer> <tiempo_para_dormir> [<num_de_comidas>]
```
Siendo los argumentos:
- <num_filosofos>: Número de filósofos y tenedores en la mesa.
- <tiempo_para_morir>: Tiempo máximo (en milisegundos) que un filósofo puede pasar sin comer antes de morir.
- <tiempo_para_comer>: Tiempo que un filósofo tarda en comer.
- <tiempo_para_dormir>: Tiempo que un filósofo tarda en dormir.
- <num_de_comidas> (opcional): Número de veces que cada filósofo debe comer antes de finalizar la simulación.

### Ejemplo
Ejecutar el proyecto para 3 filosofos, que tengan 310 milisegundos de vida; 103 milisegundos para comer y 103 milisegundos para dormir.

```bash
./philo 3 310 103 103
```
o
```bash
./philo_bonus 3 310 103 103
```
