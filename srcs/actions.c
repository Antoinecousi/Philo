/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:07:32 by acousini          #+#    #+#             */
/*   Updated: 2022/02/03 16:38:49 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_start_thinking(t_philo *philo)
{
	if (is_dead(philo) || is_running(philo))
		mutex_screen(philo, "is thinking\n");
	else
		write_dead(philo);
}

void	philo_start_sleep(t_philo *philo)
{
	if (is_dead(philo) || is_running(philo))
	{
		mutex_screen(philo, "is sleeping\n");
		wait_in_ms(philo->base->tts);
	}
	else
		write_dead(philo);
}
