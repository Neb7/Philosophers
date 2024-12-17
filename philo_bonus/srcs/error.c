/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:20:19 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:44:20 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_error(char *str, size_t len)
{
	write(2, str, len);
}

void	ft_se(sem_t *tmp, char *str)
{
	sem_close(tmp);
	sem_unlink(str);
}

void	ft_end(t_philo *philo)
{
	ft_se(philo->dead, NAME_DEAD);
	ft_se(philo->writing, NAME_WRITE);
	ft_se(philo->forks, NAME);
	free(philo);
}
