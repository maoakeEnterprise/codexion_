/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/15 15:14:03 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	struct	timeval t;
	long	start_time;

	gettimeofday(&t, NULL);
	printf("Starting program with argc = %d\n", argc);
	start_time = t.tv_usec;
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

		data = init_data(argv, start);
		printf("Launching program -> %ld ms\n", calcul_time(data));
		if (!data)
			return (0);
		dongles = init_dongles(data->nb_coders);
		if (!dongles)
			return(crash_dongle(data));
		coders = init_coders(data, dongles, data->nb_coders);
		if (!coders)
			return (crash_coders(data, dongles));
		free_all(data, dongles, coders);
		return (1);
}

void	launch_coders(t_coder **coders)
{
	int	i;

	i = 0;
	while (coders[i])
	{
		pthread_create(&coders[i]->thread_id, NULL, working_coder,
			&coders[i]);
		i++;
	}
}

void	message_error(char *message)
{
	int	len;

	len = strlen(message);
	write(2, message, len);
}
