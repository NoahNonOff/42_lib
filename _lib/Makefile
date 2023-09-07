# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 15:02:44 by nbeaufil          #+#    #+#              #
#    Updated: 2023/09/07 09:18:14 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	lib-srcs/alloc.c		\
			lib-srcs/put-in.c		\
			lib-srcs/string_cmp.c	\
			lib-srcs/string_modif.c	\
			lib-srcs/conversion.c

CC		=	gcc
OBJS	=	${SRCS:.c=.o}
NAME	=	libC-utils.a
FLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I .
DEBUG	=

.c.o	:
	${CC} ${FLAGS} ${INCLUDE} ${DEBUG} -c $< -o ${<:.c=.o}

all	:	${NAME}

$(NAME)	:	${OBJS}
	ar -rcs ${NAME} ${OBJS}
	ranlib ${NAME}

clean	:
	rm -f ${OBJS}
	rm -f test.o

fclean	:	clean
	rm -f ${NAME}
	rm -f test

re	:	fclean all

.PHONY: all clean fclean re

.SILENT: