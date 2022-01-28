/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:07:32 by acousini          #+#    #+#             */
/*   Updated: 2022/01/28 20:03:30 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_start_eat(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		output_state(philo, FORK_MSG);
		pthread_mutex_lock(&philo->right_fork);
		output_state(philo, FORK_MSG);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		output_state(philo, FORK_MSG);
		pthread_mutex_lock(&philo->left_fork);
		output_state(philo, FORK_MSG);
	}
	philo->last_meal = time_now_in_ms();
	while ()
}