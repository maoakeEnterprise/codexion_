/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:22:05 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/15 17:46:14 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compiling(t_coder *coder)
{
	long	timer;

	timer = calcul_time(coder->data);
	printf("%ld %d is compiling\n", timer, coder->id);
	usleep(coder->data->time_compile * 1000);
	pthread_mutex_lock(&coder->data->data_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->data->data_mutex);
}

void	debugging(t_coder *coder)
{
	long	timer;

	timer = calcul_time(coder->data);
	printf("%ld %d is debugging\n", timer, coder->id);
	usleep(coder->data->time_debug * 1000); 	
}

void	refactoring(t_coder *coder)
{
	long	timer;

	timer = calcul_time(coder->data);
	printf("%ld %d is debugging\n", timer, coder->id);
	usleep(coder->data->time_refactor * 1000);
}

int	calcul_compile(t_coder **coders)
{
	int	i;
	int	compiled;

	i = 0;
	compiled = 0;
	pthread_mutex_lock(&coders[0]->data->data_mutex);
	while (coders[i])
	{
		compiled += coders[i]->compile_count;
		i++;
	}
	pthread_mutex_unlock(&coders[0]->data->data_mutex);
	return (compiled);
}

