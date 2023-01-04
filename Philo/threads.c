/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:35:21 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/27 17:30:34 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread(void *info)
{
	t_philo	*p;
	int		temp;

	p = (t_philo *)info;
	thread_help(p);
	pthread_mutex_lock(&p->info->var);
	temp = *p->death_flag;
	pthread_mutex_unlock(&p->info->var);
	while (!temp && p->num_ate < p->info->num_cycle)
	{
		while (!check_forks(p))
			usleep(50);
		eating(p);
		drop_forks(p);
		go_sleep(p);
		print('t', p);
		usleep(500);
		pthread_mutex_lock(&p->info->var);
		temp = *p->death_flag;
		pthread_mutex_unlock(&p->info->var);
	}
	return (NULL);
}

void	thread_help(t_philo *p)
{
	pthread_mutex_lock(&p->info->mutex_eat);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->info->mutex_eat);
	if (p->philo_id % 2)
		usleep(100);
}

void	eating(t_philo *p)
{
	print('f', p);
	print('e', p);
	pthread_mutex_lock(&p->info->mutex_eat);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->info->mutex_eat);
	sleepp(p, p->info->time_eat);
	p->num_ate++;
	pthread_mutex_lock(&p->info->mutex_eat);
	if (p->num_ate >= p->info->num_cycle)
		p->info->all_eat = 1;
	pthread_mutex_unlock(&p->info->mutex_eat);
}

void	go_sleep(t_philo *p)
{
	print('s', p);
	sleepp(p, p->info->time_sleep);
}

void	print(char c, t_philo *p)
{
	int long long	cur;

	cur = (get_time() - p->info->start_time);
	if (!check_mutex(p))
		return ;
	pthread_mutex_lock(&p->info->mutex_print);
	if (c == 'f')
	{
		printf("%s[%lld] Philosopher %d has taken a fork\n",
			WHITE, cur, p->philo_id + 1);
		printf("%s[%lld] Philosopher %d has taken a fork\n",
			WHITE, cur, p->philo_id + 1);
	}
	else if (c == 'e')
		printf("%s[%lld] Philosopher %d is eating\n",
			CYAN, cur, p->philo_id + 1);
	else if (c == 's')
		printf("%s[%lld] Philosopher %d is sleeping\n",
			BLUE, cur, p->philo_id + 1);
	else if (c == 't')
		printf("%s[%lld] Philosopher %d is thinking\n",
			PURPLE, cur, p->philo_id + 1);
	pthread_mutex_unlock(&p->info->mutex_print);
}
