/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:22:05 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/15 12:22:49 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compiling(t_coder *coder)
{
	printf("%d is compiling\n", coder->id);
	usleep(coder->data->time_compile * 1000);
}

void	debugging(t_coder *coder)
{
	printf("%d is debugging\n", coder->id);
	usleep(coder->data->time_debug * 1000);	
}

void	refactoring(t_coder *coder)
{
	printf("%d is debugging\n", coder->id);
	usleep(coder->data->time_refactor * 1000);
}
