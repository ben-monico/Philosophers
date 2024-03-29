/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:32:21 by bcarreir          #+#    #+#             */
/*   Updated: 2022/10/18 17:34:46 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pickforks(t_philo *philo)
{
	while (1)
	{
		if (death_check(philo, 0))
			return (1);
		pthread_mutex_lock(philo->arr_mtx);
		if (philo->arr[philo->left] == 0 && philo->arr[philo->right] == 0)
		{
			pthread_mutex_lock(&philo->mtx[philo->left]);
			philo->arr[philo->left] = 1;
			ft_print_msg(philo, "has taken a left fork");
			pthread_mutex_lock(&philo->mtx[philo->right]);
			philo->arr[philo->right] = 1;
			ft_print_msg(philo, "has taken a right fork");
			pthread_mutex_unlock(philo->arr_mtx);
			return (0);
		}
		else
			pthread_mutex_unlock(philo->arr_mtx);
	}
}

int	ft_eat(t_philo *philo)
{
	struct timeval	t;
	unsigned long	aux;
	int				meal_dur;
	int				ret;

	if (death_check(philo, 2))
		return (1);
	meal_dur = philo->args->eat_dur;
	gettimeofday(&t, NULL);
	ft_print_msg(philo, "is eating");
	philo->meals++;
	aux = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	philo->lastmeal_ms = aux - philo->args->init_ms;
	ret = ft_timeleft(philo);
	if (ret > 0 && ret < meal_dur)
		meal_dur = ret;
	while (((t.tv_sec * 1000) + (t.tv_usec / 1000)) - aux
		< (unsigned long)meal_dur)
		gettimeofday(&t, NULL);
    ft_unlockforks(philo);
	return (0);
}

void	ft_unlockforks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->mtx[philo->right]));
	pthread_mutex_unlock(&(philo->mtx[philo->left]));
	pthread_mutex_lock(philo->arr_mtx);
	philo->arr[philo->right] = 0;
	philo->arr[philo->left] = 0;
	pthread_mutex_unlock(philo->arr_mtx);
}

int	ft_sleep(t_philo *philo)
{
	int	ret;
	int	sleeptm;

	if (death_check(philo, 0))
		return (1);
	ft_print_msg(philo, "is sleeping");
	sleeptm = philo->args->sleep_dur;
	ret = ft_timeleft(philo);
	if (ret > 0 && ret < sleeptm)
		sleeptm = ret;
	else if (ret < 0)
		death_check(philo, 0);
	usleep(sleeptm * 1000);
	return (0);
}
