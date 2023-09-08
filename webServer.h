/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:23:12 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/08 14:43:53 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_H
# define WEBSERVER_H

/* ----------------- library ----------------- */

# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <netinet/in.h> /* sockaddr_in */
# include <regex.h> /* regcomp */
# include "./_lib/_lib.h"

/* ----------------- macros ------------------ */

# ifndef PORT
#  define PORT 6969
# endif

# define BUFFER_SIZE 200000
# define PREFIX "./web"
# define to_str( s ) # s

typedef enum { NONE, GET, HEAD, POST }	R_HTTP;

/* --------------- handleRequest -------------- */

const char	*getFileExt(char const *fileName);
const char	*getMIME(char const *fileExt);
R_HTTP		getREQUEST(char *request);

char		*putPrefix(char const *str);
char		*getfp(char const *pattern, char const *str);
char		*urlDecode(char const *encoded);
char		*getBodyRequest(char *header, char const *file, int file_len);

/* --------------- buildResponse -------------- */

const char	*build_get_response(char *fileName, char const *fileExt, int *response_len);
const char	*build_head_response(char *fileName, char const *fileExt, int *response_len);

#endif