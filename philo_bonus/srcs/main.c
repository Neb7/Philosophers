/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:45:18 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:33:27 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	bool		is_dead;

	is_dead = false;
	if (ac != 5 && ac != 6)
		return (ft_error(ERR_ARG, 107), EXIT_FAILURE);
	philo = NULL;
	if (!ft_init_var(&philo, ac, av, &is_dead))
		return (ft_error(ERR_MALLOC, 16), EXIT_FAILURE);
	if (ft_launch(philo, 0))
		return (ft_end(philo), ft_error(ERR_PTHR, 24), EXIT_FAILURE);
	ft_end(philo);
	return (EXIT_SUCCESS);
}

void	ft_join(t_philo *philo)
{
	int	i;
	int	max;

	i = -1;
	max = philo->max_philo;
	while (++i < max)
	{
		pthread_join(philo[i].id_philo, NULL);
	}
	i = -1;
	ft_se(philo->forks, NAME);
}
