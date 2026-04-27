/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:12:19 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/19 00:04:21 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	lock_dongle(t_data *data, t_dongle *dongle, t_coder *coder)
{
	long	avail;

	avail = get_cooldown_dong(dongle);
	add_to_queue(coder, dongle);
	while (!is_priority(dongle, coder)
		|| calcul_time(data) < avail)
	{
		usleep(10);
		if (get_simul_end(coder->data))
			return (0);
	}
	pthread_mutex_lock(&dongle->mutex);
	print_log(coder, "has taken a dongle\n");
	return (1);
}

t_dongle	*get_first_dongle(t_coder *coder)
{
	t_dongle	*first;

	if (coder->id % 2 == 0)
		first = coder->left_dongle;
	else
		first = coder->right_dongle;
	return (first);
}

t_dongle	*get_second_dongle(t_coder *coder)
{
	t_dongle	*second;

	if (coder->id % 2 == 0)
		second = coder->right_dongle;
	else
		second = coder->left_dongle;
	return (second);
}
