/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:40:35 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/07 16:39:11 by nbeaufil         ###   ########.fr       */
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

const char	*build_response(char const *fileName, char const *fileExt, int *response_len) {

	int				file_fd;
	const char		*response;
	const char		*mime_t	= getMIME(fileExt);

	if (!fileName || !fileExt)
		return NULL;

	fileName = putPrefix(fileName);
	_putstr((char *)fileName, 1); _putchar('\n', 1);

	file_fd = open(fileName, O_RDONLY); /* if the file doesn't exist */
	if (-1 == file_fd) {
		response = _putinstr("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found");
		*response_len = _strlen(response);
		return response;
	}

	struct stat file_stat; /* get the size of the file */
	fstat(file_fd, &file_stat);

	/* write the header */
	response = _putinstr("HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", mime_t);
	*response_len = _strlen(response);

	char	buff_read[file_stat.st_size + 1];
	ssize_t	bytes_read;

	/* write the file in the response */
	if ((bytes_read = read(file_fd, buff_read, file_stat.st_size)) > 0) {
		buff_read[bytes_read] = 0;
		response = addNchar(response, buff_read, file_stat.st_size);
		*response_len += file_stat.st_size;
	}

	close(file_fd);
	return response;
}

/* ----------------------------- handle_client ------------------------------ */

void	*handle_client(void *data) {

	int		response_len;
	int		client_fd = *((int *)data);
	char	*request = _calloc(BUFFER_SIZE, sizeof(char));

	// receive request data from client (save it in the request)
	ssize_t	bytes_received = recv(client_fd, request, BUFFER_SIZE, 0);
	if (bytes_received > 0) {

		request[bytes_received] = 0;

		char	*fileName = getfp("GET ~ HTTP/1.1", request);
		if (!fileName)
			goto eHandleC;

		const char	*response = build_response(fileName, getFileExt(fileName), &response_len);
		if (!response) {
			free(fileName);
			goto eHandleC;
		}

		send(client_fd, response, response_len, 0);
		//m_free(2, response, fileName);
	}

eHandleC:
	close(client_fd);
	m_free(2, request, data);
	return NULL;
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