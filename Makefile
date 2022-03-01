# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 16:38:32 by tsiguenz          #+#    #+#              #
#    Updated: 2022/03/01 10:20:18 by tsiguenz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Paths

SRC_PATH = src/
OBJ_PATH = obj/

# Names

SRC_NAME = main.c parsing.c init_philo.c routine.c get_time.c check_death.c

OBJ_NAME = $(SRC_NAME:.c=.o)

# Files

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

# Flags

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INC = -Iinclude -lpthread

# Rules

$(NAME): $(OBJ)
	@echo "Build $(NAME)"
	$(CC) $(CFLAGS) $(OBJ) $(INC) $(LIBFT) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

all: $(NAME)

clean:
	@echo "Delete $(OBJ_PATH)"
	@rm -rf $(OBJ_PATH)

fclean:	clean
	@echo "Delete $(NAME)"
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
