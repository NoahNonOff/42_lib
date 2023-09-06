/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleRequest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:55:55 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/06 16:37:43 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

/* ----------------------------- protos ----------------------------- */

static char	*extractFromStr(int begin, int end, char const *str);

/* ================================================================== */

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

static char	*extractFromStr(int begin, int end, char const *str) {

	char	*ret;
	int		len = end - begin;
	if (len <= 0)
		return NULL;
	ret = _calloc(sizeof(char), len + 1);
	if (!ret)
		return NULL;
	for (int i = 0; i < len; i++)
		ret[i] = str[begin + i];
	ret[len] = 0;
	return ret;
}

// "GET /home.html HTTP/1.1"
// should return "/home.html"

// pattern "GET ~ HTTP/1.1"

char	*getfp(char const *pattern, char const *str) {

	int		begPat;
	int		lenPat;
	int		endPat;

	if (!str || !pattern)
		return NULL;

	for (int i = 0; str[i]; i++) {
		if (str[i] == pattern[0]) {

			for (begPat = 0; (i + begPat < _strlen(str) && pattern[begPat]) &&
				pattern[begPat] != '~' && pattern[begPat] == str[i + begPat]; begPat++) {}

			if ((i + begPat < _strlen(str) && pattern[begPat]) && pattern[begPat] == '~') {

				for (lenPat = 0; (str[i + begPat + lenPat] && pattern[begPat + 1]); lenPat++) {

					if (pattern[begPat + 1] == str[i + begPat + lenPat]) {

						for (endPat = 0; (str[i + begPat + lenPat + endPat] && pattern[begPat + 1 + endPat]) &&
							pattern[begPat + 1 + endPat] == str[i + begPat + lenPat + endPat]; endPat++) {}

						if (!pattern[begPat + 1 + endPat])
							return extractFromStr(begPat + i, begPat + i + lenPat, str);
					}
				}
			}
		}
	}
	return NULL;
}