/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:23:12 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/01 16:19:18 by nbeaufil         ###   ########.fr       */
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
# include "./_lib/_lib.h"

# define PORT 8080

#endif