# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/04/08 15:01:32 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = #-Wall -Wextra -Werror
NAME = minishell
HEADER = headers

SRC_DIR = srcs
OBJ_DIR = obj

SRCS = main.c\
		parsing/ft_split_quote.c\
		builtins.c\
		arg_struct/ft_argadd_front.c\
		arg_struct/ft_argadd_front.c\
		arg_struct/ft_argclear.c\
		arg_struct/ft_argdelone.c\
		arg_struct/ft_arglast.c\
		arg_struct/ft_argnew.c\
		arg_struct/ft_argsize.c


LIBFT = libft/libft.a

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) -I $(HEADER) -lreadline
	 @echo "$(NAME) compilation successful !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $(notdir $<)..."
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(LIBFT):
	@make -s -C libft

clean:
	@echo "Removing object..."
	@rm -rf $(OBJ_DIR)
	@echo "Removing libft..."
	@make fclean -s -C libft

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
