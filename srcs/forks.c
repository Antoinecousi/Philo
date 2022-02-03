/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:37:34 by acousini          #+#    #+#             */
/*   Updated: 2022/02/03 14:36:09 by acousini         ###   ########.fr       */
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
	printf("FORK NUMBER %d INITIADED\n", i + 1);
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
		pthread_mutex_lock(philo->left_fork);
		mutex_screen(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		mutex_screen(philo, "has taken a fork\n");
		philo->last_meal = time_from_beginning(philo->base->start);
		mutex_screen(philo, "is eating\n");
		philo->meals_count++;
		wait_in_ms(philo->base->tte);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		mutex_screen(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		mutex_screen(philo, "has taken a fork\n");
		philo->last_meal = time_from_beginning(philo->base->start);
		mutex_screen(philo, "is eating\n");
		philo->meals_count++;
		wait_in_ms(philo->base->tte);
	}
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
