/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:19:21 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/15 12:22:44 by mteriier         ###   ########.fr       */
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

void	*working_coder(void *arg)
{
	t_coder	*coder;

	coder = (void *)arg;
	while(1)
	{
		lock_dongles(coder);
		compiling(coder);
		debugging(coder);
		refactoring(coder);
	}
}
