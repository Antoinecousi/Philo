/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:25:31 by acousini          #+#    #+#             */
/*   Updated: 2022/01/26 20:02:05 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

struct timeval	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}

unsigned long long int	time_now_in_ms(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long long int)(long long int)now.tv_sec * 1000
		+ (long long int)now.tv_usec / 1000);
}

// unsigned long long int	time_between()

// unsigned long long int	what_time_is_it_now(struct timeval *time)
// {
// 	return ((long long int)(long long int)time->tv_sec * 1000
// 		+ (long long int)time->tv_usec / 1000);
// }

int wait_until(int ms, struct timeval *time)
{

	while ()
}

int	sleep_time_in_ms(int ms)
{
	struct timeval beginning;
	
	gettimeofday(&beginning, NULL);
	beginning
}