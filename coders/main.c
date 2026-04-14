/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/14 13:15:49 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	printf("Starting program with argc = %d\n", argc);
	if (argc == 9 && parsing(argc, argv))
	{
		data = init_data(argv);
	}
	else
		message_error("ERROR ON THE PARSING\n");
	if (data)
		free_data(data);
	return (0);
}

void	message_error(char *message)
{
	int	len;

	len = strlen(message);
	write(2, message, len);
}
