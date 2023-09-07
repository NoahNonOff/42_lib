/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:02:58 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/07 13:31:14 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

int	main(int ac, char *av[])
{
	if (ac != 4)
		return 1;

	const char	*test = _putinstr(av[1], av[2], av[3]);
	printf("->%s\n", test);

	free((char *)test);
	return 0;
}