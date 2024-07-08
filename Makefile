# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbico <mbico@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/07/08 19:24:39 by mbico            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
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
		signal_handler_2.c\
		executer_2.c\
		parsing/parsing_utils.c\
		parsing/ft_split_quote_utils.c\
		redirect/redirection_utils.c\
		parsing/typage.c\
		parsing/ft_add_lostcmd.c\

LIBFT = libft/libft.a

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) -I $(HEADER) -lreadline
	@echo "$(GREEN)$(NAME) compilation successful !$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(LIBFT):
	@echo "$(PURPLE)Compiling LIBFT...$(NC)"
	@make -s -C libft

clean:
	@echo "$(RED)Removing object...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Removing libft...$(NC)"
	@make fclean -s -C libft

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
