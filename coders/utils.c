/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:06:42 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/30 20:50:38 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_len_dongles(t_dongle **dongles)
{
	int	i;

	i = 0;
	while (dongles[i])
		i++;
	return (i);
}

t_dongle	*dongle_left(t_dongle **dongles, int id_coder)
{
	int	len_dongles;

	len_dongles = get_len_dongles(dongles);
	if (id_coder == 0)
		return (dongles[len_dongles - 1]);
	return (dongles[id_coder -1]);
}

t_dongle	*dongle_right(t_dongle **dongles, int id_coder)
{
	return (dongles[id_coder]);
}

void	my_calloc(void **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i] = NULL;
		i++;
	}
}
