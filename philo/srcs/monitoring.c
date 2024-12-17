/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:15:03 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 15:40:50 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_all_eated(t_philo *philo);

void	*ft_monitoring(void *arg)
{
	int		j;
	int		check;
	int		max;
	t_philo	*philo;

	philo = (t_philo *)arg;
	max = philo->max_philo;
	pthread_mutex_lock(philo->dead);
	pthread_mutex_unlock(philo->dead);
	while (!(*philo->is_dead))
	{
		j = -1;
		check = 1;
		while (++j < max && check && !(*philo->is_dead))
		{
			if (philo[j].nb_ate < philo[j].max_eaten)
				check = 0;
		}
		if (check)
			ft_all_eated(philo);
		usleep(50);
	}
	return (NULL);
}

static void	ft_all_eated(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (!(*philo->is_dead))
		*philo->is_dead = true;
	pthread_mutex_unlock(philo->dead);
}
