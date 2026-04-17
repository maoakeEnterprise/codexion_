/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:12:19 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/17 19:05:23 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	lock_dongle(t_data *data, t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);
	while (calcul_time(data) < dongle->available_at)
	{
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
		if (get_simul_end(coder->data))
		{
			pthread_mutex_unlock(&dongle->mutex);
			return (0);
		}
	}
	print_log(coder, "has taken dongle\n");
	return (1);
}

t_dongle	*get_first_dongle(t_coder *coder)
{
	t_dongle	*first;

	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		first = coder->left_dongle;
	}
	else
	{
		first = coder->right_dongle;
	}
	return (first);
}

t_dongle	*get_second_dongle(t_coder *coder)
{
	t_dongle	*second;

	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		second = coder->right_dongle;
	}
	else
	{
		second = coder->left_dongle;
	}
	return (second);
}
