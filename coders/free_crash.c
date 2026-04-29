/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_crash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:22:12 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/16 14:57:21 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	crash_dongle(t_data *data)
{
	free_data(data);
	return (0);
}

t_dongle	*free_mutex_dongle(t_dongle *dongle, int step)
{
	if (step >= 1)
		pthread_mutex_destroy(&dongle->mutex);
	if (step >= 2)
		pthread_mutex_destroy(&dongle->mutex_q);
	if (step >= 3)
		pthread_mutex_destroy(&dongle->mutex_avail);
	free(dongle);
	return (NULL);
}

int	crash_coders(t_data *data, t_dongle **dongles)
{
	free_dongles(dongles);
	free_data(data);
	return (0);
}

t_data	*crash_data(t_data *data, int step)
{
	if (step == 1)
		pthread_mutex_destroy(&data->write_mutex);
	free(data);
	return (NULL);
}

int	crash_thread_coder(t_coder **coders, int pos)
{
	int	i;

	i = pos;
	while (--i >= 0)
		pthread_join(coders[i]->thread_id, NULL);
	return (0);
}
