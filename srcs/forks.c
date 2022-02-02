/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:37:34 by acousini          #+#    #+#             */
/*   Updated: 2022/02/02 20:06:13 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
	ft_putstr("FORK INITIADED\n");
	return (0);
}

int	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	if (is_dead(philo) == 0 || is_running(philo) == 0)
		return (0);
	pthread_mutex_lock(fork);
	mutex_screen(philo, "has taken a fork\n");
	return (1);
}

int	take_forks(t_philo *philo)
{
	int		right;	

	right = philo->id + 1;
	if (right == philo->base->nb_phils)
		right = 0;
	if (philo->base->nb_phils == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		mutex_screen(philo, "has taken a fork\n");
		philo->last_meal = time_from_beginning(philo->base->start);
		pthread_mutex_unlock(&philo->meal_check);
	}
	else if ((philo->id + 1) % 2 == 0)
	{
		mutex_screen(philo, "IS GONNA TAKE HIS OWN FORK\n");
		take_fork(philo->left_fork, philo);
		if (take_fork(philo->right_fork, philo) == 0)
		{
			mutex_screen(philo, "wtf\n");
			pthread_mutex_unlock(philo->left_fork);
		}
		mutex_screen(philo, "is eating\n");
		philo->meals_count++;
		philo->last_meal = time_from_beginning(philo->base->start);
		wait_in_ms(philo->base->tte);
		mutex_screen(philo, "proceeds to unlock\n");
	}
	else
	{
		mutex_screen(philo, "IS GONNA TAKE HIS OWN FORK\n");
		take_fork(philo->right_fork, philo);
		if (take_fork(philo->left_fork, philo) == 0)
		{
			mutex_screen(philo, "wtf\n");
			pthread_mutex_unlock(philo->right_fork);
		}
		mutex_screen(philo, "is eating\n");
		philo->meals_count++;
		philo->last_meal = time_from_beginning(philo->base->start);
		wait_in_ms(philo->base->tte);
	}
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		mutex_screen(philo, "\t\thas unlocked LEFT\n");
		pthread_mutex_unlock(philo->right_fork);
		mutex_screen(philo, "\t\tunlocked RIGHT\n");
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		mutex_screen(philo, "\t\tunlocked RIGHT\n");
		pthread_mutex_unlock(philo->left_fork);
		mutex_screen(philo, "\t\tunlocked LEFT\n");
	}
}
