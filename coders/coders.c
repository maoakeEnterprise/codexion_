/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:19:21 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/19 00:03:55 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	lock_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	first = get_first_dongle(coder);
	second = get_second_dongle(coder);
	if (!lock_dongle(coder->data, first, coder))
		return (0);
	if (!lock_dongle(coder->data, second, coder))
	{
		pthread_mutex_unlock(&first->mutex);
		return (0);
	}
	return (1);
}

void	unlock_dongles(t_coder *coder)
{
	long	now;
	long	dongle_cd;

	now = calcul_time(coder->data);
	dongle_cd = coder->data->dongle_cooldown;
	coder->left_dongle->available_at = now + dongle_cd;
	coder->right_dongle->available_at = now + dongle_cd;
	pthread_mutex_unlock(&(coder->left_dongle->mutex));
	pop_queue(coder->left_dongle);
	pthread_mutex_unlock(&(coder->right_dongle->mutex));
	pop_queue(coder->right_dongle);
}

void	*working_coder(void *arg)
{
	t_coder	*coder;

	coder = (void *)arg;
	if (coder->id % 2 == 0)
		usleep(100);
	while (!get_simul_end(coder->data))
	{
		if (!lock_dongles(coder))
			return (NULL);
		if (get_simul_end(coder->data))
		{
			unlock_dongles(coder);
			break;
		}
		compiling(coder);
		unlock_dongles(coder);
		debugging(coder);
		refactoring(coder);
	}
	unlock_dongles(coder);
	return (NULL);
}

void	launch_coders(t_coder **coders)
{
	int	i;

	i = 0;
	while (coders[i])
	{
		pthread_create(&coders[i]->thread_id, NULL, working_coder,
			coders[i]);
		i++;
	};
}

void	unlaunch_coders(t_coder **coders)
{
	int	i;

	i = 0;
	while (coders[i])
	{
		pthread_join(coders[i]->thread_id, NULL);
		i++;
	}
}
