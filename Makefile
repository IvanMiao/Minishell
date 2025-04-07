# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 01:27:01 by ymiao             #+#    #+#              #
#    Updated: 2025/04/07 15:12:30 by ymiao            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LIBS	=	-lreadline

SRC_TEST	=	test_main.c
SRC_MAIN	=	main.c
SRCS		=	$(addprefix src/, builtins/cd.c builtins/env.c \
				builtins/export.c builtins/unset.c \
				builtins/echo.c builtins/pwd.c \
				builtins/exit.c \
				ctrl/signals.c \
				env/env_list.c env/env_free.c \
				env/get_env.c env/explain_dollar.c \
				parsing/check_command.c parsing/quotes.c \
				parsing/token_list.c parsing/tokenization.c \
				exec/cmd.c exec/cmd_utils.c \
				exec/cmd_utils_part2.c \
				utils/libft_part1.c utils/libft_part2.c \
				utils/ft_split.c \
				utils/ft_fprintf.c)

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(SRC_MAIN) -o $(NAME) $(LIBS)
	@echo "Compilation complete."

test:
	@$(CC) $(CFLAGS) $(SRCS) $(SRC_TEST) -o test_minishell $(LIBS)
	@echo "Test programme done."

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME) test_minishell
	@echo "Fully cleaned up."

re: fclean all
	@echo "Recompiled."
	
.PHONY: all clean fclean re
