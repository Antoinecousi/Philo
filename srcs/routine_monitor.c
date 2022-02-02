/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:14:54 by acousini          #+#    #+#             */
/*   Updated: 2022/02/02 20:05:43 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	is_dead(t_philo *philo)
{
	int		ret;

	// ret = 1;
	// pthread_mutex_lock(&philo->alive_check);
	ret = philo->alive;
	// pthread_mutex_unlock(&philo->alive_check);
	return (ret);
}

int	is_running(t_philo *philo)
{
	int		ret;

	ret = 1;
	pthread_mutex_lock(&philo->base->running_check);
	ret = philo->base->running;
	pthread_mutex_unlock(&philo->base->running_check);
	return (ret);
}

int	has_eaten(t_philo *philo)
{
	unsigned long		last_meal;
	int					is_alive;

	is_alive = 1;
	pthread_mutex_lock(&philo->meal_check);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_check);
	if ((time_from_beginning(philo->base->start)
			- last_meal > philo->base->ttd))
	{
		pthread_mutex_lock(&philo->alive_check);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->alive_check);
		write_dead(philo);
		pthread_mutex_lock(&philo->base->running_check);
		philo->base->running = 0;
		pthread_mutex_unlock(&philo->base->running_check);
		is_alive = 0;
	}
	return (is_alive);
}

int		has_eaten_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_check);
	if (philo->meals_count == philo->base->nb_eats)
	{
		pthread_mutex_unlock(&philo->meal_check);
		return (1);
	}		
	pthread_mutex_unlock(&philo->meal_check);
	return (0);
}

void	*monitor(void *data)
{
	t_philo	*philo;
	int		dead;
	int		running;

	dead = 1;
	running = 1;
	philo = (t_philo *)data;
	while (dead && running)
	{
		dead = is_dead(philo);
		running = is_running(philo);
		if (has_eaten(philo) == 0)
			break ;
		if (has_eaten_enough(philo))
			break ;
		usleep(100);
	}
	return (NULL);
}

void	*only_one_phil(t_philo *philo)
{
	int		alive;
	int		running;
	
	running = 1;
	alive = 1;
	mutex_screen(philo, "has taken a fork\n");
	while (alive && running)
	{
		alive = is_dead(philo);
		running = is_running(philo);
		wait_in_ms(1);
	}
	write_dead(philo);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	dead_check;

	philo = (t_philo *)data;
	if (philo->base->tte >= philo->base->ttd && (philo->id + 1) % 2 == 1)
	{
		usleep(philo->base->ttd * 1001);
		write_dead(philo);
	}
	if ((philo->id + 1) % 2 == 1)
		usleep(philo->base->tte * 900);
	if (pthread_create(&dead_check, NULL, monitor, (void *)philo))
		return (NULL);
	int alive = 1;
	int	running = 1;
	if (philo->base->nb_phils == 1)
		return (only_one_phil(philo));
	while (alive && running)
	{
		alive = is_dead(philo);
		running = is_running(philo);
		take_forks(philo);
		unlock_forks(philo);
		philo_start_sleep(philo);
		philo_start_thinking(philo);
		if (philo->meals_count >= philo->base->nb_eats)
			return (NULL);
		// pthread_mutex_lock(&philo->base->screen_lock);
		// printf("nb %d ate %d on %d needed\n", philo->id, philo->meals_count, philo->base->nb_eats);
		// pthread_mutex_unlock(&philo->base->screen_lock);
	}
	return (NULL);
}
