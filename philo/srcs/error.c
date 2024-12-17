/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:33:07 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 13:47:39 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(char *str, size_t len)
{
	write(2, str, len);
}

void	ft_des_forks(t_info *tmp, int max)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		pthread_mutex_destroy(tmp->forks[i]);
		free(tmp->forks[i]);
	}
	free(tmp->forks);
}

void	ft_end_philo(t_philo *philo)
{
	pthread_mutex_destroy(philo->left);
	free(philo->left);
}

void	ft_end(t_philo *philo)
{
	pthread_mutex_destroy(philo->dead);
	pthread_mutex_destroy(philo->writing);
	free(philo->dead);
	free(philo->writing);
	free(philo);
}
