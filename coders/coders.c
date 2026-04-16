/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:19:21 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/16 22:22:03 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	lock_dongles(t_coder *coder)
{
	t_dongle *first;
	t_dongle *second;

	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		first = coder->left_dongle;
		second = coder->right_dongle;
	}
	else
	{
		
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	pthread_mutex_lock(&first->mutex);
	print_log(coder, "has taken a dongle\n");
	pthread_mutex_lock(&second->mutex);
	print_log(coder, "has taken a dongle\n");
}

void	unlock_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&(coder->left_dongle->mutex));
	print_log(coder, "has untaken a dongle\n");
	pthread_mutex_unlock(&(coder->right_dongle->mutex));
	print_log(coder, "has untaken a dongle\n");
}

void	*working_coder(void *arg)
{
	t_coder	*coder;

	coder = (void *)arg;
	while (!get_simul_end(coder->data))
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
