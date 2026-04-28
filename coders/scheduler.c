/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:18:26 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/27 20:41:51 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	add_to_queue(t_coder *coder, t_dongle *dongle)
{
	t_data	*data;

	data = coder->data;
	if (data->is_edf)
	{
		logical_edf(coder, dongle);
	}
	else
		logical_fifo(coder, dongle);
}

void	logical_edf(t_coder *coder, t_dongle *dongle)
{
	int		i;
	long	value;
	long	tmp;
	int		id_coder;

	value = get_last_time_comp(coder);
	pthread_mutex_lock(&dongle->mutex_q);
	i = dongle->size_q - 1;
	while (i >= 0)
	{
		tmp = get_timer_coder(dongle->queue[i], coder->data->coders);
		if (tmp < value)
			break ;
		id_coder = dongle->queue[i];
		dongle->queue[i + 1] = id_coder;
		i--;
	}
	dongle->queue[i + 1] = coder->id;
	dongle->size_q++;
	pthread_mutex_unlock(&dongle->mutex_q);
}

long	get_timer_coder(int id, t_coder **coders)
{
	long	res;
	long	bn;

	res = get_last_time_comp(coders[id - 1]);
	bn = coders[id - 1]->data->time_burnout;
	return (res + bn);
}

void	logical_fifo(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex_q);
	dongle->queue[dongle->size_q] = coder->id;
	dongle->size_q++;
	pthread_mutex_unlock(&dongle->mutex_q);
}

void	pop_queue(t_dongle *dongle)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&dongle->mutex_q);
	while (i < dongle->size_q - 1)
	{
		dongle->queue[i] = dongle->queue[i + 1];
		i++;
	}
	dongle->size_q--;
	pthread_mutex_unlock(&dongle->mutex_q);
}
