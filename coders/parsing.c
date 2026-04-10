/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/06 16:02:18 by mteriier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

int text_is_digit(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] < '0' || text[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int text_scheduler(char *text)
{
	int	len;

	len = strlen(text);
	if (len == 4)
	{
		printf("%s %d \n",text, strcmp(text, "fifo"));
		if (strcmp(text, "fifo") == 0)
			return (1);
	}
	else if (len == 3)
	{
		if (strcmp(text, "edf") == 0)
			return (1);
	}
	return (0);
}
