/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleRequest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:55:55 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/08 09:28:18 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

/* ----------------------------- protos ----------------------------- */

static char	*extractFromStr(int begin, int end, char const *str);

/* ================================================================== */

const char	*getFileExt(char const *fileName) {

	int			pos;

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

const char	*getMIME(char const *fileExt) {

	if (!_comp(fileExt, "html"))
		return "text/html";
	else if (!_comp(fileExt, "css"))
		return "text/css";
	else if (!_comp(fileExt, "javascript"))
		return "text/javascript";

	if (!_comp(fileExt, "gif"))
		return "image/gif";
	else if (!_comp(fileExt, "jpeg") || !_comp(fileExt, "jpg"))
		return "image/jpeg";
	else if (!_comp(fileExt, "png"))
		return "image/png";
	else if (!_comp(fileExt, "gif"))
		return "image/gif";
	else if (!_comp(fileExt, "webp"))
		return "image/webp";

	return "application/octet-stream";
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

// "http%3A%2F%2F" -> "http://"
//  "a+t+%26+t" -> "a t & t"

char	*urlDecode(char const *encoded) {

	int		sz = 0;
	int		len_encoded = _strlen(encoded);
	char	decoded[len_encoded];

	for (int i = 0; i < len_encoded;) {

		switch (encoded[i]) {

			case '+':
				decoded[sz++] = ' ';
				i++;
				break ;
			case '%':
				if (i + 2 < len_encoded) {
					char	toConvert[3] = {0};

					toConvert[0] = encoded[i + 1];
					toConvert[1] = encoded[i + 2];
					decoded[sz++] = _atoi_base(toConvert, "0123456789ABCDEF");
					i += 2;
					break ;
				}
				[[fallthrough]];
			default:
				decoded[sz++] = encoded[i++];
				break ;
		}
	}
	decoded[sz] = 0;
	return _strdup(decoded);
}

const char	*putPrefix(char const *str) {

	int			i;
	char	*ret = _calloc(sizeof(char), _strlen(str) + _strlen(PREFIX) + 1);
	if (!ret)
		goto eputPre;

	for (i = 0; PREFIX[i]; i++)
		ret[i] = PREFIX[i];
	for (int j = 0; str && str[j]; j++)
		ret[i++] = str[j];
	ret[i] = 0;

eputPre:
	free((char *)str);
	return ret;
}