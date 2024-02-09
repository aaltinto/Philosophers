/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:34:13 by aaltinto          #+#    #+#             */
/*   Updated: 2024/02/09 18:08:56 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fork) != 0)
		return (err_msg("Error\nFork can't be locked"), 1);
	if (is_dead(philo))
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	print_time("has taken a fork", philo->index, philo->vars, get_time());
	if (is_dead(philo) && philo->vars->count == 1)
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (err_msg("Error\nMutex can't be locked"), 1);
	if (is_dead(philo))
		return (pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	return (print_time("has taken a fork", philo->index, philo->vars,
			get_time()), 0);
}

int	eat(t_philo *philo)
{
	if (is_dead(philo))
		return (pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	print_time("\033[0;32mis eating", philo->index, philo->vars, get_time());
	ft_usleep(philo->vars->time_to_eat);
	if (pthread_mutex_lock(&philo->vars->eat) != 0)
		return (err_msg("Error\nMutex can't be locked"), 1);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->vars->eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (philo->eat_count++, 0);
}

int	sleep_think(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	print_time("is sleeping", philo->index, philo->vars, get_time());
	ft_usleep(philo->vars->time_to_sleep);
	if (is_dead(philo))
		return (1);
	print_time("is thinking", philo->index, philo->vars, get_time());
	return (0);
}

void	*eat_sleep_repeat(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	if (philo->index % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (take_fork(philo))
			return (die(vars, 3, 0));
		if (eat(philo))
			return (die(vars, 3, 0));
		if (sleep_think(philo))
			return (die(vars, 3, 0));
	}
	return (NULL);
}
