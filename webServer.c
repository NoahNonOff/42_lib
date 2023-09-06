/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:40:35 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/06 18:11:55 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

int	server_fd = 0;

/* ----------------------------- initiateServer ----------------------------- */

/*
	AF_INET: use IPv4 (vs IPv6)
	SOCK_STREAM: use TCP (vs UDP)
	INADDR_ANY: the server accepts connections from any network interface
	SO_REUSEADDR: the server bind itself even if the port is already in use
*/

void	initiateServer(int *server_fd, struct sockaddr_in *server_addr) {

	// create server socket
	if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("error: [Socket] initialisation failed");
		exit(1);
	}

	// get and set option on socket
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
    	perror("error: [Socket] setsockopt(SO_REUSEADDR) failed");
	}

	// config the socket
	_bzero(server_addr, sizeof(*server_addr));
	server_addr->sin_family = AF_INET;
	server_addr->sin_addr.s_addr = INADDR_ANY;
	server_addr->sin_port = htons(PORT);

	// bind [fr:lier/attacher] socket to port
	if (bind(*server_fd, (struct sockaddr *)server_addr, sizeof(*server_addr)) < 0) {
		perror("error: [Socket] bindding failed");
		exit(1);
	}

	// listen for connections (10 max.)
	if (listen(*server_fd, 10) < 0) {
		perror("error: [Socket] listening failed");
		exit(1);
	}
}

/* ----------------------------- build_response ----------------------------- */

char	*build_response(void) {

	char	*response = _calloc(sizeof(char), 200);

	_strncpy(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found", 200);
	return response;
}

/* ----------------------------- handle_client ------------------------------ */

void	*handle_client(void *data) {
	
	int		client_fd = *((int *)data);
	char	*buffer = _calloc(BUFFER_SIZE, sizeof(char)); // to check [Buffer size]

	// receive request data from client (save it in the buffer)
	ssize_t	bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
	if (bytes_received > 0) {

		buffer[bytes_received] = 0;
		// _putstr(buffer, 1);
		char	*fileName = getfp("GET ~ HTTP/1.1", buffer);
		if (!fileName) {
			close(client_fd);
			m_free(2, buffer, data);
			return NULL;
		}
			
		_putstr(fileName, 1);
		_putchar('\n', 1);
		// char	*response = build_response();

		// send(client_fd, response, _strlen(response), 0);
		// free(response);
	}

	close(client_fd);
	m_free(2, buffer, data);
}

/* ------------------------------ acceptClient ------------------------------ */

void	acceptClient(void) {

	int					*client_fd;
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_len = sizeof(client_addr);

	if (!(client_fd = malloc(sizeof(int)))) {
		perror("error: Allocation failed");
		return ;
	}

	// accept client connection
	if ((*client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
		perror("error: failed during the acceptation");
		return ;
	}

	// create thread to handle client request
	pthread_t	thrId;
	pthread_create(&thrId, NULL, handle_client, (void *)client_fd);
	pthread_detach(thrId);
}

/* --------------------------------- main ----------------------------------- */

void	endProg(int signal) {

	if (signal != SIGTERM)
		return ;
	close(server_fd);
	exit(0);
}

int	main(void)
{
	struct sockaddr_in server_addr;

	initiateServer(&server_fd, &server_addr);
	_putstr("Server listening on port [", 1);
	_putnbr(PORT, 1);
	_putstr("]\n", 1);

	signal(SIGTERM, &endProg);

	while (1)
		acceptClient();

	close(server_fd);
	return (0);
}