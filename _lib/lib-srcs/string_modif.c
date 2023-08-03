/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:11:06 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/08/03 10:12:07 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lib.h"

static int	len_sep_string(const char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			counter++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (counter + 1);
}

static char	*get_next_word(int *index, const char *str, char c)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (str[*index] == c)
		(*index)++;
	while (str[*index + len] != c && str[*index + len])
		len++;
	ret = _calloc((len + 1), sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
		ret[i++] = str[(*index)++];
	ret[i] = 0;
	return (ret);
}

char	**_split(char const *s, char c)
{
	int		i;
	int		j;
	int		ac;
	char	**ret;

	i = 0;
	j = 0;
	ac = len_sep_string(s, c);
	ret = _calloc(ac, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < ac - 1)
	{
		ret[i] = get_next_word(&j, s, c);
		if (!ret[i++])
			return (_ftab(ret));
	}
	ret[i] = NULL;
	return (ret);
}

char	*_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*ret;

	i = -1;
	len1 = _strlen(s1);
	len2 = _strlen(s2);
	ret = _calloc(sizeof(char), (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	while (++i < len1)
		ret[i] = s1[i];
	i = -1;
	while (++i < len2)
		ret[len1 + i] = s2[i];
	ret[len1 + len2] = 0;
	return (ret);
}

void	_bzero(void *addr, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = addr;
	while (ptr && i < n)
		ptr[i++] = 0;
}