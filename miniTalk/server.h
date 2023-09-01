/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:53:50 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/01 14:17:38 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../_lib/_lib.h"
# include <signal.h>

/* ------------------------- struct ------------------------- */

typedef struct	{
	char	c;
	int		bit_pos;
}	t_character;

#endif