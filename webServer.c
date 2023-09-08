/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:40:35 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/08 14:57:50 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

int					server_fd = 0;
pthread_mutex_t		Output_mutex;

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

/* ----------------------------- handle_client ------------------------------ */

void	*handle_client(void *data) {

	int		response_len;
	int		client_fd = *((int *)data);
	char	*request = _calloc(BUFFER_SIZE, sizeof(char));

	// receive request data from client (save it in the request)
	ssize_t	bytes_received = recv(client_fd, request, BUFFER_SIZE, 0);
	if (bytes_received > 0) {

		const char	*response;
		request[bytes_received] = 0;
		/* =================== handle http request =================== */

		const R_HTTP	type = getREQUEST(request);
		if (!type) /* the request doesn't have an expected type */
			goto eHandleC;

		/* GET request */
		if (type == GET) {
			char	*fileName = getfp("GET ~ HTTP/1.1", request);
			if (!fileName)
				goto eHandleC;

			response = build_get_response(fileName, getFileExt(fileName), &response_len);
			if (!response) /* response creation failed */
				goto eHandleC;
		}

		/* HEAD request */
		if (type == HEAD) {
			char	*fileName = getfp("HEAD ~ HTTP/1.1", request);
			if (!fileName)
				goto eHandleC;

			response = build_head_response(fileName, getFileExt(fileName), &response_len);
			if (!response) /* response creation failed */
				goto eHandleC;
		}

		send(client_fd, response, response_len, 0);
		free((char *)response);

		/* =========================================================== */
	}

eHandleC:
	close(client_fd);
	m_free(2, request, data);
	return NULL;
}

/* ------------------------------ acceptClient ------------------------------ */

void	acceptClient(void) {

	int					*arg;
	int					client_fd;
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_len = sizeof(client_addr);

	// accept client connection
	if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
		perror("error: failed during the acceptation");
		return ;
	}

	/* create the arguments for the thread */
	if (!(arg = malloc(sizeof(int)))) {
		close(client_fd);
		perror("error: Allocation failed");
		return ;
	}

	*arg = client_fd;

	// create thread to handle client request
	pthread_t	thrId;
	pthread_create(&thrId, NULL, handle_client, (void *)arg);
	pthread_detach(thrId);
}

/* --------------------------------- main ----------------------------------- */

void	endProg(int signal) {

	if (signal != SIGTERM && signal != SIGINT)
		return ;
	close(server_fd);
	pthread_mutex_destroy(&Output_mutex);
	exit(0);
}

int	main(void)
{
	struct sockaddr_in server_addr;

	pthread_mutex_init(&Output_mutex, NULL);
	initiateServer(&server_fd, &server_addr);
	_putstr("Server listening on port [", 1);
	_putnbr(PORT, 1);
	_putstr("]\n", 1);

	signal(SIGTERM, &endProg);
	signal(SIGINT, &endProg);

	while (1)
		acceptClient();

	close(server_fd);
	return (0);
}