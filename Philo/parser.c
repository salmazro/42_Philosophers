/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:39:06 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/27 17:30:28 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_ac(t_info *info, int ac)
{
	if (!(ac == 5 || ac == 6))
	{
		free (info);
		printf("Invalid number of arguements\n");
		return (0);
	}
	else
		return (1);
}

int	ft_parser(char **av, t_info *info)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	info->num_philo = ft_atoi(av[1]);
	info->time_die = ft_atoi(av[2]);
	info->time_eat = ft_atoi(av[3]);
	info->time_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		info->num_cycle = ft_atoi(av[5]);
		if (info->num_cycle <= 0)
			return (0);
	}
	else if (!av[5])
		info->num_cycle = 99999999;
	if (info->num_philo <= 0 || info->time_die <= 60 || info->time_sleep <= 60
		|| info->time_eat <= 60 || info->num_philo > 200)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	return (sign * num);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n > 0)
	{
		((unsigned char *)s)[i] = 0;
		n--;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count >= 909999999999999 || size >= 999999999999999)
		return (NULL);
	ret = malloc(count * size);
	if (!ret)
		return (0);
	ft_bzero (ret, count * size);
	return (ret);
}
