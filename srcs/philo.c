/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:13:43 by acousini          #+#    #+#             */
/*   Updated: 2022/01/25 19:29:05 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine()
{
	printf("Test fromp threads\n");
	sleep(1);
	printf("Ending threads\n");
	return (NULL);
}

int	main(int ac, char **argv)
{
	t_base	*base;

	base = malloc(sizeof(t_base));
	if (ac != 5)
		return (USAGE);
	fill_base(base, argv + 1);
	init_pthread();
	return (0);
}

	// if (pthread_join(t2, NULL) != 0)
	// 	return (4);
