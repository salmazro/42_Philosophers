/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:34:48 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/27 17:30:25 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_mutex_init(&info->mutex_forks[i++], NULL))
			return (0);
	}
	if (pthread_mutex_init(&info->mutex_print, NULL))
		return (0);
	if (pthread_mutex_init(&info->mutex_dead, NULL))
		return (0);
	if (pthread_mutex_init(&info->mutex_eat, NULL))
		return (0);
	if (pthread_mutex_init(&info->var, NULL))
		return (0);
	return (1);
}

int	check_mutex(t_philo *p)
{
	pthread_mutex_lock(&p->info->var);
	if (*p->death_flag)
	{
		pthread_mutex_unlock(&p->info->var);
		return (0);
	}
	pthread_mutex_unlock(&p->info->var);
	return (1);
}

void	destroy_mutex(t_info *info)
{
	unsigned int	i;

	i = 0;
	free (info->dead);
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->mutex_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->mutex_print);
	pthread_mutex_destroy(&info->mutex_dead);
	pthread_mutex_destroy(&info->mutex_eat);
	pthread_mutex_destroy(&info->var);
	free(info);
}
