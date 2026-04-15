/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:20:42 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/15 14:36:33 by mteriier         ###   ########.fr       */
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