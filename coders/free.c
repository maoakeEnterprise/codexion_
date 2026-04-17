/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:21:21 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/17 18:14:37 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	free(data);
}

void	free_dongle(t_dongle *dongle)
{
	pthread_mutex_destroy(&dongle->mutex);
	pthread_cond_destroy(&dongle->cond);
	free(dongle->queue);
	free(dongle);
}

void	free_dongles(t_dongle **dongles)
{
	int	i;

	i = 0;
	while (dongles[i])
	{
		free_dongle(dongles[i]);
		i++;
	}
	free(dongles);
}

void	free_coders(t_coder **coders)
{
	int	i;

	i = 0;
	while (coders[i])
	{
		free(coders[i]);
		i++;
	}
	free(coders);
}

void	free_all(t_data *data, t_dongle **dongles, t_coder **coders)
{
	free_coders(coders);
	free_dongles(dongles);
	free_data(data);
}
