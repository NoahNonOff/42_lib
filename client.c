/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:22:41 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/08/03 12:28:10 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_char(pid_t pid_server, char c)
{
	int	pos;
	int	last_bit;

	pos = 0;
	while (pos < 8)
	{
		last_bit = (1 & (c >> pos++));
		if (last_bit)
			kill(pid_server, SIGUSR2);
		else
			kill(pid_server, SIGUSR1);
		// wait for answer
		usleep(100); // to remove
	}
}

void	send_string(pid_t pid_server, char *msg)
{
	int	i;

	i = -1;
	while (msg && msg[++i])
		send_char(pid_server, msg[i]);
}

int	main(int ac, char **av)
{
	pid_t	pid_server;

	if (ac != 3)
	{
		_putstr("error: ./client <pid-server> <string>\n", 2);
		return (1);
	}
	pid_server = atoi(av[1]);
	send_string(pid_server, av[2]);
	//kill(pid_server, SIGTERM);
	return (0);
}