/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:16 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/30 20:49:38 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	text_is_digit(char *text, int pos)
{
	int	i;
	int	res;

	i = 0;
	while (text[i])
	{
		if (text[i] < '0' || text[i] > '9')
			return (0);
		i++;
	}
	res = atoi(text);
	if (res < 1 && (pos == 1 || pos == 2 || pos == 6))
		return (0);
	return (1);
}

static int	overflow(const char *str)
{
	size_t	i;
	int		tmp;
	int		before;

	i = 0;
	tmp = 0;
	before = 0;
	if (strcmp(str, "-2147483648"))
		return (1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		before = tmp;
		tmp = tmp * 10 + str[i] - '0';
		if (before > tmp)
			return (0);
		i++;
	}
	return (1);
}

int	text_scheduler(char *text)
{
	int	len;

	len = strlen(text);
	if (len == 4)
	{
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

int	is_edf(char *text)
{
	if (strcmp(text, "edf") == 0)
		return (1);
	return (0);
}

int	parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!argv[i])
			return (0);
		if (i != 8)
		{
			if (!text_is_digit(argv[i], i))
				return (0);
			if (!overflow(argv[i]))
				return (0);
		}
		else
		{
			if (!text_scheduler(argv[i]))
				return (0);
		}
		i++;
	}
	return (1);
}
