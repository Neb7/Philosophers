/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:33:35 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:44:28 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_launch(t_philo *philo, int ret)
{
	int			i;
	int			max;
	pthread_t	moni;

	sem_wait(philo->dead);
	i = -1;
	max = philo[0].max_philo;
	if (philo->max_philo > 1)
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
	sem_post(philo->dead);
	if (philo->max_philo > 1)
		pthread_join(moni, NULL);
	ft_join(philo);
	return (ret);
}

void	ft_write(t_philo *philo, char *str, bool check)
{
	static int	start = 0;
	int			time_tmp;

	if (!start)
		start = ft_get_time();
	time_tmp = (ft_get_time() - start);
	sem_wait(philo->writing);
	if (!(*philo->is_dead) || check)
		printf("%d %d %s\n", time_tmp, philo->id, str);
	sem_post(philo->writing);
	(void)str;
}

void	ft_dead(t_philo *philo)
{
	if ((*philo->is_dead))
		return ;
	sem_wait(philo->dead);
	if (!(*philo->is_dead))
	{
		*philo->is_dead = true;
		ft_write(philo, MES_DEAD, true);
	}
	sem_post(philo->dead);
}
