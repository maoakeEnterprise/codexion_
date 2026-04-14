/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteriier <mteriier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:19:21 by mteriier          #+#    #+#             */
/*   Updated: 2026/04/14 15:29:50 by mteriier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    ask_dongles(t_coder *coder)
{
    pthread_mutex_lock(&coder->dongle_left->mutex);
    pthread_mutex_lock(&coder->dongle_right->mutex);
}