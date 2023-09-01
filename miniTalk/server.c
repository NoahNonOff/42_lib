/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:53:48 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/08/03 12:28:12 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

// SIGUSR1 (0)
// SIGUSR2 (1)

static void	sigusr_handler(int signal, siginfo_t *info, void *context)
{
	static pid_t		client_pid;
	static t_character	chr = {0, 0};

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (signal == SIGUSR2)
		chr.c |= 1 << chr.bit_pos; // <-- (sens d'ecriture)
	if (++chr.bit_pos == 8)
	{
		_putchar(chr.c, 1);
		chr.c = 0;
		chr.bit_pos = 0;
	}
	// kill(client_pid, SIGUSR2); // message recu
}

void	endFunct(int signal)
{
	if (signal == SIGTERM)
		exit(0);
}

int	main(void)
{
	struct	sigaction	s_sig;

	_bzero(&s_sig, sizeof(s_sig));
	_putstr("Serveur PID: ", 1);
	_putnbr(getpid(), 1);
	_putchar('\n', 1);

	s_sig.sa_sigaction = &sigusr_handler;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	signal(SIGTERM, &endFunct);

	while (1)
		pause();
	return 0;
}