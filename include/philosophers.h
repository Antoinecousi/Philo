/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:06:31 by acousini          #+#    #+#             */
/*   Updated: 2022/02/02 19:33:14 by acousini         ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_base	t_base;

typedef struct s_philo
{
	int						id;
	int						meals_count;
	unsigned long long int	last_meal;
	int						alive;
	t_base					*base;
	pthread_mutex_t			meal_check;
	pthread_mutex_t			alive_check;
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
	unsigned long long int	start;
	int						malloced;
	int						running;
	pthread_mutex_t			running_check;
	pthread_mutex_t			screen_lock;
	pthread_mutex_t			die_lock;
	t_philo					*philosophers;
}				t_base;

// actions
void					*routine(void *philosopher);
void					philo_start_eat(t_philo *philo);
void					philo_start_thinking(t_philo *philo);
void					philo_start_sleep(t_philo *philo);
void					unlock_forks(t_philo *philo);
int						take_forks(t_philo *philo);
int						can_eat(t_philo *philo);
int						is_running(t_philo *philo);
int						is_dead(t_philo *philo);

// output
void					write_dead(t_philo *philo);
void					mutex_screen(t_philo *philo, char *str);
void					output_state(t_philo *philo, char *str);

// time functions
void					wait_in_ms(unsigned long long int ms);
unsigned long long int	time_of_arg_in_ms(struct timeval time);
unsigned long long int	time_now_in_ms(void);
struct timeval			time_now(void);
unsigned long long int	time_from_beginning(unsigned long long int start);
long long int			utc_time_in_usec(struct timeval time);
struct timeval			now(void);
long long int			elapsed_time(struct timeval start);
void					sleep_time(int time);

// inits
int						init_each_philo(t_base *base, int id);
int						init_fork(t_base *base, int i);
int						fill_philo(t_base *base);
int						init_philosopher(t_base *base);
int						init_philosophers(t_base *base);
int						fill_base(t_base *base, char **str, int i);

// miscellaneous
int						clean_base(t_base *base, int error, char *str);
unsigned long long int	ft_atoi(const char *str);
void					ft_putstr(char *str);
void					ft_putnbr(int n);
void					ft_putchar(char c);
int						ft_strlen(char *str);

#endif
