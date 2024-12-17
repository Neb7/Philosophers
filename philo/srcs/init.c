/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:29 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:07:50 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*ft_init_philo(t_info *tmp, t_philo **philo, bool *is_dead);
static t_philo	*ft_innit_ph(t_philo *ph, t_info *tmp, bool *is_dead);
static t_info	*ft_init_forks(t_info *tmp);

t_philo	*ft_init_var(t_philo **philo, int ac, char **av, bool *is_dead)
{
	t_info	*tmp;

	tmp = (t_info *)malloc(sizeof(t_info));
	if (!tmp)
		return (NULL);
	tmp->max_philo = ft_atoi(av[1], MAX_PHILO);
	if (tmp->max_philo < 0)
		return (free(tmp), ft_error(ERR_PHILO, 42), NULL);
	tmp->time_deat = ft_atoi(av[2], MAX_TIME);
	tmp->time_eat = ft_atoi(av[3], MAX_TIME);
	tmp->time_sleep = ft_atoi(av[4], MAX_TIME);
	if (ac > 5)
		tmp->max_eaten = ft_atoi(av[5], MAX_TIME);
	else
		tmp->max_eaten = INT_MAX;
	if (tmp->max_eaten < 0 || tmp->time_deat < 0 || tmp->time_eat < 0 || \
	tmp->time_sleep < 0)
		return (free(tmp), ft_error(ERR_TIME, 70), NULL);
	if (!ft_init_forks(tmp))
		return (free(tmp), ft_error(ERR_MALLOC, 16), NULL);
	return (ft_init_philo(tmp, philo, is_dead));
}

static t_philo	*ft_init_philo(t_info *tmp, t_philo **philo, bool *is_dead)
{
	t_philo	*ph;

	ph = (t_philo *)malloc(sizeof(t_philo) * tmp->max_philo);
	if (!ph)
		return (ft_des_forks(tmp, tmp->max_philo), free(tmp), NULL);
	tmp->writing = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(tmp->writing))
		return (ft_des_forks(tmp, tmp->max_philo), free(ph), free(tmp), NULL);
	tmp->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(tmp->dead))
		return (free(ph), free(tmp->writing), \
		ft_des_forks(tmp, tmp->max_philo), NULL);
	if (!ft_innit_ph(ph, tmp, is_dead))
		return (pthread_mutex_destroy(tmp->writing), ft_des_forks(tmp, \
		tmp->max_philo), pthread_mutex_destroy(tmp->dead), free(tmp), \
		free(ph), NULL);
	*philo = ph;
	return (free(tmp->forks), free(tmp), ph);
}

static t_philo	*ft_innit_ph(t_philo *ph, t_info *tmp, bool *is_dead)
{
	int	i;

	if (pthread_mutex_init(tmp->writing, NULL))
		return (NULL);
	if (pthread_mutex_init(tmp->dead, NULL))
		return (pthread_mutex_destroy(tmp->writing), NULL);
	i = -1;
	while (++i < tmp->max_philo)
	{
		ph[i].is_dead = is_dead;
		ph[i].id = i + 1;
		ph[i].nb_ate = 0;
		ph[i].time_no_eat = 0;
		ph[i].time_deat = tmp->time_deat + 5;
		ph[i].time_eat = tmp->time_eat;
		ph[i].time_sleep = tmp->time_sleep;
		ph[i].max_eaten = tmp->max_eaten;
		ph[i].left = tmp->forks[i];
		ph[i].right = tmp->forks[(i + 1) % tmp->max_philo];
		ph[i].writing = tmp->writing;
		ph[i].dead = tmp->dead;
		ph[i].max_philo = tmp->max_philo;
	}
	return (ph);
}

static t_info	*ft_init_forks(t_info *tmp)
{
	int	i;

	i = -1;
	tmp->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) \
	* tmp->max_philo);
	if (!tmp->forks)
		return (NULL);
	while (++i < tmp->max_philo)
	{
		tmp->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!(tmp->forks[i]))
			return (ft_des_forks(tmp, i), NULL);
		if (pthread_mutex_init(tmp->forks[i], NULL))
			return (ft_des_forks(tmp, i), NULL);
	}
	return (tmp);
}
