/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:04:12 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/17 19:45:21 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_coder	t_coder;

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
	t_coder			**coders;
}	t_data;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				available_at;
	int				*queue;
	int				size_q;
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

// FUNCTIONS PARSING
int			text_is_digit(char *text);
int			text_scheduler(char *text);
int			parsing(int argc, char **argv);
int			is_edf(char *text);
// FUNCTIONS INIT STRUCT
t_dongle	*init_dongle(int id, int size);
t_dongle	**init_dongles(int nb_dongles);
t_coder		*init_coder(t_data *data, t_dongle *left, t_dongle *right, int id);
t_data		*init_data(char **argv, long start);
t_coder		**init_coders(t_data *data, t_dongle **dongles, int nb_coders);
//	FUNCTIONS UTILS
long		ft_atol(const char *nptr);
int			get_len_dongles(t_dongle **dongles);
t_dongle	*dongle_left(t_dongle **dongles, int id_coder);
t_dongle	*dongle_right(t_dongle **dongles, int id_coder);
void		my_calloc(void **tab, int len);
long		calcul_time(t_data *data);
int			get_simul_end(t_data *data);
void		print_log(t_coder *coder, char *str);
void		update_simul_end(t_coder **coders);
// FUNCTIONS FREE
void		free_data(t_data *data);
void		free_dongle(t_dongle *dongle);
void		free_dongles(t_dongle **dongles);
void		free_coders(t_coder **coders);
void		free_all(t_data *data, t_dongle **dongles, t_coder **coders);
// MAIN
int			launch_program(char **argv, long start);
void		message_error(char *message);
// CRASH MALLOC
int			crash_dongle(t_data *data);
int			crash_coders(t_data *data, t_dongle **dongles);
// FUNCTION CODERS
void		compiling(t_coder *coder);
void		debugging(t_coder *coder);
void		refactoring(t_coder *coder);
int			lock_dongles(t_coder *coder);
void		unlock_dongles(t_coder *coder);
void		*working_coder(void *arg);
int			calcul_compile(t_coder **coders);
int			is_nb_compiled(t_coder **coders);
void		launch_coders(t_coder **coders);
void		unlaunch_coders(t_coder **coders);
// FUNCtiON IN DONGLE
int			lock_dongle(t_data *data, t_dongle *dongle, t_coder *coder);
t_dongle	*get_first_dongle(t_coder *coder);
t_dongle	*get_second_dongle(t_coder *coder);
// FUNCTION IN SCHEDULER
void		add_to_queue(t_coder *coder, t_dongle *dongle);
void		logical_edf(t_coder *coder, t_dongle *dongle);
long		get_timer_coder(int id, t_coder **coders);
void		logical_fifo(t_coder *coder, t_dongle *dongle);
void		pop_queue(t_dongle *dongle);
int			is_priority(t_dongle *dongle, t_coder *coder);
// FUNCTION MONITOR
void		launch_monitor(t_coder **coders, pthread_t *thread);
void		unlaunch_monitor(pthread_t thread);
void		*monitor(void *arg);
void		stop_on_burn(t_coder *coder, t_data *data);
int			is_burned(t_coder *coder);

#endif
