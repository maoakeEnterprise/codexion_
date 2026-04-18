/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:20:42 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/18 23:29:34 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	calcul_time(t_data *data)
{
	struct timeval	t;
	long			now;

	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (now - data->start_time);
}

int	is_nb_compiled(t_coder **coders)
{
	int	compiled;

	compiled = calcul_compile(coders);
	if (compiled < coders[0]->data->nb_compile_required)
		return (0);
	pthread_mutex_lock(&coders[0]->data->data_mutex);
	coders[0]->data->simul_end = 1;
	pthread_mutex_unlock(&coders[0]->data->data_mutex);
	printf("SOMETHING NEED TO BE FINISH\n");
	return (1);
}

int	get_simul_end(t_data *data)
{
	int	end;

	pthread_mutex_lock(&data->data_mutex);
	end = data->simul_end;
	pthread_mutex_unlock(&data->data_mutex);
	return (end);
}

void	print_log(t_coder *coder, char *str)
{
	long	timer;

	pthread_mutex_lock(&coder->data->write_mutex);
	if (!get_simul_end(coder->data))
	{
		timer = calcul_time(coder->data);
		printf("%ld %d %s", timer, coder->id, str);
	}
	pthread_mutex_unlock(&coder->data->write_mutex);
}

void	update_simul_end(t_coder **coders)
{
	while (!is_nb_compiled(coders) && !get_simul_end(coders[0]->data))
		usleep(10000);
}
