/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:24 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/03 18:10:51 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lib.h"

int	_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	_comp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while ((t1[i] && t2[i]) && (t1[i] == t2[i]))
		i++;
	return (t1[i] - t2[i]);
}

int	_compn(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while ((t1[i] && t2[i]) && (t1[i] == t2[i]) && (n < 0 || i < n))
		i++;
	return (t1[i] - t2[i]);
}
