/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:06:31 by acousini          #+#    #+#             */
/*   Updated: 2022/01/25 19:30:47 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>


# define USAGE		100


typedef struct s_philo
{
	int					id;
	int					meals_count;
	long long			last_meal;
	t_base				*base;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread_id;
}				t_philo;


typedef struct s_base
{
	int					t_to_eat;
	int					is_dead;
	int					t_to_sleep;
	int					t_to_die;
	int					nb_phils;
	int					printed_death;
	int					nb_eats;
	int					inited;
	struct timeval		start;
	int					malloced;
	pthread_mutex_t		screen_lock;
	pthread_mutex_t		die_lock;
	t_philo				*philosophers;
}				t_base;


void	fill_base(t_base *base, char **str);


#endif
