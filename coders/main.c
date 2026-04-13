/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/13 15:01:08 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	if (argc == 9 && parsing(argc, argv))
	{
	}
	else
		message_error("ERROR ON THE PARSING\n");
	return (0);
}

void	message_error(char *message)
{
	int	len;

	len = strlen(message);
	write(2, message, len);
}
