/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:22:05 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/27 20:34:20 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compiling(t_coder *coder)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	print_log(coder, "is compiling\n");
	set_compile_coder(coder);
	usleep(coder->data->time_compile * 1000);
}

void	debugging(t_coder *coder)
{
	print_log(coder, "is debugging\n");
	usleep(coder->data->time_debug * 1000);
}

void	refactoring(t_coder *coder)
{
	print_log(coder, "is refactoring\n");
	usleep(coder->data->time_refactor * 1000);
}

int	check_compiled(t_coder **coders)
{
	int	i;
	int	compiled_required;
	int	comp_count;

	i = 0;
	compiled_required = coders[0]->data->nb_compile_required;
	while (coders[i])
	{
		comp_count = get_compile_coder(coders[i]);
		if (comp_count < compiled_required)
			return (0);
		i++;
	}
	return (1);
}
