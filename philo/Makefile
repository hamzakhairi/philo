# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 20:53:05 by hkhairi           #+#    #+#              #
#    Updated: 2025/06/05 11:27:49 by hkhairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

HEADER_FILE = philosophers.h

SRC = init_data.c  init_philo.c  main.c  \
		philo_life.c philo_utils.c  validation.c philo_utils_tow.c

OBJ_SRC = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME) : $(OBJ_SRC)
	$(CC) $(CFLAGS) -pthread $(OBJ_SRC) -o $(NAME) 

%.o : %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ_SRC)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean 