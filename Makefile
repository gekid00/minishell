# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gekido <gekido@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 00:13:59 by gekido            #+#    #+#              #
#    Updated: 2025/04/17 17:07:55 by gekido           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -g3 -Wall -Wextra -Werror 
INCLUDES = -I./includes
LIBFT_DIR = ./libft

SRC_DIR = srcs
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXECUTOR_DIR = $(SRC_DIR)/executor
BUILTINS_DIR = $(SRC_DIR)/builtins
UTILS_DIR = $(SRC_DIR)/utils
EXPAND_DIR = $(SRC_DIR)/expand

SRCS	= $(SRC_DIR)/main.c \
		$(LEXER_DIR)/lexer.c \
		$(LEXER_DIR)/lexer_words.c \
		$(LEXER_DIR)/lexer_operators.c \
		$(PARSER_DIR)/parser_core.c \
		$(PARSER_DIR)/parser_utils.c \
		$(PARSER_DIR)/parser_ast.c \
		$(EXECUTOR_DIR)/executor_command.c \
		$(EXECUTOR_DIR)/executor_external.c \
		$(EXECUTOR_DIR)/executor_path.c \
		$(EXECUTOR_DIR)/executor_redirections.c \
		$(EXECUTOR_DIR)/executor_pipe.c \
		$(BUILTINS_DIR)/builtins_basic.c \
		$(BUILTINS_DIR)/builtins_env.c \
		$(BUILTINS_DIR)/builtins_utils.c \
		$(UTILS_DIR)/env_utils.c \
		$(UTILS_DIR)/signals.c \
		$(UTILS_DIR)/utils.c \
		$(UTILS_DIR)/utils2.c \
		$(EXPAND_DIR)/expand.c \
		$(EXPAND_DIR)/expand_utils.c \

OBJS = $(SRCS:.c=.o)

READLINE_LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	clang $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $(NAME)

%.o: %.c
	clang $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

dev: re
	make clean
	valgrind --suppressions=$(PWD)/readline.supp -s --track-fds=yes --trace-children=yes --show-leak-kinds=all --leak-check=full -q ./minishell

.PHONY: all clean fclean re