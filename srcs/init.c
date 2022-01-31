/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:56:30 by acousini          #+#    #+#             */
/*   Updated: 2022/01/31 19:55:36 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *data)
{
	t_philo	*philo;
	int		dead;

	philo = (t_philo *)data;
	printf("\nPHILO nb %d created!\n", philo->id);
	while (philo->base->is_dead == 0)
	{
		dead = can_eat(philo);
		if (dead == 0)
		{
			philo_start_eat(philo);
			philo_start_sleep(philo);
			philo_start_thinking(philo);
		}
		else
			write_dead(philo);
		if (philo->meals_count >= philo->base->nb_eats)
			return (NULL);
	}
	return (NULL);
}

int	init_each_philo(t_base *base, int id)
{
	int		reader;

	base->printed_death = 0;
	base->philosophers[id].last_meal = 0;
	base->philosophers[id].meals_count = 0;
	base->philosophers[id].base = base;
	reader = pthread_create(&(base->philosophers[id].thread_id),
			NULL, &routine, &(base->philosophers[id]));
	wait_in_ms(2);
	return (reader);
}

int	init_fork(t_base *base, int i)
{
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork)
		return (1);
	if (pthread_mutex_init(fork, NULL) != 0)
		return (1);
	base->philosophers[i].left_fork = fork;
	if (i > 0)
		base->philosophers[i - 1].right_fork = base->philosophers[i].left_fork;
	if (i == base->nb_phils - 1)
		base->philosophers[i].right_fork = base->philosophers[0].left_fork;
	base->inited += 1;
	printf("FORK INITIADED\n");
	return (0);
}

int	fill_philo(t_base *base)
{
	int		id;

	id = -1;
	while (++id < base->nb_phils) 
		if (init_fork(base, id))
			return (clean_base(base, 2, "init fork error. Exit.\n"));
	id = -1;
	while (++id < base->nb_phils)
		if (init_each_philo(base, id))
			return (clean_base(base, 2, "init_each_philo error. Exit.\n"));
	id = -1;
	while (++id < base->nb_phils)
		if (pthread_join(base->philosophers[id].thread_id, NULL) == -1)
			return (clean_base(base, 2, "pthread_join error. Exit.\n"));
	return (0);
}

int	init_philosopher(t_base *base)
{
	t_philo	*phil;
	int		i;

	i = -1;
	phil = malloc(sizeof(t_philo) * base->nb_phils);
	if (!phil)
		return (clean_base(base, 2, "Malloc error. Exit\n"));
	base->malloced = 1;
	base->philosophers = phil;
	while (++i < base->nb_phils)
	{
		base->philosophers[i].base = base;
		base->philosophers[i].id = i + 1;
	}
	return (0);
}

int	fill_base(t_base *base, char **str, int i)
{
	base->nb_phils = ft_atoi(str[0]);
	base->is_dead = 0;
	if (base->nb_phils < 1)
		return (clean_base(base, -2, "Wrong number of philosophers. Exit\n"));
	base->ttd = ft_atoi(str[1]);
	if (base->ttd <= 0)
		return (clean_base(base, -2, "Wrong value of time to die. Exit\n"));
	base->tte = ft_atoi(str[2]);
	if (base->tte <= 0)
		return (clean_base(base, -2, "Wrong value of time to eat. Exit\n"));
	base->tts = ft_atoi(str[3]);
	if (base->tts <= 0)
		return (clean_base(base, -2, "Wrong value of time to sleep. Exit\n"));
	if (i == 6)
	{
		base->nb_eats = ft_atoi(str[4]);
		if (base->nb_eats <= 0)
			return (clean_base(base, -2, "Wrong value of meals needed. Exit"));
	}
	else
		base->nb_eats = -1;
	base->start = time_now_in_ms();
	init_philosopher(base);
	return (0);
}
