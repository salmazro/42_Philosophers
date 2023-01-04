/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:11:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/27 17:30:22 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_dead(t_philo *p)
{
	sleepp(p, p->info->time_die);
	printf("%s[%u] Philosopher %d has died\n", RED, p->info->time_die, 1);
}

int	death_monitor(t_info *info)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&info->mutex_eat);
	while (!*info->dead && !info->all_eat)
	{
		pthread_mutex_unlock(&info->mutex_eat);
		i = 0;
		while (i < info->num_philo)
		{
			if (!death_check(&info->philo[i]))
				break ;
			i++;
		}
		usleep(100);
		pthread_mutex_lock(&info->mutex_eat);
	}
	pthread_mutex_unlock(&info->mutex_eat);
	return (1);
}

int	death_check(t_philo *p)
{
	long long	temp;

	pthread_mutex_lock(&p->info->mutex_eat);
	temp = get_time() - p->last_meal;
	pthread_mutex_unlock(&p->info->mutex_eat);
	pthread_mutex_lock(&p->info->var);
	if (temp >= p->info->time_die)
	{
		print_death(p);
		*p->death_flag = 1;
		pthread_mutex_unlock(&p->info->var);
		return (0);
	}
	pthread_mutex_unlock(&p->info->var);
	return (1);
}

void	print_death(t_philo *p)
{
	pthread_mutex_lock(&p->info->mutex_dead);
	if (*p->death_flag)
	{
		pthread_mutex_unlock(&p->info->mutex_dead);
		return ;
	}
	pthread_mutex_unlock(&p->info->mutex_dead);
	pthread_mutex_lock(&p->info->mutex_print);
	printf("%s[%lld] Philosopher %d has died\n",
		RED, get_time() - p->info->start_time, p->philo_id +1);
	pthread_mutex_unlock(&p->info->mutex_print);
}
