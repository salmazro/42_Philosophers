/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:06:57 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/27 17:30:31 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleepp(t_philo *p, int ms)
{
	long long	t;

	t = get_time();
	while (get_time() - t < ms)
	{
		if (get_time() - p->last_meal > p->info->time_die)
			break ;
		usleep(ms);
	}
}

static void	start_philo(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_create(&info->phils[i], NULL, &thread, &info->philo[i]);
		usleep(100);
		i++;
	}
	i = 0;
	death_monitor(info);
	while (i < info->num_philo)
		pthread_join(info->phils[i++], NULL);
}

void	init_philo(t_info *info)
{
	unsigned int	i;

	i = 0;
	info->dead = malloc(sizeof(int));
	if (!info->dead)
		return ;
	*info->dead = 0;
	info->start_time = get_time();
	info->all_eat = 0;
	while (i < info->num_philo)
	{
		info->philo[i].info = info;
		info->philo[i].death_flag = info->dead;
		info->philo[i].num_ate = 0;
		i++;
	}
	if (info->num_philo == 1)
	{
		philo_dead(&info->philo[0]);
		return ;
	}
	start_philo(info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!info)
		return (0);
	if (!check_ac(info, ac))
		return (0);
	if (!ft_parser(av, info))
	{
		free(info);
		printf("Invalid arguements\n");
		return (0);
	}
	set_fork(info);
	if (!init_mutex(info))
	{
		destroy_mutex(info);
		return (0);
	}
	init_philo(info);
	destroy_mutex(info);
	return (0);
}
