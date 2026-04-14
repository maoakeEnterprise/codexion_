/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/14 14:17:37 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	printf("Starting program with argc = %d\n", argc);
	if (argc == 9 && parsing(argc, argv))
	{
		launch_program(argv);
	}
	else
		message_error("ERROR ON THE PARSING\n");
	return (0);
}

int	launch_program(char **argv)
{
	t_data		*data;
	t_dongle	**dongles;
	t_coder		**coders;

		data = init_data(argv);
		if (!data)
			return (0);
		dongles = init_dongles(data->nb_coders);
		if (!dongles)
		{
			free_data(data);
			return (0);
		}
		coders = init_coders(data, dongles, data->nb_coders);
		if (!coders)
		{
			free_dongles(dongles);
			free_data(data);
			return (0);
		}
		free_all(data, dongles, coders);
		return (1);
}

void	message_error(char *message)
{
	int	len;

	len = strlen(message);
	write(2, message, len);
}
