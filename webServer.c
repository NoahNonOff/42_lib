/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:40:35 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/01 16:17:34 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

/*
    AF_INET: use IPv4 (vs IPv6)
    SOCK_STREAM: use TCP (vs UDP)
    INADDR_ANY: the server accepts connections from any network interface
*/

void	initiateServer(int *server_fd, struct sockaddr_in *server_addr) {

	// create server socket
	if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("error: [Socket] initialisation failed\n");
		exit(1);
	}

	// config socket
	_bzero(server_addr, sizeof(*server_addr));
	server_addr->sin_family = AF_INET;
	server_addr->sin_addr.s_addr = INADDR_ANY;
	server_addr->sin_port = htons(PORT);

	// bind [fr:lier/attacher] socket to port
	if (bind(*server_fd, (struct sockaddr *)server_addr, sizeof(*server_addr)) < 0) {
		perror("error: [Socket] bindding failed\n");
		exit(1);
	}

	// listen for connections (10 max.)
	if (listen(*server_fd, 10) < 0) {
		perror("error: [Socket] listening failed\n");
		exit(1);
	}
}

void	*handle_client(void *data) {
	(void)data;
}

void	acceptClient(int server_fd) {

	int					*client_fd;
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_len = sizeof(client_addr);

	if (!(client_fd = malloc(sizeof(int)))) {
		perror("error: Allocation failed\n");
		return ;
	}

	// accept client connection
	if ((*client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
		perror("error: failed during the acceptation\n");
		return ;
	}

	// create thread to handle client request
	pthread_t	thrId;
	pthread_create(&thrId, NULL, handle_client, (void *)client_fd);
	pthread_detach(thrId);
}


void	endProg(int signal) {

	if (signal == SIGTERM)
		exit(0);
}

int	main(void)
{
	int					server_fd = 0;
	struct sockaddr_in server_addr;

	initiateServer(&server_fd, &server_addr);
	_putstr("Server listening on port ", 1);
	_putnbr(PORT, 1);
	_putchar('\n', 1);

	signal(SIGTERM, &endProg);

	while (1)
		acceptClient(server_fd);

	close(server_fd);
	return (0);
}