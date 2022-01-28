/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:06:31 by acousini          #+#    #+#             */
/*   Updated: 2022/01/28 18:48:13 by acousini         ###   ########.fr       */
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
	int						id;
	int						meals_count;
	unsigned long long int	last_meal;
	t_base					*base;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_t				thread_id;
}				t_philo;

typedef struct s_base
{
	unsigned long long int	tte;
	int						is_dead;
	unsigned long long int	tts;
	unsigned long long int	ttd;
	int						nb_phils;
	int						printed_death;
	int						nb_eats;
	int						inited;
	struct timeval			start;
	int						malloced;
	pthread_mutex_t			screen_lock;
	pthread_mutex_t			die_lock;
	t_philo					*philosophers;
}				t_base;

// time functions
void					wait_in_ms(unsigned long long int ms);
unsigned long long int	time_of_arg_in_ms(struct timeval time);
unsigned long long int	time_now_in_ms(void);
struct timeval			time_now(void);

// inits
int						init_philosophers(t_base *base);
int						fill_base(t_base *base, char **str);

// miscellaneous
void					ft_putstr(char *str);
void					ft_putnbr(int n);
void					ft_putchar(char c);
int						ft_strlen(char *str);

#endif
