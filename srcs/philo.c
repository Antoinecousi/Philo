/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:13:43 by acousini          #+#    #+#             */
/*   Updated: 2022/01/28 20:03:17 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	if (philo->base->is_dead == 1)
		return (philo->id);
	if (philo->last_meal + philo->base->ttd >= time_now_in_ms())
	{
		philo->base->is_dead = philo->id;
		return (philo->id);
	}
	return (0);
}

int	can_eat(t_philo *philo)
{
	if (is_dead(philo))
}

void	routine(t_philo *philo)
{
	while (philo->base->is_dead == 0)
	{
		if (can_eat(philo))
		{
			philo_start_eat(philo);
			philo_start_sleep(philo);
			philo_start_thinking(philo);
		}
	}
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
	wait_in_ms(1);
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
	return (0);
}

int	fill_philo(t_base *base)
{
	int		id;

	id = -1;
	while (++id < base->nb_phils)
		if (init_fork(base, id))
			return (clean_base(base, 2, "Init fork error. Exit.\n"));
	id = -1;
	while (++id < base->nb_phils)
		if (init_each_philo(base, id))
			return (clean_base(base, 2, "init_each_philo error. Exit.\n"));
	id = -1;
	while (++id < base->nb_phils)
		if (pthread_join(base->philosophers[id].thread_id, NULL) == -1)
			return (clean_base(base, 2, "pthread_join error. Exit.\n"));
}

int	main(int argc, char **argv)
{
	t_base	*base;

	if (!(argc >= 5 && argc <= 6))
		return (write(1, "Usage is ./philo Philnbr TTDie TTE TTS EatTot", 48));
	base = malloc(sizeof(t_base));
	if (!base)
		return (write(1, "Couldn't malloc struct in main. Exit\n", 38));
	if (fill_base(base, argv + 1))
		return (1);
	if (fill_philo(base))
		return (2);
	gettimeofday(&base->start, NULL);
	init_pthread();
	return (0);
}
