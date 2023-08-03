/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:36:27 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/08/02 17:38:32 by nbeaufil         ###   ########.fr       */
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