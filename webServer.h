/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:23:12 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/07 15:25:37 by nbeaufil         ###   ########.fr       */
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

# define PORT 6969
# define BUFFER_SIZE 200000
# define PREFIX "./web"

/* --------------- handleRequest -------------- */

const char	*getFileExt(char const *fileName);
const char	*getMIME(char const *fileExt);
const char	*putPrefix(char const *str);
char		*getfp(char const *pattern, char const *str);
char		*urlDecode(char const *encoded);

#endif