/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:33:01 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:31:54 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_launch(t_philo *philo, int ret)
{
	int			i;
	int			max;
	pthread_t	moni;

	pthread_mutex_lock(philo[0].dead);
	i = -1;
	max = philo[0].max_philo;
	if (philo->left != philo->right)
		if (pthread_create(&moni, NULL, &ft_monitoring, philo))
			i = max + 1;
	while (++i < max)
	{
		if (pthread_create(&philo[i].id_philo, NULL, &ft_it_lives, &philo[i]))
			break ;
	}
	if (i != max)
	{
		ret = 1;
		ft_dead(philo);
	}
	pthread_mutex_unlock(philo[0].dead);
	ft_join(philo);
	if (philo->left != philo->right)
		pthread_join(moni, NULL);
	return (ret);
}

void	ft_write(t_philo *philo, char *str, bool check)
{
	static int	start = 0;
	int			time_tmp;

	if (!start)
		start = ft_get_time();
	time_tmp = (ft_get_time() - start);
	pthread_mutex_lock(philo->writing);
	if (!(*philo->is_dead) || check)
		printf("%d %d %s\n", time_tmp, philo->id, str);
	pthread_mutex_unlock(philo->writing);
	(void)str;
}

void	ft_dead(t_philo *philo)
{
	if ((*philo->is_dead))
		return ;
	pthread_mutex_lock(philo->dead);
	if (!(*philo->is_dead))
	{
		*philo->is_dead = true;
		ft_write(philo, MES_DEAD, true);
	}
	pthread_mutex_unlock(philo->dead);
}
