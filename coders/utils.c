/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:06:42 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/14 13:16:06 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ft_atol(const char *nptr)
{
	size_t	i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

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
