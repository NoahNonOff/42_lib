/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleRequest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:55:55 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/03 18:38:14 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

const char	*getFileExt(char const *fileName) {

	int			pos;
	const char	*dot;

	for (pos = _strlen(fileName) - 1; pos > -1; pos--) {
		if (fileName[pos] == '.')
			break ;
	}
	if (pos == (_strlen(fileName) - 1) || !pos)
		return NULL;
	return &fileName[pos + 1];
}