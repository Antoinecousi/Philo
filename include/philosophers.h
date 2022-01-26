/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:06:31 by acousini          #+#    #+#             */
/*   Updated: 2022/01/26 16:53:27 by acousini         ###   ########.fr       */
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
	int					tte;
	int					is_dead;
	int					tts;
	int					ttd;
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

// inits
int		init_philosophers(t_base *base);
int		fill_base(t_base *base, char **str);

// miscellaneous
void	ft_putstr(char *str);
void	ft_putnbr(int n);
void	ft_putchar(char c);
int		ft_strlen(char *str);

#endif
