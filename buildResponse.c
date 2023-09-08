/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildResponse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:56:26 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/08 14:52:49 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

extern pthread_mutex_t		Output_mutex;

/* --------------------------- build_404_response --------------------------- */

const char	*error404(int *response_len) {

	int		file_fd;
	char	*response;

	file_fd = open("./web/error/404.html", O_RDONLY);
	if (-1 == file_fd) {

		response = _putinstr("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found");
		*response_len = _strlen(response);

		return response;
	}

	/* get the size of the file */
	struct stat 	fileInfo;
	fstat(file_fd, &fileInfo);

	/* write the header in the response */
	response = _putinstr("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
	*response_len = _strlen(response);

	char	buff_read[fileInfo.st_size + 1];
	ssize_t	bytes_read;

	/* write the http response body from the file */
	if (0 < (bytes_read = read(file_fd, buff_read, fileInfo.st_size))) {
		buff_read[bytes_read] = 0;
		response = getBodyRequest(response, buff_read, fileInfo.st_size);
		*response_len += fileInfo.st_size;
	}
	return response;
}

/* --------------------------- build_get_response --------------------------- */

const char	*build_get_response(char *fileName, char const *fileExt, int *response_len) {

	int				file_fd;
	char			*response;
	const char		*mime_t	= getMIME(fileExt);

	if (!fileExt || !mime_t) {
		free(fileName);
		return NULL;
	}

	/* write the fileName of the get http request */
	fileName = putPrefix(fileName);
	pthread_mutex_lock(&Output_mutex);
	_putstr("GET: ", 1); _putstr(fileName, 1); _putchar('\n', 1);
	pthread_mutex_unlock(&Output_mutex);

	/* check if the file exist */
	file_fd = open(fileName, O_RDONLY);
	if (-1 == file_fd) { /* file doesn't exist */

		pthread_mutex_lock(&Output_mutex);
		perror(fileName);
		pthread_mutex_unlock(&Output_mutex);

		free(fileName);
		return error404(response_len);
	}

	/* get the size of the file */
	struct stat 	fileInfo;
	fstat(file_fd, &fileInfo);

	/* write the header in the response */
	response = _putinstr("HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", mime_t);
	*response_len = _strlen(response);

	char	buff_read[fileInfo.st_size + 1];
	ssize_t	bytes_read;

	/* write the http response body from the file */
	if (0 < (bytes_read = read(file_fd, buff_read, fileInfo.st_size))) {
		buff_read[bytes_read] = 0;
		response = getBodyRequest(response, buff_read, fileInfo.st_size);
		*response_len += fileInfo.st_size;
	}

	free(fileName);
	close(file_fd);
	return response;
}

/* --------------------------- build_head_response -------------------------- */

const char	*build_head_response(char *fileName, char const *fileExt, int *response_len) {

	int				file_fd;
	char			*response;
	const char		*mime_t	= getMIME(fileExt);

	if (!fileExt || !mime_t) {
		free(fileName);
		return NULL;
	}

	/* write the fileName of the get http request */
	fileName = putPrefix(fileName);
	pthread_mutex_lock(&Output_mutex);
	_putstr("HEAD: ", 1); _putstr(fileName, 1); _putchar('\n', 1);
	pthread_mutex_unlock(&Output_mutex);

	/* check if the file exist */
	file_fd = open(fileName, O_RDONLY);
	if (-1 == file_fd) { /* file doesn't exist */

		pthread_mutex_lock(&Output_mutex);
		perror(fileName);
		pthread_mutex_unlock(&Output_mutex);

		response = _putinstr("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found");
		*response_len = _strlen(response);

		free(fileName);
		return response;
	}

	/* get the size of the file */
	struct stat 	fileInfo;
	fstat(file_fd, &fileInfo);

	/* write the header in the response */
	response = _putinstr("HTTP/1.1 200 OK\r\nContent-Length: %s\r\nContent-Type: %s\r\n\r\n", to_str(fileInfo.st_size), mime_t);
	*response_len = _strlen(response);

	free(fileName);
	close(file_fd);
	return response;
}