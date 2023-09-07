/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:17:28 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/07 09:55:23 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lib.h"

static bool	verif_base(char const *base) {

	for (int i = 0; base && base[i]; i++) {
		for (int j = i + 1; base[j]; j++) {
			if (base[i] == base[j] || base[i] == ' ' || base[j] == ' ')
				return false;
		}
	}
	return true;
}

static int	i_in_base(char c, char const *base) {

	for (int i = 0; base && base[i]; i++)
		if (c == base[i])
			return i;
	return -1;
}

int	_atoi_base(char const *to_convert, char const *base) {

	int	ret = 0, sign = 1, i;

	if (!verif_base(base) || !to_convert)
		return 0;
	for (i = 0; to_convert[i] && to_convert[i] == '-'; i++) {}
	for (; to_convert[i] && (to_convert[i] == '+' || to_convert[i] == '-'); i++) {
		if (to_convert[i] == '-')
			sign *= -1;
	}
	for (; to_convert[i]; i++) {
		int	index = i_in_base(to_convert[i], base);
		if (index == -1)
			break ;
		ret *= _strlen(base);
		ret += index;
	}
	return ret;
}