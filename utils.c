/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:48:52 by bcarreir          #+#    #+#             */
/*   Updated: 2022/10/18 17:47:21 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ft_print_msg(t_philo *philo, char *str)
{
	struct timeval			t;
	unsigned long			ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	pthread_mutex_lock(philo->printmtx);
	printf("[%lu ms] %d %s\n", ms - philo->args->init_ms, philo->id, str);
	pthread_mutex_unlock(philo->printmtx);
}

void	free_all(t_global *g)
{
	free(g->mutexes);
	free(g->arr);
	free(g->args);
	free(g->print);
	free(g->deathmtx);
	free(g->arrmtx);
	free(g->philo);
}
