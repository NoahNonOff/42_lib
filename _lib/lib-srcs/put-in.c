/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:36:27 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/08 11:06:52 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lib.h"

void	_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
		write(fd, &str[i++], 1);
}

void	_putnbr(int n, int fd)
{
	if (n == INT_MIN)
	{
		_putstr("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		_putchar('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		_putnbr(n / 10, fd);
		_putchar(n % 10 + '0', fd);
	}
	else
		_putchar(n + '0', fd);
}

char	*addtostr(char const *str, char const *new_str) {

	int		i;
	char	*ret = _calloc(sizeof(char), _strlen(str) + _strlen(new_str) + 1);
	if (!ret)
		goto eAddStr;

	for (i = 0; str && str[i]; i++)
		ret[i] = str[i];
	for (int j = 0; new_str && new_str[j]; j++)
		ret[i++] = new_str[j];

	ret[i] = 0;

eAddStr:
	free((char *)str);
	return ret;
}

char	*_putinstr(char	const *str, ...) {

	va_list	ptr;
	va_start(ptr, str);

	char	*ret = _calloc(1, 1);
	char	c[2] = {0};

	for (int i = 0; str && str[i]; i++) {
		if (str[i] == '%') {
			char const *sub_str = va_arg(ptr, char const *);
			ret = addtostr(ret, sub_str);
			i++;
			continue ;
		}
		c[0] = str[i];
		ret = addtostr(ret, c);
	}

	va_end(ptr);
	return ret;
}