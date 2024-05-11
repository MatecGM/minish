# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbico <mbico@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/05/11 17:16:24 by mbico            ###   ########.fr        #
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
		parsing/ft_tokenizer.c\
		parsing/parsing.c\
		parsing/ft_quote_first_arg.c\
		divpipe/ft_pipeadd_back.c\
		divpipe/ft_pipenew.c\
		redirect/ft_redadd_back.c\
		redirect/ft_rednew.c\
		env_struct/ft_envadd_front.c\
		env_struct/ft_envadd_front.c\
		env_struct/ft_envclear.c\
		env_struct/ft_envdelone.c\
		env_struct/ft_envlast.c\
		env_struct/ft_envnew.c\
		env_struct/ft_envsize.c\
		env.c\
		export.c\
		builtins.c\
		builtins_2.c\
		signal_handler.c\

LIBFT = libft/libft.a

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) -I $(HEADER) -lreadline
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
