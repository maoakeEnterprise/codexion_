/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:04:12 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/13 15:22:46 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	int				nb_coders;
	long			time_burnout;
	long			time_compile;
	long			time_debug;
	long			time_refactor;
	int				nb_compile_required;
	long			dongle_cooldown;
	int				is_edf;

	long			start_time;
	int				simul_end;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	data_mutex;
}	t_data;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	int				available_at;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	pthread_t	thread_id;
	int			compile_count;
	long		last_compile_start;

	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	t_data		*data;
}	t_coder;

int			text_is_digit(char *text);
int			text_scheduler(char *text);
int			parsing(int argc, char **argv);
int			is_edf(char *text);
void		message_error(char *message);
t_dongle	*init_dongle(int id);
t_coder		*init_coder(t_data *data, t_dongle *left, t_dongle *right);
t_data		*init_data(char **argv);
long		ft_atol(const char *nptr);
void		free_data(t_data *data);
void		free_dongle(t_dongle *dongle);
void		free_coder(t_coder *coder);
void		free_all(t_data *data, t_dongle **dongles, t_coder **coders);

#endif
