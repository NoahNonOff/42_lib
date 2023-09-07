/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:29:37 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/09/07 15:55:39 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIB_H
# define _LIB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stdarg.h>

typedef enum { false, true }	BOOL;

# ifndef bool
#  define bool BOOL
# endif

/* ------------------------- string ------------------------- */
int		_strlen(const char *str);
int		_comp(const char *s1, const char *s2);
int		_compn(const char *s1, const char *s2, int n);

char	**_split(char const *s, char c);
char	*_strjoin(char const *s1, char const *s2);
void	_bzero(void *addr, size_t n);
void	_strncpy(char *dest, char const *src, int sz);

/* ----------------------- allocation ----------------------- */
void	*_calloc(size_t nmemb, size_t size);
char	*_strdup(char *str);
void	*_ftab(char **tab);
char	**_tdpush(char **tab, char *to_add);
void	m_free(int n, ...);

/* ------------------------- put-in ------------------------- */
void		_putchar(char c, int fd);
void		_putstr(char *str, int fd);
void		_putnbr(int n, int fd);
char		*addNchar(char const *str, char const *new_str, int n);
char		*addtostr(char const *str, char const *new_str);
const char	*_putinstr(char	const *str, ...);

/* ----------------------- conversion ----------------------- */
int		_atoi_base(char const *to_convert, char const *base);

#endif