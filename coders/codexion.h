/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:04:12 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/06 16:04:14 by mteriier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

typedef struct s_data
{
	int			number_of_compiles_required
	s_coder		*coders;
	s_dongle	*dongles;
}	t_data;

typedef struct s_coder
{
	s_time	*timers;
}	t_coder;

typedef struct s_dongle
{
	float	dongle_cooldown;
}	t_dongle;

typedef struct s_time
{
	float	time_to_compile;
	float	time_to_debug;
	float	time_to_refactor; 
}	t_time;

#endif
