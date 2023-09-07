# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 14:21:46 by nbeaufil          #+#    #+#              #
#    Updated: 2023/09/07 14:43:24 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	webServer.c		\
		handleRequest.c

OBJ = $(SRC:.c=.o)
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3
LIBS = ./_lib/libC-utils.a -lpthread

NAME = webServer

all: $(NAME)

$(NAME): $(OBJ)
	make all -C _lib
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

test:
	make all -C _lib
	$(CC) -g3 handleRequest.c mainTest.c $(LIBS) -o test

clean:
	make clean -C _lib
	$(RM) $(OBJ)

fclean: clean
	make fclean -C _lib
	$(RM) $(NAME)
	$(RM) test

re: fclean $(NAME)

.PHONY: all clean fclean re

.SILENT: