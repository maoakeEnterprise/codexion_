/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:52:58 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/30 20:49:10 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle	*init_dongle(int id, int size)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->id = id;
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (free_mutex_dongle(dongle, 0));
	if (pthread_mutex_init(&dongle->mutex_q, NULL) != 0)
		return (free_mutex_dongle(dongle, 1));
	if (pthread_mutex_init(&dongle->mutex_avail, NULL) != 0)
		return (free_mutex_dongle(dongle, 2));
	dongle->available_at = 0;
	dongle->queue = malloc((size) * sizeof(int));
	if (!dongle->queue)
		return (free_mutex_dongle(dongle, 3));
	dongle->size_q = 0;
	return (dongle);
}

t_dongle	**init_dongles(int nb_dongles)
{
	int			i;
	t_dongle	**dongles;

	i = 0;
	dongles = malloc((nb_dongles + 1) * sizeof(t_dongle *));
	if (!dongles)
		return (NULL);
	my_calloc((void **)dongles, nb_dongles);
	while (i < nb_dongles)
	{
		dongles[i] = init_dongle(i, nb_dongles);
		if (!dongles[i])
		{
			free_dongles(dongles);
			return (NULL);
		}
		i++;
	}
	dongles[i] = NULL;
	return (dongles);
}

t_coder	*init_coder(t_data *data, t_dongle *left,
	t_dongle *right, int id)
{
	t_coder			*coder;

	coder = malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	if (pthread_mutex_init(&coder->mutex_coder, NULL) != 0)
	{
		free(coder);
		return (NULL);
	}
	coder->id = id + 1;
	coder->compile_count = 0;
	coder->last_compile_start = get_actual_time();
	coder->data = data;
	coder->left_dongle = left;
	coder->right_dongle = right;
	coder->thread_id = 0;
	return (coder);
}

t_coder	**init_coders(t_data *data, t_dongle **dongles, int nb_coders)
{
	int			i;
	t_coder		**coders;
	t_dongle	*left;
	t_dongle	*right;

	i = 0;
	coders = malloc((nb_coders + 1) * sizeof(t_coder *));
	if (!coders)
		return (NULL);
	my_calloc((void **)coders, nb_coders);
	while (i < nb_coders)
	{
		left = dongle_left(dongles, i);
		right = dongle_right(dongles, i);
		coders[i] = init_coder(data, left, right, i);
		if (!coders[i])
		{
			free_coders(coders);
			return (NULL);
		}
		i++;
	}
	coders[i] = NULL;
	return (coders);
}

t_data	*init_data(char **argv, long start)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_coders = atoi(argv[1]);
	data->time_burnout = atoi(argv[2]);
	data->time_compile = atoi(argv[3]);
	data->time_debug = atoi(argv[4]);
	data->time_refactor = atoi(argv[5]);
	data->nb_compile_required = atoi(argv[6]);
	data->dongle_cooldown = atoi(argv[7]);
	data->is_edf = is_edf(argv[8]);
	data->coders = NULL;
	data->simul_end = 0;
	data->start_time = start;
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (crash_data(data, 0));
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (crash_data(data, 1));
	return (data);
}
