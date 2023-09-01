/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:40:35 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/02 00:15:50 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

int	server_fd = 0;

/* ----------------------------- initiateServer ----------------------------- */

/*
	AF_INET: use IPv4 (vs IPv6)
	SOCK_STREAM: use TCP (vs UDP)
	INADDR_ANY: the server accepts connections from any network interface
*/

void	initiateServer(int *server_fd, struct sockaddr_in *server_addr) {

	// create server socket
	if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("error: [Socket] initialisation failed");
		exit(1);
	}

	// config socket
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

/* ------------------------------ urlDecoder -------------------------------- */

char	*urlDecoder(const char *urlEncoded) {

}

/* ----------------------------- handle_client ------------------------------ */

void	*handle_client(void *data) {
	
	int		client_fd = *((int *)data);
	char	*buffer = _calloc(BUFFER_SIZE, sizeof(char)); // to check [Buffer size]

	// receive request data from client (save it in the buffer)
	ssize_t	bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
	if (bytes_received > 0) {

		// check if request is GET
		regex_t		regex;
		regmatch_t	matches[2];
		regcomp(&regex, "^GET /([^ ]*) HTTP/1", REG_EXTENDED);

		if (!regexec(&regex, buffer, 2, matches, 0)) {
			// extract filename from request + decode URL
			// rm_so -> beginning of the substring
			// rm_eo -> end of the substring
			buffer[matches[1].rm_eo] = 0;
			const char	*urlEncoded = buffer + matches[1].rm_so;

			// char	*filename = urlDecoder(urlEncoded);
			printf("urlEncoded: %s[%d:%d]\n", urlEncoded, matches[1].rm_so, matches[1].rm_eo);

			// get file extension
			// char	fileExt[32];
			// get_file_ext(fileExt, filename);
		}
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
	_putstr("Server listening on port ", 1);
	_putnbr(PORT, 1);
	_putchar('\n', 1);

	signal(SIGTERM, &endProg);

	while (1)
		acceptClient();

	close(server_fd);
	return (0);
}