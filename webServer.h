/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:23:12 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/01 23:08:00 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_H
# define WEBSERVER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>
# include <pthread.h>
# include <signal.h>
# include <netinet/in.h> /* sockaddr_in */
# include <regex.h> /* regcomp */
# include "./_lib/_lib.h"

# define PORT 6969
# define BUFFER_SIZE 2147483647

// request example:
//
// GET / HTTP/1.1
// Host: 127.0.0.1:6969
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate, br
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1
// Sec-Fetch-Dest: document
// Sec-Fetch-Mode: navigate
// Sec-Fetch-Site: none
// Sec-Fetch-User: ?1


#endif