# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 15:02:44 by nbeaufil          #+#    #+#              #
#    Updated: 2023/09/01 14:18:41 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS1	=	server.c

NAME1	=	server
OBJS1	=	${SRCS1:.c=.o}

SRCS2	=	client.c

NAME2	=	client
OBJS2	=	${SRCS2:.c=.o}

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
LIBS	=	../_lib/libC-utils.a
INCLUDE	=	-I .
DEBUG	=

.c.o	:
	${CC} ${FLAGS} ${INCLUDE} ${DEBUG} -c $< -o ${<:.c=.o}

all	:	${NAME1} ${NAME2}

$(NAME1)	:	${OBJS1}
	make all -C ../_lib
	${CC} ${FLAGS} ${OBJS1} ${LIBS} ${DEBUG} -o ${NAME1}

$(NAME2)	:	${OBJS2}
	make all -C ../_lib
	${CC} ${FLAGS} ${OBJS2} ${LIBS} ${DEBUG} -o ${NAME2}

clean	:
	make clean -C ../_lib
	rm -f ${OBJS1}
	rm -f ${OBJS2}

fclean	:	clean
	make fclean -C ../_lib
	rm -f ${NAME1}
	rm -f ${NAME2}

re	:	fclean all

.PHONY: all clean fclean re

.SILENT: