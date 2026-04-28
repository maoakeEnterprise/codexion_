/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:18:45 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/27 19:52:12 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	set_cooldown_dong(t_dongle *dongle, long new_cd)
{
	pthread_mutex_lock(&dongle->mutex_avail);
	dongle->available_at = new_cd;
	pthread_mutex_unlock(&dongle->mutex_avail);
}

long	get_cooldown_dong(t_dongle *dongle)
{
	long	avail;

	pthread_mutex_lock(&dongle->mutex_avail);
	avail = dongle->available_at;
	pthread_mutex_unlock(&dongle->mutex_avail);
	return (avail);
}
