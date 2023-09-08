/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:32:19 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/08 11:02:21 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lib.h"

void	*_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	void			*ret;
	unsigned char	*ptr;

	i = 0;
	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ret = malloc(size * nmemb);
	if (!ret)
		return (NULL);
	ptr = ret;
	while (i < size * nmemb)
		ptr[i++] = 0;
	return (ret);
}

char	*_strdup(char *str)
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	if (!str)
		return (NULL);
	len = _strlen(str);
	ret = _calloc(sizeof(char), (len + 1));
	if (!ret)
		return (NULL);
	while (str && str[++i])
		ret[i] = str[i];
	ret[len] = 0;
	return (ret);
}

void	*_ftab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**_tdpush(char **tab, char *to_add)
{
	int		len;
	char	**ret;

	len = 0;
	while (tab && tab[len])
		len++;
	ret = _calloc(sizeof(char *), (len + 2));
	if (!ret)
		return (NULL);
	len = 0;
	while (tab && tab[len])
	{
		ret[len] = tab[len];
		if (!ret[len++])
			return (_ftab(ret));
	}
	ret[len] = _strdup(to_add);
	if (!ret[len++])
		return (_ftab(ret));
	ret[len] = NULL;
	if (tab)
		free(tab);
	return (ret);
}

void	m_free(int n, ...)
{
	va_list	ptr;
	va_start(ptr, n);

	for (int i = 0; i < n; i++)
		free(va_arg(ptr, void *));

	va_end(ptr);
}
