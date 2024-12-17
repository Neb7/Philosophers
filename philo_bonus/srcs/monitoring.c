/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:59:43 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:44:43 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_all_eated(t_philo *philo);

void	*ft_monitoring(void *arg)
{
	int		j;
	int		check;
	int		max;
	t_philo	*philo;

	philo = (t_philo *)arg;
	max = philo->max_philo;
	sem_wait(philo->dead);
	sem_post(philo->dead);
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
	sem_wait(philo->dead);
	if (!(*philo->is_dead))
		*philo->is_dead = true;
	sem_post(philo->dead);
}
