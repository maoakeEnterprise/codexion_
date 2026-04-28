/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_util_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:29:25 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/27 20:39:20 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	set_compile_coder(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_coder);
	coder->compile_count++;
	coder->last_compile_start = get_actual_time();
	pthread_mutex_unlock(&coder->mutex_coder);
}

int	get_compile_coder(t_coder *coder)
{
	int	compile;

	pthread_mutex_lock(&coder->mutex_coder);
	compile = coder->compile_count;
	pthread_mutex_unlock(&coder->mutex_coder);
	return (compile);
}

long	get_last_time_comp(t_coder *coder)
{
	long	timer_coder;

	pthread_mutex_lock(&coder->mutex_coder);
	timer_coder = coder->last_compile_start;
	pthread_mutex_unlock(&coder->mutex_coder);
	return (timer_coder);
}
