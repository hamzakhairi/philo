# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/23 22:21:13 by hkhairi           #+#    #+#              #
#    Updated: 2025/06/05 09:40:25 by hkhairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAG =  -Wall -Wextra -Werror

SRC = ft_atio_bonus.c                 ft_itoa_bonus.c                 ft_strjoin_bonus.c              ft_validation_argumnet_bonus.c  \
	fail_init_data_bonus.c          ft_init_data_bonus.c            ft_philo_life_bonus.c           ft_utils_bonus.c                ft_validation_data_bonus.c      stop_program_bonus.c \
	fail_init_philo_bonus.c         ft_init_philo_bonus.c           ft_strdup_bonus.c               ft_utils_tow_bonus.c            main_bonus.c \

OBJ = $(SRC:.c=.o)
HEADER_FILE = philosopher_bonus.h
NAME = philo_bonus

all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) -o $(NAME) $(OBJ)

%.o : %.c $(HEADER_FILE)
	$(CC) $(CFLAG) -c $< -o $@

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean 