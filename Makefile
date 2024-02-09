# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 11:30:00 by vpoirot           #+#    #+#              #
#    Updated: 2024/02/09 13:43:24 by vpoirot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
LIBFT		= TheLibft/libft.a
FLAGS	=	-Wall -Wextra -Werror ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

_RED	=	\033[01;31m
_GREEN	=	\033[01;32m
_CYAN	=	\033[01;36m
_YELLOW	=	\033[01;33m
_BOLD	=	\033[1m
_END	=	\033[00m

SRCS	=	src/main.c\
			src/parsing.c\
			src/tab_utils.c\
			src/parsing_utils.c\
			src/setup_mlx.c\
			src/key_handler.c\
			src/raycast.c\
			src/graphics.c\
			src/colors.c\
			src/hooks.c\
			src/ft_dda.c\
			src/minimap.c\

OBJS	=	${SRCS:.c=.o}

all: $(LIBFT) $(NAME)
	@echo ""
	@echo "$(_CYAN)$(_BOLD)[Makefile]$(_END) $(_BOLD) $(_GREEN)Project $(NAME) ready$(_END)"

$(LIBFT):
	@cd TheLibft && $(MAKE) --no-print-directory

%.o: %.c
	@gcc -Wall -Werror -Wextra -c $< -o $@

$(NAME): $(OBJS)
	@gcc $(OBJS) $(FLAGS) $(LIBFT) -o $(NAME)
	@echo "$(_CYAN)$(_BOLD)[Makefile]$(_END) $(_BOLD)$(NAME) $(_GREEN)created$(_END)"

clean:
	@rm -f $(OBJS)
	@cd TheLibft && $(MAKE) --no-print-directory clean
	@echo "$(_CYAN)$(_BOLD)[Makefile]$(_END) $(_BOLD)$(NAME) is now $(_YELLOW)clean$(_END)"

fclean: clean
	@rm -f $(NAME)
	@rm -f TheLibft/libft.a
	@echo "$(_CYAN)$(_BOLD)[Makefile]$(_END) $(_BOLD)libft.a $(_RED)deleted$(_END)"
	@echo "$(_CYAN)$(_BOLD)[Makefile]$(_END) $(_BOLD)$(NAME) $(_RED)deleted$(_END)"

re: clean all

.PHONY: all, clean, fclean, re