/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:04:11 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:04:30 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_atoi(char *nbr, int max)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		if ((ret > max / 10))
			return (-1);
		else if ((ret * 10) > max - (nbr[i] - '0'))
			return (-1);
		else
			ret = (ret * 10) + (nbr[i] - '0');
		i++;
	}
	return (ret);
}

int	ft_get_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((int)((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000)));
}
