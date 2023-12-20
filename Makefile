# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 17:07:53 by ekuchel           #+#    #+#              #
#    Updated: 2023/10/04 12:23:13 by ekuchel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c \
	src/execution/heredoc.c \
	src/execution/redirections.c \
	src/execution/execute_utils.c \
	src/execution/execute_utils2.c \
	src/execution/execute_utils3.c \
	src/execution/execute.c \
	src/execution/exit.c \
	src/execution/libft_utils.c \
	src/execution/libft_utils1.c \
	src/utils/clear.c \
	src/utils/environ.c \
	src/utils/num_utils.c \
	src/utils/str_utils.c \
	src/utils/print.c \
	src/parsing/commands.c \
	src/parsing/input.c \
	src/parsing/parse_utils.c \
	src/parsing/parse.c \
	src/builtins/cd.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/pwd.c \
	src/builtins/unset.c \
	src/signals.c

HDRS_DIR	= ./includes/

HDRS	=	-I$(HDRS_DIR) -I/usr/local/Cellar/readline/8.1.2/include/
LIBS	=	-L /usr/local/Cellar/readline/8.1.2/lib/

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
CC = gcc

all: $(NAME)
	@echo "Minishell successfully compiled!";

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(LIBS) $(HDRS) -o $(NAME) $(SRC) -lreadline

fclean:
	$(RM) -f $(NAME)
	@echo "Cleaning minishell... ";

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all re clean fclean sclean
