/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:22:05 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/16 22:13:47 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compiling(t_coder *coder)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	print_log(coder, "is compiling\n");
	pthread_mutex_lock(&coder->data->data_mutex);
	coder->compile_count++;
	coder->last_compile_start = t.tv_sec * 1000 + t.tv_usec / 1000;
	pthread_mutex_unlock(&coder->data->data_mutex);
	usleep(coder->data->time_compile * 1000);
	
}

void	debugging(t_coder *coder)
{
	print_log(coder, "is debugging\n");
	usleep(coder->data->time_debug * 1000);
}

void	refactoring(t_coder *coder)
{
	print_log(coder, "is refactoring\n");
	usleep(coder->data->time_refactor * 1000);
}

int	check_compiled(t_coder **coders)
{
	int	i;
	int	compiled_required;

	i = 0;
	compiled_required = coders[0]->data->nb_compile_required;
	while (coders[i])
	{
		if (coders[i]->compile_count < compiled_required)
			return (0);
		i++;
	}
	return (1);
}
