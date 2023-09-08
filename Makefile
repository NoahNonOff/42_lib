# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 14:21:46 by nbeaufil          #+#    #+#              #
#    Updated: 2023/09/08 09:50:57 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	webServer.c		\
		handleRequest.c

OBJ = $(SRC:.c=.o)
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3
LIBS = ./_lib/libC-utils.a -lpthread

NAME = webserver

all: $(NAME)

$(NAME): $(OBJ)
	make all -C _lib
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

clean:
	make clean -C _lib
	$(RM) $(OBJ)

fclean: clean
	make fclean -C _lib
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re

.SILENT: