# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 01:27:01 by ymiao             #+#    #+#              #
#    Updated: 2025/04/30 17:07:33 by cgerner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LIBS	=	-lreadline

SRC_MAIN	=	main.c
SRCS		=	$(addprefix src/, builtins/cd.c builtins/env.c \
				builtins/export.c builtins/unset.c \
				builtins/echo.c builtins/pwd.c \
				builtins/exit.c \
				ctrl/signals.c \
				env/env_list.c env/env_free.c \
				env/get_env.c \
				parsing/check_syntaxe.c parsing/check_quotes.c \
				parsing/state_machine.c \
				parsing/dollar_expansion.c \
				parsing/token_list.c parsing/tokenization.c \
				exec/cmd.c exec/cmd_utils.c \
				exec/cmd_utils_part2.c \
				exec/exec.c exec/exec_utils.c \
				exec/exec_utils_part2.c \
				exec/here_doc.c exec/here_doc2.c \
				exec/here_doc_utils.c \
				exec/pipex.c \
				exec/exec_builtin.c \
				utils/libft_part1.c utils/libft_part2.c \
				utils/libft_part3.c \
				utils/ft_split.c utils/ft_itoa.c \
				utils/ft_fprintf.c utils/mem_manager.c)

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(SRC_MAIN)
	@$(CC) $(CFLAGS) $(SRCS) $(SRC_MAIN) -o $(NAME) $(LIBS)
	@echo "Compilation complete."

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=readline.supp ./$(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME) test_minishell create_supp
	@echo "Fully cleaned up."

re: fclean all
	@echo "Recompiled."
	
.PHONY: all clean fclean re val
