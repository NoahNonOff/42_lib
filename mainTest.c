/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:02:58 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/06 16:12:31 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServer.h"

int	main(int ac, char *av[])
{
	char	*test;

	if (ac != 2)
		return 1;
	test = getfp("GET ~ HTTP/1.1", av[1]);
	if (!test) {
		printf("NULL\n");
	} else {
		printf("-> %s\n", test);
		free(test);
	}
	return 0;
}