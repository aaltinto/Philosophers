/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:18:59 by aaltinto          #+#    #+#             */
/*   Updated: 2024/02/15 17:21:46 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ARG_MSG "Args must be like:\n\x1b[33m<number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"
# define ERR_MSG_POSITIVE "Invalid argument\nArgs must be positive int"

# include <pthread.h>

typedef struct s_philo
{
	int				eat_count;
	size_t			last_ate;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_vars	*vars;
	int				index;
}		t_philo;

typedef struct s_vars
{
	int				count;
	int				is_dead;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				max_eat;
	int				num;
	int				death_i;
	pthread_mutex_t	death;
	pthread_mutex_t	eat;
	size_t			start_time;
	t_philo			*philos;
}		t_vars;

int		ft_atoi(char *num);
void	err_msg(char *msg);
size_t	get_time(void);
void	print_time(char *msg, int i, t_vars *vars, size_t current);
int		ft_usleep(size_t milliseconds, t_philo *philo);

void	abort_mission(t_vars *vars, pthread_t **threads_id);

void	*death_note(void *arg);
void	*die(t_vars *vars, int index, int print);
int		is_dead(t_philo *philo);

void	*eat_sleep_repeat(void *arg);

int		philo_fill(int argc, char **argv, t_vars *vars);
int		philo_mutex_init(t_vars *vars, int i);

#endif