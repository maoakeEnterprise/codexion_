/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/19 00:05:12 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	long			start_time;

	start_time = get_actual_time();
	if (argc == 9 && parsing(argc, argv))
	{
		launch_program(argv, start_time);
	}
	else
		message_error("ERROR ON THE PARSING\n");
	return (0);
}

int	launch_program(char **argv, long start)
{
	t_data		*data;
	t_dongle	**dongles;
	t_coder		**coders;
	pthread_t	thread_monitor;

	data = init_data(argv, start);
	if (!data)
		return (0);
	dongles = init_dongles(data->nb_coders);
	if (!dongles)
		return (crash_dongle(data));
	coders = init_coders(data, dongles, data->nb_coders);
	if (!coders)
		return (crash_coders(data, dongles));
	data->coders = coders;
	if (launch_process(data, &thread_monitor))
	{
		unlaunch_coders(coders);
		unlaunch_monitor(thread_monitor);
	}
	free_all(data, dongles, coders);
	return (1);
}

int	launch_process(t_data *data, pthread_t *thread_monitor)
{
	t_coder	**coders;

	coders = data->coders;
	if (!launch_monitor(coders, thread_monitor))
		return (0);
	if (!launch_coders(coders))
	{
		unlaunch_monitor(*thread_monitor);
		return (0);
	}
	update_simul_end(coders);
	return (1);
}

void	message_error(char *message)
{
	int	len;

	len = strlen(message);
	write(2, message, len);
}
