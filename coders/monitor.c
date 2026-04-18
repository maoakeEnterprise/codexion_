/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:05:46 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/19 00:03:08 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	launch_monitor(t_coder **coders, pthread_t *thread)
{
	pthread_create(thread, NULL, monitor, coders);
}

void	unlaunch_monitor(pthread_t thread)
{
	pthread_join(thread, NULL);
}

void	*monitor(void *arg)
{
	t_coder	**coders;
	t_data	*data;
	int		i;

	coders = (t_coder **)arg;
	data = coders[0]->data;
	while (!get_simul_end(data))
	{
		i = 0;
		while (coders[i])
		{
			if (is_burned(coders[i]))
				stop_on_burn(coders[i], data);
			i++;
		}
	}
	return (NULL);
}

void	stop_on_burn(t_coder *coder, t_data *data)
{
	pthread_mutex_lock(&data->write_mutex);
	pthread_mutex_lock(&data->data_mutex);
	data->simul_end = 1;
	printf("%ld %d burned out\n", calcul_time(coder->data), coder->id);
	pthread_mutex_unlock(&data->data_mutex);
	pthread_mutex_unlock(&data->write_mutex);
}

int	is_burned(t_coder *coder)
{
	long			last_comp;
	long			time_burnout;
	long			total_time;
	struct timeval	t;
	long			actual_time;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(&coder->data->data_mutex);
	actual_time = t.tv_sec * 1000 + t.tv_usec / 1000;
	time_burnout = coder->data->time_burnout;
	last_comp = coder->last_compile_start;
	total_time = actual_time - last_comp;
	pthread_mutex_unlock(&coder->data->data_mutex);
	if (total_time > time_burnout)
		return (1);
	return (0);
}
