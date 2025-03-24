# Procesos vs. Hilos: Una Breve Explicación

Este proyecto, **PHILOSOPHERS** de 42, se centra en la concurrencia y la gestión de tareas. Para entender mejor cómo funciona, es útil comprender las diferencias fundamentales entre **procesos** e **hilos**.

## Procesos

* Cada proceso posee su propio **espacio de memoria**, su propio **conjunto de registros** y su propio **contexto de ejecución**.
* Se ejecutan de forma **independiente** y **no comparten memoria** entre sí por defecto.
* La **comunicación entre procesos** requiere mecanismos explícitos como **pipes** o **sockets**.

## Hilos

* Los hilos **comparten el mismo espacio de memoria y recursos** que su proceso padre.
* Esto permite una **comunicación más eficiente** entre hilos al acceder directamente a variables compartidas.
* Sin embargo, es crucial **sincronizar el acceso a los datos compartidos** para evitar **condiciones de carrera (Data Race)** y otros problemas de concurrencia.

## Diferencias Clave

La principal distinción radica en su **creación y gestión**:

* Los **procesos** se crean utilizando la llamada al sistema `fork()`, que genera una copia exacta del proceso padre.
* Los **hilos** se crean **dentro de un proceso existente** mediante el uso de una biblioteca de hilos, como **POSIX Threads (pthread)** en C++.

## Estados de un Hilo

Se refiere a todas las diferentes etapas por las que pasa un hilo mientras este vivo; determina lo que puede hacer el hilo 
en ese momento.

* Nuevo (New): Cuando se crea un hilo pero aún no se ha iniciado. En este estado, el hilo aún no ha asignado recursos ni ha comenzado su ejecución.

* Ejecutable (Runnable): El hilo está listo para ser ejecutado y está esperando que el planificador del sistema operativo le asigne tiempo de CPU. Puede haber varios hilos en estado ejecutable esperando su turno para ejecutarse.

* En ejecución (Running): El hilo está actualmente en ejecución, utilizando la CPU para realizar sus tareas. Solo un hilo puede estar en estado de ejecución en un solo núcleo de CPU en un momento dado.

* Bloqueado (Blocked) o Esperando (Waiting): El hilo está temporalmente inactivo y no puede continuar su ejecución hasta que se cumpla alguna condición o se libere algún recurso. Esto puede ocurrir por varias razones, como esperar la finalización de otra tarea, adquirir un bloqueo o esperar una señal.

* En espera con tiempo (Timed Waiting): Similar al estado de espera, pero el hilo está esperando durante un período de tiempo limitado. Después de que expira el tiempo, el hilo vuelve al estado ejecutable.

* Terminado (Terminated): El hilo ha completado su ejecución y ya no está activo. Ha finalizado su tarea y ha liberado los recursos que tenía asignados.

## Sobre el Proyecto "PHILOSOPHERS" de 42

Este proyecto, **PHILOSOPHERS**, probablemente implementa un problema clásico de concurrencia. [Aquí puedes añadir una breve descripción de lo que hace tu proyecto específico, por ejemplo: "En este proyecto, simulamos el problema de los filósofos comiendo, donde varios filósofos compiten por recursos compartidos (tenedores) para comer."].
