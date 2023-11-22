# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoirot <vpoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 11:30:00 by vpoirot           #+#    #+#              #
#    Updated: 2023/11/22 09:35:24 by vpoirot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := cub3d
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -fsanitize=address -g #./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRCS        :=      src/main.c\
						src/ft_printf.c\
						src/parsing.c\
						src/get_next_line/get_next_line.c\
						src/get_next_line/get_next_line_utils.c\
						src/utils.c\
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	@${CC} ${FLAGS} -o ${NAME} ${OBJS}
	@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
	@ ${RM} *.o */*.o */*/*.o
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
	@ ${RM} ${NAME}
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


