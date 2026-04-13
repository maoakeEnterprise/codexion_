/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:21:21 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/13 15:21:52 by mteriier         ###   ########.fr       */
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
    free(dongle);
}

void	free_coder(t_coder *coder)
{
    free(coder);
}

void	free_all(t_data *data, t_dongle **dongles, t_coder **coders)
{
    for (int i = 0; i < data->nb_coders; i++)
    {
        free_coder(coders[i]);
        free_dongle(dongles[i]);
    }
    free(coders);
    free(dongles);
    free_data(data);
}
