/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:52:58 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/13 15:09:27 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle	*init_dongle(int id)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->id = id;
	pthread_mutex_init(&dongle->mutex, NULL);
	dongle->available_at = 0;
	return (dongle);
}

t_coder	*init_coder(t_data *data, t_dongle *left,
	t_dongle *right)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->compile_count = 0;
	coder->last_compile_start = 0;
	coder->data = data;
	coder->left_dongle = left;
	coder->right_dongle = right;
	coder->thread_id = 0;
	return (coder);
}

t_data	*init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_coders = atoi(argv[1]);
	data->time_burnout = ft_atol(argv[2]);
	data->time_compile = ft_atol(argv[3]);
	data->time_debug = ft_atol(argv[4]);
	data->time_refactor = ft_atol(argv[5]);
	data->nb_compile_required = atoi(argv[6]);
	data->dongle_cooldown = ft_atol(argv[7]);
	data->is_edf = is_edf(argv[8]);
	data->simul_end = 0;
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->data_mutex, NULL);
	return (data);
}
