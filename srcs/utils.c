/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:28:40 by acousini          #+#    #+#             */
/*   Updated: 2022/02/02 19:33:17 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long long int	utc_time_in_usec(struct timeval time)
{
	return (((long long int)time.tv_sec * 1000) + (time.tv_usec / 1000));
}

struct timeval	now(void)
{
	struct timeval	n;

	gettimeofday(&n, NULL);
	return (n);
}

long long int	elapsed_time(struct timeval start)
{
	return (utc_time_in_usec(now()) - utc_time_in_usec(start));
}

void	sleep_time(int time)
{
	long long int	n;

	n = utc_time_in_usec(now());
	while (utc_time_in_usec(now()) - n < time)
		usleep(100);
}
