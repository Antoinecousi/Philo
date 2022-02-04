/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:13:43 by acousini          #+#    #+#             */
/*   Updated: 2022/02/03 19:13:35 by acousini         ###   ########.fr       */
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
	printf("HERE IS MY CLEAN BASE : \n");
	if (base)
	{
		if (base->malloced == 1)
		{
			while (&base->philosophers[i] && i < base->nb_phils)
			{
				printf("i is %d\n", i);
				clean_each_philosopher(&base->philosophers[i]);
				i++;
			}
			if (base->malloced == 1)
			{
				free(base->philosophers);
				printf("i freed philosophers %d\n", base->malloced);
			}
		}
		pthread_mutex_destroy(&base->screen_lock);
		pthread_mutex_destroy(&base->die_lock);
		pthread_mutex_destroy(&base->running_check);
		printf("cleaned mutexes\n");
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
	clean_base(base, 2, " SUCCESS  FRR\n");
	return (0);
}
