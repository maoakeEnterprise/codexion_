/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_crash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:22:12 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/14 14:45:25 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	crash_dongle(t_data *data)
{
	free_data(data);
	return (0);
}

int crash_coders(t_data *data, t_dongle ** dongles)
{
	free_dongles(dongles);
	free_data(data);
	return (0);
}