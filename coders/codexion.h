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

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_time
{
	float	time_to_compile;
	float	time_to_debug;
	float	time_to_refactor; 
}	t_time;

typedef struct s_coder
{
	t_time	*timers;
}	t_coder;

typedef struct s_dongle
{
	float	dongle_cooldown;
}	t_dongle;

typedef struct s_data
{
	int			number_of_compiles_required;
	t_coder		*coders;
	t_dongle	*dongles;
}	t_data;

int	text_is_digit(char *text);
int text_scheduler(char *text);
int parsing(int argc, char **argv);
void message_error(char *message);

#endif
