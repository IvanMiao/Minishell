# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 01:27:01 by ymiao             #+#    #+#              #
#    Updated: 2025/04/02 16:15:31 by ymiao            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LIBS	=	-lreadline

SRCS	=	test_main.c \
			builtins/cd.c builtins/env.c \
			builtins/export.c builtins/unset.c \
			builtins/echo.c builtins/pwd.c \
			builtins/exit.c \
			ctrl/signals.c \
			env/env_list.c env/env_free.c \
			parsing/parsing.c parsing/quotes.c \
			parsing/token_list.c parsing/tokenization.c \
			utils/libft_part1.c utils/libft_part2.c \
			utils/ft_fprintf.c

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBS)
	@echo "Compilation complete."

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "Fully cleaned up."

re: fclean all
	@echo "Recompiled."
	
.PHONY: all clean fclean re