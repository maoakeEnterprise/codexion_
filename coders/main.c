/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/06 16:02:18 by mteriier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
	if (argc == 9 && parsing(argc, argv))
	{
	}
	else
		message_error("ERROR ON THE PARSING\n");
	return (0);
}

int parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (i != 8)
		{
			if (!text_is_digit(argv[i]))
			{
				printf("TEST1\n");
				return (0);
			}
		}
		else
		{
			if (!text_scheduler(argv[i]))
			{
				printf("%s\n", argv[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void message_error(char *message)
{
	int	len;

	len = strlen(message);
	write(2, message, len);
}
