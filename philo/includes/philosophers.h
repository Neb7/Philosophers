/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:37:25 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 15:41:04 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>

# define ERR_ARG "Error: Wrong format\nTry: ./philo [NB_PHILO] [TIME_DEAD] \
[TIME_EAT] [TIME_SLEEP] (optianal)[NB_OF_EAT_TIME]\n"
# define ERR_MALLOC "Allocation fail\n"
# define ERR_PHILO "Must have minimum 1 philo and maximum 300\n"
# define ERR_TIME "Time dead, time eat, time sleep or/and number of eat \
is/are too hight\n"
# define ERR_PTHR "Pthread's creation fail\n"

# define MES_FORK "\033[0;93mhas taken a fork\033[0m"
# define MES_EAT "is eating"
# define MES_SLEE "\033[0;94mis sleeping\033[0m"
# define MES_THIN "\033[0;92mis thinking\033[0m"
# define MES_DEAD "\033[0;91mdied\033[0m"

# define MAX_TIME 2000000
# define MAX_PHILO 300

typedef struct s_philo
{
	int				id;
	int				nb_ate;
	int				time_no_eat;
	pthread_t		id_philo;
	bool			*is_dead;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*writing;
	int				time_deat;
	int				time_sleep;
	int				time_eat;
	int				max_eaten;
	int				max_philo;
}	t_philo;

typedef struct s_info
{
	int				time_deat;
	int				time_sleep;
	int				time_eat;
	int				max_philo;
	int				max_eaten;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*writing;
	pthread_mutex_t	*dead;
}	t_info;

/*error*/

void	ft_error(char *str, size_t len);
void	ft_des_forks(t_info *tmp, int max);
void	ft_end_philo(t_philo *philo);
void	ft_end(t_philo *philo);

/*init*/

t_philo	*ft_init_var(t_philo **var, int ac, char **av, bool *is_dead);

/*launch*/

int		ft_launch(t_philo *philo, int ret);
void	ft_write(t_philo *philo, char *str, bool check);
void	ft_dead(t_philo *philo);

/*ft_it_lives*/

void	*ft_it_lives(void *arg);

/*ft_monitoring*/

void	*ft_monitoring(void *arg);

/*utils*/

int		ft_atoi(char *nbr, int max);
int		ft_get_time(void);

void	ft_join(t_philo *philo);

#endif
