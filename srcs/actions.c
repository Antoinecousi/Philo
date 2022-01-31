/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:07:32 by acousini          #+#    #+#             */
/*   Updated: 2022/01/31 20:39:13 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	is_dead(t_philo *philo)
{
	if (philo->base->is_dead == 1)
		return (philo->id);
	if (philo->last_meal + philo->base->ttd < time_from_beginning(philo->base->start))
	{
		philo->base->is_dead = philo->id;
		return (philo->id);
	}
	return (0);
}

int	can_eat(t_philo *philo)
{
	int		dead;

	dead = is_dead(philo);
	if (philo->base->nb_phils == 1)
	{
		mutex_screen(philo, "has taken a fork\n");
		while (dead == 0)
		{
			dead = is_dead(philo);
			wait_in_ms(1);
		}
		return (1);
	}
	if (dead > 0)
		return (dead);
	return (0);
}

void	philo_start_thinking(t_philo *philo)
{
	int		i;

	i = is_dead(philo);
	if (i == 0 && philo->base->is_dead == 0)
		output_state(philo, "is thinking\n");
	else
		write_dead(philo);
}

void	philo_start_sleep(t_philo *philo)
{
	int		i;

	i = is_dead(philo);
	if (i == 0 && philo->base->is_dead == 0)
	{
		output_state(philo, "is eating\n");
		wait_in_ms(philo->base->tts);
	}
	else
		write_dead(philo);
}

int	take_forks(t_philo *philo, )

void	philo_start_eat(t_philo *philo)
{
	int		i;

	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		mutex_screen(philo, "has taken right fork\n");
		pthread_mutex_lock(philo->left_fork);
		mutex_screen(philo, "has taken left fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		mutex_screen(philo, "has taken left fork\n");
		pthread_mutex_lock(philo->right_fork);
		mutex_screen(philo, "has taken right fork\n");
	}
	i = is_dead(philo);
	if (i > 0)
		write_dead(philo);
	else
	{
		philo->last_meal = time_from_beginning(philo->base->start);
		mutex_screen(philo, "is eating\n");
		wait_in_ms(philo->base->tte);
		philo->meals_count++;
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
