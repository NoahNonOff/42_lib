/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleRequest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:55:55 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/06 13:18:28 by nbeaufil         ###   ########.fr       */
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

// "GET /home.html HTTP/1.1"
// should return "/home.html"

// pattern "GET ~ HTTP/1.1"

char	*getFromPattern(char const *pattern, char const *str) {

	// char	*ret;
	int		begPat;
	int		endPat;

	if (!str || !pattern)
		return NULL;
	for (int i = 0; str[i]; i++) {
		if (str[i] == pattern[0]) {

			for (begPat = 0; (i + begPat < _strlen(str) && pattern[begPat]) &&
				pattern[begPat] != '~' && pattern[begPat] == str[i + begPat]; begPat++) {}

			if ((i + begPat < _strlen(str) && pattern[begPat]) && pattern[begPat] == '~') {

				printf("begin matched\n");
			}
		}
	}
	return NULL;
}