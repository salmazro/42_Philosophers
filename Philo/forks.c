/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:13:54 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/27 17:30:23 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i].philo_id = i;
		info->forks[i++] = 0;
	}
	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i].left_fork = info->philo[i].philo_id;
		info->philo[i].right_fork = (i + 1) % info->num_philo;
		i++;
	}
}

int	check_forks(t_philo *p)
{
	if (!p->philo_id % 2)
		return (forks_odd(p));
	pthread_mutex_lock(&p->info->mutex_forks[p->left_fork]);
	if (p->info->forks[p->left_fork])
	{
		pthread_mutex_unlock(&p->info->mutex_forks[p->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&p->info->mutex_forks[p->right_fork]);
	if (p->info->forks[p->right_fork])
	{
		pthread_mutex_unlock(&p->info->mutex_forks[p->left_fork]);
		pthread_mutex_unlock(&p->info->mutex_forks[p->right_fork]);
		return (0);
	}
	p->info->forks[p->left_fork] = 1;
	p->info->forks[p->right_fork] = 1;
	pthread_mutex_unlock(&p->info->mutex_forks[p->left_fork]);
	pthread_mutex_unlock(&p->info->mutex_forks[p->right_fork]);
	return (1);
}

int	forks_odd(t_philo *p)
{
	pthread_mutex_lock(&p->info->mutex_forks[p->right_fork]);
	if (p->info->forks[p->right_fork])
	{
		pthread_mutex_unlock(&p->info->mutex_forks[p->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&p->info->mutex_forks[p->left_fork]);
	if (p->info->forks[p->left_fork])
	{
		pthread_mutex_unlock(&p->info->mutex_forks[p->right_fork]);
		pthread_mutex_unlock(&p->info->mutex_forks[p->left_fork]);
		return (0);
	}
	p->info->forks[p->right_fork] = 1;
	p->info->forks[p->left_fork] = 1;
	pthread_mutex_unlock(&p->info->mutex_forks[p->right_fork]);
	pthread_mutex_unlock(&p->info->mutex_forks[p->left_fork]);
	return (1);
}

void	drop_forks(t_philo *p)
{
	if (!p->philo_id % 2)
	{
		drop_o_forks(p);
		return ;
	}
	pthread_mutex_lock(&p->info->mutex_forks[p->left_fork]);
	pthread_mutex_lock(&p->info->mutex_forks[p->right_fork]);
	p->info->forks[p->right_fork] = 0;
	p->info->forks[p->left_fork] = 0;
	pthread_mutex_unlock(&p->info->mutex_forks[p->left_fork]);
	pthread_mutex_unlock(&p->info->mutex_forks[p->right_fork]);
}

void	drop_o_forks(t_philo *p)
{
	pthread_mutex_lock(&p->info->mutex_forks[p->right_fork]);
	pthread_mutex_lock(&p->info->mutex_forks[p->left_fork]);
	p->info->forks[p->right_fork] = 0;
	p->info->forks[p->left_fork] = 0;
	pthread_mutex_unlock(&p->info->mutex_forks[p->left_fork]);
	pthread_mutex_unlock(&p->info->mutex_forks[p->right_fork]);
}
