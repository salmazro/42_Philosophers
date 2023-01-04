/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:40:03 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/27 17:30:33 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include "limits.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define RED "\e[0;31m"
# define WHITE "\e[1;97m"
# define CYAN "\e[1;96m"
# define BLUE "\033[1;34m"
# define PURPLE "\e[1;95m"

typedef struct s_philo{
	int				*death_flag;
	int				philo_id;
	int				left_fork;
	int				right_fork;
	int long long	last_meal;
	unsigned int	num_ate;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	struct s_philo	philo[200];
	unsigned int	num_philo;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	num_cycle;
	int long long	start_time;
	unsigned int	all_eat;
	int				*dead;
	int				forks[250];
	pthread_t		phils[200];
	pthread_mutex_t	mutex_forks[200];
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	var;
}	t_info;

int long long	get_time(void);
int				ft_parser(char **av, t_info *info);
int				ft_atoi(const char *str);
int				init_mutex(t_info *info);
int				check_forks(t_philo *p);
int				forks_odd(t_philo *p);
int				check_mutex(t_philo *p);
int				death_monitor(t_info *info);
int				death_check(t_philo *p);
void			set_fork(t_info *info);
void			print(char c, t_philo *p);
void			sleepp(t_philo *p, int ms);
void			philo_dead(t_philo *p);
void			*thread(void *info);
void			thread_help(t_philo *p);
void			eating(t_philo *p);
void			drop_forks(t_philo *p);
void			drop_o_forks(t_philo *p);
void			go_sleep(t_philo *p);
void			print_death(t_philo *p);
void			destroy_mutex(t_info *info);
void			*ft_calloc(size_t count, size_t size);
int				check_ac(t_info *info, int ac);
#endif
