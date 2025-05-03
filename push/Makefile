# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 20:53:05 by hkhairi           #+#    #+#              #
#    Updated: 2025/05/02 16:25:05 by hkhairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

HEADER_FILE = philosophers.h

SRC = init_data.c  init_philo.c  main.c  \
		philo_life.c philo_utils.c  validation.c

OBJ_SRC = $(SRC:.c=.o)

NAME = a.out

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
