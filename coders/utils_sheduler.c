/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sheduler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:37:02 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/17 19:47:02 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_priority(t_dongle *dongle, t_coder *coder)
{
	int	verif;

	verif = 0;
	pthread_mutex_lock(&dongle->mutex_q);
	if (dongle->queue[0] == coder->id)
		verif = 1;
	pthread_mutex_unlock(&dongle->mutex_q);
	return verif;
}
