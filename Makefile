# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/06/13 17:40:54 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g #-Wall -Wextra -Werror
NAME = minishell
HEADER = headers

SRC_DIR = srcs
OBJ_DIR = obj

SRCS = main.c\
		parsing/ft_split_quote.c\
		parsing/ft_tokenizer.c\
		parsing/parsing.c\
		parsing/ft_quote_first_arg.c\
		parsing/env_var_extend.c\
		divpipe/ft_pipeadd_back.c\
		divpipe/ft_pipenew.c\
		redirect/ft_redadd_back.c\
		redirect/ft_rednew.c\
		redirect/redirection.c\
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
		get_paths.c\
		executer.c\
		env_2.c\
		heredoc.c\
		divpipe/ft_freepipe.c\
		redirect/ft_freered.c\
		free_minish.c\
		update_var.c\
		cd_utils.c\
		signal_handler_2.c

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
