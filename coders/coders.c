/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:19:21 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/15 15:09:30 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	lock_dongles(t_coder *coder)
{
	pthread_mutex_lock(&(coder->left_dongle->mutex));
	printf("%d has taken a dongle\n", coder->id);
	pthread_mutex_lock(&(coder->right_dongle->mutex));
	printf("%d has taken a dongle\n", coder->id);
}

void	unlock_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&(coder->left_dongle->mutex));
	printf("%d has untaken a dongle\n", coder->id);
	pthread_mutex_unlock(&(coder->right_dongle->mutex));
	printf("%d has untaken a dongle\n", coder->id);
}

void	*working_coder(void *arg)
{
	t_coder	*coder;

	coder = (void *)arg;
	while(!coder->data->simul_end)
	{
		lock_dongles(coder);
		compiling(coder);
		unlock_dongles(coder);
		debugging(coder);
		refactoring(coder);
	}
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
		if (is_nb_compiled(coders))
			break;
		i++;
	}
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
