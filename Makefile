# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 16:15:33 by mhnatovs          #+#    #+#              #
#    Updated: 2025/12/25 18:23:26 by mhnatovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a

CC				= cc
FLAGS			= -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)
LIBS			= -lreadline

OBJ_DIR			= obj

SRC				= main.c find_cmd.c expand_args_and_execute.c split.c

OBJ				= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
		$(CC) $(FLAGS) $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
		$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
		make -C $(LIBFT_DIR) clean
		rm -f $(OBJ)

fclean:	clean
		make -C $(LIBFT_DIR) fclean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re