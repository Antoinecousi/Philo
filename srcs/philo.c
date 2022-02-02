/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:13:43 by acousini          #+#    #+#             */
/*   Updated: 2022/02/01 14:58:56 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_each_philosopher(t_philo *philo)
{
	pthread_mutex_destroy(philo->left_fork);
	free(philo->left_fork);
}

int	clean_base(t_base *base, int error, char *str)
{
	int		i;

	i = 0;
	(void)error;
	if (base)
	{
		pthread_mutex_destroy(&base->screen_lock);
		pthread_mutex_destroy(&base->die_lock);
		while (&base->philosophers[i])
			clean_each_philosopher(&base->philosophers[i++]);
		if (base->malloced == 1)
			free(base->philosophers);
		free(base);
	}
	ft_putstr(str);
	return (1);
}

int	main(int argc, char **argv)
{
	t_base	*base;

	if (!(argc >= 5 && argc <= 6))
		return (write(1, "Usage is ./philo phil_nbr tts tte tts totalmeal"
				, 48));
	base = malloc(sizeof(t_base));
	if (!base)
		return (write(1, "Couldn't malloc struct in main. Exit\n", 38));
	if (fill_base(base, argv + 1, argc))
		return (1);
	pthread_mutex_init(&base->screen_lock, NULL);
	pthread_mutex_init(&base->die_lock, NULL);
	if (fill_philo(base))
		return (2);
	write(1, "SUCCESS", 8);
	// init_pthread();
	return (0);
}
