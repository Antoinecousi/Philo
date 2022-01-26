/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:56:30 by acousini          #+#    #+#             */
/*   Updated: 2022/01/26 17:08:14 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_time(t_base *base)
{
	gettimeofday(&base->start, NULL);
	if (!base->start.tv_sec)
		return (1);
}

int	init_philosopher(t_base *base)
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
	base->ttd = ft_atoi(str[2]);
	if (base->ttd <= 0)
		return (clean_base(base, -2, "Wrong value of time to die. Exit\n"));
	base->tte = ft_atoi(str[3]);
	if (base->tte <= 0)
		return (clean_base(base, -2, "Wrong value of time to eat. Exit\n"));
	base->tts = ft_atoi(str[4]);
	if (base->tts <= 0)
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
	init_philosopher(base);
	base->start = now();
	return (0);
}
