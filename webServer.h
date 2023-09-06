/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:23:12 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/06 12:55:12 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_H
# define WEBSERVER_H

/* ----------------- library ----------------- */

# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>
# include <pthread.h>
# include <signal.h>
# include <netinet/in.h> /* sockaddr_in */
# include <regex.h> /* regcomp */
# include "./_lib/_lib.h"

/* ----------------- macros ------------------ */

# define PORT 6969
# define BUFFER_SIZE 2147483647

/* --------------- handleRequest -------------- */

const char	*getFileExt(char const *fileName);
char		*getFromPattern(char const *pattern, char const *str);

#endif