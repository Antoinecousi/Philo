/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:56:30 by acousini          #+#    #+#             */
/*   Updated: 2022/02/02 19:00:57 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_each_philo(t_base *base, int id)
{
	int		reader;

	base->printed_death = 0;
	base->philosophers[id].last_meal = 0;
	base->philosophers[id].meals_count = 0;
	base->philosophers[id].base = base;
	reader = pthread_create(&(base->philosophers[id].thread_id),
			NULL, &routine, &(base->philosophers[id]));
	return (reader);
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
	{
		if (init_each_philo(base, id))
			return (clean_base(base, 2, "init_each_philo error. Exit.\n"));
	}
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
		base->philosophers[i].alive = 1;
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
	base->running = 1;
	base->start = time_now_in_ms();
	init_philosopher(base);
	return (0);
}
