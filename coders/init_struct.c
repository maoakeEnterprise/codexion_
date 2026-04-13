/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:52:58 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/13 14:38:47 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_dongle(t_dongle *dongle, int id)
{
	dongle->id = id;
	pthread_mutex_init(&dongle->mutex, NULL);
	dongle->available_at = 0;
}

void	init_coder(t_coder *coder, t_data *data, t_dongle *left,
	t_dongle *right)
{
	coder->compile_count = 0;
	coder->last_compile_start = 0;
	coder->data = data;
	coder->left_dongle = left;
	coder->right_dongle = right;
	coder->thread_id = 0;
}
