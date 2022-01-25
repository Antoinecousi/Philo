/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:56:30 by acousini          #+#    #+#             */
/*   Updated: 2022/01/25 19:28:40 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_fork(t_base *base, int i)
{
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork)
		return (destroy(base, -3, "Malloc error. Exit\n"));
	if (pthread_mutex_init(fork, NULL) != 0)
		return (-1);
	base->philosophers[i].left_fork = fork;
	if (i > 0)
		base->philosophers[i - 1].right_fork = base->philosophers[i].left_fork;
	if (i == base->nb_phils - 1)
		base->philosophers[i].right_fork = base->philosophers[0].left_fork;
	base->inited += 1;
	return (0);
}

int	init_philosophers(t_base *base)
{
	t_philo	*phil;
	int		i;

	i = -1;
	phil = malloc(sizeof(t_philo));
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

int	fill_base(t_base *base, char **str)
{
	base->nb_phils = ft_atoi(str[1]);
	base->is_dead = 0;
	if (base->nb_phils < 1)
		return (clean_base(base, -2, "Wrong number of philosophers. Exit\n"));
	base->t_to_die = ft_atoi(str[2]);
	if (base->t_to_die <= 0)
		return (clean_base(base, -2, "Wrong value of time to die. Exit\n"));
	base->t_to_eat = ft_atoi(str[3]);
	if (base->t_to_eat <= 0)
		return (clean_base(base, -2, "Wrong value of time to eat. Exit\n"));
	base->t_to_sleep = ft_atoi(str[4]);
	if (base->t_to_sleep <= 0)
		return (clean_base(base, -2, "Wrong value of time to sleep. Exit\n"));
	if (str + 5)
	{
		base->nb_eats = ft_atoi(str[5]);
		if (base->nb_eats <= 0)
			return (clean_base(base, -2, "Wrong value of meals needed. Exit"));
	}
	else
		base->nb_eats = -1;
	base->is_dead = -1;
	init_philosophers(base);
	base->start = now();
	return (0);
}
