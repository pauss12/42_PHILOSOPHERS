

En este caso, el caso especifico es que una vez, los philos hayan comido `times_each_philosopher_must_eat` veces; la simulacion debe acaba, sin lanzar un mensaje

```bash

void *routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;

	# El hilo se queda bloqueado aqui
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);
	
	# Cada hilo mande un mensaje (Se esta creando 3 hilos)
	if (philo->id_philo == 1)
	{
		print_message_philo(philo, "A -");
	}
	else if (philo->id_philo == 2)
	{
		usleep(1000);
		print_message_philo(philo, "B -");
	}
	else if (philo->id_philo == 3)
	{
		usleep(2000);
		print_message_philo(philo, "C -");
	}

	return (NULL);
}


# --------------------------------------------------------------------------

void *routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;
	int			i;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;

	i = 0;
	
	# El hilo se queda bloqueado aqui. Esto se realiza para sincronizar los hilos.
	# Cada uno de los hilos que entre aqui, va a quedarse ahi bloqueado, hasta que 
	# termine las iteraccion de creacion.
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);

	
	while (1)
	{
		if (philo->id_philo == 1)
		{
			if (i == philo->times_each_philosopher_must_eat)
			{
				data->is_dead = 1;
				print_message_philo(philo, "PHILO A HA MUERTO");
				break ;
			}
			print_message_philo(philo, "A -");
		}
		else if (philo->id_philo == 2)
		{
			usleep(1000);
			print_message_philo(philo, "B -");
		}
		else if (philo->id_philo == 3)
		{
			usleep(2000);
			print_message_philo(philo, "C -");
		}
		if (data->is_dead == 1)
			break ;
		i++;
	}
	return (NULL);
}

# -------------------------------------------------------------------------------------

void *routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;
	int			i;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;

	i = 0;
	
	//El hilo se queda bloqueado aqui
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);

	
	while (1)
	{
		if (philo->id_philo == 1)
		{
			if (i == philo->times_each_philosopher_must_eat)
			{
				data->is_dead = 1;
				break ;
			}
			print_message_philo(philo, "A -");
		}
		else if (philo->id_philo == 2)
		{
			if (ft_sleep(1000, data) == 1)
				break ;
			print_message_philo(philo, "B -");
		}
		else if (philo->id_philo == 3)
		{
			if (ft_sleep(2000, data) == 1)
				break ;
			print_message_philo(philo, "C -");
		}
		if (data->is_dead == 1)
			break ;
		i++;
	}
	return (NULL);
}

```

```bash
void create_threads(t_data *data)
{
	int			i;

	i = 0;
	ft_printf("Creating threads...\n");
	
	# Se bloquea antes de la creacion de los hilos para poder sincronizarlos antes de entrar a la rutina.
	pthread_mutex_lock(&data->init);
	while (i < data->num_philos)
	{
		# En cada creacion del hilo con el `pthread_create`; se le pasa un puntero a la rutina, para decirle que
		# esa es la funcion que va a tener que ejecutar cada uno de los hilos creados.
		data->philo[i].data = (struct t_data *)data;
		if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]) != 0)
			print_error("Error creating philosopher thread");
		i++;
	}

	printf("Threads created successfully.\n");

	# Se desbloquea el mutex para que puedan iniciar a hacer la rutina.
	pthread_mutex_unlock(&data->init);

	# Comprueba si alguien ha muerto. El proceso es el que va a comprobar si todos los hilos 
	# siguen vivos.
	check_status(data);

	# Wait for all threads to finish. Joineandolos.
	wait_for_threads(data);
}
```

```bash
int main(int argc, char *argv[])
{
	t_data	data;

	# Checkeas argumentos, el parseo y que te manden la informacion correcta
    # Inicializas la estructura
    #  Inicializas los philos, junto con el array de philos
	create_threads(data);

    return (0);
}
```