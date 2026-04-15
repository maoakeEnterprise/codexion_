/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:20:42 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/15 15:27:52 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	calcul_time(t_data *data)
{
	struct 	timeval t;
	long	now;

	gettimeofday(&t, NULL);
	now = t.tv_usec;
	return (now - data->start_time);
}

int	is_nb_compiled(t_coder **coders)
{
	int	compiled;

	compiled = calcul_compile(coders);
	if (compiled < coders[0]->data->nb_compile_required)
		return (0);
	coders[0]->data->simul_end = 1;
	return (1);
}