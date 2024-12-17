/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_it_lives.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:56:53 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:44:35 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_alone(t_philo *philo);
static void	ft_eating(t_philo *philo);
static void	ft_sleeping(t_philo *philo);

void	*ft_it_lives(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->dead);
	philo->time_no_eat = ft_get_time();
	sem_post(philo->dead);
	if (!(philo->id % 2))
		usleep(2000);
	if (philo->max_philo < 2)
		return (ft_alone(philo), NULL);
	while (!(*philo->is_dead))
	{
		ft_write(philo, MES_THIN, false);
		sem_wait(philo->forks);
		ft_write(philo, MES_FORK, false);
		sem_wait(philo->forks);
		ft_write(philo, MES_FORK, false);
		ft_eating(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		ft_sleeping(philo);
	}
	return (NULL);
}

static void	ft_alone(t_philo *philo)
{
	ft_write(philo, MES_THIN, false);
	usleep(philo->time_deat * 1000 - 5000);
	ft_dead(philo);
}

static void	ft_eating(t_philo *philo)
{
	ft_write(philo, MES_EAT, false);
	philo->time_no_eat = ft_get_time();
	while (!(*philo->is_dead) && ft_get_time() - philo->time_no_eat < \
	philo->time_eat && ft_get_time() - philo->time_no_eat < philo->time_deat)
		usleep(500);
	if (ft_get_time() - philo->time_no_eat < philo->time_eat)
		ft_dead(philo);
	(philo->nb_ate)++;
}

static void	ft_sleeping(t_philo *philo)
{
	int	tmp;

	tmp = ft_get_time();
	ft_write(philo, MES_SLEE, false);
	while (!(*philo->is_dead) && ft_get_time() - tmp < philo->time_sleep && \
	ft_get_time() - philo->time_no_eat < philo->time_deat)
		usleep(500);
	if (ft_get_time() - philo->time_no_eat > philo->time_deat)
		ft_dead(philo);
}
